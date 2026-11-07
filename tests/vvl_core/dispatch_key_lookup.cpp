/*
 * Copyright (c) 2026 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

// Tests the dispatch-key registry directly, without a driver

#include "../framework/test_common.h"

#include <thread>
#include <vector>

#include "chassis/dispatch_object.h"

TEST(VvlCoreDispatchKeyLookup, ConcurrentLookupsOfUnknownKeys) {
    constexpr size_t kThreadCount = 8;
    constexpr size_t kLookupsPerThread = 1000;

    // A dispatchable handle points at an object whose first member is the loader's dispatch table pointer, and that pointer
    // is the lookup key. Give every fake handle a different key that nothing registered.
    struct FakeDispatchable {
        const void* dispatch_table;
    };
    std::vector<FakeDispatchable> objects(kThreadCount * kLookupsPerThread);
    for (auto& object : objects) {
        object.dispatch_table = &object;
    }

    // Lookups only hold a read lock, so a miss must not insert anything into the map
    std::vector<size_t> found(kThreadCount, 0);
    std::vector<std::thread> threads;
    for (size_t t = 0; t < kThreadCount; ++t) {
        threads.emplace_back([&, t] {
            for (size_t i = 0; i < kLookupsPerThread; ++i) {
                auto instance = reinterpret_cast<VkInstance>(&objects[t * kLookupsPerThread + i]);
                if (vvl::GetDispatchInstance(instance) != nullptr) {
                    ++found[t];
                }
            }
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }

    for (size_t t = 0; t < kThreadCount; ++t) {
        EXPECT_EQ(found[t], 0u);
    }
}
