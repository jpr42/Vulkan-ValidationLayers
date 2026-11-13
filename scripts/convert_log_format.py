#!/usr/bin/env python3
# Copyright (c) 2026 LunarG, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Rewrites printf-style Log* calls (LogError, LogWarning, ...) to std::format-style format strings.

    python scripts/convert_log_format.py layers tests/vvl_core            # convert in place
    python scripts/convert_log_format.py layers --dry-run                 # only list what cannot be converted

Only the format string and the arguments change; the printed text stays the same, except that %p arguments are cast to
const void* and print as std::format prints pointers. Inside the arguments of converted calls,
FormatHandle(x).c_str() becomes Handle(x), loc.Fields().c_str() becomes loc and string_Vk<Name>(v).c_str() becomes
vvl::Flags::<Name>(v) when a generated vvl::Flags helper exists. Calls that cannot be converted are listed with file and
line and left untouched; the exit code is non-zero while any remain. A second run changes nothing.

Generated code (layers/vulkan/generated/) is never edited: the script fails if it finds a printf-style call there.
"""

import argparse
import os
import re
import sys
from dataclasses import dataclass

CALL_RE = re.compile(r'\bLog(?:Error|Warning|InternalError|UndefinedValue|PerformanceWarning|Info|Verbose)\s*\(')
IDENT_RE = re.compile(r'[A-Za-z_]\w*')
PRI_RE = re.compile(r'PRI([diouxX])(?:8|16|32|64|PTR|MAX|LEAST\d+|FAST\d+)$')
# A std::format replacement field, after "{{" and "}}" are removed: {}, {0}, {:x}, {:>{}}
FIELD_RE = re.compile(r'\{\d*(?::[^{}]*(?:\{\d*\}[^{}]*)*)?\}')
# A printf conversion as VVL writes them (no space flag), so a converted "{}% done" is not mistaken for one
STRICT_PRINTF_RE = re.compile(r'%[-+#0]*\d*(?:\.\d+)?(?:hh|h|ll|l|z|j|t)?[diuxXoscfFeEgGp]|%"')
CALL_KEYWORDS = {'return', 'co_return', 'else', 'do', 'throw'}
GENERATED_DIR = os.path.join('layers', 'vulkan', 'generated')
SOURCE_EXTENSIONS = ('.cpp', '.h', '.hpp', '.cc')


@dataclass
class Problem:
    line: int
    reason: str


class Unconvertible(Exception):
    pass


def is_ident_char(c):
    return c.isalnum() or c == '_'


def mask_source(text):
    """Returns text of the same length where comments are spaces and literal contents are 'x' (quotes kept), so calls,
    parentheses and commas can be found without looking inside comments or literals."""
    out = list(text)
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if text.startswith('//', i):
            end = text.find('\n', i)
            end = n if end < 0 else end
            out[i:end] = ' ' * (end - i)
            i = end
        elif text.startswith('/*', i):
            end = text.find('*/', i + 2)
            end = n if end < 0 else end + 2
            out[i:end] = [ch if ch in '\r\n' else ' ' for ch in text[i:end]]
            i = end
        elif c == '"' and i > 0 and text[i - 1] == 'R' and (i < 2 or not is_ident_char(text[i - 2]) or text[i - 2] in 'uUL8'):
            open_paren = text.find('(', i)
            delimiter = text[i + 1:open_paren]
            end = text.find(f'){delimiter}"', open_paren)
            end = n if end < 0 else end + len(delimiter) + 2
            out[i + 1:end - 1] = [ch if ch in '\r\n' else 'x' for ch in text[i + 1:end - 1]]
            i = end
        elif c == '"' or (c == "'" and not (i > 0 and text[i - 1].isalnum() and i + 1 < n and text[i + 1].isalnum())):
            j = i + 1
            while j < n and text[j] != c and text[j] != '\n':
                j += 2 if text[j] == '\\' else 1
            out[i + 1:j] = 'x' * (j - i - 1)
            i = j + 1
        else:
            i += 1
    return ''.join(out)


def matching_paren(masked, open_index):
    depth = 0
    for i in range(open_index, len(masked)):
        if masked[i] in '([{':
            depth += 1
        elif masked[i] in ')]}':
            depth -= 1
            if depth == 0:
                return i
    return -1


def split_arguments(masked, open_index, close_index):
    """Spans (start, end) of the top-level arguments between the parentheses"""
    spans, depth, start = [], 0, open_index + 1
    for i in range(open_index + 1, close_index):
        if masked[i] in '([{':
            depth += 1
        elif masked[i] in ')]}':
            depth -= 1
        elif masked[i] == ',' and depth == 0:
            spans.append((start, i))
            start = i + 1
    spans.append((start, close_index))
    return spans


def is_call(masked, name_start):
    """False for declarations and definitions (bool LogError(...), Logger::LogInfo(...), &Logger::LogError)"""
    i = name_start - 1
    while i >= 0 and masked[i].isspace():
        i -= 1
    if i < 0:
        return True
    if masked[i] == ':' and i > 0 and masked[i - 1] == ':':
        return False
    if re.search(r'DECORATE_PRINTF\s*\([^()]*\)\s*$', masked[:name_start]):
        return False
    if is_ident_char(masked[i]):
        j = i
        while j >= 0 and is_ident_char(masked[j]):
            j -= 1
        return masked[j + 1:i + 1] in CALL_KEYWORDS
    return True


# ---------------------------------------------------------------- format strings

@dataclass
class Token:
    kind: str  # 'literal' (content excludes the quotes), 'macro', 'other'
    start: int  # span in the file text, quotes included for literals
    end: int
    text: str


def tokenize_format(text, masked, start, end):
    """Tokens of a format argument, or a reason it is not a literal format"""
    tokens = []
    i = start
    while i < end:
        c = masked[i]
        if c.isspace():
            i += 1
        elif c == '"':
            close = masked.index('"', i + 1)
            tokens.append(Token('literal', i, close + 1, text[i + 1:close]))
            i = close + 1
        elif is_ident_char(c) and not c.isdigit():
            m = IDENT_RE.match(masked, i)
            name = m.group(0)
            if m.end() < end and masked[m.end()] == '"':
                raise Unconvertible('raw or prefixed string literal: convert by hand' if name.endswith('R') else
                                    'prefixed string literal: convert by hand')
            tokens.append(Token('macro' if PRI_RE.match(name) else 'other', i, m.end(), name))
            i = m.end()
        else:
            tokens.append(Token('other', i, i + 1, c))
            i += 1
    return tokens


@dataclass
class Unit:
    token: int  # index of its literal or macro token
    text: str  # one character, or one escape sequence
    out: str  # its replacement


def literal_units(tokens):
    units = []
    for index, token in enumerate(tokens):
        if token.kind == 'macro':
            units.append(Unit(index, token.text, None))
            continue
        content, i = token.text, 0
        while i < len(content):
            length = 2 if content[i] == '\\' else 1
            units.append(Unit(index, content[i:i + length], content[i:i + length]))
            i += length
    return units


def std_spec(flags, width, precision, conversion):
    """The std::format replacement field for one printf conversion, and whether its argument needs a const void* cast"""
    if '*' in (width or '') or '*' in (precision or ''):
        raise Unconvertible('* width or precision: convert by hand')
    if conversion in 'diu':
        presentation = ''
        if precision is not None:
            raise Unconvertible('precision on an integer: convert by hand')
    elif conversion in 'xXo':
        presentation = conversion
        if '#' in flags:
            raise Unconvertible('# flag (prints differently for zero): convert by hand')
    elif conversion in 'fFeEgG':
        presentation = conversion
        if '#' in flags:
            raise Unconvertible('# flag: convert by hand')
    elif conversion in 'scp':
        presentation = 'c' if conversion == 'c' else ''
        if precision is not None and conversion != 's':
            raise Unconvertible(f'precision on %{conversion}: convert by hand')
    else:
        raise Unconvertible(f'%{conversion} conversion: convert by hand')

    align = ''
    if '-' in flags:
        align = '<'
    elif width and conversion in 'scp':
        align = '>'  # printf right-aligns everything; std::format left-aligns strings and characters by default
    sign = '+' if '+' in flags else (' ' if ' ' in flags else '')
    if sign and conversion in 'scp':
        sign = ''
    zero = '0' if '0' in flags and not align and conversion not in 'scp' else ''
    spec = f'{align}{sign}{zero}{width or ""}{"." + precision if precision is not None else ""}{presentation}'
    return ('{:' + spec + '}' if spec else '{}'), conversion == 'p'


def convert_specifiers(units):
    """Rewrites the units in place; returns, per argument, whether it needs a const void* cast"""
    pointer_args = []
    i = 0
    while i < len(units):
        unit = units[i]
        if unit.out is None:  # a macro outside a specifier
            raise Unconvertible(f'{unit.text} outside a conversion: convert by hand')
        if unit.text in '{}':
            unit.out = unit.text * 2
            i += 1
            continue
        if unit.text != '%':
            i += 1
            continue
        if i + 1 < len(units) and units[i + 1].text == '%':
            units[i + 1].out = ''
            i += 2
            continue
        # Read the conversion: flags, width, precision, length, then the conversion character or an inttypes macro
        j = i + 1

        def next_text():
            return units[j].text if j < len(units) else ''

        flags = ''
        while next_text() and next_text() in '-+ #0':
            flags += next_text()
            j += 1
        width = ''
        while next_text() and (next_text().isdigit() or next_text() == '*'):
            width += next_text()
            j += 1
        precision = None
        if next_text() == '.':
            j += 1
            precision = ''
            while next_text() and (next_text().isdigit() or next_text() == '*'):
                precision += next_text()
                j += 1
            precision = precision or '0'
        while next_text() in ('h', 'l', 'z', 'j', 't', 'L', 'q'):
            j += 1
        if j >= len(units):
            raise Unconvertible('incomplete conversion: convert by hand')
        if units[j].out is None:
            m = PRI_RE.match(units[j].text)
            conversion = m.group(1)
        elif len(units[j].text) == 1 and units[j].text.isalpha():
            conversion = units[j].text
        else:
            raise Unconvertible(f'unknown conversion "%{units[j].text}": convert by hand')
        field, is_pointer = std_spec(flags, width, precision, conversion)
        unit.out = field
        for k in range(i + 1, j + 1):
            units[k].out = ''
        pointer_args.append(is_pointer)
        i = j + 1
    return pointer_args


def arguments_used(fields):
    """How many arguments std::format replacement fields use, as vvl::log_format::ArgumentsUsed counts them: one per
    automatic field, nested fields included ("{:>{}}" uses two), or the highest manual index plus one ("{0} {0}" uses one)"""
    automatic, manual = 0, 0
    for field in fields:
        for index in re.findall(r'\{(\d*)', field):
            if index:
                manual = max(manual, int(index) + 1)
            else:
                automatic += 1
    return manual if manual else automatic


def scan_braces(content):
    """Left to right like the format libraries: the replacement fields, whether a brace stands alone (printf text), and
    whether "{{" or "}}" escapes appear. A nested field's "}}" closes two fields, it is not an escape."""
    fields, single_brace, has_escaped = [], False, False
    i = 0
    while i < len(content):
        if content.startswith('{{', i) or content.startswith('}}', i):
            has_escaped = True
            i += 2
        elif content[i] == '{' and FIELD_RE.match(content, i):
            field = FIELD_RE.match(content, i)
            fields.append(field.group(0))
            i = field.end()
        else:
            single_brace |= content[i] in '{}'
            i += 1
    return fields, single_brace, has_escaped


