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
#
# Run with: python scripts/convert_log_format_test.py

import os
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import convert_log_format as clf

FLAGS = {'ShaderStageFlags', 'FormatFeatureFlags2', 'CullModeFlags'}


def call(fmt_and_args, function='LogError'):
    return f'skip |= {function}(vuid, objlist, loc, {fmt_and_args});'


# (printf call arguments after the location, expected std::format arguments)
CASES = [
    # Integer and string conversions, length modifiers and inttypes macros all become {}
    ('"%s, %d, %u, %i", a, b, c, d', '"{}, {}, {}, {}", a, b, c, d'),
    ('"%zu %llu %lu %ld %lld %hu %hhu", a, b, c, d, e, f, g', '"{} {} {} {} {} {} {}", a, b, c, d, e, f, g'),
    ('"count %" PRIu32 " and %" PRIu64 ".", a, b', '"count {}" " and {}" ".", a, b'),
    ('"signed %" PRId64 " and %" PRIi32, a, b', '"signed {}" " and {}", a, b'),
    # Hex
    ('"0x%x", a', '"0x{:x}", a'),
    ('"0x%" PRIx64 " end", a', '"0x{:x}" " end", a'),
    ('"0x%08x 0x%02X %X", a, b, c', '"0x{:08x} 0x{:02X} {:X}", a, b, c'),
    ('"0x%" PRIX64, a', '"0x{:X}", a'),
    # Floating point
    ('"%f %.2f %e %g %lf", a, b, c, d, e', '"{:f} {:.2f} {:e} {:g} {:f}", a, b, c, d, e'),
    # Characters
    ('"%c", a', '"{:c}", a'),
    # Pointers: the argument is cast; std::format prints 0x... where printf's %p text varies by platform
    ('"ptr %p", pData', '"ptr {}", static_cast<const void*>(pData)'),
    # Escapes
    ('"100%% done, %u left", n', '"100% done, {} left", n'),
    ('"100%% done"', '"100% done"'),
    ('"struct { int x; } is %u", n', '"struct {{ int x; }} is {}", n'),
    ('"a } alone"', '"a }} alone"'),
    ('"quote \\"%s\\" and \\\\ backslash", s', '"quote \\"{}\\" and \\\\ backslash", s'),
    # Widths, alignment, signs and string precision
    ('"[%5d] [%-5d] [%05u] [%+d] [% d]", a, b, c, d, e', '"[{:5}] [{:<5}] [{:05}] [{:+}] [{: }]", a, b, c, d, e'),
    ('"[%10s] [%-10s] [%.3s] [%3c]", a, b, c, d', '"[{:>10}] [{:<10}] [{:.3}] [{:>3c}]", a, b, c, d'),
    # Literal pieces on several lines keep their layout
    ('"first %u "\n                "second %s", a, b', '"first {} "\n                "second {}", a, b'),
    # Non-literal formats with no further arguments
    ('error_message.c_str()', '"{}", error_message.c_str()'),
    ('kMessage', '"{}", kMessage'),
    # A format with no specifier and no brace is left alone
    ('"nothing to convert"', '"nothing to convert"'),
    # Rewrites inside the arguments
    ('"%s is bad", FormatHandle(buffer).c_str()', '"{} is bad", Handle(buffer)'),
    ('"%s is bad", dev_data->FormatHandle(*buffer_state).c_str()', '"{} is bad", dev_data->Handle(*buffer_state)'),
    ('"%s and %s", this->FormatHandle(a).c_str(), dev.FormatHandle(b, c).c_str()', '"{} and {}", this->Handle(a), dev.Handle(b, c)'),
    ('"%s is 0", loc.dot(Field::size).Fields().c_str()', '"{} is 0", loc.dot(Field::size)'),
    ('"%s is %s", region_loc.Fields().c_str(), string_VkShaderStageFlags(stages).c_str()',
     '"{} is {}", region_loc, vvl::Flags::ShaderStageFlags(stages)'),
    ('"%s", string_VkFormatFeatureFlags2(GetFeatures(x, y)).c_str()', '"{}", vvl::Flags::FormatFeatureFlags2(GetFeatures(x, y))'),
    # Not rewritten: no .c_str(), a flags helper with no vvl::Flags version, a FlagBits helper
    ('"%s %s %s", name.c_str(), string_VkAccessFlags3KHR(a).c_str(), string_VkShaderStageFlagBits(b)',
     '"{} {} {}", name.c_str(), string_VkAccessFlags3KHR(a).c_str(), string_VkShaderStageFlagBits(b)'),
    # Rewrites only apply to a whole argument: inside a ternary or a wrapping call the type would no longer match
    ('"%s", allowed == 0 ? "none (0)" : string_VkShaderStageFlags(allowed).c_str()',
     '"{}", allowed == 0 ? "none (0)" : string_VkShaderStageFlags(allowed).c_str()'),
    ('"%s", h ? FormatHandle(h).c_str() : "null"', '"{}", h ? FormatHandle(h).c_str() : "null"'),
    ('"%s", std::string(loc.Fields().c_str()).substr(1).c_str()', '"{}", std::string(loc.Fields().c_str()).substr(1).c_str()'),
    ('"%s", infos[i].loc->dot(Field::x).Fields().c_str()', '"{}", infos[i].loc->dot(Field::x)'),
    # A handle pointer with %p is cast after the rewrite
    ('"%p", FormatHandle(a).c_str()', '"{}", static_cast<const void*>(Handle(a))'),
]

