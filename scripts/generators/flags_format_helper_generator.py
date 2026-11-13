#!/usr/bin/python3 -i
#
# Copyright (c) 2026 The Khronos Group Inc.
# Copyright (c) 2026 Valve Corporation
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

import os

from base_generator import BaseGenerator
from generators.generator_utils import PlatformGuardHelper

# vvl::Flags::<Name>(value) formats like string_Vk<Name>(value) of vk_enum_string_helper.h. These follow the choices of
# Vulkan-Utility-Libraries' enum_string_helper_generator.py: a helper for every bitmask with at least one flag, the
# multi-bit flags checked as whole values first, then each set bit, then "<FlagsName>(0)".
class FlagsFormatHelperOutputGenerator(BaseGenerator):
    def __init__(self):
        BaseGenerator.__init__(self)

    def generate(self):
        out = []
        out.append(f'''// *** THIS FILE IS GENERATED - DO NOT EDIT ***
            // See {os.path.basename(__file__)} for modifications

            /***************************************************************************
            *
            * Copyright (c) 2026 The Khronos Group Inc.
            * Copyright (c) 2026 Valve Corporation
            * Copyright (c) 2026 LunarG, Inc.
            *
            * Licensed under the Apache License, Version 2.0 (the "License");
            * you may not use this file except in compliance with the License.
            * You may obtain a copy of the License at
            *
            *     http://www.apache.org/licenses/LICENSE-2.0
            *
            * Unless required by applicable law or agreed to in writing, software
            * distributed under the License is distributed on an "AS IS" BASIS,
            * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
            * See the License for the specific language governing permissions and
            * limitations under the License.
            ****************************************************************************/\n''')
        out.append('// NOLINTBEGIN\n\n')  # Wrap for clang-tidy to ignore

        if self.filename == 'flags_format_helper.h':
            out.append(self.generateHeader())
        elif self.filename == 'flags_format_helper.cpp':
            out.append(self.generateSource())
        elif self.filename == 'flags_format_test_cases.h':
            out.append(self.generateTestCases())
        else:
            out.append(f'\nFile name {self.filename} has no code to generate\n')

        out.append('// NOLINTEND')  # Wrap for clang-tidy to ignore
        self.write(''.join(out))

    def bitmasks(self):
        return [x for x in self.vk.bitmasks.values() if len(x.flags) > 0]

    @staticmethod
    def functionName(bitmask):
        return bitmask.flagName[2:]  # string_VkShaderStageFlags -> vvl::Flags::ShaderStageFlags

    def generateHeader(self):
        out = []
        out.append('#pragma once\n\n')
        out.append('#include <vulkan/vulkan.h>\n')
        out.append('#include "error_message/log_flags.h"\n\n')
        out.append('// For the Log* functions: "{}" with vvl::Flags::ShaderStageFlags(stages) prints like\n')
        out.append('// string_VkShaderStageFlags(stages), but formats only if the message is delivered and never allocates\n')
        out.append('namespace vvl::Flags {\n')
        guard_helper = PlatformGuardHelper()
        for bitmask in self.bitmasks():
            out.extend(guard_helper.add_guard(bitmask.protect))
            out.append(f'FlagsRef {self.functionName(bitmask)}({bitmask.flagName} value);\n')
        out.extend(guard_helper.add_guard(None))
        out.append('}  // namespace vvl::Flags\n')
        return ''.join(out)

    def generateSource(self):
        out = []
        out.append('#include "flags_format_helper.h"\n\n')
        out.append('#include <iterator>\n\n')
        out.append('#include <vulkan/vk_enum_string_helper.h>\n\n')
        out.append('namespace vvl::Flags {\n')
        guard_helper = PlatformGuardHelper()
        for bitmask in self.bitmasks():
            out.extend(guard_helper.add_guard(bitmask.protect, extra_newline=True))
            name = self.functionName(bitmask)
            bit_type = bitmask.name if bitmask.bitWidth == 32 else 'uint64_t'
            bit_name = f'string_{bitmask.name}(static_cast<{bit_type}>(bit))' if bitmask.bitWidth == 32 else f'string_{bitmask.name}(bit)'
            whole_values = [x for x in bitmask.flags if x.multiBit]
            out.append(f'static const char* {name}BitName(uint64_t bit) {{ return {bit_name}; }}\n')
            if whole_values:
                out.append(f'static constexpr FlagsWholeValueName k{name}WholeValues[] = {{\n')
                flag_guard_helper = PlatformGuardHelper()
                for flag in whole_values:
                    out.extend(flag_guard_helper.add_guard(flag.protect))
                    out.append(f'    {{{flag.name}, "{flag.name}"}},\n')
                out.extend(flag_guard_helper.add_guard(None))
                out.append('};\n')
                whole = f'k{name}WholeValues, static_cast<uint32_t>(std::size(k{name}WholeValues))'
            else:
                whole = 'nullptr, 0'
            out.append(f'static constexpr FlagsDescription k{name} = {{{name}BitName, "{bitmask.flagName}(0)", {whole}}};\n')
            out.append(f'FlagsRef {name}({bitmask.flagName} value) {{ return FlagsRef{{&k{name}, value}}; }}\n')
        out.extend(guard_helper.add_guard(None))
        out.append('}  // namespace vvl::Flags\n')
        return ''.join(out)

    def generateTestCases(self):
        out = []
        out.append('#pragma once\n\n')
        out.append('// Test data only: for each flags type, the values whose vvl::Flags formatting is compared with string_Vk*Flags*()\n\n')
        out.append('#include <cstdint>\n#include <string>\n#include <vector>\n\n')
        out.append('#include <vulkan/vk_enum_string_helper.h>\n')
        out.append('#include "flags_format_helper.h"\n\n')
        out.append('namespace vvl {\n')
        out.append('struct FlagsFormatTestCase {\n')
        out.append('    const char* name;\n')
        out.append('    FlagsRef (*make)(uint64_t value);\n')
        out.append('    std::string (*expected)(uint64_t value);\n')
        out.append('    std::vector<uint64_t> values;\n')
        out.append('};\n\n')
        out.append('inline const FlagsFormatTestCase kFlagsFormatTestCases[] = {\n')
        guard_helper = PlatformGuardHelper()
        for bitmask in self.bitmasks():
            out.extend(guard_helper.add_guard(bitmask.protect))
            name = self.functionName(bitmask)
            # Zero, every whole-value name alone and with the top bit added (it must then print bit by bit), the two
            # lowest named bits together and the top bit (usually unnamed)
            top_bit = f'uint64_t(1) << {bitmask.bitWidth - 1}'
            values = ['0']
            for flag in [x for x in bitmask.flags if x.multiBit and x.protect is None]:
                values += [flag.name, f'{flag.name} | ({top_bit})']
            single_bits = sorted([x for x in bitmask.flags if x.bitpos is not None and x.protect is None], key=lambda x: x.bitpos)
            if len(single_bits) >= 2:
                values.append(f'{single_bits[0].name} | {single_bits[1].name}')
            values.append(top_bit)
            values = ', '.join(f'static_cast<uint64_t>({x})' for x in values)
            out.append(f'    {{"{bitmask.flagName}",\n')
            out.append(f'     [](uint64_t value) {{ return Flags::{name}(static_cast<{bitmask.flagName}>(value)); }},\n')
            out.append(f'     [](uint64_t value) {{ return string_{bitmask.flagName}(static_cast<{bitmask.flagName}>(value)); }},\n')
            out.append(f'     {{{values}}}}},\n')
        out.extend(guard_helper.add_guard(None))
        out.append('};\n')
        out.append('}  // namespace vvl\n')
        return ''.join(out)