def format_state(content, argument_count):
    """'converted', 'convert' or 'unchanged' for a literal format, from its text and argument count"""
    fields, single_brace, has_escaped = scan_braces(content)
    if fields or has_escaped:
        if (arguments_used(fields) == argument_count and not single_brace and
                not STRICT_PRINTF_RE.search(content.replace('%%', ''))):
            return 'converted'
        raise Unconvertible('mixes std::format braces with printf-style arguments: convert by hand')
    if argument_count > 0 or '%%' in content:
        return 'convert'
    if '%' in content:
        return 'converted'  # a lone % with no arguments only comes from a converted "%%"
    return 'convert' if single_brace else 'unchanged'


# ---------------------------------------------------------------- arguments

C_STR_RE = re.compile(r'\s*\.\s*c_str\s*\(\s*\)')
POSTFIX_RE = re.compile(r'[A-Za-z_]\w*(?:\s*(?:\.|->|::)\s*[A-Za-z_]\w*|\s*\(\)|\s*\[\])*')


def is_postfix_expression(masked):
    """True for a single chain such as loc, infos[i].loc->dot(Field::x) or state->Handle(): something that a ternary,
    an operator or a wrapping call would make false"""
    flattened, depth = [], 0
    for c in masked.strip():
        if c in '([':
            if depth == 0:
                flattened.append(c)
            depth += 1
        elif c in ')]':
            depth -= 1
            if depth == 0:
                flattened.append(c)
        elif depth == 0:
            flattened.append(c)
    return POSTFIX_RE.fullmatch(''.join(flattened)) is not None


