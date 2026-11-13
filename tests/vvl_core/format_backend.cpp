/*
 * Copyright (c) 2026 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

// The formatting backend (std::format or fmtlib) must give identical text for everything the layer formats

#include "../framework/test_common.h"

#include <cstdint>
#include <string>
#include <string_view>

#include "error_message/format_backend.h"

namespace {
struct Point {
    int x;
    int y;
};
}  // namespace

template <>
struct VVL_FMT_NS::formatter<Point> {
    constexpr auto parse(VVL_FMT_NS::format_parse_context& ctx) { return ctx.begin(); }
    auto format(const Point& point, VVL_FMT_NS::format_context& ctx) const {
        return VVL_FMT_NS::format_to(ctx.out(), "({}, {})", point.x, point.y);
    }
};

namespace {
// The same shape the Log* functions use: checked format string, type-erased arguments, one non-template function
template <typename... Args>
std::string Format(vvl::format::format_string<Args...> fmt, Args&&... args) {
    std::string out;
    vvl::format::VFormatTo(out, vvl::format::View(fmt), vvl::format::MakeArgs(args...));
    return out;
}
}  // namespace

TEST(VvlCoreFormatBackend, BuiltinTypesAndUserFormatter) {
    EXPECT_EQ(Format("{} {:#x} {:.2f} {} {}", 1, 255u, 1.5, std::string_view("text"), Point{1, 2}), "1 0xff 1.50 text (1, 2)");
}

// Where std::format and fmtlib are most likely to differ
TEST(VvlCoreFormatBackend, PointersBoolsCharsAndAlignment) {
    const void* pointer = reinterpret_cast<const void*>(uintptr_t{0x1234});
    EXPECT_EQ(Format("{} {} {}", pointer, true, 'c'), "0x1234 true c");
    EXPECT_EQ(Format("[{:>4}] [{:<4}] [{:^5}] [{:08x}]", 7, 7, "ab", 0xbeefu), "[   7] [7   ] [ ab  ] [0000beef]");
    EXPECT_EQ(Format("{} {} {}", -2.5, 1e20, 0.1f), "-2.5 1e+20 0.1");
}
