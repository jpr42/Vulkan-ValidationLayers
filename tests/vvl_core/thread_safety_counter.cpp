/*
 * Copyright (c) 2026 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

// Tests threadsafety::Counter directly, without a device or driver. The API-level collision tests (see
// unit/threading.cpp) need a real driver and depend on two threads happening to overlap, so they are skipped on the
// mock ICD. Here the overlap is forced, so the result is deterministic and the test also runs under thread sanitizer.

#include "../framework/test_common.h"

#include <atomic>
#include <future>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "error_message/logging.h"
#include "thread_tracker/thread_safety_validation.h"
#include "utils/cast_utils.h"

class VvlCoreThreading : public testing::Test {
  protected:
    void SetUp() override {
        VkDebugUtilsMessengerCreateInfoEXT create_info = vku::InitStructHelper();
        create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                  VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        create_info.pfnUserCallback = RecordVuid;
        create_info.pUserData = this;
        VkDebugUtilsMessengerEXT messenger = VK_NULL_HANDLE;
        LayerCreateMessengerCallback(&debug_report_, false, &create_info, &messenger);

        counter_.Init(kVulkanObjectTypeBuffer, &logger_);
        counter_.CreateObject(buffer_);
    }

    std::vector<std::string> Vuids() {
        std::lock_guard<std::mutex> lock(vuids_mutex_);
        return vuids_;
    }

    // Called from whichever thread reports the error
    static VKAPI_ATTR VkBool32 VKAPI_CALL RecordVuid(VkDebugUtilsMessageSeverityFlagBitsEXT, VkDebugUtilsMessageTypeFlagsEXT,
                                                     const VkDebugUtilsMessengerCallbackDataEXT* callback_data, void* user_data) {
        auto* test = static_cast<VvlCoreThreading*>(user_data);
        std::lock_guard<std::mutex> lock(test->vuids_mutex_);
        test->vuids_.emplace_back(callback_data->pMessageIdName);
        return VK_FALSE;
    }

    DebugReport debug_report_;
    Logger logger_{&debug_report_};
    threadsafety::Counter<VkBuffer> counter_;
    // Never dereferenced, so any non-null value works as a handle
    const VkBuffer buffer_ = CastFromUint64<VkBuffer>(0x1234);
    const Location fill_loc_{vvl::Func::vkCmdFillBuffer};
    const Location copy_loc_{vvl::Func::vkCmdCopyBuffer};

    std::mutex vuids_mutex_;
    std::vector<std::string> vuids_;
};

TEST_F(VvlCoreThreading, WriteWriteCollision) {
    std::promise<void> other_writing;
    std::promise<void> main_done;
    auto other_writing_future = other_writing.get_future();
    auto main_done_future = main_done.get_future();

    std::thread other([&] {
        counter_.StartWrite(buffer_, fill_loc_);
        other_writing.set_value();
        main_done_future.wait();
        counter_.FinishWrite(buffer_, fill_loc_);
    });

    // The other thread is now inside its write, so this one must collide
    other_writing_future.wait();
    counter_.StartWrite(buffer_, copy_loc_);
    counter_.FinishWrite(buffer_, copy_loc_);
    main_done.set_value();
    other.join();

    EXPECT_EQ(Vuids(), std::vector<std::string>{"UNASSIGNED-Threading-MultipleThreads-Write"});
}

TEST_F(VvlCoreThreading, ReadWriteCollision) {
    std::promise<void> other_writing;
    std::promise<void> main_done;
    auto other_writing_future = other_writing.get_future();
    auto main_done_future = main_done.get_future();

    std::thread other([&] {
        counter_.StartWrite(buffer_, fill_loc_);
        other_writing.set_value();
        main_done_future.wait();
        counter_.FinishWrite(buffer_, fill_loc_);
    });

    other_writing_future.wait();
    counter_.StartRead(buffer_, copy_loc_);
    counter_.FinishRead(buffer_, copy_loc_);
    main_done.set_value();
    other.join();

    EXPECT_EQ(Vuids(), std::vector<std::string>{"UNASSIGNED-Threading-MultipleThreads-Read"});
}

TEST_F(VvlCoreThreading, ConcurrentReads) {
    constexpr uint32_t kThreadCount = 8;
    std::atomic<uint32_t> readers_inside{0};

    std::vector<std::thread> threads;
    for (uint32_t i = 0; i < kThreadCount; ++i) {
        threads.emplace_back([&] {
            counter_.StartRead(buffer_, copy_loc_);
            // Wait until every thread holds its read, so all reads overlap
            readers_inside.fetch_add(1);
            while (readers_inside.load() < kThreadCount) {
                std::this_thread::yield();
            }
            counter_.FinishRead(buffer_, copy_loc_);
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }

    EXPECT_TRUE(Vuids().empty());
}

TEST_F(VvlCoreThreading, SameThreadNestedUse) {
    // One call can use an object more than once, e.g. a write and then a read of the same handle
    counter_.StartWrite(buffer_, fill_loc_);
    counter_.StartRead(buffer_, fill_loc_);
    counter_.FinishRead(buffer_, fill_loc_);
    counter_.FinishWrite(buffer_, fill_loc_);

    EXPECT_TRUE(Vuids().empty());
}