def call_with_c_str(masked, name_end):
    """Spans of the call whose '(' ends at name_end and of its .c_str() when that is the end of the argument, else None"""
    close = matching_paren(masked, name_end - 1)
    tail = C_STR_RE.match(masked, close + 1) if close > 0 else None
    if tail and tail.end() == len(masked):
        return close, tail
    return None


def rewrite_argument(text, masked, flags_names):
    """When it is the whole argument: FormatHandle(x).c_str() -> Handle(x), <loc>.Fields().c_str() -> <loc> and
    string_Vk<Name>(v).c_str() -> vvl::Flags::<Name>(v). Inside a larger expression (a ternary, a wrapping call) the
    argument stays a const char*, which formats the same."""
    for m in re.finditer(r'\bFormatHandle\s*\(', masked):
        found = call_with_c_str(masked, m.end())
        receiver = re.sub(r'\s*(?:\.|->)\s*$', '', masked[:m.start()])
        if found and (not masked[:m.start()].strip() or
                      (receiver != masked[:m.start()] and is_postfix_expression(receiver))):
            close, tail = found
            return text[:m.start()] + 'Handle' + text[m.start() + len('FormatHandle'):close + 1]
    m = re.search(r'\s*\.\s*Fields\s*\(\s*\)' + C_STR_RE.pattern + '$', masked)
    if m and is_postfix_expression(masked[:m.start()]):
        return text[:m.start()]
    m = re.match(r'string_Vk(\w+)\s*\(', masked)
    if m and m.group(1) in flags_names:
        found = call_with_c_str(masked, m.end())
        if found:
            close, tail = found
            return f'vvl::Flags::{m.group(1)}' + text[len('string_Vk') + len(m.group(1)):close + 1]
    return text


