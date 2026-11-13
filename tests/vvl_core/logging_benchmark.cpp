/*
 * Copyright (c) 2026 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

// On-demand benchmarks of message delivery, disabled in normal runs:
//   vk_layer_validation_tests --gtest_filter=VvlCoreLoggingBenchmark.* --gtest_also_run_disabled_tests
// Each prints one "[ BENCH    ]" line with the median of several repeats.

#include "../framework/test_common.h"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cinttypes>
#include <cstdio>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "error_message/error_location.h"
#include "error_message/logging.h"
#include "utils/cast_utils.h"

namespace {

constexpr int kRepeats = 5;
constexpr uint32_t kVuidCount = 8;
const char* const kVuids[kVuidCount] = {"VUID-Bench-0", "VUID-Bench-1", "VUID-Bench-2", "VUID-Bench-3",
                                        "VUID-Bench-4", "VUID-Bench-5", "VUID-Bench-6", "VUID-Bench-7"};

double Median(std::vector<double> values) {
    std::sort(values.begin(), values.end());
    return values[values.size() / 2];
}

}  // namespace

class VvlCoreLoggingBenchmark : public testing::Test {
  protected:
    void SetUp() override {
        VkDebugUtilsMessengerCreateInfoEXT create_info = vku::InitStructHelper();
        create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
        create_info.pfnUserCallback = Record;
        create_info.pUserData = this;
        VkDebugUtilsMessengerEXT messenger = VK_NULL_HANDLE;
        LayerCreateMessengerCallback(&debug_report_, false, &create_info, &messenger);
        debug_report_.duplicate_message_limit = 0;  // every message is formatted and delivered

        for (uint64_t i = 0; i < kBufferCount; ++i) {
            buffers_[i] = CastFromUint64<VkBuffer>(0x1000 + i);
            Name(buffers_[i], "buffer " + std::to_string(i));
        }
    }

    // Like an application callback: copies the text it receives
    static VKAPI_ATTR VkBool32 VKAPI_CALL Record(VkDebugUtilsMessageSeverityFlagBitsEXT, VkDebugUtilsMessageTypeFlagsEXT,
                                                 const VkDebugUtilsMessengerCallbackDataEXT* data, void* user_data) {
        auto* self = static_cast<VvlCoreLoggingBenchmark*>(user_data);
        std::lock_guard<std::mutex> lock(self->last_message_mutex_);
        self->last_message_.assign(data->pMessage);
        self->delivered_.fetch_add(1, std::memory_order_relaxed);
        return VK_FALSE;
    }

    void Name(VkBuffer buffer, const std::string& name) {
        VkDebugUtilsObjectNameInfoEXT name_info = vku::InitStructHelper();
        name_info.objectType = VK_OBJECT_TYPE_BUFFER;
        name_info.objectHandle = CastToUint64(buffer);
        name_info.pObjectName = name.c_str();
        debug_report_.SetUtilsObjectName(&name_info);
    }

    void LogOne(uint32_t i) {
        const VkBuffer buffer = buffers_[i % kBufferCount];
        logger_.LogError(kVuids[i % kVuidCount], buffer, loc_.dot(vvl::Field::size),
                         "{} has size {}, which exceeds {}"
                         ".",
                         logger_.Handle(buffer), i, uint64_t{4096});
    }

    static constexpr uint64_t kBufferCount = 16;
    DebugReport debug_report_;
    Logger logger_{&debug_report_};
    VkBuffer buffers_[kBufferCount] = {};
    const Location loc_{vvl::Func::vkCreateBuffer, vvl::Field::pCreateInfo};
    std::mutex last_message_mutex_;
    std::string last_message_;
    std::atomic<uint64_t> delivered_{0};
};

TEST_F(VvlCoreLoggingBenchmark, DISABLED_SingleThread) {
    constexpr uint32_t kMessages = 20000;
    std::vector<double> ns_per_message;
    for (int repeat = 0; repeat < kRepeats; ++repeat) {
        delivered_ = 0;
        const auto start = std::chrono::steady_clock::now();
        for (uint32_t i = 0; i < kMessages; ++i) {
            LogOne(i);
        }
        const auto elapsed = std::chrono::duration<double, std::nano>(std::chrono::steady_clock::now() - start).count();
        ASSERT_EQ(delivered_.load(), kMessages);
        ns_per_message.push_back(elapsed / kMessages);
    }
    std::printf("[ BENCH    ] single_thread messages=%u median_ns_per_message=%.1f\n", kMessages, Median(ns_per_message));
}

// Many threads report errors at once while other threads name objects and record debug labels, as an engine with
// validation errors would. Reports message throughput and, separately, label throughput (labels take the same lock).
TEST_F(VvlCoreLoggingBenchmark, DISABLED_Storm) {
    const uint32_t thread_count = std::max(2u, std::thread::hardware_concurrency());
    constexpr uint32_t kMessagesPerThread = 4000;
    std::vector<double> messages_per_second, labels_per_second;
    for (int repeat = 0; repeat < kRepeats; ++repeat) {
        delivered_ = 0;
        std::atomic<bool> go{false}, stop{false};
        std::atomic<uint64_t> labels{0};
        std::vector<std::thread> threads;
        for (uint32_t t = 0; t < thread_count; ++t) {
            threads.emplace_back([&, t] {
                while (!go) std::this_thread::yield();
                for (uint32_t i = 0; i < kMessagesPerThread; ++i) LogOne(t * kMessagesPerThread + i);
            });
        }
        std::thread naming([&] {
            while (!go) std::this_thread::yield();
            for (uint64_t i = 0; !stop; ++i) Name(CastFromUint64<VkBuffer>(0x9000 + (i % 64)), "renamed " + std::to_string(i));
        });
        std::thread labelling([&] {
            const VkCommandBuffer command_buffer = CastFromUint64<VkCommandBuffer>(0x7000);
            VkDebugUtilsLabelEXT label = vku::InitStructHelper();
            label.pLabelName = "frame";
            while (!go) std::this_thread::yield();
            while (!stop) {
                debug_report_.BeginCmdDebugUtilsLabel(command_buffer, &label);
                debug_report_.EndCmdDebugUtilsLabel(command_buffer);
                labels.fetch_add(1, std::memory_order_relaxed);
            }
        });
        const auto start = std::chrono::steady_clock::now();
        go = true;
        for (auto& thread : threads) thread.join();
        const double seconds = std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
        const uint64_t label_count = labels.load();
        stop = true;
        naming.join();
        labelling.join();
        ASSERT_EQ(delivered_.load(), uint64_t{thread_count} * kMessagesPerThread);
        messages_per_second.push_back(static_cast<double>(delivered_.load()) / seconds);
        labels_per_second.push_back(static_cast<double>(label_count) / seconds);
    }
    std::printf("[ BENCH    ] storm threads=%u messages=%u median_messages_per_second=%.0f median_labels_per_second=%.0f\n",
                thread_count, thread_count * kMessagesPerThread, Median(messages_per_second), Median(labels_per_second));
}
