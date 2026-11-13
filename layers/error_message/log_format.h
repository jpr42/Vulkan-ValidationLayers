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

#include <cstddef>
#include <concepts>
#include <string_view>
#include <type_traits>

#include "error_message/format_backend.h"

namespace vvl {
namespace log_format {

// How many arguments the replacement fields of `text` use: the number of fields with automatic indexing ("{}"), or the
// highest index plus one with manual indexing ("{1}"). Fields nested in a format spec ("{:>{}}") count too. Malformed
// strings are left to the backend's own check.
consteval std::size_t ArgumentsUsed(std::string_view text) {
    std::size_t automatic = 0;
    std::size_t manual = 0;
    // Reads one replacement field's argument id, starting just after its '{'
    auto read_field = [&](std::size_t& i) {
        std::size_t id = 0;
        bool has_id = false;
        while (i < text.size() && text[i] >= '0' && text[i] <= '9') {
            id = id * 10 + static_cast<std::size_t>(text[i] - '0');
            has_id = true;
            ++i;
        }
        if (has_id) {
            manual = id + 1 > manual ? id + 1 : manual;
        } else {
            ++automatic;
        }
    };
    for (std::size_t i = 0; i < text.size(); ++i) {
        if (text[i] == '}') {
            ++i;  // "}}" is an escaped brace; a lone '}' is the backend's error
            continue;
        }
        if (text[i] != '{') {
            continue;
        }
        if (i + 1 < text.size() && text[i + 1] == '{') {
            ++i;
            continue;
        }
        ++i;
        read_field(i);
        // Skip the format spec up to the field's closing brace, counting nested fields
        while (i < text.size() && text[i] != '}') {
            if (text[i] == '{') {
                ++i;
                read_field(i);
            }
            ++i;
        }
    }
    return manual > 0 ? manual : automatic;
}

// Not constexpr: calling it from the consteval constructor is what makes a mismatch a compile error, and its name is
// what the compiler shows
void ReplacementFieldCountDiffersFromArgumentCount();

}  // namespace log_format

// The format string of the Log* functions. Checked at compile time twice: the backend checks every field against its
// argument's type, and the field count must match the argument count, which neither backend checks (both accept extra
// arguments).
template <typename... Args>
struct BasicLogFormat {
    template <typename String>
        requires std::convertible_to<const String&, std::string_view>
    consteval BasicLogFormat(const String& string) : text(string) {
        [[maybe_unused]] const format::format_string<Args...> backend_checked(string);
        if (log_format::ArgumentsUsed(text) != sizeof...(Args)) {
            log_format::ReplacementFieldCountDiffersFromArgumentCount();
        }
    }

    std::string_view text;
};

// std::type_identity keeps the format string out of argument deduction, so the arguments alone decide Args
template <typename... Args>
using LogFormat = BasicLogFormat<std::type_identity_t<Args>...>;

}  // namespace vvl
