// *** THIS FILE IS GENERATED - DO NOT EDIT ***
// See flags_format_helper_generator.py for modifications

/***************************************************************************
 *
 * Copyright (c) 2026 The Khronos Group Inc.
 * Copyright (c) 2026 Valve Corporation
 * Copyright (c) 2026 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ****************************************************************************/
// NOLINTBEGIN

#include "flags_format_helper.h"

#include <iterator>

#include <vulkan/vk_enum_string_helper.h>

namespace vvl::Flags {

static const char* FormatFeatureFlagsBitName(uint64_t bit) {
    return string_VkFormatFeatureFlagBits(static_cast<VkFormatFeatureFlagBits>(bit));
}
static constexpr FlagsDescription kFormatFeatureFlags = {FormatFeatureFlagsBitName, "VkFormatFeatureFlags(0)", nullptr, 0};
FlagsRef FormatFeatureFlags(VkFormatFeatureFlags value) { return FlagsRef{&kFormatFeatureFlags, value}; }

static const char* ImageCreateFlagsBitName(uint64_t bit) {
    return string_VkImageCreateFlagBits(static_cast<VkImageCreateFlagBits>(bit));
}
static constexpr FlagsDescription kImageCreateFlags = {ImageCreateFlagsBitName, "VkImageCreateFlags(0)", nullptr, 0};
FlagsRef ImageCreateFlags(VkImageCreateFlags value) { return FlagsRef{&kImageCreateFlags, value}; }

static const char* SampleCountFlagsBitName(uint64_t bit) {
    return string_VkSampleCountFlagBits(static_cast<VkSampleCountFlagBits>(bit));
}
static constexpr FlagsDescription kSampleCountFlags = {SampleCountFlagsBitName, "VkSampleCountFlags(0)", nullptr, 0};
FlagsRef SampleCountFlags(VkSampleCountFlags value) { return FlagsRef{&kSampleCountFlags, value}; }

static const char* ImageUsageFlagsBitName(uint64_t bit) {
    return string_VkImageUsageFlagBits(static_cast<VkImageUsageFlagBits>(bit));
}
static constexpr FlagsDescription kImageUsageFlags = {ImageUsageFlagsBitName, "VkImageUsageFlags(0)", nullptr, 0};
FlagsRef ImageUsageFlags(VkImageUsageFlags value) { return FlagsRef{&kImageUsageFlags, value}; }

static const char* InstanceCreateFlagsBitName(uint64_t bit) {
    return string_VkInstanceCreateFlagBits(static_cast<VkInstanceCreateFlagBits>(bit));
}
static constexpr FlagsDescription kInstanceCreateFlags = {InstanceCreateFlagsBitName, "VkInstanceCreateFlags(0)", nullptr, 0};
FlagsRef InstanceCreateFlags(VkInstanceCreateFlags value) { return FlagsRef{&kInstanceCreateFlags, value}; }

static const char* MemoryHeapFlagsBitName(uint64_t bit) {
    return string_VkMemoryHeapFlagBits(static_cast<VkMemoryHeapFlagBits>(bit));
}
static constexpr FlagsDescription kMemoryHeapFlags = {MemoryHeapFlagsBitName, "VkMemoryHeapFlags(0)", nullptr, 0};
FlagsRef MemoryHeapFlags(VkMemoryHeapFlags value) { return FlagsRef{&kMemoryHeapFlags, value}; }

static const char* MemoryPropertyFlagsBitName(uint64_t bit) {
    return string_VkMemoryPropertyFlagBits(static_cast<VkMemoryPropertyFlagBits>(bit));
}
static constexpr FlagsDescription kMemoryPropertyFlags = {MemoryPropertyFlagsBitName, "VkMemoryPropertyFlags(0)", nullptr, 0};
FlagsRef MemoryPropertyFlags(VkMemoryPropertyFlags value) { return FlagsRef{&kMemoryPropertyFlags, value}; }

static const char* QueueFlagsBitName(uint64_t bit) { return string_VkQueueFlagBits(static_cast<VkQueueFlagBits>(bit)); }
static constexpr FlagsDescription kQueueFlags = {QueueFlagsBitName, "VkQueueFlags(0)", nullptr, 0};
FlagsRef QueueFlags(VkQueueFlags value) { return FlagsRef{&kQueueFlags, value}; }

static const char* ShaderStageFlagsBitName(uint64_t bit) {
    return string_VkShaderStageFlagBits(static_cast<VkShaderStageFlagBits>(bit));
}
static constexpr FlagsWholeValueName kShaderStageFlagsWholeValues[] = {
    {VK_SHADER_STAGE_ALL_GRAPHICS, "VK_SHADER_STAGE_ALL_GRAPHICS"},
    {VK_SHADER_STAGE_ALL, "VK_SHADER_STAGE_ALL"},
};
static constexpr FlagsDescription kShaderStageFlags = {ShaderStageFlagsBitName, "VkShaderStageFlags(0)",
                                                       kShaderStageFlagsWholeValues,
                                                       static_cast<uint32_t>(std::size(kShaderStageFlagsWholeValues))};
FlagsRef ShaderStageFlags(VkShaderStageFlags value) { return FlagsRef{&kShaderStageFlags, value}; }

static const char* DeviceQueueCreateFlagsBitName(uint64_t bit) {
    return string_VkDeviceQueueCreateFlagBits(static_cast<VkDeviceQueueCreateFlagBits>(bit));
}
static constexpr FlagsDescription kDeviceQueueCreateFlags = {DeviceQueueCreateFlagsBitName, "VkDeviceQueueCreateFlags(0)", nullptr,
                                                             0};
FlagsRef DeviceQueueCreateFlags(VkDeviceQueueCreateFlags value) { return FlagsRef{&kDeviceQueueCreateFlags, value}; }

static const char* PipelineStageFlagsBitName(uint64_t bit) {
    return string_VkPipelineStageFlagBits(static_cast<VkPipelineStageFlagBits>(bit));
}
static constexpr FlagsDescription kPipelineStageFlags = {PipelineStageFlagsBitName, "VkPipelineStageFlags(0)", nullptr, 0};
FlagsRef PipelineStageFlags(VkPipelineStageFlags value) { return FlagsRef{&kPipelineStageFlags, value}; }

static const char* MemoryMapFlagsBitName(uint64_t bit) { return string_VkMemoryMapFlagBits(static_cast<VkMemoryMapFlagBits>(bit)); }
static constexpr FlagsDescription kMemoryMapFlags = {MemoryMapFlagsBitName, "VkMemoryMapFlags(0)", nullptr, 0};
FlagsRef MemoryMapFlags(VkMemoryMapFlags value) { return FlagsRef{&kMemoryMapFlags, value}; }

static const char* ImageAspectFlagsBitName(uint64_t bit) {
    return string_VkImageAspectFlagBits(static_cast<VkImageAspectFlagBits>(bit));
}
static constexpr FlagsDescription kImageAspectFlags = {ImageAspectFlagsBitName, "VkImageAspectFlags(0)", nullptr, 0};
FlagsRef ImageAspectFlags(VkImageAspectFlags value) { return FlagsRef{&kImageAspectFlags, value}; }

static const char* SparseImageFormatFlagsBitName(uint64_t bit) {
    return string_VkSparseImageFormatFlagBits(static_cast<VkSparseImageFormatFlagBits>(bit));
}
static constexpr FlagsDescription kSparseImageFormatFlags = {SparseImageFormatFlagsBitName, "VkSparseImageFormatFlags(0)", nullptr,
                                                             0};
FlagsRef SparseImageFormatFlags(VkSparseImageFormatFlags value) { return FlagsRef{&kSparseImageFormatFlags, value}; }

static const char* SparseMemoryBindFlagsBitName(uint64_t bit) {
    return string_VkSparseMemoryBindFlagBits(static_cast<VkSparseMemoryBindFlagBits>(bit));
}
static constexpr FlagsDescription kSparseMemoryBindFlags = {SparseMemoryBindFlagsBitName, "VkSparseMemoryBindFlags(0)", nullptr, 0};
FlagsRef SparseMemoryBindFlags(VkSparseMemoryBindFlags value) { return FlagsRef{&kSparseMemoryBindFlags, value}; }

static const char* FenceCreateFlagsBitName(uint64_t bit) {
    return string_VkFenceCreateFlagBits(static_cast<VkFenceCreateFlagBits>(bit));
}
static constexpr FlagsDescription kFenceCreateFlags = {FenceCreateFlagsBitName, "VkFenceCreateFlags(0)", nullptr, 0};
FlagsRef FenceCreateFlags(VkFenceCreateFlags value) { return FlagsRef{&kFenceCreateFlags, value}; }

static const char* QueryPoolCreateFlagsBitName(uint64_t bit) {
    return string_VkQueryPoolCreateFlagBits(static_cast<VkQueryPoolCreateFlagBits>(bit));
}
static constexpr FlagsDescription kQueryPoolCreateFlags = {QueryPoolCreateFlagsBitName, "VkQueryPoolCreateFlags(0)", nullptr, 0};
FlagsRef QueryPoolCreateFlags(VkQueryPoolCreateFlags value) { return FlagsRef{&kQueryPoolCreateFlags, value}; }

static const char* QueryPipelineStatisticFlagsBitName(uint64_t bit) {
    return string_VkQueryPipelineStatisticFlagBits(static_cast<VkQueryPipelineStatisticFlagBits>(bit));
}
static constexpr FlagsDescription kQueryPipelineStatisticFlags = {QueryPipelineStatisticFlagsBitName,
                                                                  "VkQueryPipelineStatisticFlags(0)", nullptr, 0};
FlagsRef QueryPipelineStatisticFlags(VkQueryPipelineStatisticFlags value) { return FlagsRef{&kQueryPipelineStatisticFlags, value}; }

static const char* QueryResultFlagsBitName(uint64_t bit) {
    return string_VkQueryResultFlagBits(static_cast<VkQueryResultFlagBits>(bit));
}
static constexpr FlagsDescription kQueryResultFlags = {QueryResultFlagsBitName, "VkQueryResultFlags(0)", nullptr, 0};
FlagsRef QueryResultFlags(VkQueryResultFlags value) { return FlagsRef{&kQueryResultFlags, value}; }

static const char* BufferCreateFlagsBitName(uint64_t bit) {
    return string_VkBufferCreateFlagBits(static_cast<VkBufferCreateFlagBits>(bit));
}
static constexpr FlagsDescription kBufferCreateFlags = {BufferCreateFlagsBitName, "VkBufferCreateFlags(0)", nullptr, 0};
FlagsRef BufferCreateFlags(VkBufferCreateFlags value) { return FlagsRef{&kBufferCreateFlags, value}; }

static const char* BufferUsageFlagsBitName(uint64_t bit) {
    return string_VkBufferUsageFlagBits(static_cast<VkBufferUsageFlagBits>(bit));
}
static constexpr FlagsDescription kBufferUsageFlags = {BufferUsageFlagsBitName, "VkBufferUsageFlags(0)", nullptr, 0};
FlagsRef BufferUsageFlags(VkBufferUsageFlags value) { return FlagsRef{&kBufferUsageFlags, value}; }

static const char* ImageViewCreateFlagsBitName(uint64_t bit) {
    return string_VkImageViewCreateFlagBits(static_cast<VkImageViewCreateFlagBits>(bit));
}
static constexpr FlagsDescription kImageViewCreateFlags = {ImageViewCreateFlagsBitName, "VkImageViewCreateFlags(0)", nullptr, 0};
FlagsRef ImageViewCreateFlags(VkImageViewCreateFlags value) { return FlagsRef{&kImageViewCreateFlags, value}; }

static const char* AccessFlagsBitName(uint64_t bit) { return string_VkAccessFlagBits(static_cast<VkAccessFlagBits>(bit)); }
static constexpr FlagsDescription kAccessFlags = {AccessFlagsBitName, "VkAccessFlags(0)", nullptr, 0};
FlagsRef AccessFlags(VkAccessFlags value) { return FlagsRef{&kAccessFlags, value}; }

static const char* DependencyFlagsBitName(uint64_t bit) {
    return string_VkDependencyFlagBits(static_cast<VkDependencyFlagBits>(bit));
}
static constexpr FlagsDescription kDependencyFlags = {DependencyFlagsBitName, "VkDependencyFlags(0)", nullptr, 0};
FlagsRef DependencyFlags(VkDependencyFlags value) { return FlagsRef{&kDependencyFlags, value}; }

static const char* CommandPoolCreateFlagsBitName(uint64_t bit) {
    return string_VkCommandPoolCreateFlagBits(static_cast<VkCommandPoolCreateFlagBits>(bit));
}
static constexpr FlagsDescription kCommandPoolCreateFlags = {CommandPoolCreateFlagsBitName, "VkCommandPoolCreateFlags(0)", nullptr,
                                                             0};
FlagsRef CommandPoolCreateFlags(VkCommandPoolCreateFlags value) { return FlagsRef{&kCommandPoolCreateFlags, value}; }

static const char* CommandPoolResetFlagsBitName(uint64_t bit) {
    return string_VkCommandPoolResetFlagBits(static_cast<VkCommandPoolResetFlagBits>(bit));
}
static constexpr FlagsDescription kCommandPoolResetFlags = {CommandPoolResetFlagsBitName, "VkCommandPoolResetFlags(0)", nullptr, 0};
FlagsRef CommandPoolResetFlags(VkCommandPoolResetFlags value) { return FlagsRef{&kCommandPoolResetFlags, value}; }

static const char* QueryControlFlagsBitName(uint64_t bit) {
    return string_VkQueryControlFlagBits(static_cast<VkQueryControlFlagBits>(bit));
}
static constexpr FlagsDescription kQueryControlFlags = {QueryControlFlagsBitName, "VkQueryControlFlags(0)", nullptr, 0};
FlagsRef QueryControlFlags(VkQueryControlFlags value) { return FlagsRef{&kQueryControlFlags, value}; }

static const char* CommandBufferUsageFlagsBitName(uint64_t bit) {
    return string_VkCommandBufferUsageFlagBits(static_cast<VkCommandBufferUsageFlagBits>(bit));
}
static constexpr FlagsDescription kCommandBufferUsageFlags = {CommandBufferUsageFlagsBitName, "VkCommandBufferUsageFlags(0)",
                                                              nullptr, 0};
FlagsRef CommandBufferUsageFlags(VkCommandBufferUsageFlags value) { return FlagsRef{&kCommandBufferUsageFlags, value}; }

static const char* CommandBufferResetFlagsBitName(uint64_t bit) {
    return string_VkCommandBufferResetFlagBits(static_cast<VkCommandBufferResetFlagBits>(bit));
}
static constexpr FlagsDescription kCommandBufferResetFlags = {CommandBufferResetFlagsBitName, "VkCommandBufferResetFlags(0)",
                                                              nullptr, 0};
FlagsRef CommandBufferResetFlags(VkCommandBufferResetFlags value) { return FlagsRef{&kCommandBufferResetFlags, value}; }

static const char* EventCreateFlagsBitName(uint64_t bit) {
    return string_VkEventCreateFlagBits(static_cast<VkEventCreateFlagBits>(bit));
}
static constexpr FlagsDescription kEventCreateFlags = {EventCreateFlagsBitName, "VkEventCreateFlags(0)", nullptr, 0};
FlagsRef EventCreateFlags(VkEventCreateFlags value) { return FlagsRef{&kEventCreateFlags, value}; }

static const char* PipelineCacheCreateFlagsBitName(uint64_t bit) {
    return string_VkPipelineCacheCreateFlagBits(static_cast<VkPipelineCacheCreateFlagBits>(bit));
}
static constexpr FlagsDescription kPipelineCacheCreateFlags = {PipelineCacheCreateFlagsBitName, "VkPipelineCacheCreateFlags(0)",
                                                               nullptr, 0};
FlagsRef PipelineCacheCreateFlags(VkPipelineCacheCreateFlags value) { return FlagsRef{&kPipelineCacheCreateFlags, value}; }

static const char* PipelineCreateFlagsBitName(uint64_t bit) {
    return string_VkPipelineCreateFlagBits(static_cast<VkPipelineCreateFlagBits>(bit));
}
static constexpr FlagsDescription kPipelineCreateFlags = {PipelineCreateFlagsBitName, "VkPipelineCreateFlags(0)", nullptr, 0};
FlagsRef PipelineCreateFlags(VkPipelineCreateFlags value) { return FlagsRef{&kPipelineCreateFlags, value}; }

static const char* PipelineLayoutCreateFlagsBitName(uint64_t bit) {
    return string_VkPipelineLayoutCreateFlagBits(static_cast<VkPipelineLayoutCreateFlagBits>(bit));
}
static constexpr FlagsDescription kPipelineLayoutCreateFlags = {PipelineLayoutCreateFlagsBitName, "VkPipelineLayoutCreateFlags(0)",
                                                                nullptr, 0};
FlagsRef PipelineLayoutCreateFlags(VkPipelineLayoutCreateFlags value) { return FlagsRef{&kPipelineLayoutCreateFlags, value}; }

static const char* PipelineShaderStageCreateFlagsBitName(uint64_t bit) {
    return string_VkPipelineShaderStageCreateFlagBits(static_cast<VkPipelineShaderStageCreateFlagBits>(bit));
}
static constexpr FlagsDescription kPipelineShaderStageCreateFlags = {PipelineShaderStageCreateFlagsBitName,
                                                                     "VkPipelineShaderStageCreateFlags(0)", nullptr, 0};
FlagsRef PipelineShaderStageCreateFlags(VkPipelineShaderStageCreateFlags value) {
    return FlagsRef{&kPipelineShaderStageCreateFlags, value};
}

static const char* SamplerCreateFlagsBitName(uint64_t bit) {
    return string_VkSamplerCreateFlagBits(static_cast<VkSamplerCreateFlagBits>(bit));
}
static constexpr FlagsDescription kSamplerCreateFlags = {SamplerCreateFlagsBitName, "VkSamplerCreateFlags(0)", nullptr, 0};
FlagsRef SamplerCreateFlags(VkSamplerCreateFlags value) { return FlagsRef{&kSamplerCreateFlags, value}; }

static const char* DescriptorPoolCreateFlagsBitName(uint64_t bit) {
    return string_VkDescriptorPoolCreateFlagBits(static_cast<VkDescriptorPoolCreateFlagBits>(bit));
}
static constexpr FlagsDescription kDescriptorPoolCreateFlags = {DescriptorPoolCreateFlagsBitName, "VkDescriptorPoolCreateFlags(0)",
                                                                nullptr, 0};
FlagsRef DescriptorPoolCreateFlags(VkDescriptorPoolCreateFlags value) { return FlagsRef{&kDescriptorPoolCreateFlags, value}; }

static const char* DescriptorSetLayoutCreateFlagsBitName(uint64_t bit) {
    return string_VkDescriptorSetLayoutCreateFlagBits(static_cast<VkDescriptorSetLayoutCreateFlagBits>(bit));
}
static constexpr FlagsDescription kDescriptorSetLayoutCreateFlags = {DescriptorSetLayoutCreateFlagsBitName,
                                                                     "VkDescriptorSetLayoutCreateFlags(0)", nullptr, 0};
FlagsRef DescriptorSetLayoutCreateFlags(VkDescriptorSetLayoutCreateFlags value) {
    return FlagsRef{&kDescriptorSetLayoutCreateFlags, value};
}

static const char* ColorComponentFlagsBitName(uint64_t bit) {
    return string_VkColorComponentFlagBits(static_cast<VkColorComponentFlagBits>(bit));
}
static constexpr FlagsDescription kColorComponentFlags = {ColorComponentFlagsBitName, "VkColorComponentFlags(0)", nullptr, 0};
FlagsRef ColorComponentFlags(VkColorComponentFlags value) { return FlagsRef{&kColorComponentFlags, value}; }

static const char* CullModeFlagsBitName(uint64_t bit) { return string_VkCullModeFlagBits(static_cast<VkCullModeFlagBits>(bit)); }
static constexpr FlagsWholeValueName kCullModeFlagsWholeValues[] = {
    {VK_CULL_MODE_FRONT_AND_BACK, "VK_CULL_MODE_FRONT_AND_BACK"},
};
static constexpr FlagsDescription kCullModeFlags = {CullModeFlagsBitName, "VkCullModeFlags(0)", kCullModeFlagsWholeValues,
                                                    static_cast<uint32_t>(std::size(kCullModeFlagsWholeValues))};
FlagsRef CullModeFlags(VkCullModeFlags value) { return FlagsRef{&kCullModeFlags, value}; }

static const char* PipelineColorBlendStateCreateFlagsBitName(uint64_t bit) {
    return string_VkPipelineColorBlendStateCreateFlagBits(static_cast<VkPipelineColorBlendStateCreateFlagBits>(bit));
}
static constexpr FlagsDescription kPipelineColorBlendStateCreateFlags = {PipelineColorBlendStateCreateFlagsBitName,
                                                                         "VkPipelineColorBlendStateCreateFlags(0)", nullptr, 0};
FlagsRef PipelineColorBlendStateCreateFlags(VkPipelineColorBlendStateCreateFlags value) {
    return FlagsRef{&kPipelineColorBlendStateCreateFlags, value};
}

static const char* PipelineDepthStencilStateCreateFlagsBitName(uint64_t bit) {
    return string_VkPipelineDepthStencilStateCreateFlagBits(static_cast<VkPipelineDepthStencilStateCreateFlagBits>(bit));
}
static constexpr FlagsDescription kPipelineDepthStencilStateCreateFlags = {PipelineDepthStencilStateCreateFlagsBitName,
                                                                           "VkPipelineDepthStencilStateCreateFlags(0)", nullptr, 0};
FlagsRef PipelineDepthStencilStateCreateFlags(VkPipelineDepthStencilStateCreateFlags value) {
    return FlagsRef{&kPipelineDepthStencilStateCreateFlags, value};
}

static const char* AttachmentDescriptionFlagsBitName(uint64_t bit) {
    return string_VkAttachmentDescriptionFlagBits(static_cast<VkAttachmentDescriptionFlagBits>(bit));
}
static constexpr FlagsDescription kAttachmentDescriptionFlags = {AttachmentDescriptionFlagsBitName,
                                                                 "VkAttachmentDescriptionFlags(0)", nullptr, 0};
FlagsRef AttachmentDescriptionFlags(VkAttachmentDescriptionFlags value) { return FlagsRef{&kAttachmentDescriptionFlags, value}; }

static const char* FramebufferCreateFlagsBitName(uint64_t bit) {
    return string_VkFramebufferCreateFlagBits(static_cast<VkFramebufferCreateFlagBits>(bit));
}
static constexpr FlagsDescription kFramebufferCreateFlags = {FramebufferCreateFlagsBitName, "VkFramebufferCreateFlags(0)", nullptr,
                                                             0};
FlagsRef FramebufferCreateFlags(VkFramebufferCreateFlags value) { return FlagsRef{&kFramebufferCreateFlags, value}; }

static const char* RenderPassCreateFlagsBitName(uint64_t bit) {
    return string_VkRenderPassCreateFlagBits(static_cast<VkRenderPassCreateFlagBits>(bit));
}
static constexpr FlagsDescription kRenderPassCreateFlags = {RenderPassCreateFlagsBitName, "VkRenderPassCreateFlags(0)", nullptr, 0};
FlagsRef RenderPassCreateFlags(VkRenderPassCreateFlags value) { return FlagsRef{&kRenderPassCreateFlags, value}; }

static const char* SubpassDescriptionFlagsBitName(uint64_t bit) {
    return string_VkSubpassDescriptionFlagBits(static_cast<VkSubpassDescriptionFlagBits>(bit));
}
static constexpr FlagsDescription kSubpassDescriptionFlags = {SubpassDescriptionFlagsBitName, "VkSubpassDescriptionFlags(0)",
                                                              nullptr, 0};
FlagsRef SubpassDescriptionFlags(VkSubpassDescriptionFlags value) { return FlagsRef{&kSubpassDescriptionFlags, value}; }

static const char* StencilFaceFlagsBitName(uint64_t bit) {
    return string_VkStencilFaceFlagBits(static_cast<VkStencilFaceFlagBits>(bit));
}
static constexpr FlagsWholeValueName kStencilFaceFlagsWholeValues[] = {
    {VK_STENCIL_FACE_FRONT_AND_BACK, "VK_STENCIL_FACE_FRONT_AND_BACK"},
};
static constexpr FlagsDescription kStencilFaceFlags = {StencilFaceFlagsBitName, "VkStencilFaceFlags(0)",
                                                       kStencilFaceFlagsWholeValues,
                                                       static_cast<uint32_t>(std::size(kStencilFaceFlagsWholeValues))};
FlagsRef StencilFaceFlags(VkStencilFaceFlags value) { return FlagsRef{&kStencilFaceFlags, value}; }

static const char* SubgroupFeatureFlagsBitName(uint64_t bit) {
    return string_VkSubgroupFeatureFlagBits(static_cast<VkSubgroupFeatureFlagBits>(bit));
}
static constexpr FlagsDescription kSubgroupFeatureFlags = {SubgroupFeatureFlagsBitName, "VkSubgroupFeatureFlags(0)", nullptr, 0};
FlagsRef SubgroupFeatureFlags(VkSubgroupFeatureFlags value) { return FlagsRef{&kSubgroupFeatureFlags, value}; }

static const char* PeerMemoryFeatureFlagsBitName(uint64_t bit) {
    return string_VkPeerMemoryFeatureFlagBits(static_cast<VkPeerMemoryFeatureFlagBits>(bit));
}
static constexpr FlagsDescription kPeerMemoryFeatureFlags = {PeerMemoryFeatureFlagsBitName, "VkPeerMemoryFeatureFlags(0)", nullptr,
                                                             0};
FlagsRef PeerMemoryFeatureFlags(VkPeerMemoryFeatureFlags value) { return FlagsRef{&kPeerMemoryFeatureFlags, value}; }

static const char* MemoryAllocateFlagsBitName(uint64_t bit) {
    return string_VkMemoryAllocateFlagBits(static_cast<VkMemoryAllocateFlagBits>(bit));
}
static constexpr FlagsDescription kMemoryAllocateFlags = {MemoryAllocateFlagsBitName, "VkMemoryAllocateFlags(0)", nullptr, 0};
FlagsRef MemoryAllocateFlags(VkMemoryAllocateFlags value) { return FlagsRef{&kMemoryAllocateFlags, value}; }

static const char* ExternalMemoryHandleTypeFlagsBitName(uint64_t bit) {
    return string_VkExternalMemoryHandleTypeFlagBits(static_cast<VkExternalMemoryHandleTypeFlagBits>(bit));
}
static constexpr FlagsDescription kExternalMemoryHandleTypeFlags = {ExternalMemoryHandleTypeFlagsBitName,
                                                                    "VkExternalMemoryHandleTypeFlags(0)", nullptr, 0};
FlagsRef ExternalMemoryHandleTypeFlags(VkExternalMemoryHandleTypeFlags value) {
    return FlagsRef{&kExternalMemoryHandleTypeFlags, value};
}

static const char* ExternalMemoryFeatureFlagsBitName(uint64_t bit) {
    return string_VkExternalMemoryFeatureFlagBits(static_cast<VkExternalMemoryFeatureFlagBits>(bit));
}
static constexpr FlagsDescription kExternalMemoryFeatureFlags = {ExternalMemoryFeatureFlagsBitName,
                                                                 "VkExternalMemoryFeatureFlags(0)", nullptr, 0};
FlagsRef ExternalMemoryFeatureFlags(VkExternalMemoryFeatureFlags value) { return FlagsRef{&kExternalMemoryFeatureFlags, value}; }

static const char* ExternalFenceHandleTypeFlagsBitName(uint64_t bit) {
    return string_VkExternalFenceHandleTypeFlagBits(static_cast<VkExternalFenceHandleTypeFlagBits>(bit));
}
static constexpr FlagsDescription kExternalFenceHandleTypeFlags = {ExternalFenceHandleTypeFlagsBitName,
                                                                   "VkExternalFenceHandleTypeFlags(0)", nullptr, 0};
FlagsRef ExternalFenceHandleTypeFlags(VkExternalFenceHandleTypeFlags value) {
    return FlagsRef{&kExternalFenceHandleTypeFlags, value};
}

static const char* ExternalFenceFeatureFlagsBitName(uint64_t bit) {
    return string_VkExternalFenceFeatureFlagBits(static_cast<VkExternalFenceFeatureFlagBits>(bit));
}
static constexpr FlagsDescription kExternalFenceFeatureFlags = {ExternalFenceFeatureFlagsBitName, "VkExternalFenceFeatureFlags(0)",
                                                                nullptr, 0};
FlagsRef ExternalFenceFeatureFlags(VkExternalFenceFeatureFlags value) { return FlagsRef{&kExternalFenceFeatureFlags, value}; }

static const char* FenceImportFlagsBitName(uint64_t bit) {
    return string_VkFenceImportFlagBits(static_cast<VkFenceImportFlagBits>(bit));
}
static constexpr FlagsDescription kFenceImportFlags = {FenceImportFlagsBitName, "VkFenceImportFlags(0)", nullptr, 0};
FlagsRef FenceImportFlags(VkFenceImportFlags value) { return FlagsRef{&kFenceImportFlags, value}; }

static const char* SemaphoreImportFlagsBitName(uint64_t bit) {
    return string_VkSemaphoreImportFlagBits(static_cast<VkSemaphoreImportFlagBits>(bit));
}
static constexpr FlagsDescription kSemaphoreImportFlags = {SemaphoreImportFlagsBitName, "VkSemaphoreImportFlags(0)", nullptr, 0};
FlagsRef SemaphoreImportFlags(VkSemaphoreImportFlags value) { return FlagsRef{&kSemaphoreImportFlags, value}; }

static const char* ExternalSemaphoreHandleTypeFlagsBitName(uint64_t bit) {
    return string_VkExternalSemaphoreHandleTypeFlagBits(static_cast<VkExternalSemaphoreHandleTypeFlagBits>(bit));
}
static constexpr FlagsDescription kExternalSemaphoreHandleTypeFlags = {ExternalSemaphoreHandleTypeFlagsBitName,
                                                                       "VkExternalSemaphoreHandleTypeFlags(0)", nullptr, 0};
FlagsRef ExternalSemaphoreHandleTypeFlags(VkExternalSemaphoreHandleTypeFlags value) {
    return FlagsRef{&kExternalSemaphoreHandleTypeFlags, value};
}

static const char* ExternalSemaphoreFeatureFlagsBitName(uint64_t bit) {
    return string_VkExternalSemaphoreFeatureFlagBits(static_cast<VkExternalSemaphoreFeatureFlagBits>(bit));
}
static constexpr FlagsDescription kExternalSemaphoreFeatureFlags = {ExternalSemaphoreFeatureFlagsBitName,
                                                                    "VkExternalSemaphoreFeatureFlags(0)", nullptr, 0};
FlagsRef ExternalSemaphoreFeatureFlags(VkExternalSemaphoreFeatureFlags value) {
    return FlagsRef{&kExternalSemaphoreFeatureFlags, value};
}

static const char* ResolveModeFlagsBitName(uint64_t bit) {
    return string_VkResolveModeFlagBits(static_cast<VkResolveModeFlagBits>(bit));
}
static constexpr FlagsDescription kResolveModeFlags = {ResolveModeFlagsBitName, "VkResolveModeFlags(0)", nullptr, 0};
FlagsRef ResolveModeFlags(VkResolveModeFlags value) { return FlagsRef{&kResolveModeFlags, value}; }

static const char* SemaphoreWaitFlagsBitName(uint64_t bit) {
    return string_VkSemaphoreWaitFlagBits(static_cast<VkSemaphoreWaitFlagBits>(bit));
}
static constexpr FlagsDescription kSemaphoreWaitFlags = {SemaphoreWaitFlagsBitName, "VkSemaphoreWaitFlags(0)", nullptr, 0};
FlagsRef SemaphoreWaitFlags(VkSemaphoreWaitFlags value) { return FlagsRef{&kSemaphoreWaitFlags, value}; }

static const char* DescriptorBindingFlagsBitName(uint64_t bit) {
    return string_VkDescriptorBindingFlagBits(static_cast<VkDescriptorBindingFlagBits>(bit));
}
static constexpr FlagsDescription kDescriptorBindingFlags = {DescriptorBindingFlagsBitName, "VkDescriptorBindingFlags(0)", nullptr,
                                                             0};
FlagsRef DescriptorBindingFlags(VkDescriptorBindingFlags value) { return FlagsRef{&kDescriptorBindingFlags, value}; }

static const char* ToolPurposeFlagsBitName(uint64_t bit) {
    return string_VkToolPurposeFlagBits(static_cast<VkToolPurposeFlagBits>(bit));
}
static constexpr FlagsDescription kToolPurposeFlags = {ToolPurposeFlagsBitName, "VkToolPurposeFlags(0)", nullptr, 0};
FlagsRef ToolPurposeFlags(VkToolPurposeFlags value) { return FlagsRef{&kToolPurposeFlags, value}; }

static const char* PrivateDataSlotCreateFlagsBitName(uint64_t bit) {
    return string_VkPrivateDataSlotCreateFlagBits(static_cast<VkPrivateDataSlotCreateFlagBits>(bit));
}
static constexpr FlagsDescription kPrivateDataSlotCreateFlags = {PrivateDataSlotCreateFlagsBitName,
                                                                 "VkPrivateDataSlotCreateFlags(0)", nullptr, 0};
FlagsRef PrivateDataSlotCreateFlags(VkPrivateDataSlotCreateFlags value) { return FlagsRef{&kPrivateDataSlotCreateFlags, value}; }

static const char* PipelineStageFlags2BitName(uint64_t bit) { return string_VkPipelineStageFlagBits2(bit); }
static constexpr FlagsDescription kPipelineStageFlags2 = {PipelineStageFlags2BitName, "VkPipelineStageFlags2(0)", nullptr, 0};
FlagsRef PipelineStageFlags2(VkPipelineStageFlags2 value) { return FlagsRef{&kPipelineStageFlags2, value}; }

static const char* AccessFlags2BitName(uint64_t bit) { return string_VkAccessFlagBits2(bit); }
static constexpr FlagsDescription kAccessFlags2 = {AccessFlags2BitName, "VkAccessFlags2(0)", nullptr, 0};
FlagsRef AccessFlags2(VkAccessFlags2 value) { return FlagsRef{&kAccessFlags2, value}; }

static const char* SubmitFlagsBitName(uint64_t bit) { return string_VkSubmitFlagBits(static_cast<VkSubmitFlagBits>(bit)); }
static constexpr FlagsDescription kSubmitFlags = {SubmitFlagsBitName, "VkSubmitFlags(0)", nullptr, 0};
FlagsRef SubmitFlags(VkSubmitFlags value) { return FlagsRef{&kSubmitFlags, value}; }

static const char* FormatFeatureFlags2BitName(uint64_t bit) { return string_VkFormatFeatureFlagBits2(bit); }
static constexpr FlagsDescription kFormatFeatureFlags2 = {FormatFeatureFlags2BitName, "VkFormatFeatureFlags2(0)", nullptr, 0};
FlagsRef FormatFeatureFlags2(VkFormatFeatureFlags2 value) { return FlagsRef{&kFormatFeatureFlags2, value}; }

static const char* PipelineCreationFeedbackFlagsBitName(uint64_t bit) {
    return string_VkPipelineCreationFeedbackFlagBits(static_cast<VkPipelineCreationFeedbackFlagBits>(bit));
}
static constexpr FlagsDescription kPipelineCreationFeedbackFlags = {PipelineCreationFeedbackFlagsBitName,
                                                                    "VkPipelineCreationFeedbackFlags(0)", nullptr, 0};
FlagsRef PipelineCreationFeedbackFlags(VkPipelineCreationFeedbackFlags value) {
    return FlagsRef{&kPipelineCreationFeedbackFlags, value};
}

static const char* RenderingFlagsBitName(uint64_t bit) { return string_VkRenderingFlagBits(static_cast<VkRenderingFlagBits>(bit)); }
static constexpr FlagsDescription kRenderingFlags = {RenderingFlagsBitName, "VkRenderingFlags(0)", nullptr, 0};
FlagsRef RenderingFlags(VkRenderingFlags value) { return FlagsRef{&kRenderingFlags, value}; }

static const char* MemoryUnmapFlagsBitName(uint64_t bit) {
    return string_VkMemoryUnmapFlagBits(static_cast<VkMemoryUnmapFlagBits>(bit));
}
static constexpr FlagsDescription kMemoryUnmapFlags = {MemoryUnmapFlagsBitName, "VkMemoryUnmapFlags(0)", nullptr, 0};
FlagsRef MemoryUnmapFlags(VkMemoryUnmapFlags value) { return FlagsRef{&kMemoryUnmapFlags, value}; }

static const char* BufferUsageFlags2BitName(uint64_t bit) { return string_VkBufferUsageFlagBits2(bit); }
static constexpr FlagsDescription kBufferUsageFlags2 = {BufferUsageFlags2BitName, "VkBufferUsageFlags2(0)", nullptr, 0};
FlagsRef BufferUsageFlags2(VkBufferUsageFlags2 value) { return FlagsRef{&kBufferUsageFlags2, value}; }

static const char* HostImageCopyFlagsBitName(uint64_t bit) {
    return string_VkHostImageCopyFlagBits(static_cast<VkHostImageCopyFlagBits>(bit));
}
static constexpr FlagsDescription kHostImageCopyFlags = {HostImageCopyFlagsBitName, "VkHostImageCopyFlags(0)", nullptr, 0};
FlagsRef HostImageCopyFlags(VkHostImageCopyFlags value) { return FlagsRef{&kHostImageCopyFlags, value}; }

static const char* PipelineCreateFlags2BitName(uint64_t bit) { return string_VkPipelineCreateFlagBits2(bit); }
static constexpr FlagsDescription kPipelineCreateFlags2 = {PipelineCreateFlags2BitName, "VkPipelineCreateFlags2(0)", nullptr, 0};
FlagsRef PipelineCreateFlags2(VkPipelineCreateFlags2 value) { return FlagsRef{&kPipelineCreateFlags2, value}; }

static const char* SurfaceTransformFlagsKHRBitName(uint64_t bit) {
    return string_VkSurfaceTransformFlagBitsKHR(static_cast<VkSurfaceTransformFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kSurfaceTransformFlagsKHR = {SurfaceTransformFlagsKHRBitName, "VkSurfaceTransformFlagsKHR(0)",
                                                               nullptr, 0};
FlagsRef SurfaceTransformFlagsKHR(VkSurfaceTransformFlagsKHR value) { return FlagsRef{&kSurfaceTransformFlagsKHR, value}; }

static const char* CompositeAlphaFlagsKHRBitName(uint64_t bit) {
    return string_VkCompositeAlphaFlagBitsKHR(static_cast<VkCompositeAlphaFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kCompositeAlphaFlagsKHR = {CompositeAlphaFlagsKHRBitName, "VkCompositeAlphaFlagsKHR(0)", nullptr,
                                                             0};
FlagsRef CompositeAlphaFlagsKHR(VkCompositeAlphaFlagsKHR value) { return FlagsRef{&kCompositeAlphaFlagsKHR, value}; }

static const char* SwapchainCreateFlagsKHRBitName(uint64_t bit) {
    return string_VkSwapchainCreateFlagBitsKHR(static_cast<VkSwapchainCreateFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kSwapchainCreateFlagsKHR = {SwapchainCreateFlagsKHRBitName, "VkSwapchainCreateFlagsKHR(0)",
                                                              nullptr, 0};
FlagsRef SwapchainCreateFlagsKHR(VkSwapchainCreateFlagsKHR value) { return FlagsRef{&kSwapchainCreateFlagsKHR, value}; }

static const char* DeviceGroupPresentModeFlagsKHRBitName(uint64_t bit) {
    return string_VkDeviceGroupPresentModeFlagBitsKHR(static_cast<VkDeviceGroupPresentModeFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kDeviceGroupPresentModeFlagsKHR = {DeviceGroupPresentModeFlagsKHRBitName,
                                                                     "VkDeviceGroupPresentModeFlagsKHR(0)", nullptr, 0};
FlagsRef DeviceGroupPresentModeFlagsKHR(VkDeviceGroupPresentModeFlagsKHR value) {
    return FlagsRef{&kDeviceGroupPresentModeFlagsKHR, value};
}

static const char* DisplayPlaneAlphaFlagsKHRBitName(uint64_t bit) {
    return string_VkDisplayPlaneAlphaFlagBitsKHR(static_cast<VkDisplayPlaneAlphaFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kDisplayPlaneAlphaFlagsKHR = {DisplayPlaneAlphaFlagsKHRBitName, "VkDisplayPlaneAlphaFlagsKHR(0)",
                                                                nullptr, 0};
FlagsRef DisplayPlaneAlphaFlagsKHR(VkDisplayPlaneAlphaFlagsKHR value) { return FlagsRef{&kDisplayPlaneAlphaFlagsKHR, value}; }

static const char* VideoCodecOperationFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoCodecOperationFlagBitsKHR(static_cast<VkVideoCodecOperationFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoCodecOperationFlagsKHR = {VideoCodecOperationFlagsKHRBitName,
                                                                  "VkVideoCodecOperationFlagsKHR(0)", nullptr, 0};
FlagsRef VideoCodecOperationFlagsKHR(VkVideoCodecOperationFlagsKHR value) { return FlagsRef{&kVideoCodecOperationFlagsKHR, value}; }

static const char* VideoChromaSubsamplingFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoChromaSubsamplingFlagBitsKHR(static_cast<VkVideoChromaSubsamplingFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoChromaSubsamplingFlagsKHR = {VideoChromaSubsamplingFlagsKHRBitName,
                                                                     "VkVideoChromaSubsamplingFlagsKHR(0)", nullptr, 0};
FlagsRef VideoChromaSubsamplingFlagsKHR(VkVideoChromaSubsamplingFlagsKHR value) {
    return FlagsRef{&kVideoChromaSubsamplingFlagsKHR, value};
}

static const char* VideoComponentBitDepthFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoComponentBitDepthFlagBitsKHR(static_cast<VkVideoComponentBitDepthFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoComponentBitDepthFlagsKHR = {VideoComponentBitDepthFlagsKHRBitName,
                                                                     "VkVideoComponentBitDepthFlagsKHR(0)", nullptr, 0};
FlagsRef VideoComponentBitDepthFlagsKHR(VkVideoComponentBitDepthFlagsKHR value) {
    return FlagsRef{&kVideoComponentBitDepthFlagsKHR, value};
}

static const char* VideoCapabilityFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoCapabilityFlagBitsKHR(static_cast<VkVideoCapabilityFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoCapabilityFlagsKHR = {VideoCapabilityFlagsKHRBitName, "VkVideoCapabilityFlagsKHR(0)",
                                                              nullptr, 0};
FlagsRef VideoCapabilityFlagsKHR(VkVideoCapabilityFlagsKHR value) { return FlagsRef{&kVideoCapabilityFlagsKHR, value}; }

static const char* VideoSessionCreateFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoSessionCreateFlagBitsKHR(static_cast<VkVideoSessionCreateFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoSessionCreateFlagsKHR = {VideoSessionCreateFlagsKHRBitName,
                                                                 "VkVideoSessionCreateFlagsKHR(0)", nullptr, 0};
FlagsRef VideoSessionCreateFlagsKHR(VkVideoSessionCreateFlagsKHR value) { return FlagsRef{&kVideoSessionCreateFlagsKHR, value}; }

static const char* VideoSessionParametersCreateFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoSessionParametersCreateFlagBitsKHR(static_cast<VkVideoSessionParametersCreateFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoSessionParametersCreateFlagsKHR = {VideoSessionParametersCreateFlagsKHRBitName,
                                                                           "VkVideoSessionParametersCreateFlagsKHR(0)", nullptr, 0};
FlagsRef VideoSessionParametersCreateFlagsKHR(VkVideoSessionParametersCreateFlagsKHR value) {
    return FlagsRef{&kVideoSessionParametersCreateFlagsKHR, value};
}

static const char* VideoCodingControlFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoCodingControlFlagBitsKHR(static_cast<VkVideoCodingControlFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoCodingControlFlagsKHR = {VideoCodingControlFlagsKHRBitName,
                                                                 "VkVideoCodingControlFlagsKHR(0)", nullptr, 0};
FlagsRef VideoCodingControlFlagsKHR(VkVideoCodingControlFlagsKHR value) { return FlagsRef{&kVideoCodingControlFlagsKHR, value}; }

static const char* VideoDecodeCapabilityFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoDecodeCapabilityFlagBitsKHR(static_cast<VkVideoDecodeCapabilityFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoDecodeCapabilityFlagsKHR = {VideoDecodeCapabilityFlagsKHRBitName,
                                                                    "VkVideoDecodeCapabilityFlagsKHR(0)", nullptr, 0};
FlagsRef VideoDecodeCapabilityFlagsKHR(VkVideoDecodeCapabilityFlagsKHR value) {
    return FlagsRef{&kVideoDecodeCapabilityFlagsKHR, value};
}

static const char* VideoDecodeUsageFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoDecodeUsageFlagBitsKHR(static_cast<VkVideoDecodeUsageFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoDecodeUsageFlagsKHR = {VideoDecodeUsageFlagsKHRBitName, "VkVideoDecodeUsageFlagsKHR(0)",
                                                               nullptr, 0};
FlagsRef VideoDecodeUsageFlagsKHR(VkVideoDecodeUsageFlagsKHR value) { return FlagsRef{&kVideoDecodeUsageFlagsKHR, value}; }

static const char* VideoEncodeH264CapabilityFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoEncodeH264CapabilityFlagBitsKHR(static_cast<VkVideoEncodeH264CapabilityFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoEncodeH264CapabilityFlagsKHR = {VideoEncodeH264CapabilityFlagsKHRBitName,
                                                                        "VkVideoEncodeH264CapabilityFlagsKHR(0)", nullptr, 0};
FlagsRef VideoEncodeH264CapabilityFlagsKHR(VkVideoEncodeH264CapabilityFlagsKHR value) {
    return FlagsRef{&kVideoEncodeH264CapabilityFlagsKHR, value};
}

static const char* VideoEncodeH264StdFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoEncodeH264StdFlagBitsKHR(static_cast<VkVideoEncodeH264StdFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoEncodeH264StdFlagsKHR = {VideoEncodeH264StdFlagsKHRBitName,
                                                                 "VkVideoEncodeH264StdFlagsKHR(0)", nullptr, 0};
FlagsRef VideoEncodeH264StdFlagsKHR(VkVideoEncodeH264StdFlagsKHR value) { return FlagsRef{&kVideoEncodeH264StdFlagsKHR, value}; }

static const char* VideoEncodeH264RateControlFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoEncodeH264RateControlFlagBitsKHR(static_cast<VkVideoEncodeH264RateControlFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoEncodeH264RateControlFlagsKHR = {VideoEncodeH264RateControlFlagsKHRBitName,
                                                                         "VkVideoEncodeH264RateControlFlagsKHR(0)", nullptr, 0};
FlagsRef VideoEncodeH264RateControlFlagsKHR(VkVideoEncodeH264RateControlFlagsKHR value) {
    return FlagsRef{&kVideoEncodeH264RateControlFlagsKHR, value};
}

static const char* VideoEncodeH265CapabilityFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoEncodeH265CapabilityFlagBitsKHR(static_cast<VkVideoEncodeH265CapabilityFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoEncodeH265CapabilityFlagsKHR = {VideoEncodeH265CapabilityFlagsKHRBitName,
                                                                        "VkVideoEncodeH265CapabilityFlagsKHR(0)", nullptr, 0};
FlagsRef VideoEncodeH265CapabilityFlagsKHR(VkVideoEncodeH265CapabilityFlagsKHR value) {
    return FlagsRef{&kVideoEncodeH265CapabilityFlagsKHR, value};
}

static const char* VideoEncodeH265StdFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoEncodeH265StdFlagBitsKHR(static_cast<VkVideoEncodeH265StdFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoEncodeH265StdFlagsKHR = {VideoEncodeH265StdFlagsKHRBitName,
                                                                 "VkVideoEncodeH265StdFlagsKHR(0)", nullptr, 0};
FlagsRef VideoEncodeH265StdFlagsKHR(VkVideoEncodeH265StdFlagsKHR value) { return FlagsRef{&kVideoEncodeH265StdFlagsKHR, value}; }

static const char* VideoEncodeH265CtbSizeFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoEncodeH265CtbSizeFlagBitsKHR(static_cast<VkVideoEncodeH265CtbSizeFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoEncodeH265CtbSizeFlagsKHR = {VideoEncodeH265CtbSizeFlagsKHRBitName,
                                                                     "VkVideoEncodeH265CtbSizeFlagsKHR(0)", nullptr, 0};
FlagsRef VideoEncodeH265CtbSizeFlagsKHR(VkVideoEncodeH265CtbSizeFlagsKHR value) {
    return FlagsRef{&kVideoEncodeH265CtbSizeFlagsKHR, value};
}

static const char* VideoEncodeH265TransformBlockSizeFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoEncodeH265TransformBlockSizeFlagBitsKHR(static_cast<VkVideoEncodeH265TransformBlockSizeFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoEncodeH265TransformBlockSizeFlagsKHR = {
    VideoEncodeH265TransformBlockSizeFlagsKHRBitName, "VkVideoEncodeH265TransformBlockSizeFlagsKHR(0)", nullptr, 0};
FlagsRef VideoEncodeH265TransformBlockSizeFlagsKHR(VkVideoEncodeH265TransformBlockSizeFlagsKHR value) {
    return FlagsRef{&kVideoEncodeH265TransformBlockSizeFlagsKHR, value};
}

static const char* VideoEncodeH265RateControlFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoEncodeH265RateControlFlagBitsKHR(static_cast<VkVideoEncodeH265RateControlFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoEncodeH265RateControlFlagsKHR = {VideoEncodeH265RateControlFlagsKHRBitName,
                                                                         "VkVideoEncodeH265RateControlFlagsKHR(0)", nullptr, 0};
FlagsRef VideoEncodeH265RateControlFlagsKHR(VkVideoEncodeH265RateControlFlagsKHR value) {
    return FlagsRef{&kVideoEncodeH265RateControlFlagsKHR, value};
}

static const char* VideoDecodeH264PictureLayoutFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoDecodeH264PictureLayoutFlagBitsKHR(static_cast<VkVideoDecodeH264PictureLayoutFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoDecodeH264PictureLayoutFlagsKHR = {VideoDecodeH264PictureLayoutFlagsKHRBitName,
                                                                           "VkVideoDecodeH264PictureLayoutFlagsKHR(0)", nullptr, 0};
FlagsRef VideoDecodeH264PictureLayoutFlagsKHR(VkVideoDecodeH264PictureLayoutFlagsKHR value) {
    return FlagsRef{&kVideoDecodeH264PictureLayoutFlagsKHR, value};
}

static const char* PerformanceCounterDescriptionFlagsKHRBitName(uint64_t bit) {
    return string_VkPerformanceCounterDescriptionFlagBitsKHR(static_cast<VkPerformanceCounterDescriptionFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kPerformanceCounterDescriptionFlagsKHR = {
    PerformanceCounterDescriptionFlagsKHRBitName, "VkPerformanceCounterDescriptionFlagsKHR(0)", nullptr, 0};
FlagsRef PerformanceCounterDescriptionFlagsKHR(VkPerformanceCounterDescriptionFlagsKHR value) {
    return FlagsRef{&kPerformanceCounterDescriptionFlagsKHR, value};
}

static const char* VideoEncodeFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoEncodeFlagBitsKHR(static_cast<VkVideoEncodeFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoEncodeFlagsKHR = {VideoEncodeFlagsKHRBitName, "VkVideoEncodeFlagsKHR(0)", nullptr, 0};
FlagsRef VideoEncodeFlagsKHR(VkVideoEncodeFlagsKHR value) { return FlagsRef{&kVideoEncodeFlagsKHR, value}; }

static const char* VideoEncodeCapabilityFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoEncodeCapabilityFlagBitsKHR(static_cast<VkVideoEncodeCapabilityFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoEncodeCapabilityFlagsKHR = {VideoEncodeCapabilityFlagsKHRBitName,
                                                                    "VkVideoEncodeCapabilityFlagsKHR(0)", nullptr, 0};
FlagsRef VideoEncodeCapabilityFlagsKHR(VkVideoEncodeCapabilityFlagsKHR value) {
    return FlagsRef{&kVideoEncodeCapabilityFlagsKHR, value};
}

static const char* VideoEncodeRateControlModeFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoEncodeRateControlModeFlagBitsKHR(static_cast<VkVideoEncodeRateControlModeFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoEncodeRateControlModeFlagsKHR = {VideoEncodeRateControlModeFlagsKHRBitName,
                                                                         "VkVideoEncodeRateControlModeFlagsKHR(0)", nullptr, 0};
FlagsRef VideoEncodeRateControlModeFlagsKHR(VkVideoEncodeRateControlModeFlagsKHR value) {
    return FlagsRef{&kVideoEncodeRateControlModeFlagsKHR, value};
}

static const char* VideoEncodeFeedbackFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoEncodeFeedbackFlagBitsKHR(static_cast<VkVideoEncodeFeedbackFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoEncodeFeedbackFlagsKHR = {VideoEncodeFeedbackFlagsKHRBitName,
                                                                  "VkVideoEncodeFeedbackFlagsKHR(0)", nullptr, 0};
FlagsRef VideoEncodeFeedbackFlagsKHR(VkVideoEncodeFeedbackFlagsKHR value) { return FlagsRef{&kVideoEncodeFeedbackFlagsKHR, value}; }

static const char* VideoEncodeUsageFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoEncodeUsageFlagBitsKHR(static_cast<VkVideoEncodeUsageFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoEncodeUsageFlagsKHR = {VideoEncodeUsageFlagsKHRBitName, "VkVideoEncodeUsageFlagsKHR(0)",
                                                               nullptr, 0};
FlagsRef VideoEncodeUsageFlagsKHR(VkVideoEncodeUsageFlagsKHR value) { return FlagsRef{&kVideoEncodeUsageFlagsKHR, value}; }

static const char* VideoEncodeContentFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoEncodeContentFlagBitsKHR(static_cast<VkVideoEncodeContentFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoEncodeContentFlagsKHR = {VideoEncodeContentFlagsKHRBitName,
                                                                 "VkVideoEncodeContentFlagsKHR(0)", nullptr, 0};
FlagsRef VideoEncodeContentFlagsKHR(VkVideoEncodeContentFlagsKHR value) { return FlagsRef{&kVideoEncodeContentFlagsKHR, value}; }

static const char* AddressCommandFlagsKHRBitName(uint64_t bit) {
    return string_VkAddressCommandFlagBitsKHR(static_cast<VkAddressCommandFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kAddressCommandFlagsKHR = {AddressCommandFlagsKHRBitName, "VkAddressCommandFlagsKHR(0)", nullptr,
                                                             0};
FlagsRef AddressCommandFlagsKHR(VkAddressCommandFlagsKHR value) { return FlagsRef{&kAddressCommandFlagsKHR, value}; }

static const char* ConditionalRenderingFlagsEXTBitName(uint64_t bit) {
    return string_VkConditionalRenderingFlagBitsEXT(static_cast<VkConditionalRenderingFlagBitsEXT>(bit));
}
static constexpr FlagsDescription kConditionalRenderingFlagsEXT = {ConditionalRenderingFlagsEXTBitName,
                                                                   "VkConditionalRenderingFlagsEXT(0)", nullptr, 0};
FlagsRef ConditionalRenderingFlagsEXT(VkConditionalRenderingFlagsEXT value) {
    return FlagsRef{&kConditionalRenderingFlagsEXT, value};
}

static const char* AccelerationStructureCreateFlagsKHRBitName(uint64_t bit) {
    return string_VkAccelerationStructureCreateFlagBitsKHR(static_cast<VkAccelerationStructureCreateFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kAccelerationStructureCreateFlagsKHR = {AccelerationStructureCreateFlagsKHRBitName,
                                                                          "VkAccelerationStructureCreateFlagsKHR(0)", nullptr, 0};
FlagsRef AccelerationStructureCreateFlagsKHR(VkAccelerationStructureCreateFlagsKHR value) {
    return FlagsRef{&kAccelerationStructureCreateFlagsKHR, value};
}

static const char* PresentScalingFlagsKHRBitName(uint64_t bit) {
    return string_VkPresentScalingFlagBitsKHR(static_cast<VkPresentScalingFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kPresentScalingFlagsKHR = {PresentScalingFlagsKHRBitName, "VkPresentScalingFlagsKHR(0)", nullptr,
                                                             0};
FlagsRef PresentScalingFlagsKHR(VkPresentScalingFlagsKHR value) { return FlagsRef{&kPresentScalingFlagsKHR, value}; }

static const char* PresentGravityFlagsKHRBitName(uint64_t bit) {
    return string_VkPresentGravityFlagBitsKHR(static_cast<VkPresentGravityFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kPresentGravityFlagsKHR = {PresentGravityFlagsKHRBitName, "VkPresentGravityFlagsKHR(0)", nullptr,
                                                             0};
FlagsRef PresentGravityFlagsKHR(VkPresentGravityFlagsKHR value) { return FlagsRef{&kPresentGravityFlagsKHR, value}; }

static const char* VideoEncodeAV1CapabilityFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoEncodeAV1CapabilityFlagBitsKHR(static_cast<VkVideoEncodeAV1CapabilityFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoEncodeAV1CapabilityFlagsKHR = {VideoEncodeAV1CapabilityFlagsKHRBitName,
                                                                       "VkVideoEncodeAV1CapabilityFlagsKHR(0)", nullptr, 0};
FlagsRef VideoEncodeAV1CapabilityFlagsKHR(VkVideoEncodeAV1CapabilityFlagsKHR value) {
    return FlagsRef{&kVideoEncodeAV1CapabilityFlagsKHR, value};
}

static const char* VideoEncodeAV1StdFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoEncodeAV1StdFlagBitsKHR(static_cast<VkVideoEncodeAV1StdFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoEncodeAV1StdFlagsKHR = {VideoEncodeAV1StdFlagsKHRBitName, "VkVideoEncodeAV1StdFlagsKHR(0)",
                                                                nullptr, 0};
FlagsRef VideoEncodeAV1StdFlagsKHR(VkVideoEncodeAV1StdFlagsKHR value) { return FlagsRef{&kVideoEncodeAV1StdFlagsKHR, value}; }

static const char* VideoEncodeAV1SuperblockSizeFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoEncodeAV1SuperblockSizeFlagBitsKHR(static_cast<VkVideoEncodeAV1SuperblockSizeFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoEncodeAV1SuperblockSizeFlagsKHR = {VideoEncodeAV1SuperblockSizeFlagsKHRBitName,
                                                                           "VkVideoEncodeAV1SuperblockSizeFlagsKHR(0)", nullptr, 0};
FlagsRef VideoEncodeAV1SuperblockSizeFlagsKHR(VkVideoEncodeAV1SuperblockSizeFlagsKHR value) {
    return FlagsRef{&kVideoEncodeAV1SuperblockSizeFlagsKHR, value};
}

static const char* VideoEncodeAV1RateControlFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoEncodeAV1RateControlFlagBitsKHR(static_cast<VkVideoEncodeAV1RateControlFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoEncodeAV1RateControlFlagsKHR = {VideoEncodeAV1RateControlFlagsKHRBitName,
                                                                        "VkVideoEncodeAV1RateControlFlagsKHR(0)", nullptr, 0};
FlagsRef VideoEncodeAV1RateControlFlagsKHR(VkVideoEncodeAV1RateControlFlagsKHR value) {
    return FlagsRef{&kVideoEncodeAV1RateControlFlagsKHR, value};
}

static const char* AddressCopyFlagsKHRBitName(uint64_t bit) {
    return string_VkAddressCopyFlagBitsKHR(static_cast<VkAddressCopyFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kAddressCopyFlagsKHR = {AddressCopyFlagsKHRBitName, "VkAddressCopyFlagsKHR(0)", nullptr, 0};
FlagsRef AddressCopyFlagsKHR(VkAddressCopyFlagsKHR value) { return FlagsRef{&kAddressCopyFlagsKHR, value}; }

static const char* VideoEncodeIntraRefreshModeFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoEncodeIntraRefreshModeFlagBitsKHR(static_cast<VkVideoEncodeIntraRefreshModeFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoEncodeIntraRefreshModeFlagsKHR = {VideoEncodeIntraRefreshModeFlagsKHRBitName,
                                                                          "VkVideoEncodeIntraRefreshModeFlagsKHR(0)", nullptr, 0};
FlagsRef VideoEncodeIntraRefreshModeFlagsKHR(VkVideoEncodeIntraRefreshModeFlagsKHR value) {
    return FlagsRef{&kVideoEncodeIntraRefreshModeFlagsKHR, value};
}

static const char* DeviceFaultFlagsKHRBitName(uint64_t bit) {
    return string_VkDeviceFaultFlagBitsKHR(static_cast<VkDeviceFaultFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kDeviceFaultFlagsKHR = {DeviceFaultFlagsKHRBitName, "VkDeviceFaultFlagsKHR(0)", nullptr, 0};
FlagsRef DeviceFaultFlagsKHR(VkDeviceFaultFlagsKHR value) { return FlagsRef{&kDeviceFaultFlagsKHR, value}; }

static const char* AccessFlags3KHRBitName(uint64_t bit) { return string_VkAccessFlagBits3KHR(bit); }
static constexpr FlagsDescription kAccessFlags3KHR = {AccessFlags3KHRBitName, "VkAccessFlags3KHR(0)", nullptr, 0};
FlagsRef AccessFlags3KHR(VkAccessFlags3KHR value) { return FlagsRef{&kAccessFlags3KHR, value}; }

static const char* VideoEncodePerPartitionFeedbackFlagsKHRBitName(uint64_t bit) {
    return string_VkVideoEncodePerPartitionFeedbackFlagBitsKHR(static_cast<VkVideoEncodePerPartitionFeedbackFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kVideoEncodePerPartitionFeedbackFlagsKHR = {
    VideoEncodePerPartitionFeedbackFlagsKHRBitName, "VkVideoEncodePerPartitionFeedbackFlagsKHR(0)", nullptr, 0};
FlagsRef VideoEncodePerPartitionFeedbackFlagsKHR(VkVideoEncodePerPartitionFeedbackFlagsKHR value) {
    return FlagsRef{&kVideoEncodePerPartitionFeedbackFlagsKHR, value};
}

static const char* RenderingAttachmentFlagsKHRBitName(uint64_t bit) {
    return string_VkRenderingAttachmentFlagBitsKHR(static_cast<VkRenderingAttachmentFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kRenderingAttachmentFlagsKHR = {RenderingAttachmentFlagsKHRBitName,
                                                                  "VkRenderingAttachmentFlagsKHR(0)", nullptr, 0};
FlagsRef RenderingAttachmentFlagsKHR(VkRenderingAttachmentFlagsKHR value) { return FlagsRef{&kRenderingAttachmentFlagsKHR, value}; }

static const char* ResolveImageFlagsKHRBitName(uint64_t bit) {
    return string_VkResolveImageFlagBitsKHR(static_cast<VkResolveImageFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kResolveImageFlagsKHR = {ResolveImageFlagsKHRBitName, "VkResolveImageFlagsKHR(0)", nullptr, 0};
FlagsRef ResolveImageFlagsKHR(VkResolveImageFlagsKHR value) { return FlagsRef{&kResolveImageFlagsKHR, value}; }

static const char* ImageUsageFlags2KHRBitName(uint64_t bit) { return string_VkImageUsageFlagBits2KHR(bit); }
static constexpr FlagsDescription kImageUsageFlags2KHR = {ImageUsageFlags2KHRBitName, "VkImageUsageFlags2KHR(0)", nullptr, 0};
FlagsRef ImageUsageFlags2KHR(VkImageUsageFlags2KHR value) { return FlagsRef{&kImageUsageFlags2KHR, value}; }

static const char* ImageCreateFlags2KHRBitName(uint64_t bit) { return string_VkImageCreateFlagBits2KHR(bit); }
static constexpr FlagsDescription kImageCreateFlags2KHR = {ImageCreateFlags2KHRBitName, "VkImageCreateFlags2KHR(0)", nullptr, 0};
FlagsRef ImageCreateFlags2KHR(VkImageCreateFlags2KHR value) { return FlagsRef{&kImageCreateFlags2KHR, value}; }

static const char* DebugReportFlagsEXTBitName(uint64_t bit) {
    return string_VkDebugReportFlagBitsEXT(static_cast<VkDebugReportFlagBitsEXT>(bit));
}
static constexpr FlagsDescription kDebugReportFlagsEXT = {DebugReportFlagsEXTBitName, "VkDebugReportFlagsEXT(0)", nullptr, 0};
FlagsRef DebugReportFlagsEXT(VkDebugReportFlagsEXT value) { return FlagsRef{&kDebugReportFlagsEXT, value}; }

static const char* ExternalMemoryHandleTypeFlagsNVBitName(uint64_t bit) {
    return string_VkExternalMemoryHandleTypeFlagBitsNV(static_cast<VkExternalMemoryHandleTypeFlagBitsNV>(bit));
}
static constexpr FlagsDescription kExternalMemoryHandleTypeFlagsNV = {ExternalMemoryHandleTypeFlagsNVBitName,
                                                                      "VkExternalMemoryHandleTypeFlagsNV(0)", nullptr, 0};
FlagsRef ExternalMemoryHandleTypeFlagsNV(VkExternalMemoryHandleTypeFlagsNV value) {
    return FlagsRef{&kExternalMemoryHandleTypeFlagsNV, value};
}

static const char* ExternalMemoryFeatureFlagsNVBitName(uint64_t bit) {
    return string_VkExternalMemoryFeatureFlagBitsNV(static_cast<VkExternalMemoryFeatureFlagBitsNV>(bit));
}
static constexpr FlagsDescription kExternalMemoryFeatureFlagsNV = {ExternalMemoryFeatureFlagsNVBitName,
                                                                   "VkExternalMemoryFeatureFlagsNV(0)", nullptr, 0};
FlagsRef ExternalMemoryFeatureFlagsNV(VkExternalMemoryFeatureFlagsNV value) {
    return FlagsRef{&kExternalMemoryFeatureFlagsNV, value};
}

static const char* SurfaceCounterFlagsEXTBitName(uint64_t bit) {
    return string_VkSurfaceCounterFlagBitsEXT(static_cast<VkSurfaceCounterFlagBitsEXT>(bit));
}
static constexpr FlagsDescription kSurfaceCounterFlagsEXT = {SurfaceCounterFlagsEXTBitName, "VkSurfaceCounterFlagsEXT(0)", nullptr,
                                                             0};
FlagsRef SurfaceCounterFlagsEXT(VkSurfaceCounterFlagsEXT value) { return FlagsRef{&kSurfaceCounterFlagsEXT, value}; }

static const char* DebugUtilsMessageSeverityFlagsEXTBitName(uint64_t bit) {
    return string_VkDebugUtilsMessageSeverityFlagBitsEXT(static_cast<VkDebugUtilsMessageSeverityFlagBitsEXT>(bit));
}
static constexpr FlagsDescription kDebugUtilsMessageSeverityFlagsEXT = {DebugUtilsMessageSeverityFlagsEXTBitName,
                                                                        "VkDebugUtilsMessageSeverityFlagsEXT(0)", nullptr, 0};
FlagsRef DebugUtilsMessageSeverityFlagsEXT(VkDebugUtilsMessageSeverityFlagsEXT value) {
    return FlagsRef{&kDebugUtilsMessageSeverityFlagsEXT, value};
}

static const char* DebugUtilsMessageTypeFlagsEXTBitName(uint64_t bit) {
    return string_VkDebugUtilsMessageTypeFlagBitsEXT(static_cast<VkDebugUtilsMessageTypeFlagBitsEXT>(bit));
}
static constexpr FlagsDescription kDebugUtilsMessageTypeFlagsEXT = {DebugUtilsMessageTypeFlagsEXTBitName,
                                                                    "VkDebugUtilsMessageTypeFlagsEXT(0)", nullptr, 0};
FlagsRef DebugUtilsMessageTypeFlagsEXT(VkDebugUtilsMessageTypeFlagsEXT value) {
    return FlagsRef{&kDebugUtilsMessageTypeFlagsEXT, value};
}

static const char* GpaSqShaderStageFlagsAMDBitName(uint64_t bit) {
    return string_VkGpaSqShaderStageFlagBitsAMD(static_cast<VkGpaSqShaderStageFlagBitsAMD>(bit));
}
static constexpr FlagsDescription kGpaSqShaderStageFlagsAMD = {GpaSqShaderStageFlagsAMDBitName, "VkGpaSqShaderStageFlagsAMD(0)",
                                                               nullptr, 0};
FlagsRef GpaSqShaderStageFlagsAMD(VkGpaSqShaderStageFlagsAMD value) { return FlagsRef{&kGpaSqShaderStageFlagsAMD, value}; }

static const char* TensorViewCreateFlagsARMBitName(uint64_t bit) { return string_VkTensorViewCreateFlagBitsARM(bit); }
static constexpr FlagsDescription kTensorViewCreateFlagsARM = {TensorViewCreateFlagsARMBitName, "VkTensorViewCreateFlagsARM(0)",
                                                               nullptr, 0};
FlagsRef TensorViewCreateFlagsARM(VkTensorViewCreateFlagsARM value) { return FlagsRef{&kTensorViewCreateFlagsARM, value}; }

static const char* SpirvResourceTypeFlagsEXTBitName(uint64_t bit) {
    return string_VkSpirvResourceTypeFlagBitsEXT(static_cast<VkSpirvResourceTypeFlagBitsEXT>(bit));
}
static constexpr FlagsWholeValueName kSpirvResourceTypeFlagsEXTWholeValues[] = {
    {VK_SPIRV_RESOURCE_TYPE_ALL_EXT, "VK_SPIRV_RESOURCE_TYPE_ALL_EXT"},
};
static constexpr FlagsDescription kSpirvResourceTypeFlagsEXT = {
    SpirvResourceTypeFlagsEXTBitName, "VkSpirvResourceTypeFlagsEXT(0)", kSpirvResourceTypeFlagsEXTWholeValues,
    static_cast<uint32_t>(std::size(kSpirvResourceTypeFlagsEXTWholeValues))};
FlagsRef SpirvResourceTypeFlagsEXT(VkSpirvResourceTypeFlagsEXT value) { return FlagsRef{&kSpirvResourceTypeFlagsEXT, value}; }

static const char* GeometryFlagsKHRBitName(uint64_t bit) {
    return string_VkGeometryFlagBitsKHR(static_cast<VkGeometryFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kGeometryFlagsKHR = {GeometryFlagsKHRBitName, "VkGeometryFlagsKHR(0)", nullptr, 0};
FlagsRef GeometryFlagsKHR(VkGeometryFlagsKHR value) { return FlagsRef{&kGeometryFlagsKHR, value}; }

static const char* GeometryInstanceFlagsKHRBitName(uint64_t bit) {
    return string_VkGeometryInstanceFlagBitsKHR(static_cast<VkGeometryInstanceFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kGeometryInstanceFlagsKHR = {GeometryInstanceFlagsKHRBitName, "VkGeometryInstanceFlagsKHR(0)",
                                                               nullptr, 0};
FlagsRef GeometryInstanceFlagsKHR(VkGeometryInstanceFlagsKHR value) { return FlagsRef{&kGeometryInstanceFlagsKHR, value}; }

static const char* BuildAccelerationStructureFlagsKHRBitName(uint64_t bit) {
    return string_VkBuildAccelerationStructureFlagBitsKHR(static_cast<VkBuildAccelerationStructureFlagBitsKHR>(bit));
}
static constexpr FlagsDescription kBuildAccelerationStructureFlagsKHR = {BuildAccelerationStructureFlagsKHRBitName,
                                                                         "VkBuildAccelerationStructureFlagsKHR(0)", nullptr, 0};
FlagsRef BuildAccelerationStructureFlagsKHR(VkBuildAccelerationStructureFlagsKHR value) {
    return FlagsRef{&kBuildAccelerationStructureFlagsKHR, value};
}

static const char* PresentStageFlagsEXTBitName(uint64_t bit) {
    return string_VkPresentStageFlagBitsEXT(static_cast<VkPresentStageFlagBitsEXT>(bit));
}
static constexpr FlagsDescription kPresentStageFlagsEXT = {PresentStageFlagsEXTBitName, "VkPresentStageFlagsEXT(0)", nullptr, 0};
FlagsRef PresentStageFlagsEXT(VkPresentStageFlagsEXT value) { return FlagsRef{&kPresentStageFlagsEXT, value}; }

static const char* PastPresentationTimingFlagsEXTBitName(uint64_t bit) {
    return string_VkPastPresentationTimingFlagBitsEXT(static_cast<VkPastPresentationTimingFlagBitsEXT>(bit));
}
static constexpr FlagsDescription kPastPresentationTimingFlagsEXT = {PastPresentationTimingFlagsEXTBitName,
                                                                     "VkPastPresentationTimingFlagsEXT(0)", nullptr, 0};
FlagsRef PastPresentationTimingFlagsEXT(VkPastPresentationTimingFlagsEXT value) {
    return FlagsRef{&kPastPresentationTimingFlagsEXT, value};
}

static const char* PresentTimingInfoFlagsEXTBitName(uint64_t bit) {
    return string_VkPresentTimingInfoFlagBitsEXT(static_cast<VkPresentTimingInfoFlagBitsEXT>(bit));
}
static constexpr FlagsDescription kPresentTimingInfoFlagsEXT = {PresentTimingInfoFlagsEXTBitName, "VkPresentTimingInfoFlagsEXT(0)",
                                                                nullptr, 0};
FlagsRef PresentTimingInfoFlagsEXT(VkPresentTimingInfoFlagsEXT value) { return FlagsRef{&kPresentTimingInfoFlagsEXT, value}; }

static const char* IndirectStateFlagsNVBitName(uint64_t bit) {
    return string_VkIndirectStateFlagBitsNV(static_cast<VkIndirectStateFlagBitsNV>(bit));
}
static constexpr FlagsDescription kIndirectStateFlagsNV = {IndirectStateFlagsNVBitName, "VkIndirectStateFlagsNV(0)", nullptr, 0};
FlagsRef IndirectStateFlagsNV(VkIndirectStateFlagsNV value) { return FlagsRef{&kIndirectStateFlagsNV, value}; }

static const char* IndirectCommandsLayoutUsageFlagsNVBitName(uint64_t bit) {
    return string_VkIndirectCommandsLayoutUsageFlagBitsNV(static_cast<VkIndirectCommandsLayoutUsageFlagBitsNV>(bit));
}
static constexpr FlagsDescription kIndirectCommandsLayoutUsageFlagsNV = {IndirectCommandsLayoutUsageFlagsNVBitName,
                                                                         "VkIndirectCommandsLayoutUsageFlagsNV(0)", nullptr, 0};
FlagsRef IndirectCommandsLayoutUsageFlagsNV(VkIndirectCommandsLayoutUsageFlagsNV value) {
    return FlagsRef{&kIndirectCommandsLayoutUsageFlagsNV, value};
}

static const char* DeviceDiagnosticsConfigFlagsNVBitName(uint64_t bit) {
    return string_VkDeviceDiagnosticsConfigFlagBitsNV(static_cast<VkDeviceDiagnosticsConfigFlagBitsNV>(bit));
}
static constexpr FlagsDescription kDeviceDiagnosticsConfigFlagsNV = {DeviceDiagnosticsConfigFlagsNVBitName,
                                                                     "VkDeviceDiagnosticsConfigFlagsNV(0)", nullptr, 0};
FlagsRef DeviceDiagnosticsConfigFlagsNV(VkDeviceDiagnosticsConfigFlagsNV value) {
    return FlagsRef{&kDeviceDiagnosticsConfigFlagsNV, value};
}

static const char* TileShadingRenderPassFlagsQCOMBitName(uint64_t bit) {
    return string_VkTileShadingRenderPassFlagBitsQCOM(static_cast<VkTileShadingRenderPassFlagBitsQCOM>(bit));
}
static constexpr FlagsDescription kTileShadingRenderPassFlagsQCOM = {TileShadingRenderPassFlagsQCOMBitName,
                                                                     "VkTileShadingRenderPassFlagsQCOM(0)", nullptr, 0};
FlagsRef TileShadingRenderPassFlagsQCOM(VkTileShadingRenderPassFlagsQCOM value) {
    return FlagsRef{&kTileShadingRenderPassFlagsQCOM, value};
}

#ifdef VK_USE_PLATFORM_METAL_EXT
static const char* ExportMetalObjectTypeFlagsEXTBitName(uint64_t bit) {
    return string_VkExportMetalObjectTypeFlagBitsEXT(static_cast<VkExportMetalObjectTypeFlagBitsEXT>(bit));
}
static constexpr FlagsDescription kExportMetalObjectTypeFlagsEXT = {ExportMetalObjectTypeFlagsEXTBitName,
                                                                    "VkExportMetalObjectTypeFlagsEXT(0)", nullptr, 0};
FlagsRef ExportMetalObjectTypeFlagsEXT(VkExportMetalObjectTypeFlagsEXT value) {
    return FlagsRef{&kExportMetalObjectTypeFlagsEXT, value};
}
#endif  // VK_USE_PLATFORM_METAL_EXT

static const char* GraphicsPipelineLibraryFlagsEXTBitName(uint64_t bit) {
    return string_VkGraphicsPipelineLibraryFlagBitsEXT(static_cast<VkGraphicsPipelineLibraryFlagBitsEXT>(bit));
}
static constexpr FlagsDescription kGraphicsPipelineLibraryFlagsEXT = {GraphicsPipelineLibraryFlagsEXTBitName,
                                                                      "VkGraphicsPipelineLibraryFlagsEXT(0)", nullptr, 0};
FlagsRef GraphicsPipelineLibraryFlagsEXT(VkGraphicsPipelineLibraryFlagsEXT value) {
    return FlagsRef{&kGraphicsPipelineLibraryFlagsEXT, value};
}

static const char* ImageCompressionFlagsEXTBitName(uint64_t bit) {
    return string_VkImageCompressionFlagBitsEXT(static_cast<VkImageCompressionFlagBitsEXT>(bit));
}
static constexpr FlagsDescription kImageCompressionFlagsEXT = {ImageCompressionFlagsEXTBitName, "VkImageCompressionFlagsEXT(0)",
                                                               nullptr, 0};
FlagsRef ImageCompressionFlagsEXT(VkImageCompressionFlagsEXT value) { return FlagsRef{&kImageCompressionFlagsEXT, value}; }

static const char* ImageCompressionFixedRateFlagsEXTBitName(uint64_t bit) {
    return string_VkImageCompressionFixedRateFlagBitsEXT(static_cast<VkImageCompressionFixedRateFlagBitsEXT>(bit));
}
static constexpr FlagsDescription kImageCompressionFixedRateFlagsEXT = {ImageCompressionFixedRateFlagsEXTBitName,
                                                                        "VkImageCompressionFixedRateFlagsEXT(0)", nullptr, 0};
FlagsRef ImageCompressionFixedRateFlagsEXT(VkImageCompressionFixedRateFlagsEXT value) {
    return FlagsRef{&kImageCompressionFixedRateFlagsEXT, value};
}

static const char* DeviceAddressBindingFlagsEXTBitName(uint64_t bit) {
    return string_VkDeviceAddressBindingFlagBitsEXT(static_cast<VkDeviceAddressBindingFlagBitsEXT>(bit));
}
static constexpr FlagsDescription kDeviceAddressBindingFlagsEXT = {DeviceAddressBindingFlagsEXTBitName,
                                                                   "VkDeviceAddressBindingFlagsEXT(0)", nullptr, 0};
FlagsRef DeviceAddressBindingFlagsEXT(VkDeviceAddressBindingFlagsEXT value) {
    return FlagsRef{&kDeviceAddressBindingFlagsEXT, value};
}

#ifdef VK_USE_PLATFORM_FUCHSIA
static const char* ImageConstraintsInfoFlagsFUCHSIABitName(uint64_t bit) {
    return string_VkImageConstraintsInfoFlagBitsFUCHSIA(static_cast<VkImageConstraintsInfoFlagBitsFUCHSIA>(bit));
}
static constexpr FlagsDescription kImageConstraintsInfoFlagsFUCHSIA = {ImageConstraintsInfoFlagsFUCHSIABitName,
                                                                       "VkImageConstraintsInfoFlagsFUCHSIA(0)", nullptr, 0};
FlagsRef ImageConstraintsInfoFlagsFUCHSIA(VkImageConstraintsInfoFlagsFUCHSIA value) {
    return FlagsRef{&kImageConstraintsInfoFlagsFUCHSIA, value};
}
#endif  // VK_USE_PLATFORM_FUCHSIA

static const char* FrameBoundaryFlagsEXTBitName(uint64_t bit) {
    return string_VkFrameBoundaryFlagBitsEXT(static_cast<VkFrameBoundaryFlagBitsEXT>(bit));
}
static constexpr FlagsDescription kFrameBoundaryFlagsEXT = {FrameBoundaryFlagsEXTBitName, "VkFrameBoundaryFlagsEXT(0)", nullptr, 0};
FlagsRef FrameBoundaryFlagsEXT(VkFrameBoundaryFlagsEXT value) { return FlagsRef{&kFrameBoundaryFlagsEXT, value}; }

static const char* VideoEncodeRgbModelConversionFlagsVALVEBitName(uint64_t bit) {
    return string_VkVideoEncodeRgbModelConversionFlagBitsVALVE(static_cast<VkVideoEncodeRgbModelConversionFlagBitsVALVE>(bit));
}
static constexpr FlagsDescription kVideoEncodeRgbModelConversionFlagsVALVE = {
    VideoEncodeRgbModelConversionFlagsVALVEBitName, "VkVideoEncodeRgbModelConversionFlagsVALVE(0)", nullptr, 0};
FlagsRef VideoEncodeRgbModelConversionFlagsVALVE(VkVideoEncodeRgbModelConversionFlagsVALVE value) {
    return FlagsRef{&kVideoEncodeRgbModelConversionFlagsVALVE, value};
}

static const char* VideoEncodeRgbRangeCompressionFlagsVALVEBitName(uint64_t bit) {
    return string_VkVideoEncodeRgbRangeCompressionFlagBitsVALVE(static_cast<VkVideoEncodeRgbRangeCompressionFlagBitsVALVE>(bit));
}
static constexpr FlagsDescription kVideoEncodeRgbRangeCompressionFlagsVALVE = {
    VideoEncodeRgbRangeCompressionFlagsVALVEBitName, "VkVideoEncodeRgbRangeCompressionFlagsVALVE(0)", nullptr, 0};
FlagsRef VideoEncodeRgbRangeCompressionFlagsVALVE(VkVideoEncodeRgbRangeCompressionFlagsVALVE value) {
    return FlagsRef{&kVideoEncodeRgbRangeCompressionFlagsVALVE, value};
}

static const char* VideoEncodeRgbChromaOffsetFlagsVALVEBitName(uint64_t bit) {
    return string_VkVideoEncodeRgbChromaOffsetFlagBitsVALVE(static_cast<VkVideoEncodeRgbChromaOffsetFlagBitsVALVE>(bit));
}
static constexpr FlagsDescription kVideoEncodeRgbChromaOffsetFlagsVALVE = {VideoEncodeRgbChromaOffsetFlagsVALVEBitName,
                                                                           "VkVideoEncodeRgbChromaOffsetFlagsVALVE(0)", nullptr, 0};
FlagsRef VideoEncodeRgbChromaOffsetFlagsVALVE(VkVideoEncodeRgbChromaOffsetFlagsVALVE value) {
    return FlagsRef{&kVideoEncodeRgbChromaOffsetFlagsVALVE, value};
}

static const char* BuildMicromapFlagsEXTBitName(uint64_t bit) {
    return string_VkBuildMicromapFlagBitsEXT(static_cast<VkBuildMicromapFlagBitsEXT>(bit));
}
static constexpr FlagsDescription kBuildMicromapFlagsEXT = {BuildMicromapFlagsEXTBitName, "VkBuildMicromapFlagsEXT(0)", nullptr, 0};
FlagsRef BuildMicromapFlagsEXT(VkBuildMicromapFlagsEXT value) { return FlagsRef{&kBuildMicromapFlagsEXT, value}; }

static const char* MicromapCreateFlagsEXTBitName(uint64_t bit) {
    return string_VkMicromapCreateFlagBitsEXT(static_cast<VkMicromapCreateFlagBitsEXT>(bit));
}
static constexpr FlagsDescription kMicromapCreateFlagsEXT = {MicromapCreateFlagsEXTBitName, "VkMicromapCreateFlagsEXT(0)", nullptr,
                                                             0};
FlagsRef MicromapCreateFlagsEXT(VkMicromapCreateFlagsEXT value) { return FlagsRef{&kMicromapCreateFlagsEXT, value}; }

static const char* PhysicalDeviceSchedulingControlsFlagsARMBitName(uint64_t bit) {
    return string_VkPhysicalDeviceSchedulingControlsFlagBitsARM(bit);
}
static constexpr FlagsDescription kPhysicalDeviceSchedulingControlsFlagsARM = {
    PhysicalDeviceSchedulingControlsFlagsARMBitName, "VkPhysicalDeviceSchedulingControlsFlagsARM(0)", nullptr, 0};
FlagsRef PhysicalDeviceSchedulingControlsFlagsARM(VkPhysicalDeviceSchedulingControlsFlagsARM value) {
    return FlagsRef{&kPhysicalDeviceSchedulingControlsFlagsARM, value};
}

static const char* MemoryDecompressionMethodFlagsEXTBitName(uint64_t bit) {
    return string_VkMemoryDecompressionMethodFlagBitsEXT(bit);
}
static constexpr FlagsDescription kMemoryDecompressionMethodFlagsEXT = {MemoryDecompressionMethodFlagsEXTBitName,
                                                                        "VkMemoryDecompressionMethodFlagsEXT(0)", nullptr, 0};
FlagsRef MemoryDecompressionMethodFlagsEXT(VkMemoryDecompressionMethodFlagsEXT value) {
    return FlagsRef{&kMemoryDecompressionMethodFlagsEXT, value};
}

static const char* TensorCreateFlagsARMBitName(uint64_t bit) { return string_VkTensorCreateFlagBitsARM(bit); }
static constexpr FlagsDescription kTensorCreateFlagsARM = {TensorCreateFlagsARMBitName, "VkTensorCreateFlagsARM(0)", nullptr, 0};
FlagsRef TensorCreateFlagsARM(VkTensorCreateFlagsARM value) { return FlagsRef{&kTensorCreateFlagsARM, value}; }

static const char* TensorUsageFlagsARMBitName(uint64_t bit) { return string_VkTensorUsageFlagBitsARM(bit); }
static constexpr FlagsDescription kTensorUsageFlagsARM = {TensorUsageFlagsARMBitName, "VkTensorUsageFlagsARM(0)", nullptr, 0};
FlagsRef TensorUsageFlagsARM(VkTensorUsageFlagsARM value) { return FlagsRef{&kTensorUsageFlagsARM, value}; }

static const char* OpticalFlowGridSizeFlagsNVBitName(uint64_t bit) {
    return string_VkOpticalFlowGridSizeFlagBitsNV(static_cast<VkOpticalFlowGridSizeFlagBitsNV>(bit));
}
static constexpr FlagsDescription kOpticalFlowGridSizeFlagsNV = {OpticalFlowGridSizeFlagsNVBitName,
                                                                 "VkOpticalFlowGridSizeFlagsNV(0)", nullptr, 0};
FlagsRef OpticalFlowGridSizeFlagsNV(VkOpticalFlowGridSizeFlagsNV value) { return FlagsRef{&kOpticalFlowGridSizeFlagsNV, value}; }

static const char* OpticalFlowUsageFlagsNVBitName(uint64_t bit) {
    return string_VkOpticalFlowUsageFlagBitsNV(static_cast<VkOpticalFlowUsageFlagBitsNV>(bit));
}
static constexpr FlagsDescription kOpticalFlowUsageFlagsNV = {OpticalFlowUsageFlagsNVBitName, "VkOpticalFlowUsageFlagsNV(0)",
                                                              nullptr, 0};
FlagsRef OpticalFlowUsageFlagsNV(VkOpticalFlowUsageFlagsNV value) { return FlagsRef{&kOpticalFlowUsageFlagsNV, value}; }

static const char* OpticalFlowSessionCreateFlagsNVBitName(uint64_t bit) {
    return string_VkOpticalFlowSessionCreateFlagBitsNV(static_cast<VkOpticalFlowSessionCreateFlagBitsNV>(bit));
}
static constexpr FlagsDescription kOpticalFlowSessionCreateFlagsNV = {OpticalFlowSessionCreateFlagsNVBitName,
                                                                      "VkOpticalFlowSessionCreateFlagsNV(0)", nullptr, 0};
FlagsRef OpticalFlowSessionCreateFlagsNV(VkOpticalFlowSessionCreateFlagsNV value) {
    return FlagsRef{&kOpticalFlowSessionCreateFlagsNV, value};
}

static const char* OpticalFlowExecuteFlagsNVBitName(uint64_t bit) {
    return string_VkOpticalFlowExecuteFlagBitsNV(static_cast<VkOpticalFlowExecuteFlagBitsNV>(bit));
}
static constexpr FlagsDescription kOpticalFlowExecuteFlagsNV = {OpticalFlowExecuteFlagsNVBitName, "VkOpticalFlowExecuteFlagsNV(0)",
                                                                nullptr, 0};
FlagsRef OpticalFlowExecuteFlagsNV(VkOpticalFlowExecuteFlagsNV value) { return FlagsRef{&kOpticalFlowExecuteFlagsNV, value}; }

static const char* ShaderCreateFlagsEXTBitName(uint64_t bit) {
    return string_VkShaderCreateFlagBitsEXT(static_cast<VkShaderCreateFlagBitsEXT>(bit));
}
static constexpr FlagsDescription kShaderCreateFlagsEXT = {ShaderCreateFlagsEXTBitName, "VkShaderCreateFlagsEXT(0)", nullptr, 0};
FlagsRef ShaderCreateFlagsEXT(VkShaderCreateFlagsEXT value) { return FlagsRef{&kShaderCreateFlagsEXT, value}; }

static const char* DataGraphPipelineSessionCreateFlagsARMBitName(uint64_t bit) {
    return string_VkDataGraphPipelineSessionCreateFlagBitsARM(bit);
}
static constexpr FlagsDescription kDataGraphPipelineSessionCreateFlagsARM = {
    DataGraphPipelineSessionCreateFlagsARMBitName, "VkDataGraphPipelineSessionCreateFlagsARM(0)", nullptr, 0};
FlagsRef DataGraphPipelineSessionCreateFlagsARM(VkDataGraphPipelineSessionCreateFlagsARM value) {
    return FlagsRef{&kDataGraphPipelineSessionCreateFlagsARM, value};
}

static const char* DataGraphTOSAQualityFlagsARMBitName(uint64_t bit) {
    return string_VkDataGraphTOSAQualityFlagBitsARM(static_cast<VkDataGraphTOSAQualityFlagBitsARM>(bit));
}
static constexpr FlagsDescription kDataGraphTOSAQualityFlagsARM = {DataGraphTOSAQualityFlagsARMBitName,
                                                                   "VkDataGraphTOSAQualityFlagsARM(0)", nullptr, 0};
FlagsRef DataGraphTOSAQualityFlagsARM(VkDataGraphTOSAQualityFlagsARM value) {
    return FlagsRef{&kDataGraphTOSAQualityFlagsARM, value};
}

static const char* ClusterAccelerationStructureAddressResolutionFlagsNVBitName(uint64_t bit) {
    return string_VkClusterAccelerationStructureAddressResolutionFlagBitsNV(
        static_cast<VkClusterAccelerationStructureAddressResolutionFlagBitsNV>(bit));
}
static constexpr FlagsDescription kClusterAccelerationStructureAddressResolutionFlagsNV = {
    ClusterAccelerationStructureAddressResolutionFlagsNVBitName, "VkClusterAccelerationStructureAddressResolutionFlagsNV(0)",
    nullptr, 0};
FlagsRef ClusterAccelerationStructureAddressResolutionFlagsNV(VkClusterAccelerationStructureAddressResolutionFlagsNV value) {
    return FlagsRef{&kClusterAccelerationStructureAddressResolutionFlagsNV, value};
}

static const char* ClusterAccelerationStructureClusterFlagsNVBitName(uint64_t bit) {
    return string_VkClusterAccelerationStructureClusterFlagBitsNV(
        static_cast<VkClusterAccelerationStructureClusterFlagBitsNV>(bit));
}
static constexpr FlagsDescription kClusterAccelerationStructureClusterFlagsNV = {
    ClusterAccelerationStructureClusterFlagsNVBitName, "VkClusterAccelerationStructureClusterFlagsNV(0)", nullptr, 0};
FlagsRef ClusterAccelerationStructureClusterFlagsNV(VkClusterAccelerationStructureClusterFlagsNV value) {
    return FlagsRef{&kClusterAccelerationStructureClusterFlagsNV, value};
}

static const char* ClusterAccelerationStructureGeometryFlagsNVBitName(uint64_t bit) {
    return string_VkClusterAccelerationStructureGeometryFlagBitsNV(
        static_cast<VkClusterAccelerationStructureGeometryFlagBitsNV>(bit));
}
static constexpr FlagsDescription kClusterAccelerationStructureGeometryFlagsNV = {
    ClusterAccelerationStructureGeometryFlagsNVBitName, "VkClusterAccelerationStructureGeometryFlagsNV(0)", nullptr, 0};
FlagsRef ClusterAccelerationStructureGeometryFlagsNV(VkClusterAccelerationStructureGeometryFlagsNV value) {
    return FlagsRef{&kClusterAccelerationStructureGeometryFlagsNV, value};
}

static const char* ClusterAccelerationStructureIndexFormatFlagsNVBitName(uint64_t bit) {
    return string_VkClusterAccelerationStructureIndexFormatFlagBitsNV(
        static_cast<VkClusterAccelerationStructureIndexFormatFlagBitsNV>(bit));
}
static constexpr FlagsDescription kClusterAccelerationStructureIndexFormatFlagsNV = {
    ClusterAccelerationStructureIndexFormatFlagsNVBitName, "VkClusterAccelerationStructureIndexFormatFlagsNV(0)", nullptr, 0};
FlagsRef ClusterAccelerationStructureIndexFormatFlagsNV(VkClusterAccelerationStructureIndexFormatFlagsNV value) {
    return FlagsRef{&kClusterAccelerationStructureIndexFormatFlagsNV, value};
}

static const char* PartitionedAccelerationStructureInstanceFlagsNVBitName(uint64_t bit) {
    return string_VkPartitionedAccelerationStructureInstanceFlagBitsNV(
        static_cast<VkPartitionedAccelerationStructureInstanceFlagBitsNV>(bit));
}
static constexpr FlagsDescription kPartitionedAccelerationStructureInstanceFlagsNV = {
    PartitionedAccelerationStructureInstanceFlagsNVBitName, "VkPartitionedAccelerationStructureInstanceFlagsNV(0)", nullptr, 0};
FlagsRef PartitionedAccelerationStructureInstanceFlagsNV(VkPartitionedAccelerationStructureInstanceFlagsNV value) {
    return FlagsRef{&kPartitionedAccelerationStructureInstanceFlagsNV, value};
}

static const char* IndirectCommandsInputModeFlagsEXTBitName(uint64_t bit) {
    return string_VkIndirectCommandsInputModeFlagBitsEXT(static_cast<VkIndirectCommandsInputModeFlagBitsEXT>(bit));
}
static constexpr FlagsDescription kIndirectCommandsInputModeFlagsEXT = {IndirectCommandsInputModeFlagsEXTBitName,
                                                                        "VkIndirectCommandsInputModeFlagsEXT(0)", nullptr, 0};
FlagsRef IndirectCommandsInputModeFlagsEXT(VkIndirectCommandsInputModeFlagsEXT value) {
    return FlagsRef{&kIndirectCommandsInputModeFlagsEXT, value};
}

static const char* IndirectCommandsLayoutUsageFlagsEXTBitName(uint64_t bit) {
    return string_VkIndirectCommandsLayoutUsageFlagBitsEXT(static_cast<VkIndirectCommandsLayoutUsageFlagBitsEXT>(bit));
}
static constexpr FlagsDescription kIndirectCommandsLayoutUsageFlagsEXT = {IndirectCommandsLayoutUsageFlagsEXTBitName,
                                                                          "VkIndirectCommandsLayoutUsageFlagsEXT(0)", nullptr, 0};
FlagsRef IndirectCommandsLayoutUsageFlagsEXT(VkIndirectCommandsLayoutUsageFlagsEXT value) {
    return FlagsRef{&kIndirectCommandsLayoutUsageFlagsEXT, value};
}

static const char* DataGraphOpticalFlowGridSizeFlagsARMBitName(uint64_t bit) {
    return string_VkDataGraphOpticalFlowGridSizeFlagBitsARM(static_cast<VkDataGraphOpticalFlowGridSizeFlagBitsARM>(bit));
}
static constexpr FlagsDescription kDataGraphOpticalFlowGridSizeFlagsARM = {DataGraphOpticalFlowGridSizeFlagsARMBitName,
                                                                           "VkDataGraphOpticalFlowGridSizeFlagsARM(0)", nullptr, 0};
FlagsRef DataGraphOpticalFlowGridSizeFlagsARM(VkDataGraphOpticalFlowGridSizeFlagsARM value) {
    return FlagsRef{&kDataGraphOpticalFlowGridSizeFlagsARM, value};
}

static const char* DataGraphOpticalFlowCreateFlagsARMBitName(uint64_t bit) {
    return string_VkDataGraphOpticalFlowCreateFlagBitsARM(static_cast<VkDataGraphOpticalFlowCreateFlagBitsARM>(bit));
}
static constexpr FlagsDescription kDataGraphOpticalFlowCreateFlagsARM = {DataGraphOpticalFlowCreateFlagsARMBitName,
                                                                         "VkDataGraphOpticalFlowCreateFlagsARM(0)", nullptr, 0};
FlagsRef DataGraphOpticalFlowCreateFlagsARM(VkDataGraphOpticalFlowCreateFlagsARM value) {
    return FlagsRef{&kDataGraphOpticalFlowCreateFlagsARM, value};
}

static const char* DataGraphOpticalFlowImageUsageFlagsARMBitName(uint64_t bit) {
    return string_VkDataGraphOpticalFlowImageUsageFlagBitsARM(static_cast<VkDataGraphOpticalFlowImageUsageFlagBitsARM>(bit));
}
static constexpr FlagsDescription kDataGraphOpticalFlowImageUsageFlagsARM = {
    DataGraphOpticalFlowImageUsageFlagsARMBitName, "VkDataGraphOpticalFlowImageUsageFlagsARM(0)", nullptr, 0};
FlagsRef DataGraphOpticalFlowImageUsageFlagsARM(VkDataGraphOpticalFlowImageUsageFlagsARM value) {
    return FlagsRef{&kDataGraphOpticalFlowImageUsageFlagsARM, value};
}

static const char* DataGraphOpticalFlowExecuteFlagsARMBitName(uint64_t bit) {
    return string_VkDataGraphOpticalFlowExecuteFlagBitsARM(static_cast<VkDataGraphOpticalFlowExecuteFlagBitsARM>(bit));
}
static constexpr FlagsDescription kDataGraphOpticalFlowExecuteFlagsARM = {DataGraphOpticalFlowExecuteFlagsARMBitName,
                                                                          "VkDataGraphOpticalFlowExecuteFlagsARM(0)", nullptr, 0};
FlagsRef DataGraphOpticalFlowExecuteFlagsARM(VkDataGraphOpticalFlowExecuteFlagsARM value) {
    return FlagsRef{&kDataGraphOpticalFlowExecuteFlagsARM, value};
}

static const char* CooperativeMatrixFlagsEXTBitName(uint64_t bit) {
    return string_VkCooperativeMatrixFlagBitsEXT(static_cast<VkCooperativeMatrixFlagBitsEXT>(bit));
}
static constexpr FlagsDescription kCooperativeMatrixFlagsEXT = {CooperativeMatrixFlagsEXTBitName, "VkCooperativeMatrixFlagsEXT(0)",
                                                                nullptr, 0};
FlagsRef CooperativeMatrixFlagsEXT(VkCooperativeMatrixFlagsEXT value) { return FlagsRef{&kCooperativeMatrixFlagsEXT, value}; }
}  // namespace vvl::Flags
// NOLINTEND
