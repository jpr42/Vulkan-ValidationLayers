/*
 * Copyright (c) 2026 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

// Tests vvl::HandleWrapper directly. Handles are never dereferenced, so fake values are enough. The id map is shared by the
// whole process, so every test erases what it wraps.

#include "../framework/test_common.h"

#include <thread>
#include <vector>

#include "chassis/dispatch_object.h"
#include "utils/cast_utils.h"

class VvlCoreHandleWrapper : public testing::Test {
  protected:
    DebugReport debug_report_;
    vvl::HandleWrapper wrapper_{&debug_report_};
    const VkBuffer driver_buffer_ = CastFromUint64<VkBuffer>(0xb0ff);
    const VkBuffer other_driver_buffer_ = CastFromUint64<VkBuffer>(0xb1ff);
};

TEST_F(VvlCoreHandleWrapper, WrapUnwrapErase) {
    const VkBuffer wrapped = wrapper_.WrapNew(driver_buffer_);
    EXPECT_NE(wrapped, VK_NULL_HANDLE);
    EXPECT_NE(wrapped, driver_buffer_);
    EXPECT_EQ(wrapper_.Unwrap(wrapped), driver_buffer_);
    EXPECT_EQ(wrapper_.Find(wrapped), driver_buffer_);

    EXPECT_EQ(wrapper_.Erase(wrapped), driver_buffer_);
    // Once erased, the id no longer maps to anything
    EXPECT_EQ(wrapper_.Unwrap(wrapped), VK_NULL_HANDLE);
}

TEST_F(VvlCoreHandleWrapper, NullHandle) {
    EXPECT_EQ(wrapper_.WrapNew(VkBuffer(VK_NULL_HANDLE)), VK_NULL_HANDLE);
    EXPECT_EQ(wrapper_.Unwrap(VkBuffer(VK_NULL_HANDLE)), VK_NULL_HANDLE);
}

TEST_F(VvlCoreHandleWrapper, UniqueIdsForSameDriverHandle) {
    // Some drivers return the same handle value for different objects, so each wrap gets its own id
    const VkBuffer first = wrapper_.WrapNew(driver_buffer_);
    const VkBuffer second = wrapper_.WrapNew(driver_buffer_);
    EXPECT_NE(first, second);
    EXPECT_EQ(wrapper_.Unwrap(first), driver_buffer_);
    EXPECT_EQ(wrapper_.Unwrap(second), driver_buffer_);
    wrapper_.Erase(first);
    wrapper_.Erase(second);
}

TEST_F(VvlCoreHandleWrapper, Passthrough) {
    // Handles wrapped before passthrough was turned on (e.g. by the instance) still translate
    const VkBuffer wrapped = wrapper_.WrapNew(driver_buffer_);

    wrapper_.passthrough_handles = true;
    EXPECT_EQ(wrapper_.WrapNew(other_driver_buffer_), other_driver_buffer_);
    EXPECT_EQ(wrapper_.Unwrap(other_driver_buffer_), other_driver_buffer_);
    EXPECT_EQ(wrapper_.Unwrap(wrapped), driver_buffer_);

    wrapper_.passthrough_handles = false;
    EXPECT_EQ(wrapper_.Unwrap(other_driver_buffer_), VK_NULL_HANDLE);
    wrapper_.Erase(wrapped);
}

TEST_F(VvlCoreHandleWrapper, Replace) {
    const VkBuffer wrapped = wrapper_.WrapNew(driver_buffer_);
    EXPECT_EQ(wrapper_.Replace(wrapped, other_driver_buffer_), driver_buffer_);
    EXPECT_EQ(wrapper_.Unwrap(wrapped), other_driver_buffer_);
    wrapper_.Erase(wrapped);
}

TEST_F(VvlCoreHandleWrapper, SharedBetweenWrappers) {
    // An instance and its devices each have a wrapper, and a handle wrapped by one can be unwrapped by another
    vvl::HandleWrapper other_wrapper(&debug_report_);
    const VkBuffer wrapped = wrapper_.WrapNew(driver_buffer_);
    EXPECT_EQ(other_wrapper.Unwrap(wrapped), driver_buffer_);
    wrapper_.Erase(wrapped);
}

TEST_F(VvlCoreHandleWrapper, ConcurrentUse) {
    constexpr uint64_t kThreadCount = 8;
    constexpr uint64_t kHandlesPerThread = 1000;

    std::vector<uint64_t> mismatches(kThreadCount, 0);
    std::vector<std::thread> threads;
    for (uint64_t t = 0; t < kThreadCount; ++t) {
        threads.emplace_back([&, t] {
            for (uint64_t i = 0; i < kHandlesPerThread; ++i) {
                const VkBuffer driver = CastFromUint64<VkBuffer>(0x10000 + t * kHandlesPerThread + i);
                const VkBuffer wrapped = wrapper_.WrapNew(driver);
                if (wrapper_.Unwrap(wrapped) != driver || wrapper_.Erase(wrapped) != driver) {
                    ++mismatches[t];
                }
            }
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }

    for (uint64_t t = 0; t < kThreadCount; ++t) {
        EXPECT_EQ(mismatches[t], 0u);
    }
}
