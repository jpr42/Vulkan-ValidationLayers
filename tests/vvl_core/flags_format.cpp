/*
 * Copyright (c) 2026 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

// vvl::Flags::<Name>(value) must format exactly like string_Vk<Name>(value) from vk_enum_string_helper.h, without
// allocating

#include "../framework/test_common.h"

#include <string>

#include <vulkan/vk_enum_string_helper.h>
#include "error_message/log_flags.h"
#include "generated/flags_format_helper.h"
#include "generated/flags_format_test_cases.h"

#include "allocation_counter.h"

namespace {
template <typename... Args>
std::string Format(vvl::format::format_string<Args...> fmt, Args&&... args) {
    std::string out;
    vvl::format::VFormatTo(out, vvl::format::View(fmt), vvl::format::MakeArgs(args...));
    return out;
}
}  // namespace

TEST(VvlCoreFlags, WholeValueNamesZeroAndBits) {
    EXPECT_EQ(Format("{}", vvl::Flags::ShaderStageFlags(VK_SHADER_STAGE_ALL)), "VK_SHADER_STAGE_ALL");
    EXPECT_EQ(Format("{}", vvl::Flags::ShaderStageFlags(VK_SHADER_STAGE_ALL_GRAPHICS)), "VK_SHADER_STAGE_ALL_GRAPHICS");
    EXPECT_EQ(Format("{}", vvl::Flags::CullModeFlags(VK_CULL_MODE_FRONT_AND_BACK)), "VK_CULL_MODE_FRONT_AND_BACK");
    EXPECT_EQ(Format("{}", vvl::Flags::StencilFaceFlags(VK_STENCIL_FACE_FRONT_AND_BACK)), "VK_STENCIL_FACE_FRONT_AND_BACK");
    EXPECT_EQ(Format("{}", vvl::Flags::ShaderStageFlags(0)), "VkShaderStageFlags(0)");
    EXPECT_EQ(Format("{}", vvl::Flags::ShaderStageFlags(VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_COMPUTE_BIT)),
              "VK_SHADER_STAGE_VERTEX_BIT|VK_SHADER_STAGE_COMPUTE_BIT");
    EXPECT_EQ(Format("{}", vvl::Flags::FormatFeatureFlags2(VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_BIT |
                                                           VK_FORMAT_FEATURE_2_HOST_IMAGE_TRANSFER_BIT)),
              "VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_BIT|VK_FORMAT_FEATURE_2_HOST_IMAGE_TRANSFER_BIT");
    // A bit with no name
    EXPECT_EQ(Format("{}", vvl::Flags::CullModeFlags(VK_CULL_MODE_FRONT_BIT | 0x80000000u)),
              string_VkCullModeFlags(VK_CULL_MODE_FRONT_BIT | 0x80000000u));
}

TEST(VvlCoreFlags, EveryFlagsTypeFormatsLikeItsStringHelper) {
    for (const vvl::FlagsFormatTestCase& test_case : vvl::kFlagsFormatTestCases) {
        // At least zero and the top bit; also whole-value names, each with an extra bit, and two named bits together
        EXPECT_GE(test_case.values.size(), 2u) << test_case.name;
        for (const uint64_t value : test_case.values) {
            EXPECT_EQ(Format("{}", test_case.make(value)), test_case.expected(value)) << test_case.name << " " << value;
        }
    }
}

TEST(VvlCoreFlags, FormattingDoesNotAllocate) {
    if (!vvl_test::AllocationCountingAvailable()) {
        GTEST_SKIP() << "Allocation counting is not available under this sanitizer";
    }
    std::string out;
    out.reserve(256);
    auto format = [&] {
        out.clear();
        const vvl::FlagsRef stages = vvl::Flags::ShaderStageFlags(VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT);
        const vvl::FlagsRef features = vvl::Flags::FormatFeatureFlags2(VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_BIT);
        const vvl::FlagsRef cull = vvl::Flags::CullModeFlags(VK_CULL_MODE_FRONT_AND_BACK);
        vvl::format::VFormatTo(out, "{} {} {}", vvl::format::MakeArgs(stages, features, cull));
    };
    format();
    EXPECT_EQ(vvl_test::CountAllocations(format), 0u);
    EXPECT_EQ(out,
              "VK_SHADER_STAGE_VERTEX_BIT|VK_SHADER_STAGE_FRAGMENT_BIT VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_BIT "
              "VK_CULL_MODE_FRONT_AND_BACK");
}
