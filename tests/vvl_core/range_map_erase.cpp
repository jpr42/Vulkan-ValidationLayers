/*
 * Copyright (c) 2026 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

#include "../framework/test_common.h"

#include <algorithm>
#include <tuple>
#include <vector>

#include "containers/range_map.h"

namespace {
using Values = std::vector<int>;
using Map = sparse_container::range_map<uint64_t, Values>;
using Range = vvl::range<uint64_t>;
using Entry = std::tuple<uint64_t, uint64_t, Values>;

std::vector<Entry> Entries(const Map& map) {
    std::vector<Entry> entries;
    for (const auto& [range, values] : map) {
        entries.emplace_back(range.begin, range.end, values);
    }
    return entries;
}

// Removes one value from every entry in bounds, and erases an entry only once it has no values left. This is how the state
// tracker drops a buffer from its device address map.
void RemoveValue(Map& map, Range bounds, int value) {
    map.erase_range_or_touch(bounds, [value](Values& values) {
        values.erase(std::remove(values.begin(), values.end(), value), values.end());
        return values.empty();
    });
}
}  // namespace

TEST(VvlCoreRangeMap, EraseRangeOrTouchStartingInsideEntry) {
    Map map;
    map.insert({Range(0, 100), Values{1, 2}});

    // The bounds start inside the entry and end past it. The part inside the bounds still holds 2, so it must stay.
    RemoveValue(map, Range(50, 150), 1);

    const std::vector<Entry> expected = {{0, 50, Values{1, 2}}, {50, 100, Values{2}}};
    EXPECT_EQ(Entries(map), expected);
}

TEST(VvlCoreRangeMap, EraseRangeOrTouchInsideEntry) {
    Map map;
    map.insert({Range(0, 200), Values{1, 2}});

    RemoveValue(map, Range(50, 150), 1);

    const std::vector<Entry> expected = {{0, 50, Values{1, 2}}, {50, 150, Values{2}}, {150, 200, Values{1, 2}}};
    EXPECT_EQ(Entries(map), expected);
}

TEST(VvlCoreRangeMap, EraseRangeStartingInsideEntry) {
    Map map;
    map.insert({Range(0, 100), Values{1}});

    map.erase_range(Range(50, 150));

    const std::vector<Entry> expected = {{0, 50, Values{1}}};
    EXPECT_EQ(Entries(map), expected);
}
