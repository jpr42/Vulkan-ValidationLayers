/*
 * Copyright (c) 2026 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

// Tests object_lifetimes::Tracker poison tracking directly, without a device or driver

#include "../framework/test_common.h"

#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <future>
#include <thread>

#include "error_message/logging.h"
#include "object_tracker/object_lifetime_validation.h"
#include "utils/cast_utils.h"

class VvlCoreObjectLifetimes : public testing::Test {
  protected:
    // Handles are never dereferenced, so any unique non-null value works
    template <typename T>
    T Create(uint64_t value, VulkanObjectType type) {
        const T handle = CastFromUint64<T>(value);
        tracker_.CreateObject(handle, type, nullptr, loc_, device_);
        return handle;
    }

    bool IsPoisoned(VulkanTypedHandle object) const {
        auto state = tracker_.GetObjectState(object);
        return state && (state->status_flags & object_lifetimes::kObjectStatusPoisoned) != 0;
    }

    DebugReport debug_report_;
    object_lifetimes::Tracker tracker_{&debug_report_};
    const Location loc_{vvl::Func::vkCreatePipelineLayout};
    const VkDevice device_ = reinterpret_cast<VkDevice>(uintptr_t{1});
};

TEST_F(VvlCoreObjectLifetimes, DestroyingPoisoneeUnlinksIt) {
    // vkCreatePipelineLayout registers its set layouts as poisoners of the new pipeline layout
    VkDescriptorSetLayout set_layout = Create<VkDescriptorSetLayout>(0x10, kVulkanObjectTypeDescriptorSetLayout);
    VkPipelineLayout pipeline_layout = Create<VkPipelineLayout>(0x20, kVulkanObjectTypePipelineLayout);
    const VulkanTypedHandle pipeline_layout_handle(pipeline_layout, kVulkanObjectTypePipelineLayout);
    tracker_.RegisterPoisonPairs(pipeline_layout_handle, vvl::span<VkDescriptorSetLayout>(&set_layout, 1),
                                 kVulkanObjectTypeDescriptorSetLayout);

    // Destroying the pipeline layout must remove it from the set layout's list, or the list grows for as long as the set
    // layout lives
    tracker_.RecordDestroyObject(pipeline_layout, kVulkanObjectTypePipelineLayout, loc_);

    auto set_layout_state = tracker_.GetObjectState(VulkanTypedHandle(set_layout, kVulkanObjectTypeDescriptorSetLayout));
    ASSERT_NE(set_layout_state, nullptr);
    EXPECT_TRUE(set_layout_state->objects_to_poison.empty());
}

TEST_F(VvlCoreObjectLifetimes, PoisonPropagatesDownChain) {
    VkPipelineLayout layout = Create<VkPipelineLayout>(0x30, kVulkanObjectTypePipelineLayout);
    VkPipeline library = Create<VkPipeline>(0x31, kVulkanObjectTypePipeline);
    VkPipeline pipeline = Create<VkPipeline>(0x32, kVulkanObjectTypePipeline);
    const VulkanTypedHandle layout_handle(layout, kVulkanObjectTypePipelineLayout);
    const VulkanTypedHandle library_handle(library, kVulkanObjectTypePipeline);
    const VulkanTypedHandle pipeline_handle(pipeline, kVulkanObjectTypePipeline);
    tracker_.RegisterPoisonPair(library_handle, layout_handle);
    tracker_.RegisterPoisonPair(pipeline_handle, library_handle);

    tracker_.RecordDestroyObject(layout, kVulkanObjectTypePipelineLayout, loc_);

    EXPECT_TRUE(IsPoisoned(library_handle));
    EXPECT_TRUE(IsPoisoned(pipeline_handle));
    // The chain records how the poison got here: the destroyed object first, then each object it passed through
    auto pipeline_state = tracker_.GetObjectState(pipeline_handle);
    ASSERT_NE(pipeline_state, nullptr);
    ASSERT_EQ(pipeline_state->poison_chain.size(), 2u);
    EXPECT_EQ(pipeline_state->poison_chain[0], layout_handle);
    EXPECT_EQ(pipeline_state->poison_chain[1], library_handle);
}

TEST_F(VvlCoreObjectLifetimes, ConcurrentDestroyOfLinkedObjects) {
    // Destroying a pipeline layout and a pipeline that uses it on two threads is valid. Each destroy used to hold its own
    // object's lock while waiting for the other object's lock, which could deadlock.
    constexpr uint64_t kIterations = 2000;

    auto run = std::async(std::launch::async, [&] {
        for (uint64_t i = 0; i < kIterations; ++i) {
            VkPipelineLayout layout = Create<VkPipelineLayout>(0x1000 + i, kVulkanObjectTypePipelineLayout);
            VkPipeline pipeline = Create<VkPipeline>(0x100000 + i, kVulkanObjectTypePipeline);
            tracker_.RegisterPoisonPair(VulkanTypedHandle(pipeline, kVulkanObjectTypePipeline),
                                        VulkanTypedHandle(layout, kVulkanObjectTypePipelineLayout));

            // Start both destroys at the same time
            std::atomic<int> ready{0};
            auto destroy = [&](auto handle, VulkanObjectType type) {
                ready.fetch_add(1);
                while (ready.load() < 2) {
                    std::this_thread::yield();
                }
                tracker_.RecordDestroyObject(handle, type, loc_);
            };
            std::thread other(destroy, layout, kVulkanObjectTypePipelineLayout);
            destroy(pipeline, kVulkanObjectTypePipeline);
            other.join();
        }
    });

    if (run.wait_for(std::chrono::seconds(60)) != std::future_status::ready) {
        // The threads cannot be joined, so stop here with a clear message instead of hanging
        std::fprintf(stderr, "VvlCoreObjectLifetimes.ConcurrentDestroyOfLinkedObjects deadlocked\n");
        std::abort();
    }
    run.get();
}
