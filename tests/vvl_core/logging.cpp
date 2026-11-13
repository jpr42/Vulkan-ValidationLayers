/*
 * Copyright (c) 2026 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

// Pins the exact text of delivered validation messages, without a device or driver, so a rewrite of the logging path can
// prove it changes nothing an application sees.

#include "../framework/test_common.h"

#include <stdexcept>
#include <string>
#include <vector>

#include "error_message/error_location.h"
#include "error_message/logging.h"
#include "utils/cast_utils.h"
#include "utils/hash_util.h"

#include "allocation_counter.h"

namespace {

struct Delivered {
    std::string vuid;
    std::string message;
    std::vector<std::string> object_names;  // "" when the object has no name
};

// Counts how many times it is formatted
struct CountsFormatting {
    int* count;
};

}  // namespace

template <>
struct VVL_FMT_NS::formatter<CountsFormatting> {
    constexpr auto parse(VVL_FMT_NS::format_parse_context& ctx) { return ctx.begin(); }
    template <typename FormatContext>
    auto format(const CountsFormatting& value, FormatContext& ctx) const {
        ++*value.count;
        return VVL_FMT_NS::format_to(ctx.out(), "counted");
    }
};

class VvlCoreLogging : public testing::Test {
  protected:
    void SetUp() override {
        VkDebugUtilsMessengerCreateInfoEXT create_info = vku::InitStructHelper();
        create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
                                      VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                      VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
        create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                  VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        create_info.pfnUserCallback = Record;
        create_info.pUserData = this;
        VkDebugUtilsMessengerEXT messenger = VK_NULL_HANDLE;
        ASSERT_EQ(LayerCreateMessengerCallback(&debug_report_, false, &create_info, &messenger), VK_SUCCESS);
    }

    static VKAPI_ATTR VkBool32 VKAPI_CALL Record(VkDebugUtilsMessageSeverityFlagBitsEXT, VkDebugUtilsMessageTypeFlagsEXT,
                                                 const VkDebugUtilsMessengerCallbackDataEXT* data, void* user_data) {
        auto* self = static_cast<VvlCoreLogging*>(user_data);
        ++self->delivered_count_;
        if (!self->record_text_) {
            return VK_FALSE;  // counting allocations: the test's own copies must not be counted
        }
        Delivered delivered{data->pMessageIdName, data->pMessage, {}};
        for (uint32_t i = 0; i < data->objectCount; ++i) {
            delivered.object_names.emplace_back(data->pObjects[i].pObjectName ? data->pObjects[i].pObjectName : "");
        }
        self->delivered_.push_back(std::move(delivered));
        return VK_FALSE;
    }

    // Checks that every one of the `count` delivered messages has the expected text
    void ExpectMessages(size_t count, const std::string& expected) const {
        ASSERT_EQ(delivered_.size(), count);
        for (size_t i = 0; i < count; ++i) {
            EXPECT_EQ(delivered_[i].message, expected) << "message " << i;
        }
    }

    DebugReport debug_report_;
    Logger logger_{&debug_report_};
    std::vector<Delivered> delivered_;
    uint32_t delivered_count_ = 0;
    bool record_text_ = true;
    // Never dereferenced, so any non-null values work as handles
    const VkBuffer buffer_ = CastFromUint64<VkBuffer>(0x1234);
};

TEST_F(VvlCoreLogging, PlainMessage) {
    const Location loc(vvl::Func::vkCreateBuffer, vvl::Field::pCreateInfo);
    logger_.LogError("VUID-Test-plain", buffer_, loc.dot(vvl::Field::size), "is {}.", 0u);

    ExpectMessages(1, "vkCreateBuffer(): pCreateInfo->size is 0.");
    EXPECT_EQ(delivered_[0].vuid, "VUID-Test-plain");
}

TEST_F(VvlCoreLogging, SpecTextIsAppendedForKnownVuids) {
    const Location loc(vvl::Func::vkCreateBuffer, vvl::Field::pCreateInfo);
    logger_.LogError("VUID-VkBufferCreateInfo-size-00912", buffer_, loc.dot(vvl::Field::size), "is {}", 0u);

    // No period is added after a trailing digit, so the number does not read like a floating point value
    ExpectMessages(1,
                   "vkCreateBuffer(): pCreateInfo->size is 0\n"
                   "The Vulkan spec states: size must be greater than 0 "
                   "(https://docs.vulkan.org/spec/latest/chapters/resources.html#VUID-VkBufferCreateInfo-size-00912)");
}

TEST_F(VvlCoreLogging, SpecTextAddsAMissingPeriod) {
    logger_.LogError("VUID-VkBufferCreateInfo-size-00912", buffer_, Location(vvl::Func::vkCreateBuffer), "size is zero");

    ExpectMessages(1,
                   "vkCreateBuffer(): size is zero.\n"
                   "The Vulkan spec states: size must be greater than 0 "
                   "(https://docs.vulkan.org/spec/latest/chapters/resources.html#VUID-VkBufferCreateInfo-size-00912)");
}

TEST_F(VvlCoreLogging, HandleWithoutName) {
    logger_.LogError("VUID-Test-handle", buffer_, Location(vvl::Func::vkDestroyBuffer), "{} is in use.", logger_.Handle(buffer_));
    logger_.LogError("VUID-Test-handle", buffer_, Location(vvl::Func::vkDestroyBuffer), "{} is in use.",
                     logger_.FormatHandle(buffer_));

    ExpectMessages(2, "vkDestroyBuffer(): VkBuffer 0x1234 is in use.");
    EXPECT_EQ(delivered_[1].object_names, std::vector<std::string>{""});
}

TEST_F(VvlCoreLogging, HandleWithDebugUtilsName) {
    VkDebugUtilsObjectNameInfoEXT name_info = vku::InitStructHelper();
    name_info.objectType = VK_OBJECT_TYPE_BUFFER;
    name_info.objectHandle = CastToUint64(buffer_);
    name_info.pObjectName = "vertices";
    debug_report_.SetUtilsObjectName(&name_info);

    logger_.LogError("VUID-Test-handle", buffer_, Location(vvl::Func::vkDestroyBuffer), "{} is in use.", logger_.Handle(buffer_));
    logger_.LogError("VUID-Test-handle", buffer_, Location(vvl::Func::vkDestroyBuffer), "{} is in use.",
                     logger_.FormatHandle(buffer_));

    ExpectMessages(2, "vkDestroyBuffer(): VkBuffer 0x1234[vertices] is in use.");
    EXPECT_EQ(delivered_[1].object_names, std::vector<std::string>{"vertices"});
}

TEST_F(VvlCoreLogging, HandleWithDebugMarkerName) {
    VkDebugMarkerObjectNameInfoEXT name_info = vku::InitStructHelper();
    name_info.objectType = VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT;
    name_info.object = CastToUint64(buffer_);
    name_info.pObjectName = "indices";
    debug_report_.SetMarkerObjectName(&name_info);

    logger_.LogError("VUID-Test-handle", buffer_, Location(vvl::Func::vkDestroyBuffer), "{} is in use.", logger_.Handle(buffer_));
    logger_.LogError("VUID-Test-handle", buffer_, Location(vvl::Func::vkDestroyBuffer), "{} is in use.",
                     logger_.FormatHandle(buffer_));

    ExpectMessages(2, "vkDestroyBuffer(): VkBuffer 0x1234[indices] is in use.");
    EXPECT_EQ(delivered_[1].object_names, std::vector<std::string>{"indices"});
}

TEST_F(VvlCoreLogging, LocationFields) {
    // Each Location points at its parent, so every level of the chain must outlive the last one
    const Location loc(vvl::Func::vkCreateImage, vvl::Field::pCreateInfo);
    const Location extent_loc = loc.dot(vvl::Field::extent);
    const Location field_loc = extent_loc.dot(vvl::Field::width);
    EXPECT_EQ(field_loc.Fields(), "pCreateInfo->extent.width");

    logger_.LogError("VUID-Test-location", buffer_, field_loc, "({}) is too large.", 70000u);

    ExpectMessages(1, "vkCreateImage(): pCreateInfo->extent.width (70000) is too large.");
}

TEST_F(VvlCoreLogging, LocationFieldsInsideTheMessage) {
    const Location regions_loc(vvl::Func::vkCmdCopyBuffer, vvl::Field::pRegions, 2);
    const Location loc = regions_loc.dot(vvl::Field::size);
    logger_.LogError("VUID-Test-location", buffer_, Location(vvl::Func::vkCmdCopyBuffer), "{} is 0.", loc);
    logger_.LogError("VUID-Test-location", buffer_, Location(vvl::Func::vkCmdCopyBuffer), "{} is 0.", loc.Fields());

    ExpectMessages(2, "vkCmdCopyBuffer(): pRegions[2].size is 0.");
}

TEST_F(VvlCoreLogging, Flags) {
    logger_.LogError("VUID-Test-flags", buffer_, Location(vvl::Func::vkCreateBuffer), "stages {}, none {}, two {}.",
                     vvl::Flags::ShaderStageFlags(VK_SHADER_STAGE_ALL_GRAPHICS), vvl::Flags::ShaderStageFlags(0),
                     vvl::Flags::ShaderStageFlags(VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_COMPUTE_BIT));
    logger_.LogError("VUID-Test-flags", buffer_, Location(vvl::Func::vkCreateBuffer), "stages {}, none {}, two {}.",
                     string_VkShaderStageFlags(VK_SHADER_STAGE_ALL_GRAPHICS), string_VkShaderStageFlags(0),
                     string_VkShaderStageFlags(VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_COMPUTE_BIT));

    ExpectMessages(2,
                   "vkCreateBuffer(): stages VK_SHADER_STAGE_ALL_GRAPHICS, none VkShaderStageFlags(0), "
                   "two VK_SHADER_STAGE_VERTEX_BIT|VK_SHADER_STAGE_COMPUTE_BIT.");
}

TEST_F(VvlCoreLogging, Flags64) {
    logger_.LogError(
        "VUID-Test-flags", buffer_, Location(vvl::Func::vkCreateBuffer), "{}.",
        vvl::Flags::FormatFeatureFlags2(VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_BIT | VK_FORMAT_FEATURE_2_HOST_IMAGE_TRANSFER_BIT));
    logger_.LogError(
        "VUID-Test-flags", buffer_, Location(vvl::Func::vkCreateBuffer), "{}.",
        string_VkFormatFeatureFlags2(VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_BIT | VK_FORMAT_FEATURE_2_HOST_IMAGE_TRANSFER_BIT));

    ExpectMessages(2, "vkCreateBuffer(): VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_BIT|VK_FORMAT_FEATURE_2_HOST_IMAGE_TRANSFER_BIT.");
}

TEST_F(VvlCoreLogging, JsonOutput) {
    debug_report_.message_format_settings.json = true;
    logger_.LogError("VUID-Test-json", buffer_, Location(vvl::Func::vkCreateBuffer), "bad \"{}\".", "value");

    ExpectMessages(1,
                   "{\n"
                   "\t\"Severity\" : \"Error\",\n"
                   "\t\"VUID\" : \"VUID-Test-json\",\n"
                   "\t\"Objects\" : [\n"
                   "\t\t{\"type\" : \"VkBuffer\", \"handle\" : \"0x1234\", \"name\" : \"\"}\n"
                   "\t],\n"
                   "\t\"MessageID\" : \"0x22b44914\",\n"
                   "\t\"Function\" : \"vkCreateBuffer\",\n"
                   "\t\"Location\" : \"\",\n"
                   "\t\"MainMessage\" : \"bad \\\"value\\\".\",\n"
                   "\t\"VkFrameBoundaryEXT::frameID\" : \"\",\n"
                   "\t\"DebugRegion\" : \"\",\n"
                   "\t\"SpecText\" : \"\",\n"
                   "\t\"SpecUrl\" : \"\"\n"
                   "}");
}

TEST_F(VvlCoreLogging, DuplicateLimitNoteAndDrop) {
    debug_report_.duplicate_message_limit = 2;
    for (uint32_t i = 0; i < 3; ++i) {
        logger_.LogError("VUID-Test-duplicate", buffer_, Location(vvl::Func::vkCreateBuffer), "attempt {}.", i);
    }
    // The limit counts per VUID, so the format-string API needs its own
    for (uint32_t i = 0; i < 3; ++i) {
        logger_.LogError("VUID-Test-duplicate-fmt", buffer_, Location(vvl::Func::vkCreateBuffer), "attempt {}.", i);
    }

    ASSERT_EQ(delivered_.size(), 4u);
    for (size_t first : {0u, 2u}) {
        EXPECT_EQ(delivered_[first].message, "vkCreateBuffer(): attempt 0.");
        EXPECT_EQ(delivered_[first + 1].message,
                  "(Warning - This VUID has now been reported 2 times, which is the duplicate_message_limit value, this will be "
                  "the last time reporting it).\nvkCreateBuffer(): attempt 1.");
    }
}

TEST(VvlCoreAllocationCounter, StopsCountingWhenTheMeasuredCodeThrows) {
    if (!vvl_test::AllocationCountingAvailable()) {
        GTEST_SKIP() << "Allocation counting is not available under this sanitizer";
    }
    EXPECT_THROW(vvl_test::CountAllocations([] { throw std::runtime_error("measured code failed"); }), std::runtime_error);
    EXPECT_FALSE(vvl_test::CountingAllocations());
}

TEST_F(VvlCoreLogging, PreformattedTextIsDeliveredVerbatim) {
    // GPU-AV dumps and SPIR-V text are formatted before logging; braces and percent signs must survive untouched
    debug_report_.LogMessage(kErrorBit, "VUID-Test-preformatted", LogObjectList(buffer_), Location(vvl::Func::vkCreateBuffer),
                             std::string("struct { int x; } and 100% {{done}}"));

    ASSERT_EQ(delivered_.size(), 1u);
    EXPECT_EQ(delivered_[0].message, "vkCreateBuffer(): struct { int x; } and 100% {{done}}");
}

TEST_F(VvlCoreLogging, DroppedMessagesAreNeverFormatted) {
    int formatted = 0;
    const CountsFormatting argument{&formatted};
    const Location loc(vvl::Func::vkCreateBuffer);

    // No messenger listens to verbose messages
    logger_.LogVerbose("VUID-Test-lazy-severity", buffer_, loc, "{}", argument);
    // Filtered out by message ID
    debug_report_.filter_message_ids.insert(hash_util::VuidHash("VUID-Test-lazy-filtered"));
    logger_.LogError("VUID-Test-lazy-filtered", buffer_, loc, "{}", argument);
    // Over the duplicate limit after the first
    debug_report_.duplicate_message_limit = 1;
    logger_.LogError("VUID-Test-lazy-limit", buffer_, loc, "{}", argument);
    logger_.LogError("VUID-Test-lazy-limit", buffer_, loc, "{}", argument);

    ASSERT_EQ(delivered_.size(), 1u);
    EXPECT_EQ(formatted, 1);
}

TEST_F(VvlCoreLogging, FormatStringEscapesIndexesAndNestedFields) {
    logger_.LogError("VUID-Test-fields", buffer_, Location(vvl::Func::vkCreateBuffer), "{{literal}} {0}-{0} [{1:>{2}}]", 5, 7, 3);

    ExpectMessages(1, "vkCreateBuffer(): {literal} 5-5 [  7]");
}

TEST_F(VvlCoreLogging, WarmedUpDeliveryDoesNotAllocate) {
    if (!vvl_test::AllocationCountingAvailable()) {
        GTEST_SKIP() << "Allocation counting is not available under this sanitizer";
    }
    VkDebugUtilsObjectNameInfoEXT name_info = vku::InitStructHelper();
    name_info.objectType = VK_OBJECT_TYPE_BUFFER;
    name_info.objectHandle = CastToUint64(buffer_);
    name_info.pObjectName = "vertices";
    debug_report_.SetUtilsObjectName(&name_info);
    record_text_ = false;  // the callback only counts, so every counted allocation is the layer's
    const Location loc(vvl::Func::vkCreateBuffer, vvl::Field::pCreateInfo);
    const Location size_loc = loc.dot(vvl::Field::size);
    // A named object, a Location with fields, handle and Location arguments, appended spec text: everything assembly does
    auto log = [&] {
        logger_.LogError("VUID-VkBufferCreateInfo-size-00912", buffer_, size_loc, "{} ({}) has size {}", logger_.Handle(buffer_),
                         size_loc, 0u);
    };

    log();  // warm up the per-thread buffers
    EXPECT_EQ(vvl_test::CountAllocations(log), 0u) << "text output";

    debug_report_.message_format_settings.json = true;
    log();
    EXPECT_EQ(vvl_test::CountAllocations(log), 0u) << "JSON output";
    EXPECT_EQ(delivered_count_, 4u);
}

TEST_F(VvlCoreLogging, HandleFormatsLikeFormatHandle) {
    // Through the Logger and the DebugReport, for a typed handle, a VulkanTypedHandle and a type name with a raw handle
    const VulkanTypedHandle typed(buffer_, kVulkanObjectTypeBuffer);
    auto check = [&](const std::string& context) {
        logger_.LogError("VUID-Test-handle", buffer_, Location(vvl::Func::vkDestroyBuffer), "{} {} {} {}", logger_.Handle(buffer_),
                         debug_report_.Handle(buffer_), debug_report_.Handle(typed),
                         debug_report_.Handle("VkBuffer", CastToUint64(buffer_)));
        const std::string expected = logger_.FormatHandle(buffer_);
        ASSERT_FALSE(delivered_.empty());
        EXPECT_EQ(delivered_.back().message, "vkDestroyBuffer(): " + expected + " " + expected + " " + expected + " " + expected)
            << context;
    };
    check("no name");

    VkDebugMarkerObjectNameInfoEXT marker_name = vku::InitStructHelper();
    marker_name.objectType = VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT;
    marker_name.object = CastToUint64(buffer_);
    marker_name.pObjectName = "marker";
    debug_report_.SetMarkerObjectName(&marker_name);
    check("marker name");

    VkDebugUtilsObjectNameInfoEXT utils_name = vku::InitStructHelper();
    utils_name.objectType = VK_OBJECT_TYPE_BUFFER;
    utils_name.objectHandle = CastToUint64(buffer_);
    utils_name.pObjectName = "utils";
    debug_report_.SetUtilsObjectName(&utils_name);
    check("debug utils name wins over the marker name");

    utils_name.pObjectName = "";
    debug_report_.SetUtilsObjectName(&utils_name);
    check("an empty debug utils name falls back to the marker name");

    marker_name.pObjectName = "";
    debug_report_.SetMarkerObjectName(&marker_name);
    check("empty names count as no name");
}

TEST_F(VvlCoreLogging, LocationFormatsLikeFields) {
    const Location create_info_loc(vvl::Func::vkCreateGraphicsPipelines, vvl::Field::pCreateInfos, 1);
    const Location stages_loc = create_info_loc.dot(vvl::Field::pStages, 0);
    const Location pnext_loc =
        stages_loc.pNext(vvl::Struct::VkPipelineShaderStageRequiredSubgroupSizeCreateInfo, vvl::Field::requiredSubgroupSize);
    for (const Location* loc : {&create_info_loc, &stages_loc, &pnext_loc}) {
        logger_.LogError("VUID-Test-location", buffer_, Location(vvl::Func::vkCreateGraphicsPipelines), "[{}]", *loc);
        ASSERT_FALSE(delivered_.empty());
        EXPECT_EQ(delivered_.back().message, "vkCreateGraphicsPipelines(): [" + loc->Fields() + "]");
    }
    EXPECT_EQ(delivered_.back().message,
              "vkCreateGraphicsPipelines(): [pCreateInfos[1].pStages[0].pNext<VkPipelineShaderStageRequiredSubgroupSizeCreateInfo>"
              ".requiredSubgroupSize]");
}

// Handle() resolves through the same VkHandleInfo traits as FormatHandle(). On 32-bit every non-dispatchable handle is a
// uint64_t, so both must fall back to the generic non-dispatchable type name (compiled by the armeabi-v7a CI job).
template <typename T>
constexpr VkObjectType HandleObjectType(HandleRef (DebugReport::*)(T) const) {
    return VkHandleInfo<T>::kVkObjectType;
}
#ifdef TYPESAFE_NONDISPATCHABLE_HANDLES
static_assert(HandleObjectType(&DebugReport::Handle<VkBuffer>) == VK_OBJECT_TYPE_BUFFER);
#else
static_assert(HandleObjectType(&DebugReport::Handle<VkBuffer>) == VK_OBJECT_TYPE_UNKNOWN);
#endif