def strip_span(masked, start, end):
    while start < end and masked[start].isspace():
        start += 1
    while end > start and masked[end - 1].isspace():
        end -= 1
    return start, end


def constexpr_format_content(text, masked, name, before):
    """The literal text of the closest definition of `name` before offset `before` when that one is constexpr, or None"""
    found = None
    definition = r'\b(?:constexpr\s+)?(?:static\s+)?(?:constexpr\s+)?(?:const\s+)?char\s*(?:const\s*)?\*?\s*(?:const\s+)?'
    for m in re.finditer(definition + re.escape(name) + r'\s*(?:\[\s*\])?\s*=', masked[:before]):
        found = m
    if not found or 'constexpr' not in found.group(0):
        return None
    tokens = tokenize_format(text, masked, found.end(), masked.index(';', found.end()))
    if tokens and all(t.kind == 'literal' for t in tokens):
        return ''.join(t.text for t in tokens)
    return None


def convert_call(text, masked, spans, flags_names, call_start):
    """Edits (start, end, replacement) for one call, or [] when it needs none"""
    if len(spans) < 4:
        raise Unconvertible('fewer than four arguments')
    format_start, format_end = strip_span(masked, *spans[3])
    arguments = [strip_span(masked, *span) for span in spans[4:]]
    tokens = tokenize_format(text, masked, format_start, format_end)
    literal = any(t.kind == 'literal' for t in tokens) and all(t.kind in ('literal', 'macro') for t in tokens)
    if not literal:
        if any(t.kind == 'literal' for t in tokens) and all(t.kind != 'other' or IDENT_RE.fullmatch(t.text) for t in tokens):
            raise Unconvertible('macro in the format string: convert by hand')
        if arguments and len(tokens) == 1 and IDENT_RE.fullmatch(tokens[0].text):
            # A constexpr format variable is still checked at compile time, so it is converted in its definition
            content = constexpr_format_content(text, masked, tokens[0].text, call_start)
            if content is not None:
                if format_state(content, len(arguments)) == 'converted':
                    return []
                raise Unconvertible(f'constexpr format {tokens[0].text} is still printf-style: convert its definition by hand')
        if arguments:
            raise Unconvertible('non-literal format with arguments: convert by hand')
        return [(format_start, format_start, '"{}", ')]

    content = ''.join(t.text if t.kind == 'literal' else '' for t in tokens)
    state = format_state(content, len(arguments))
    if state != 'convert':
        return []
    units = literal_units(tokens)
    pointer_args = convert_specifiers(units)
    if len(pointer_args) != len(arguments):
        raise Unconvertible(f'{len(pointer_args)} conversions for {len(arguments)} arguments')

    edits = []
    for index, token in enumerate(tokens):
        new = ''.join(u.out for u in units if u.token == index)
        if token.kind == 'literal':
            edits.append((token.start + 1, token.end - 1, new))
        else:  # a consumed inttypes macro, with the spaces before it on its line (line numbers stay the same)
            start = token.start
            while start > format_start and masked[start - 1] in ' \t':
                start -= 1
            edits.append((start, token.end, ''))
    for (start, end), is_pointer in zip(arguments, pointer_args):
        new = rewrite_argument(text[start:end], masked[start:end], flags_names)
        if is_pointer:
            new = f'static_cast<const void*>({new})'
        if new != text[start:end]:
            edits.append((start, end, new))
    return edits


