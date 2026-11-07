/*
 * Copyright (c) 2026 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

// Regression tests for sparse_container::range_map algorithms that needed fixes in the past. Before vvl_core, they were only
// reached through image layout and memory binding tracking in API-level tests.

#include "../framework/test_common.h"

#include <optional>
#include <tuple>
#include <vector>

#include "containers/range_map.h"

namespace {
using Map = sparse_container::range_map<uint64_t, int>;
using Range = vvl::range<uint64_t>;
using Entry = std::tuple<uint64_t, uint64_t, int>;

std::vector<Entry> Entries(const Map& map) {
    std::vector<Entry> entries;
    for (const auto& [range, value] : map) {
        entries.emplace_back(range.begin, range.end, value);
    }
    return entries;
}

Map MakeMap(const std::vector<Entry>& entries) {
    Map map;
    for (const auto& [begin, end, value] : entries) {
        map.insert({Range(begin, end), value});
    }
    return map;
}
}  // namespace

TEST(VvlCoreRangeMap, SpliceMisalignedRanges) {
    // Only the intersection of the two maps is updated (#2793, #2910)
    Map to = MakeMap({{0, 10, 1}});
    const Map from = MakeMap({{5, 15, 2}});
    struct AddUpdater {
        void update(int& dst, const int& src) const { dst += src; }
        std::optional<int> insert(const int& src) const { return src; }
    };

    sparse_container::splice(to, from, AddUpdater{});

    const std::vector<Entry> expected = {{0, 5, 1}, {5, 10, 3}, {10, 15, 2}};
    EXPECT_EQ(Entries(to), expected);
}

TEST(VvlCoreRangeMap, EraseRangeTrimsEntries) {
    {
        Map map = MakeMap({{0, 10, 1}});
        map.erase_range(Range(2, 5));
        const std::vector<Entry> expected = {{0, 2, 1}, {5, 10, 1}};
        EXPECT_EQ(Entries(map), expected);
    }
    {
        Map map = MakeMap({{0, 10, 1}});
        map.erase_range(Range(0, 10));
        EXPECT_TRUE(map.empty());
    }
    {
        Map map = MakeMap({{0, 10, 1}});
        map.erase_range(Range(5, 20));
        const std::vector<Entry> expected = {{0, 5, 1}};
        EXPECT_EQ(Entries(map), expected);
    }
}

TEST(VvlCoreRangeMap, InfillUpdateRangePastLastEntry) {
    // The position hint is the last entry and the range lies after it, so the shortcut that steps to the next entry reaches
    // end() (425bb31b0)
    Map map = MakeMap({{0, 4, 1}});
    struct Ops {
        void infill(Map& map, const Map::iterator& pos, const Range& range) const { map.insert(pos, {range, 2}); }
        void update(const Map::iterator& pos) const { pos->second += 10; }
    };

    sparse_container::infill_update_range(map, map.begin(), Range(8, 12), Ops{});

    const std::vector<Entry> expected = {{0, 4, 1}, {8, 12, 2}};
    EXPECT_EQ(Entries(map), expected);
}

TEST(VvlCoreRangeMap, UpdateRangeValueAcrossGaps) {
    // prefer_dest only fills the gaps (0d4e65db4)
    {
        Map map = MakeMap({{2, 4, 1}});
        EXPECT_TRUE(sparse_container::update_range_value(map, Range(0, 6), 5, sparse_container::value_precedence::prefer_dest));
        const std::vector<Entry> expected = {{0, 2, 5}, {2, 4, 1}, {4, 6, 5}};
        EXPECT_EQ(Entries(map), expected);
    }
    // prefer_source overwrites the whole range
    {
        Map map = MakeMap({{2, 4, 1}});
        EXPECT_TRUE(sparse_container::update_range_value(map, Range(0, 6), 5, sparse_container::value_precedence::prefer_source));
        const std::vector<Entry> expected = {{0, 6, 5}};
        EXPECT_EQ(Entries(map), expected);
    }
}

TEST(VvlCoreRangeMap, ConsolidateMergesOnlyAdjacentEqualEntries) {
    Map map = MakeMap({{0, 2, 1}, {2, 4, 1}, {5, 6, 1}, {6, 8, 2}});

    sparse_container::consolidate(map);

    const std::vector<Entry> expected = {{0, 4, 1}, {5, 6, 1}, {6, 8, 2}};
    EXPECT_EQ(Entries(map), expected);
}
