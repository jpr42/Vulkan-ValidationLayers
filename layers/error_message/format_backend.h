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

// The formatting backend: C++20 std::format, or fmtlib with VVL_FORMAT_BACKEND_FMT. Everything else in the layer formats
// through these names, so the backend is a build option. Formatter specializations use VVL_FMT_NS, for example:
//   template <> struct VVL_FMT_NS::formatter<MyType> { ... };
// A formatter must never log: messages are formatted into a per-thread buffer that a nested message would overwrite.

#include <string>
#include <string_view>

#if defined(VVL_FORMAT_BACKEND_FMT)
#include <fmt/format.h>
// Without consteval, fmt silently stops checking format strings at compile time (for example MSVC before 19.40)
#if !FMT_USE_CONSTEVAL
#error "The fmt formatting backend needs fmt's compile-time format string checks (FMT_USE_CONSTEVAL)"
#endif
#define VVL_FMT_NS fmt
#else
#include <format>
#define VVL_FMT_NS std
#endif

namespace vvl::format {

template <typename... Args>
using format_string = VVL_FMT_NS::format_string<Args...>;
using format_args = VVL_FMT_NS::format_args;

// The format string as std::string_view; fmt's own string_view does not convert to it. Takes any format string type:
// format_string<Args...> is an alias whose Args cannot be deduced.
template <typename FormatString>
constexpr std::string_view View(const FormatString& fmt) {
    const auto view = fmt.get();
    return std::string_view(view.data(), view.size());
}

// The result only refers to `args`: pass it straight to VFormatTo in the same expression, never store it
template <typename... Args>
[[nodiscard]] auto MakeArgs(Args&... args) {
    return VVL_FMT_NS::make_format_args(args...);
}

// Appends the formatted text to `out`
void VFormatTo(std::string& out, std::string_view fmt, format_args args);

}  // namespace vvl::format