# Calls the script must report and leave untouched
UNCONVERTIBLE = [
    ('"%*d", width, a', '*'),
    ('"%.*s", length, text', '*'),
    ('"%#x", a', '#'),
    ('"%5.2d", a', 'precision'),
    ('"%n", a', 'n'),
    ('"%a", a', 'a'),
    ('"%u %u", a', 'argument'),
    ('"%u", a, b', 'argument'),
    ('use_a ? "a %u" : "b %u", a', 'non-literal'),
    ('kFormat, a', 'non-literal'),
    ('"value %" MY_MACRO, a', 'macro'),
    ('R"(%u)", a', 'raw'),
    # A printf string that also holds a std::format-looking field cannot be told apart from a converted one
    ('"{} %u", a', 'mixes'),
]


class ConvertTest(unittest.TestCase):
    def convert(self, text):
        return clf.convert_source(text, FLAGS)

    def test_mapping_table(self):
        for before, after in CASES:
            with self.subTest(before=before):
                new_text, problems = self.convert(call(before))
                self.assertEqual(problems, [])
                self.assertEqual(new_text, call(after))

    def test_every_log_function(self):
        for function in ['LogError', 'LogWarning', 'LogInternalError', 'LogUndefinedValue', 'LogPerformanceWarning', 'LogInfo',
                         'LogVerbose']:
            with self.subTest(function=function):
                new_text, problems = self.convert(call('"%u", a', function))
                self.assertEqual(problems, [])
                self.assertEqual(new_text, call('"{}", a', function))

    def test_receivers_and_contexts(self):
        source = '''bool Check() const {
    bool skip = LogError(vuid, objlist, loc, "%u", a);
    skip |= device_state->LogWarning(vuid, objlist, loc, "%u", a);
    if (x) return log.LogInfo(vuid, objlist, loc, "%u", a);
    return !dev.LogError(vuid, objlist, loc, "%u", a);
}'''
        new_text, problems = self.convert(source)
        self.assertEqual(problems, [])
        self.assertEqual(new_text, source.replace('"%u"', '"{}"'))

    def test_unconvertible_calls_are_reported_and_unchanged(self):
        for before, reason in UNCONVERTIBLE:
            with self.subTest(before=before):
                text = 'void F() {\n    ' + call(before) + '\n}'
                new_text, problems = self.convert(text)
                self.assertEqual(new_text, text)
                self.assertEqual(len(problems), 1)
                self.assertEqual(problems[0].line, 2)
                self.assertIn(reason, problems[0].reason)

    def test_comments_strings_and_declarations_are_ignored(self):
        source = '''// LogError(vuid, objlist, loc, "%u", a);
/* LogWarning(vuid, objlist, loc, "%u", a); */
const char* text = "LogError(vuid, objlist, loc, \\"%u\\", a)";
bool DECORATE_PRINTF(5, 6) LogError(std::string_view vuid_text, const LogObjectList &objlist, const Location &loc,
                                    const char *format, ...) const;
bool Logger::LogInfo(std::string_view vuid_text, const LogObjectList &objlist, const Location &loc, const char *format, ...);
auto f = &Logger::LogError;
uint32_t n = 1'000'000;'''
        new_text, problems = self.convert(source)
        self.assertEqual(problems, [])
        self.assertEqual(new_text, source)

    def test_hand_converted_formats_stay_converted(self):
        # The hand conversions of %*d and of a repeated argument
        for converted in ['"{:>{}}", a, w', '"{0} and {0}", a', '"{1}{0}", a, b', '"{:{}.{}}", a, w, p']:
            with self.subTest(converted=converted):
                self.assertEqual(self.convert(call(converted)), (call(converted), []))

    def test_constexpr_format_variables(self):
        # A format string held in a constexpr variable is still checked at compile time; the closest definition before the
        # call is the one used
        converted = '''void F() {
    constexpr const char* msg = "chain does not contain a {} structure.";
    skip |= LogError(vuid, objlist, loc, msg, name);
}
void G() {
    constexpr char msg[] = "({}) does not match {}"
                           " used by the suspended instance.";
    skip |= LogError(vuid, objlist, loc, msg, a, b);
}'''
        self.assertEqual(self.convert(converted), (converted, []))
        # The closest definition decides, even when an earlier function has a constexpr one with the same name
        shadowed = converted + '\nvoid H() {\n    const char* msg = "a %s b";\n    skip |= LogError(vuid, objlist, loc, msg, name);\n}'
        new_text, problems = self.convert(shadowed)
        self.assertEqual(new_text, shadowed)
        self.assertEqual([p.line for p in problems], [12])
        for definition, reason in [('constexpr const char* msg = "chain does not contain a %s structure.";', 'printf'),
                                   ('const char* msg = "chain does not contain a {} structure.";', 'non-literal')]:
            with self.subTest(definition=definition):
                text = 'void F() {\n    ' + definition + '\n    skip |= LogError(vuid, objlist, loc, msg, name);\n}'
                new_text, problems = self.convert(text)
                self.assertEqual(new_text, text)
                self.assertEqual([p.line for p in problems], [3])
                self.assertIn(reason, problems[0].reason)

    def test_converted_percent_signs_stay_converted(self):
        # "{}% done" comes from "%u%% done"; "% d" is not a conversion a printf string would use with a field
        for converted in ['"{}% done", a', '"100% done"', '"{:x}%", a']:
            with self.subTest(converted=converted):
                self.assertEqual(self.convert(call(converted)), (call(converted), []))

    def test_only_the_generated_directory_counts_as_generated(self):
        self.assertTrue(clf.is_generated(os.path.join('layers', 'vulkan', 'generated', 'a.cpp')))
        self.assertFalse(clf.is_generated(os.path.join('layers', 'vulkan', 'generated_extra', 'a.cpp')))
        self.assertFalse(clf.is_generated(os.path.join('layers', 'vulkan', 'generated.cpp')))
        if os.path.normcase('A') == 'a':  # paths ignore case on Windows
            self.assertTrue(clf.is_generated(os.path.join('Layers', 'Vulkan', 'Generated', 'a.cpp')))

    def test_second_run_changes_nothing(self):
        source = '\n'.join(call(before) for before, _ in CASES)
        once, problems = self.convert(source)
        self.assertEqual(problems, [])
        twice, problems = self.convert(once)
        self.assertEqual(problems, [])
        self.assertEqual(twice, once)

    def test_generated_directory_is_never_edited(self):
        with tempfile.TemporaryDirectory() as root:
            generated = os.path.join(root, 'layers', 'vulkan', 'generated')
            os.makedirs(generated)
            path = os.path.join(generated, 'spirv_validation_helper.cpp')
            text = 'void F() {\n    ' + call('"%u", a') + '\n}\n'
            with open(path, 'w', newline='') as f:
                f.write(text)
            clean_path = os.path.join(generated, 'clean.cpp')
            with open(clean_path, 'w', newline='') as f:
                f.write('void G() {\n    ' + call('"{}", a') + '\n}\n')

            self.assertNotEqual(clf.main([generated, '--flags-header', os.devnull], report=lambda line: None), 0)
            with open(path, newline='') as f:
                self.assertEqual(f.read(), text)
            # Without a specifier there is nothing to fail on, but nothing is edited either
            self.assertEqual(clf.main([clean_path, '--flags-header', os.devnull]), 0)

    def test_dry_run_lists_unconvertible_calls_and_edits_nothing(self):
        with tempfile.TemporaryDirectory() as root:
            path = os.path.join(root, 'core.cpp')
            text = 'void F() {\n    ' + call('"%u", a') + '\n    ' + call('"%*d", w, a') + '\n}\n'
            with open(path, 'w', newline='') as f:
                f.write(text)
            problems = []
            self.assertNotEqual(clf.main([root, '--dry-run', '--flags-header', os.devnull], report=problems.append), 0)
            with open(path, newline='') as f:
                self.assertEqual(f.read(), text)
            self.assertEqual(len(problems), 1)
            self.assertIn(f'{path}:3:', problems[0])

    def test_files_keep_their_line_endings(self):
        with tempfile.TemporaryDirectory() as root:
            path = os.path.join(root, 'core.cpp')
            with open(path, 'w', newline='') as f:
                f.write('void F() {\r\n    ' + call('"%u", a') + '\r\n}\r\n')
            self.assertEqual(clf.main([path, '--flags-header', os.devnull]), 0)
            with open(path, newline='') as f:
                self.assertEqual(f.read(), 'void F() {\r\n    ' + call('"{}", a') + '\r\n}\r\n')

    def test_flags_names_come_from_the_generated_header(self):
        with tempfile.TemporaryDirectory() as root:
            header = os.path.join(root, 'flags_format_helper.h')
            with open(header, 'w') as f:
                f.write('namespace vvl::Flags {\nFlagsRef ShaderStageFlags(VkShaderStageFlags value);\n#ifdef X\n'
                        'FlagsRef FormatFeatureFlags2(VkFormatFeatureFlags2 value);\n#endif\n}\n')
            self.assertEqual(clf.read_flags_names(header), {'ShaderStageFlags', 'FormatFeatureFlags2'})


if __name__ == '__main__':
    unittest.main()
