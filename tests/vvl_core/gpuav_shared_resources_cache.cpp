/*
 * Copyright (c) 2026 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

// Tests gpuav::vko::SharedResourcesCache directly, without a device

#include "../framework/test_common.h"

#include <atomic>
#include <thread>
#include <vector>

#include "gpuav/resources/gpuav_vulkan_objects.h"

namespace {
std::atomic<int> probe_constructed{0};
std::atomic<int> probe_destroyed{0};

struct Probe {
    Probe() { probe_constructed.fetch_add(1); }
    ~Probe() { probe_destroyed.fetch_add(1); }
};
}  // namespace

TEST(VvlCoreGpuavSharedResourcesCache, ConcurrentGetOrCreateConstructsOnce) {
    probe_constructed = 0;
    probe_destroyed = 0;
    gpuav::vko::SharedResourcesCache<true> cache;

    // Start every thread at the same time, so several of them find the cache empty
    constexpr size_t kThreadCount = 16;
    std::atomic<size_t> ready{0};
    std::vector<Probe*> results(kThreadCount, nullptr);
    std::vector<std::thread> threads;
    for (size_t t = 0; t < kThreadCount; ++t) {
        threads.emplace_back([&, t] {
            ready.fetch_add(1);
            while (ready.load() < kThreadCount) {
                std::this_thread::yield();
            }
            results[t] = &cache.GetOrCreate<Probe>();
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }

    // A second construction would have been leaked, and its side effects (e.g. GPU allocations) repeated
    EXPECT_EQ(probe_constructed.load(), 1);
    for (Probe* result : results) {
        EXPECT_EQ(result, results[0]);
    }

    cache.Clear();
    EXPECT_EQ(probe_destroyed.load(), 1);
}