def convert_source(text, flags_names):
    """The converted text and the calls that could not be converted"""
    masked = mask_source(text)
    edits, problems = [], []
    for m in CALL_RE.finditer(masked):
        if not is_call(masked, m.start()):
            continue
        open_index = m.end() - 1
        close_index = matching_paren(masked, open_index)
        line = text.count('\n', 0, m.start()) + 1
        if close_index < 0:
            problems.append(Problem(line, 'unbalanced parentheses'))
            continue
        try:
            edits += convert_call(text, masked, split_arguments(masked, open_index, close_index), flags_names, m.start())
        except Unconvertible as e:
            problems.append(Problem(line, str(e)))
    for start, end, new in sorted(edits, reverse=True):
        text = text[:start] + new + text[end:]
    return text, problems


# ---------------------------------------------------------------- files

def read_flags_names(header):
    with open(header, encoding='utf-8') as f:
        return set(re.findall(r'\bFlagsRef\s+(\w+)\s*\(', f.read()))


def source_files(paths):
    for path in paths:
        if os.path.isfile(path):
            yield path
            continue
        for root, dirs, files in os.walk(path):
            dirs.sort()
            for name in sorted(files):
                if name.endswith(SOURCE_EXTENSIONS):
                    yield os.path.join(root, name)


def is_generated(path):
    # normcase: Windows paths ignore case, so "Layers" must not get past the guard
    parts = os.path.normcase(os.path.normpath(os.path.abspath(path))).split(os.sep)
    wanted = [os.path.normcase(part) for part in ('layers', 'vulkan', 'generated')]
    return any(parts[i:i + 3] == wanted for i in range(len(parts)))


def main(argv, report=print):
    repo = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('paths', nargs='+', help='files or directories to convert')
    parser.add_argument('--dry-run', action='store_true', help='list unconvertible calls without editing anything')
    parser.add_argument('--flags-header', default=os.path.join(repo, GENERATED_DIR, 'flags_format_helper.h'),
                        help='generated header listing the vvl::Flags helpers')
    args = parser.parse_args(argv)
    flags_names = read_flags_names(args.flags_header)

    results = []
    generated_failures = []
    for path in source_files(args.paths):
        with open(path, encoding='utf-8', newline='') as f:
            text = f.read()
        new_text, problems = convert_source(text, flags_names)
        if is_generated(path):
            if new_text != text or problems:
                generated_failures.append(path)
            continue
        results.append((path, text, new_text, problems))

    for path in generated_failures:
        report(f'{path}: printf-style Log* call in generated code: fix the generator, not the output')
    remaining = 0
    for path, text, new_text, problems in results:
        for problem in problems:
            report(f'{path}:{problem.line}: {problem.reason}')
        remaining += len(problems)
    if generated_failures:
        return 2  # nothing is edited anywhere
    if not args.dry_run:
        for path, text, new_text, problems in results:
            if new_text != text:
                with open(path, 'w', encoding='utf-8', newline='') as f:
                    f.write(new_text)
    return 1 if remaining else 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
