/*
 * Copyright (c) 2026 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

// Applications log, name objects and push labels from many threads at once. Run under TSan (CI runs *Threading.* there)
// to check the logging locks; under ASan the callback's reads of names and labels check their lifetime.

#include "../framework/test_common.h"

#include <atomic>
#include <string>
#include <thread>
#include <vector>

#include "error_message/error_location.h"
#include "error_message/logging.h"
#include "utils/cast_utils.h"

namespace {

std::atomic<uint32_t> delivered{0};
std::atomic<size_t> copied_bytes{0};

// Reads everything the layer hands over, the way an application callback may
VKAPI_ATTR VkBool32 VKAPI_CALL CopyEverything(VkDebugUtilsMessageSeverityFlagBitsEXT, VkDebugUtilsMessageTypeFlagsEXT,
                                              const VkDebugUtilsMessengerCallbackDataEXT* data, void*) {
    std::string copy = data->pMessage;
    for (uint32_t i = 0; i < data->objectCount; ++i) {
        copy += data->pObjects[i].pObjectName ? data->pObjects[i].pObjectName : "";
    }
    for (uint32_t i = 0; i < data->queueLabelCount; ++i) {
        copy += data->pQueueLabels[i].pLabelName;
    }
    for (uint32_t i = 0; i < data->cmdBufLabelCount; ++i) {
        copy += data->pCmdBufLabels[i].pLabelName;
    }
    copied_bytes += copy.size();
    ++delivered;
    return VK_FALSE;
}

}  // namespace

TEST(VvlCoreThreading, LoggingWhileNamingAndLabeling) {
    DebugReport debug_report;
    Logger logger(&debug_report);
    VkDebugUtilsMessengerCreateInfoEXT create_info = vku::InitStructHelper();
    create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
    create_info.pfnUserCallback = CopyEverything;
    VkDebugUtilsMessengerEXT messenger = VK_NULL_HANDLE;
    ASSERT_EQ(LayerCreateMessengerCallback(&debug_report, false, &create_info, &messenger), VK_SUCCESS);
    delivered = 0;

    // Never dereferenced, so any non-null values work as handles
    const VkBuffer buffer = CastFromUint64<VkBuffer>(0x1000);
    const VkQueue queue = CastFromUint64<VkQueue>(0x2000);
    const VkCommandBuffer command_buffer = CastFromUint64<VkCommandBuffer>(0x3000);

    constexpr uint32_t kLoggingThreads = 4;
    constexpr uint32_t kMessagesPerThread = 500;
    std::atomic<bool> logging_done{false};
    std::vector<std::thread> threads;
    for (uint32_t t = 0; t < kLoggingThreads; ++t) {
        threads.emplace_back([&, t] {
            const Location loc(vvl::Func::vkQueueSubmit, vvl::Field::pSubmits, t);
            LogObjectList objects(queue, command_buffer);
            objects.add(buffer);
            for (uint32_t i = 0; i < kMessagesPerThread; ++i) {
                logger.LogError("VUID-Test-threading", objects, loc.dot(vvl::Field::pCommandBuffers), "{} uses {} ({})",
                                logger.FormatHandle(command_buffer), logger.FormatHandle(buffer), i);
            }
        });
    }
    // Names change while messages read them
    threads.emplace_back([&] {
        for (uint32_t i = 0; !logging_done; ++i) {
            VkDebugUtilsObjectNameInfoEXT utils_name = vku::InitStructHelper();
            utils_name.objectType = VK_OBJECT_TYPE_BUFFER;
            utils_name.objectHandle = CastToUint64(buffer);
            const std::string name = "buffer " + std::to_string(i);
            utils_name.pObjectName = name.c_str();
            debug_report.SetUtilsObjectName(&utils_name);

            VkDebugMarkerObjectNameInfoEXT marker_name = vku::InitStructHelper();
            marker_name.objectType = VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT;
            marker_name.object = CastToUint64(command_buffer);
            marker_name.pObjectName = name.c_str();
            debug_report.SetMarkerObjectName(&marker_name);

            if (i % 8 == 0) {
                debug_report.EraseObjectName(CastToUint64(buffer));
            }
        }
    });
    // Labels change while messages export them
    threads.emplace_back([&] {
        VkDebugUtilsLabelEXT label = vku::InitStructHelper();
        label.pLabelName = "region";
        while (!logging_done) {
            debug_report.BeginQueueDebugUtilsLabel(queue, &label);
            debug_report.BeginCmdDebugUtilsLabel(command_buffer, &label);
            debug_report.InsertQueueDebugUtilsLabel(queue, &label);
            debug_report.EndCmdDebugUtilsLabel(command_buffer);
            debug_report.EndQueueDebugUtilsLabel(queue);
        }
    });

    for (uint32_t t = 0; t < kLoggingThreads; ++t) {
        threads[t].join();
    }
    logging_done = true;
    for (uint32_t t = kLoggingThreads; t < threads.size(); ++t) {
        threads[t].join();
    }

    EXPECT_EQ(delivered.load(), kLoggingThreads * kMessagesPerThread);
    EXPECT_GT(copied_bytes.load(), 0u);
}
