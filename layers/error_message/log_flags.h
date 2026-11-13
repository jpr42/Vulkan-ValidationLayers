/* Copyright (c) 2026 LunarG, Inc.
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
 */
#pragma once

#include <algorithm>
#include <cstdint>
#include <string_view>

#include "error_message/format_backend.h"

namespace vvl {

// A value with more than one bit set that has its own name, such as VK_SHADER_STAGE_ALL_GRAPHICS
struct FlagsWholeValueName {
    uint64_t value;
    const char* name;
};

// Everything needed to print one flags type; generated per type in generated/flags_format_helper.cpp
struct FlagsDescription {
    const char* (*bit_name)(uint64_t bit);  // the string_Vk*FlagBits function
    const char* zero_text;                  // "VkShaderStageFlags(0)"
    const FlagsWholeValueName* whole_values;
    uint32_t whole_value_count;
};

// A flags value to format with "{}" (vvl::Flags::<Name>(value)). Gives the same text as the matching
// string_Vk*Flags*() helper of vk_enum_string_helper.h, without building a std::string.
struct FlagsRef {
    const FlagsDescription* description;
    uint64_t value;
};

// Calls `emit` with each piece of the text, in order, without allocating
using FlagsEmitPiece = void (*)(void* context, std::string_view piece);
void VisitFlags(const FlagsRef& flags, FlagsEmitPiece emit, void* context);

}  // namespace vvl

template <>
struct VVL_FMT_NS::formatter<vvl::FlagsRef> {
    // No format spec: anything before '}' is rejected by the backend's check
    constexpr auto parse(VVL_FMT_NS::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const vvl::FlagsRef& flags, FormatContext& ctx) const {
        using Out = decltype(ctx.out());
        Out out = ctx.out();
        vvl::VisitFlags(
            flags,
            [](void* context, std::string_view piece) {
                Out& it = *static_cast<Out*>(context);
                it = std::copy(piece.begin(), piece.end(), it);
            },
            &out);
        return out;
    }
};
