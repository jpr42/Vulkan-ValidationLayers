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

#pragma once

// Test data only: for each flags type, the values whose vvl::Flags formatting is compared with string_Vk*Flags*()

#include <cstdint>
#include <string>
#include <vector>

#include <vulkan/vk_enum_string_helper.h>
#include "flags_format_helper.h"

namespace vvl {
struct FlagsFormatTestCase {
    const char* name;
    FlagsRef (*make)(uint64_t value);
    std::string (*expected)(uint64_t value);
    std::vector<uint64_t> values;
};

inline const FlagsFormatTestCase kFlagsFormatTestCases[] = {
    {"VkFormatFeatureFlags",
     [](uint64_t value) { return Flags::FormatFeatureFlags(static_cast<VkFormatFeatureFlags>(value)); },
     [](uint64_t value) { return string_VkFormatFeatureFlags(static_cast<VkFormatFeatureFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT | VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkImageCreateFlags",
     [](uint64_t value) { return Flags::ImageCreateFlags(static_cast<VkImageCreateFlags>(value)); },
     [](uint64_t value) { return string_VkImageCreateFlags(static_cast<VkImageCreateFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_IMAGE_CREATE_SPARSE_BINDING_BIT | VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkSampleCountFlags",
     [](uint64_t value) { return Flags::SampleCountFlags(static_cast<VkSampleCountFlags>(value)); },
     [](uint64_t value) { return string_VkSampleCountFlags(static_cast<VkSampleCountFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_SAMPLE_COUNT_1_BIT | VK_SAMPLE_COUNT_2_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkImageUsageFlags",
     [](uint64_t value) { return Flags::ImageUsageFlags(static_cast<VkImageUsageFlags>(value)); },
     [](uint64_t value) { return string_VkImageUsageFlags(static_cast<VkImageUsageFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkInstanceCreateFlags",
     [](uint64_t value) { return Flags::InstanceCreateFlags(static_cast<VkInstanceCreateFlags>(value)); },
     [](uint64_t value) { return string_VkInstanceCreateFlags(static_cast<VkInstanceCreateFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkMemoryHeapFlags",
     [](uint64_t value) { return Flags::MemoryHeapFlags(static_cast<VkMemoryHeapFlags>(value)); },
     [](uint64_t value) { return string_VkMemoryHeapFlags(static_cast<VkMemoryHeapFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_MEMORY_HEAP_DEVICE_LOCAL_BIT | VK_MEMORY_HEAP_MULTI_INSTANCE_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkMemoryPropertyFlags",
     [](uint64_t value) { return Flags::MemoryPropertyFlags(static_cast<VkMemoryPropertyFlags>(value)); },
     [](uint64_t value) { return string_VkMemoryPropertyFlags(static_cast<VkMemoryPropertyFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkQueueFlags",
     [](uint64_t value) { return Flags::QueueFlags(static_cast<VkQueueFlags>(value)); },
     [](uint64_t value) { return string_VkQueueFlags(static_cast<VkQueueFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkShaderStageFlags",
     [](uint64_t value) { return Flags::ShaderStageFlags(static_cast<VkShaderStageFlags>(value)); },
     [](uint64_t value) { return string_VkShaderStageFlags(static_cast<VkShaderStageFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_SHADER_STAGE_ALL_GRAPHICS),
      static_cast<uint64_t>(VK_SHADER_STAGE_ALL_GRAPHICS | (uint64_t(1) << 31)), static_cast<uint64_t>(VK_SHADER_STAGE_ALL),
      static_cast<uint64_t>(VK_SHADER_STAGE_ALL | (uint64_t(1) << 31)),
      static_cast<uint64_t>(VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkDeviceQueueCreateFlags",
     [](uint64_t value) { return Flags::DeviceQueueCreateFlags(static_cast<VkDeviceQueueCreateFlags>(value)); },
     [](uint64_t value) { return string_VkDeviceQueueCreateFlags(static_cast<VkDeviceQueueCreateFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_DEVICE_QUEUE_CREATE_PROTECTED_BIT | VK_DEVICE_QUEUE_CREATE_INTERNALLY_SYNCHRONIZED_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkPipelineStageFlags",
     [](uint64_t value) { return Flags::PipelineStageFlags(static_cast<VkPipelineStageFlags>(value)); },
     [](uint64_t value) { return string_VkPipelineStageFlags(static_cast<VkPipelineStageFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT | VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkMemoryMapFlags",
     [](uint64_t value) { return Flags::MemoryMapFlags(static_cast<VkMemoryMapFlags>(value)); },
     [](uint64_t value) { return string_VkMemoryMapFlags(static_cast<VkMemoryMapFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkImageAspectFlags",
     [](uint64_t value) { return Flags::ImageAspectFlags(static_cast<VkImageAspectFlags>(value)); },
     [](uint64_t value) { return string_VkImageAspectFlags(static_cast<VkImageAspectFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_IMAGE_ASPECT_COLOR_BIT | VK_IMAGE_ASPECT_DEPTH_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkSparseImageFormatFlags",
     [](uint64_t value) { return Flags::SparseImageFormatFlags(static_cast<VkSparseImageFormatFlags>(value)); },
     [](uint64_t value) { return string_VkSparseImageFormatFlags(static_cast<VkSparseImageFormatFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT | VK_SPARSE_IMAGE_FORMAT_ALIGNED_MIP_SIZE_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkSparseMemoryBindFlags",
     [](uint64_t value) { return Flags::SparseMemoryBindFlags(static_cast<VkSparseMemoryBindFlags>(value)); },
     [](uint64_t value) { return string_VkSparseMemoryBindFlags(static_cast<VkSparseMemoryBindFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkFenceCreateFlags",
     [](uint64_t value) { return Flags::FenceCreateFlags(static_cast<VkFenceCreateFlags>(value)); },
     [](uint64_t value) { return string_VkFenceCreateFlags(static_cast<VkFenceCreateFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkQueryPoolCreateFlags",
     [](uint64_t value) { return Flags::QueryPoolCreateFlags(static_cast<VkQueryPoolCreateFlags>(value)); },
     [](uint64_t value) { return string_VkQueryPoolCreateFlags(static_cast<VkQueryPoolCreateFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkQueryPipelineStatisticFlags",
     [](uint64_t value) { return Flags::QueryPipelineStatisticFlags(static_cast<VkQueryPipelineStatisticFlags>(value)); },
     [](uint64_t value) { return string_VkQueryPipelineStatisticFlags(static_cast<VkQueryPipelineStatisticFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_VERTICES_BIT |
                            VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_PRIMITIVES_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkQueryResultFlags",
     [](uint64_t value) { return Flags::QueryResultFlags(static_cast<VkQueryResultFlags>(value)); },
     [](uint64_t value) { return string_VkQueryResultFlags(static_cast<VkQueryResultFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_QUERY_RESULT_64_BIT | VK_QUERY_RESULT_WAIT_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkBufferCreateFlags",
     [](uint64_t value) { return Flags::BufferCreateFlags(static_cast<VkBufferCreateFlags>(value)); },
     [](uint64_t value) { return string_VkBufferCreateFlags(static_cast<VkBufferCreateFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_BUFFER_CREATE_SPARSE_BINDING_BIT | VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkBufferUsageFlags",
     [](uint64_t value) { return Flags::BufferUsageFlags(static_cast<VkBufferUsageFlags>(value)); },
     [](uint64_t value) { return string_VkBufferUsageFlags(static_cast<VkBufferUsageFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkImageViewCreateFlags",
     [](uint64_t value) { return Flags::ImageViewCreateFlags(static_cast<VkImageViewCreateFlags>(value)); },
     [](uint64_t value) { return string_VkImageViewCreateFlags(static_cast<VkImageViewCreateFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DYNAMIC_BIT_EXT |
                            VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DEFERRED_BIT_EXT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkAccessFlags",
     [](uint64_t value) { return Flags::AccessFlags(static_cast<VkAccessFlags>(value)); },
     [](uint64_t value) { return string_VkAccessFlags(static_cast<VkAccessFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_ACCESS_INDIRECT_COMMAND_READ_BIT | VK_ACCESS_INDEX_READ_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkDependencyFlags",
     [](uint64_t value) { return Flags::DependencyFlags(static_cast<VkDependencyFlags>(value)); },
     [](uint64_t value) { return string_VkDependencyFlags(static_cast<VkDependencyFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_DEPENDENCY_BY_REGION_BIT | VK_DEPENDENCY_VIEW_LOCAL_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkCommandPoolCreateFlags",
     [](uint64_t value) { return Flags::CommandPoolCreateFlags(static_cast<VkCommandPoolCreateFlags>(value)); },
     [](uint64_t value) { return string_VkCommandPoolCreateFlags(static_cast<VkCommandPoolCreateFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkCommandPoolResetFlags",
     [](uint64_t value) { return Flags::CommandPoolResetFlags(static_cast<VkCommandPoolResetFlags>(value)); },
     [](uint64_t value) { return string_VkCommandPoolResetFlags(static_cast<VkCommandPoolResetFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkQueryControlFlags",
     [](uint64_t value) { return Flags::QueryControlFlags(static_cast<VkQueryControlFlags>(value)); },
     [](uint64_t value) { return string_VkQueryControlFlags(static_cast<VkQueryControlFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkCommandBufferUsageFlags",
     [](uint64_t value) { return Flags::CommandBufferUsageFlags(static_cast<VkCommandBufferUsageFlags>(value)); },
     [](uint64_t value) { return string_VkCommandBufferUsageFlags(static_cast<VkCommandBufferUsageFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT | VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkCommandBufferResetFlags",
     [](uint64_t value) { return Flags::CommandBufferResetFlags(static_cast<VkCommandBufferResetFlags>(value)); },
     [](uint64_t value) { return string_VkCommandBufferResetFlags(static_cast<VkCommandBufferResetFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkEventCreateFlags",
     [](uint64_t value) { return Flags::EventCreateFlags(static_cast<VkEventCreateFlags>(value)); },
     [](uint64_t value) { return string_VkEventCreateFlags(static_cast<VkEventCreateFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkPipelineCacheCreateFlags",
     [](uint64_t value) { return Flags::PipelineCacheCreateFlags(static_cast<VkPipelineCacheCreateFlags>(value)); },
     [](uint64_t value) { return string_VkPipelineCacheCreateFlags(static_cast<VkPipelineCacheCreateFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_PIPELINE_CACHE_CREATE_EXTERNALLY_SYNCHRONIZED_BIT |
                            VK_PIPELINE_CACHE_CREATE_INTERNALLY_SYNCHRONIZED_MERGE_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkPipelineCreateFlags",
     [](uint64_t value) { return Flags::PipelineCreateFlags(static_cast<VkPipelineCreateFlags>(value)); },
     [](uint64_t value) { return string_VkPipelineCreateFlags(static_cast<VkPipelineCreateFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT | VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkPipelineLayoutCreateFlags",
     [](uint64_t value) { return Flags::PipelineLayoutCreateFlags(static_cast<VkPipelineLayoutCreateFlags>(value)); },
     [](uint64_t value) { return string_VkPipelineLayoutCreateFlags(static_cast<VkPipelineLayoutCreateFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT | VK_PIPELINE_LAYOUT_CREATE_NO_TASK_SHADER_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkPipelineShaderStageCreateFlags",
     [](uint64_t value) { return Flags::PipelineShaderStageCreateFlags(static_cast<VkPipelineShaderStageCreateFlags>(value)); },
     [](uint64_t value) { return string_VkPipelineShaderStageCreateFlags(static_cast<VkPipelineShaderStageCreateFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT |
                            VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkSamplerCreateFlags",
     [](uint64_t value) { return Flags::SamplerCreateFlags(static_cast<VkSamplerCreateFlags>(value)); },
     [](uint64_t value) { return string_VkSamplerCreateFlags(static_cast<VkSamplerCreateFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_SAMPLER_CREATE_SUBSAMPLED_BIT_EXT | VK_SAMPLER_CREATE_SUBSAMPLED_COARSE_RECONSTRUCTION_BIT_EXT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkDescriptorPoolCreateFlags",
     [](uint64_t value) { return Flags::DescriptorPoolCreateFlags(static_cast<VkDescriptorPoolCreateFlags>(value)); },
     [](uint64_t value) { return string_VkDescriptorPoolCreateFlags(static_cast<VkDescriptorPoolCreateFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT | VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkDescriptorSetLayoutCreateFlags",
     [](uint64_t value) { return Flags::DescriptorSetLayoutCreateFlags(static_cast<VkDescriptorSetLayoutCreateFlags>(value)); },
     [](uint64_t value) { return string_VkDescriptorSetLayoutCreateFlags(static_cast<VkDescriptorSetLayoutCreateFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT |
                            VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkColorComponentFlags",
     [](uint64_t value) { return Flags::ColorComponentFlags(static_cast<VkColorComponentFlags>(value)); },
     [](uint64_t value) { return string_VkColorComponentFlags(static_cast<VkColorComponentFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkCullModeFlags",
     [](uint64_t value) { return Flags::CullModeFlags(static_cast<VkCullModeFlags>(value)); },
     [](uint64_t value) { return string_VkCullModeFlags(static_cast<VkCullModeFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_CULL_MODE_FRONT_AND_BACK),
      static_cast<uint64_t>(VK_CULL_MODE_FRONT_AND_BACK | (uint64_t(1) << 31)),
      static_cast<uint64_t>(VK_CULL_MODE_FRONT_BIT | VK_CULL_MODE_BACK_BIT), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkPipelineColorBlendStateCreateFlags",
     [](uint64_t value) {
         return Flags::PipelineColorBlendStateCreateFlags(static_cast<VkPipelineColorBlendStateCreateFlags>(value));
     },
     [](uint64_t value) {
         return string_VkPipelineColorBlendStateCreateFlags(static_cast<VkPipelineColorBlendStateCreateFlags>(value));
     },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkPipelineDepthStencilStateCreateFlags",
     [](uint64_t value) {
         return Flags::PipelineDepthStencilStateCreateFlags(static_cast<VkPipelineDepthStencilStateCreateFlags>(value));
     },
     [](uint64_t value) {
         return string_VkPipelineDepthStencilStateCreateFlags(static_cast<VkPipelineDepthStencilStateCreateFlags>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_DEPTH_ACCESS_BIT_EXT |
                            VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_STENCIL_ACCESS_BIT_EXT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkAttachmentDescriptionFlags",
     [](uint64_t value) { return Flags::AttachmentDescriptionFlags(static_cast<VkAttachmentDescriptionFlags>(value)); },
     [](uint64_t value) { return string_VkAttachmentDescriptionFlags(static_cast<VkAttachmentDescriptionFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT |
                            VK_ATTACHMENT_DESCRIPTION_RESOLVE_SKIP_TRANSFER_FUNCTION_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkFramebufferCreateFlags",
     [](uint64_t value) { return Flags::FramebufferCreateFlags(static_cast<VkFramebufferCreateFlags>(value)); },
     [](uint64_t value) { return string_VkFramebufferCreateFlags(static_cast<VkFramebufferCreateFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkRenderPassCreateFlags",
     [](uint64_t value) { return Flags::RenderPassCreateFlags(static_cast<VkRenderPassCreateFlags>(value)); },
     [](uint64_t value) { return string_VkRenderPassCreateFlags(static_cast<VkRenderPassCreateFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_RENDER_PASS_CREATE_TRANSFORM_BIT_QCOM | VK_RENDER_PASS_CREATE_PER_LAYER_FRAGMENT_DENSITY_BIT_VALVE),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkSubpassDescriptionFlags",
     [](uint64_t value) { return Flags::SubpassDescriptionFlags(static_cast<VkSubpassDescriptionFlags>(value)); },
     [](uint64_t value) { return string_VkSubpassDescriptionFlags(static_cast<VkSubpassDescriptionFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_SUBPASS_DESCRIPTION_PER_VIEW_ATTRIBUTES_BIT_NVX |
                            VK_SUBPASS_DESCRIPTION_PER_VIEW_POSITION_X_ONLY_BIT_NVX),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkStencilFaceFlags",
     [](uint64_t value) { return Flags::StencilFaceFlags(static_cast<VkStencilFaceFlags>(value)); },
     [](uint64_t value) { return string_VkStencilFaceFlags(static_cast<VkStencilFaceFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_STENCIL_FACE_FRONT_AND_BACK),
      static_cast<uint64_t>(VK_STENCIL_FACE_FRONT_AND_BACK | (uint64_t(1) << 31)),
      static_cast<uint64_t>(VK_STENCIL_FACE_FRONT_BIT | VK_STENCIL_FACE_BACK_BIT), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkSubgroupFeatureFlags",
     [](uint64_t value) { return Flags::SubgroupFeatureFlags(static_cast<VkSubgroupFeatureFlags>(value)); },
     [](uint64_t value) { return string_VkSubgroupFeatureFlags(static_cast<VkSubgroupFeatureFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_SUBGROUP_FEATURE_BASIC_BIT | VK_SUBGROUP_FEATURE_VOTE_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkPeerMemoryFeatureFlags",
     [](uint64_t value) { return Flags::PeerMemoryFeatureFlags(static_cast<VkPeerMemoryFeatureFlags>(value)); },
     [](uint64_t value) { return string_VkPeerMemoryFeatureFlags(static_cast<VkPeerMemoryFeatureFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_PEER_MEMORY_FEATURE_COPY_SRC_BIT | VK_PEER_MEMORY_FEATURE_COPY_DST_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkMemoryAllocateFlags",
     [](uint64_t value) { return Flags::MemoryAllocateFlags(static_cast<VkMemoryAllocateFlags>(value)); },
     [](uint64_t value) { return string_VkMemoryAllocateFlags(static_cast<VkMemoryAllocateFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_MEMORY_ALLOCATE_DEVICE_MASK_BIT | VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkExternalMemoryHandleTypeFlags",
     [](uint64_t value) { return Flags::ExternalMemoryHandleTypeFlags(static_cast<VkExternalMemoryHandleTypeFlags>(value)); },
     [](uint64_t value) { return string_VkExternalMemoryHandleTypeFlags(static_cast<VkExternalMemoryHandleTypeFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT | VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkExternalMemoryFeatureFlags",
     [](uint64_t value) { return Flags::ExternalMemoryFeatureFlags(static_cast<VkExternalMemoryFeatureFlags>(value)); },
     [](uint64_t value) { return string_VkExternalMemoryFeatureFlags(static_cast<VkExternalMemoryFeatureFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT | VK_EXTERNAL_MEMORY_FEATURE_EXPORTABLE_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkExternalFenceHandleTypeFlags",
     [](uint64_t value) { return Flags::ExternalFenceHandleTypeFlags(static_cast<VkExternalFenceHandleTypeFlags>(value)); },
     [](uint64_t value) { return string_VkExternalFenceHandleTypeFlags(static_cast<VkExternalFenceHandleTypeFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_FD_BIT | VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_WIN32_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkExternalFenceFeatureFlags",
     [](uint64_t value) { return Flags::ExternalFenceFeatureFlags(static_cast<VkExternalFenceFeatureFlags>(value)); },
     [](uint64_t value) { return string_VkExternalFenceFeatureFlags(static_cast<VkExternalFenceFeatureFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_EXTERNAL_FENCE_FEATURE_EXPORTABLE_BIT | VK_EXTERNAL_FENCE_FEATURE_IMPORTABLE_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkFenceImportFlags",
     [](uint64_t value) { return Flags::FenceImportFlags(static_cast<VkFenceImportFlags>(value)); },
     [](uint64_t value) { return string_VkFenceImportFlags(static_cast<VkFenceImportFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkSemaphoreImportFlags",
     [](uint64_t value) { return Flags::SemaphoreImportFlags(static_cast<VkSemaphoreImportFlags>(value)); },
     [](uint64_t value) { return string_VkSemaphoreImportFlags(static_cast<VkSemaphoreImportFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkExternalSemaphoreHandleTypeFlags",
     [](uint64_t value) { return Flags::ExternalSemaphoreHandleTypeFlags(static_cast<VkExternalSemaphoreHandleTypeFlags>(value)); },
     [](uint64_t value) {
         return string_VkExternalSemaphoreHandleTypeFlags(static_cast<VkExternalSemaphoreHandleTypeFlags>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT | VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkExternalSemaphoreFeatureFlags",
     [](uint64_t value) { return Flags::ExternalSemaphoreFeatureFlags(static_cast<VkExternalSemaphoreFeatureFlags>(value)); },
     [](uint64_t value) { return string_VkExternalSemaphoreFeatureFlags(static_cast<VkExternalSemaphoreFeatureFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_EXTERNAL_SEMAPHORE_FEATURE_EXPORTABLE_BIT | VK_EXTERNAL_SEMAPHORE_FEATURE_IMPORTABLE_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkResolveModeFlags",
     [](uint64_t value) { return Flags::ResolveModeFlags(static_cast<VkResolveModeFlags>(value)); },
     [](uint64_t value) { return string_VkResolveModeFlags(static_cast<VkResolveModeFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_RESOLVE_MODE_SAMPLE_ZERO_BIT | VK_RESOLVE_MODE_AVERAGE_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkSemaphoreWaitFlags",
     [](uint64_t value) { return Flags::SemaphoreWaitFlags(static_cast<VkSemaphoreWaitFlags>(value)); },
     [](uint64_t value) { return string_VkSemaphoreWaitFlags(static_cast<VkSemaphoreWaitFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkDescriptorBindingFlags",
     [](uint64_t value) { return Flags::DescriptorBindingFlags(static_cast<VkDescriptorBindingFlags>(value)); },
     [](uint64_t value) { return string_VkDescriptorBindingFlags(static_cast<VkDescriptorBindingFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT | VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkToolPurposeFlags",
     [](uint64_t value) { return Flags::ToolPurposeFlags(static_cast<VkToolPurposeFlags>(value)); },
     [](uint64_t value) { return string_VkToolPurposeFlags(static_cast<VkToolPurposeFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_TOOL_PURPOSE_VALIDATION_BIT | VK_TOOL_PURPOSE_PROFILING_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkPrivateDataSlotCreateFlags",
     [](uint64_t value) { return Flags::PrivateDataSlotCreateFlags(static_cast<VkPrivateDataSlotCreateFlags>(value)); },
     [](uint64_t value) { return string_VkPrivateDataSlotCreateFlags(static_cast<VkPrivateDataSlotCreateFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkPipelineStageFlags2",
     [](uint64_t value) { return Flags::PipelineStageFlags2(static_cast<VkPipelineStageFlags2>(value)); },
     [](uint64_t value) { return string_VkPipelineStageFlags2(static_cast<VkPipelineStageFlags2>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT | VK_PIPELINE_STAGE_2_DRAW_INDIRECT_BIT),
      static_cast<uint64_t>(uint64_t(1) << 63)}},
    {"VkAccessFlags2",
     [](uint64_t value) { return Flags::AccessFlags2(static_cast<VkAccessFlags2>(value)); },
     [](uint64_t value) { return string_VkAccessFlags2(static_cast<VkAccessFlags2>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_ACCESS_2_INDIRECT_COMMAND_READ_BIT | VK_ACCESS_2_INDEX_READ_BIT),
      static_cast<uint64_t>(uint64_t(1) << 63)}},
    {"VkSubmitFlags",
     [](uint64_t value) { return Flags::SubmitFlags(static_cast<VkSubmitFlags>(value)); },
     [](uint64_t value) { return string_VkSubmitFlags(static_cast<VkSubmitFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkFormatFeatureFlags2",
     [](uint64_t value) { return Flags::FormatFeatureFlags2(static_cast<VkFormatFeatureFlags2>(value)); },
     [](uint64_t value) { return string_VkFormatFeatureFlags2(static_cast<VkFormatFeatureFlags2>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_BIT | VK_FORMAT_FEATURE_2_STORAGE_IMAGE_BIT),
      static_cast<uint64_t>(uint64_t(1) << 63)}},
    {"VkPipelineCreationFeedbackFlags",
     [](uint64_t value) { return Flags::PipelineCreationFeedbackFlags(static_cast<VkPipelineCreationFeedbackFlags>(value)); },
     [](uint64_t value) { return string_VkPipelineCreationFeedbackFlags(static_cast<VkPipelineCreationFeedbackFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_PIPELINE_CREATION_FEEDBACK_VALID_BIT |
                            VK_PIPELINE_CREATION_FEEDBACK_APPLICATION_PIPELINE_CACHE_HIT_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkRenderingFlags",
     [](uint64_t value) { return Flags::RenderingFlags(static_cast<VkRenderingFlags>(value)); },
     [](uint64_t value) { return string_VkRenderingFlags(static_cast<VkRenderingFlags>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_RENDERING_CONTENTS_SECONDARY_COMMAND_BUFFERS_BIT | VK_RENDERING_SUSPENDING_BIT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkMemoryUnmapFlags",
     [](uint64_t value) { return Flags::MemoryUnmapFlags(static_cast<VkMemoryUnmapFlags>(value)); },
     [](uint64_t value) { return string_VkMemoryUnmapFlags(static_cast<VkMemoryUnmapFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkBufferUsageFlags2",
     [](uint64_t value) { return Flags::BufferUsageFlags2(static_cast<VkBufferUsageFlags2>(value)); },
     [](uint64_t value) { return string_VkBufferUsageFlags2(static_cast<VkBufferUsageFlags2>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_BUFFER_USAGE_2_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_2_TRANSFER_DST_BIT),
      static_cast<uint64_t>(uint64_t(1) << 63)}},
    {"VkHostImageCopyFlags",
     [](uint64_t value) { return Flags::HostImageCopyFlags(static_cast<VkHostImageCopyFlags>(value)); },
     [](uint64_t value) { return string_VkHostImageCopyFlags(static_cast<VkHostImageCopyFlags>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkPipelineCreateFlags2",
     [](uint64_t value) { return Flags::PipelineCreateFlags2(static_cast<VkPipelineCreateFlags2>(value)); },
     [](uint64_t value) { return string_VkPipelineCreateFlags2(static_cast<VkPipelineCreateFlags2>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_PIPELINE_CREATE_2_DISABLE_OPTIMIZATION_BIT | VK_PIPELINE_CREATE_2_ALLOW_DERIVATIVES_BIT),
      static_cast<uint64_t>(uint64_t(1) << 63)}},
    {"VkSurfaceTransformFlagsKHR",
     [](uint64_t value) { return Flags::SurfaceTransformFlagsKHR(static_cast<VkSurfaceTransformFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkSurfaceTransformFlagsKHR(static_cast<VkSurfaceTransformFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR | VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkCompositeAlphaFlagsKHR",
     [](uint64_t value) { return Flags::CompositeAlphaFlagsKHR(static_cast<VkCompositeAlphaFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkCompositeAlphaFlagsKHR(static_cast<VkCompositeAlphaFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR | VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkSwapchainCreateFlagsKHR",
     [](uint64_t value) { return Flags::SwapchainCreateFlagsKHR(static_cast<VkSwapchainCreateFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkSwapchainCreateFlagsKHR(static_cast<VkSwapchainCreateFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_SWAPCHAIN_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR | VK_SWAPCHAIN_CREATE_PROTECTED_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkDeviceGroupPresentModeFlagsKHR",
     [](uint64_t value) { return Flags::DeviceGroupPresentModeFlagsKHR(static_cast<VkDeviceGroupPresentModeFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkDeviceGroupPresentModeFlagsKHR(static_cast<VkDeviceGroupPresentModeFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR | VK_DEVICE_GROUP_PRESENT_MODE_REMOTE_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkDisplayPlaneAlphaFlagsKHR",
     [](uint64_t value) { return Flags::DisplayPlaneAlphaFlagsKHR(static_cast<VkDisplayPlaneAlphaFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkDisplayPlaneAlphaFlagsKHR(static_cast<VkDisplayPlaneAlphaFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR | VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoCodecOperationFlagsKHR",
     [](uint64_t value) { return Flags::VideoCodecOperationFlagsKHR(static_cast<VkVideoCodecOperationFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkVideoCodecOperationFlagsKHR(static_cast<VkVideoCodecOperationFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR | VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoChromaSubsamplingFlagsKHR",
     [](uint64_t value) { return Flags::VideoChromaSubsamplingFlagsKHR(static_cast<VkVideoChromaSubsamplingFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkVideoChromaSubsamplingFlagsKHR(static_cast<VkVideoChromaSubsamplingFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_CHROMA_SUBSAMPLING_MONOCHROME_BIT_KHR | VK_VIDEO_CHROMA_SUBSAMPLING_420_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoComponentBitDepthFlagsKHR",
     [](uint64_t value) { return Flags::VideoComponentBitDepthFlagsKHR(static_cast<VkVideoComponentBitDepthFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkVideoComponentBitDepthFlagsKHR(static_cast<VkVideoComponentBitDepthFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR | VK_VIDEO_COMPONENT_BIT_DEPTH_10_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoCapabilityFlagsKHR",
     [](uint64_t value) { return Flags::VideoCapabilityFlagsKHR(static_cast<VkVideoCapabilityFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkVideoCapabilityFlagsKHR(static_cast<VkVideoCapabilityFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_CAPABILITY_PROTECTED_CONTENT_BIT_KHR | VK_VIDEO_CAPABILITY_SEPARATE_REFERENCE_IMAGES_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoSessionCreateFlagsKHR",
     [](uint64_t value) { return Flags::VideoSessionCreateFlagsKHR(static_cast<VkVideoSessionCreateFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkVideoSessionCreateFlagsKHR(static_cast<VkVideoSessionCreateFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_SESSION_CREATE_PROTECTED_CONTENT_BIT_KHR |
                            VK_VIDEO_SESSION_CREATE_ALLOW_ENCODE_PARAMETER_OPTIMIZATIONS_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoSessionParametersCreateFlagsKHR",
     [](uint64_t value) {
         return Flags::VideoSessionParametersCreateFlagsKHR(static_cast<VkVideoSessionParametersCreateFlagsKHR>(value));
     },
     [](uint64_t value) {
         return string_VkVideoSessionParametersCreateFlagsKHR(static_cast<VkVideoSessionParametersCreateFlagsKHR>(value));
     },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoCodingControlFlagsKHR",
     [](uint64_t value) { return Flags::VideoCodingControlFlagsKHR(static_cast<VkVideoCodingControlFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkVideoCodingControlFlagsKHR(static_cast<VkVideoCodingControlFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_CODING_CONTROL_RESET_BIT_KHR | VK_VIDEO_CODING_CONTROL_ENCODE_RATE_CONTROL_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoDecodeCapabilityFlagsKHR",
     [](uint64_t value) { return Flags::VideoDecodeCapabilityFlagsKHR(static_cast<VkVideoDecodeCapabilityFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkVideoDecodeCapabilityFlagsKHR(static_cast<VkVideoDecodeCapabilityFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_DECODE_CAPABILITY_DPB_AND_OUTPUT_COINCIDE_BIT_KHR |
                            VK_VIDEO_DECODE_CAPABILITY_DPB_AND_OUTPUT_DISTINCT_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoDecodeUsageFlagsKHR",
     [](uint64_t value) { return Flags::VideoDecodeUsageFlagsKHR(static_cast<VkVideoDecodeUsageFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkVideoDecodeUsageFlagsKHR(static_cast<VkVideoDecodeUsageFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_DECODE_USAGE_TRANSCODING_BIT_KHR | VK_VIDEO_DECODE_USAGE_OFFLINE_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeH264CapabilityFlagsKHR",
     [](uint64_t value) {
         return Flags::VideoEncodeH264CapabilityFlagsKHR(static_cast<VkVideoEncodeH264CapabilityFlagsKHR>(value));
     },
     [](uint64_t value) {
         return string_VkVideoEncodeH264CapabilityFlagsKHR(static_cast<VkVideoEncodeH264CapabilityFlagsKHR>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_H264_CAPABILITY_HRD_COMPLIANCE_BIT_KHR |
                            VK_VIDEO_ENCODE_H264_CAPABILITY_PREDICTION_WEIGHT_TABLE_GENERATED_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeH264StdFlagsKHR",
     [](uint64_t value) { return Flags::VideoEncodeH264StdFlagsKHR(static_cast<VkVideoEncodeH264StdFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkVideoEncodeH264StdFlagsKHR(static_cast<VkVideoEncodeH264StdFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_H264_STD_SEPARATE_COLOR_PLANE_FLAG_SET_BIT_KHR |
                            VK_VIDEO_ENCODE_H264_STD_QPPRIME_Y_ZERO_TRANSFORM_BYPASS_FLAG_SET_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeH264RateControlFlagsKHR",
     [](uint64_t value) {
         return Flags::VideoEncodeH264RateControlFlagsKHR(static_cast<VkVideoEncodeH264RateControlFlagsKHR>(value));
     },
     [](uint64_t value) {
         return string_VkVideoEncodeH264RateControlFlagsKHR(static_cast<VkVideoEncodeH264RateControlFlagsKHR>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_H264_RATE_CONTROL_ATTEMPT_HRD_COMPLIANCE_BIT_KHR |
                            VK_VIDEO_ENCODE_H264_RATE_CONTROL_REGULAR_GOP_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeH265CapabilityFlagsKHR",
     [](uint64_t value) {
         return Flags::VideoEncodeH265CapabilityFlagsKHR(static_cast<VkVideoEncodeH265CapabilityFlagsKHR>(value));
     },
     [](uint64_t value) {
         return string_VkVideoEncodeH265CapabilityFlagsKHR(static_cast<VkVideoEncodeH265CapabilityFlagsKHR>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_H265_CAPABILITY_HRD_COMPLIANCE_BIT_KHR |
                            VK_VIDEO_ENCODE_H265_CAPABILITY_PREDICTION_WEIGHT_TABLE_GENERATED_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeH265StdFlagsKHR",
     [](uint64_t value) { return Flags::VideoEncodeH265StdFlagsKHR(static_cast<VkVideoEncodeH265StdFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkVideoEncodeH265StdFlagsKHR(static_cast<VkVideoEncodeH265StdFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_H265_STD_SEPARATE_COLOR_PLANE_FLAG_SET_BIT_KHR |
                            VK_VIDEO_ENCODE_H265_STD_SAMPLE_ADAPTIVE_OFFSET_ENABLED_FLAG_SET_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeH265CtbSizeFlagsKHR",
     [](uint64_t value) { return Flags::VideoEncodeH265CtbSizeFlagsKHR(static_cast<VkVideoEncodeH265CtbSizeFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkVideoEncodeH265CtbSizeFlagsKHR(static_cast<VkVideoEncodeH265CtbSizeFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_H265_CTB_SIZE_16_BIT_KHR | VK_VIDEO_ENCODE_H265_CTB_SIZE_32_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeH265TransformBlockSizeFlagsKHR",
     [](uint64_t value) {
         return Flags::VideoEncodeH265TransformBlockSizeFlagsKHR(static_cast<VkVideoEncodeH265TransformBlockSizeFlagsKHR>(value));
     },
     [](uint64_t value) {
         return string_VkVideoEncodeH265TransformBlockSizeFlagsKHR(static_cast<VkVideoEncodeH265TransformBlockSizeFlagsKHR>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_H265_TRANSFORM_BLOCK_SIZE_4_BIT_KHR |
                            VK_VIDEO_ENCODE_H265_TRANSFORM_BLOCK_SIZE_8_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeH265RateControlFlagsKHR",
     [](uint64_t value) {
         return Flags::VideoEncodeH265RateControlFlagsKHR(static_cast<VkVideoEncodeH265RateControlFlagsKHR>(value));
     },
     [](uint64_t value) {
         return string_VkVideoEncodeH265RateControlFlagsKHR(static_cast<VkVideoEncodeH265RateControlFlagsKHR>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_H265_RATE_CONTROL_ATTEMPT_HRD_COMPLIANCE_BIT_KHR |
                            VK_VIDEO_ENCODE_H265_RATE_CONTROL_REGULAR_GOP_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoDecodeH264PictureLayoutFlagsKHR",
     [](uint64_t value) {
         return Flags::VideoDecodeH264PictureLayoutFlagsKHR(static_cast<VkVideoDecodeH264PictureLayoutFlagsKHR>(value));
     },
     [](uint64_t value) {
         return string_VkVideoDecodeH264PictureLayoutFlagsKHR(static_cast<VkVideoDecodeH264PictureLayoutFlagsKHR>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_DECODE_H264_PICTURE_LAYOUT_INTERLACED_INTERLEAVED_LINES_BIT_KHR |
                            VK_VIDEO_DECODE_H264_PICTURE_LAYOUT_INTERLACED_SEPARATE_PLANES_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkPerformanceCounterDescriptionFlagsKHR",
     [](uint64_t value) {
         return Flags::PerformanceCounterDescriptionFlagsKHR(static_cast<VkPerformanceCounterDescriptionFlagsKHR>(value));
     },
     [](uint64_t value) {
         return string_VkPerformanceCounterDescriptionFlagsKHR(static_cast<VkPerformanceCounterDescriptionFlagsKHR>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_PERFORMANCE_COUNTER_DESCRIPTION_PERFORMANCE_IMPACTING_BIT_KHR |
                            VK_PERFORMANCE_COUNTER_DESCRIPTION_CONCURRENTLY_IMPACTED_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeFlagsKHR",
     [](uint64_t value) { return Flags::VideoEncodeFlagsKHR(static_cast<VkVideoEncodeFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkVideoEncodeFlagsKHR(static_cast<VkVideoEncodeFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_WITH_QUANTIZATION_DELTA_MAP_BIT_KHR | VK_VIDEO_ENCODE_WITH_EMPHASIS_MAP_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeCapabilityFlagsKHR",
     [](uint64_t value) { return Flags::VideoEncodeCapabilityFlagsKHR(static_cast<VkVideoEncodeCapabilityFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkVideoEncodeCapabilityFlagsKHR(static_cast<VkVideoEncodeCapabilityFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_CAPABILITY_PRECEDING_EXTERNALLY_ENCODED_BYTES_BIT_KHR |
                            VK_VIDEO_ENCODE_CAPABILITY_INSUFFICIENT_BITSTREAM_BUFFER_RANGE_DETECTION_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeRateControlModeFlagsKHR",
     [](uint64_t value) {
         return Flags::VideoEncodeRateControlModeFlagsKHR(static_cast<VkVideoEncodeRateControlModeFlagsKHR>(value));
     },
     [](uint64_t value) {
         return string_VkVideoEncodeRateControlModeFlagsKHR(static_cast<VkVideoEncodeRateControlModeFlagsKHR>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DISABLED_BIT_KHR | VK_VIDEO_ENCODE_RATE_CONTROL_MODE_CBR_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeFeedbackFlagsKHR",
     [](uint64_t value) { return Flags::VideoEncodeFeedbackFlagsKHR(static_cast<VkVideoEncodeFeedbackFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkVideoEncodeFeedbackFlagsKHR(static_cast<VkVideoEncodeFeedbackFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_FEEDBACK_BITSTREAM_BUFFER_OFFSET_BIT_KHR |
                            VK_VIDEO_ENCODE_FEEDBACK_BITSTREAM_BYTES_WRITTEN_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeUsageFlagsKHR",
     [](uint64_t value) { return Flags::VideoEncodeUsageFlagsKHR(static_cast<VkVideoEncodeUsageFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkVideoEncodeUsageFlagsKHR(static_cast<VkVideoEncodeUsageFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_USAGE_TRANSCODING_BIT_KHR | VK_VIDEO_ENCODE_USAGE_STREAMING_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeContentFlagsKHR",
     [](uint64_t value) { return Flags::VideoEncodeContentFlagsKHR(static_cast<VkVideoEncodeContentFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkVideoEncodeContentFlagsKHR(static_cast<VkVideoEncodeContentFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_CONTENT_CAMERA_BIT_KHR | VK_VIDEO_ENCODE_CONTENT_DESKTOP_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkAddressCommandFlagsKHR",
     [](uint64_t value) { return Flags::AddressCommandFlagsKHR(static_cast<VkAddressCommandFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkAddressCommandFlagsKHR(static_cast<VkAddressCommandFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_ADDRESS_COMMAND_PROTECTED_BIT_KHR | VK_ADDRESS_COMMAND_FULLY_BOUND_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkConditionalRenderingFlagsEXT",
     [](uint64_t value) { return Flags::ConditionalRenderingFlagsEXT(static_cast<VkConditionalRenderingFlagsEXT>(value)); },
     [](uint64_t value) { return string_VkConditionalRenderingFlagsEXT(static_cast<VkConditionalRenderingFlagsEXT>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkAccelerationStructureCreateFlagsKHR",
     [](uint64_t value) {
         return Flags::AccelerationStructureCreateFlagsKHR(static_cast<VkAccelerationStructureCreateFlagsKHR>(value));
     },
     [](uint64_t value) {
         return string_VkAccelerationStructureCreateFlagsKHR(static_cast<VkAccelerationStructureCreateFlagsKHR>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_ACCELERATION_STRUCTURE_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT_KHR |
                            VK_ACCELERATION_STRUCTURE_CREATE_MOTION_BIT_NV),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkPresentScalingFlagsKHR",
     [](uint64_t value) { return Flags::PresentScalingFlagsKHR(static_cast<VkPresentScalingFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkPresentScalingFlagsKHR(static_cast<VkPresentScalingFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_PRESENT_SCALING_ONE_TO_ONE_BIT_KHR | VK_PRESENT_SCALING_ASPECT_RATIO_STRETCH_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkPresentGravityFlagsKHR",
     [](uint64_t value) { return Flags::PresentGravityFlagsKHR(static_cast<VkPresentGravityFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkPresentGravityFlagsKHR(static_cast<VkPresentGravityFlagsKHR>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_PRESENT_GRAVITY_MIN_BIT_KHR | VK_PRESENT_GRAVITY_MAX_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeAV1CapabilityFlagsKHR",
     [](uint64_t value) { return Flags::VideoEncodeAV1CapabilityFlagsKHR(static_cast<VkVideoEncodeAV1CapabilityFlagsKHR>(value)); },
     [](uint64_t value) {
         return string_VkVideoEncodeAV1CapabilityFlagsKHR(static_cast<VkVideoEncodeAV1CapabilityFlagsKHR>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_AV1_CAPABILITY_PER_RATE_CONTROL_GROUP_MIN_MAX_Q_INDEX_BIT_KHR |
                            VK_VIDEO_ENCODE_AV1_CAPABILITY_GENERATE_OBU_EXTENSION_HEADER_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeAV1StdFlagsKHR",
     [](uint64_t value) { return Flags::VideoEncodeAV1StdFlagsKHR(static_cast<VkVideoEncodeAV1StdFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkVideoEncodeAV1StdFlagsKHR(static_cast<VkVideoEncodeAV1StdFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_AV1_STD_UNIFORM_TILE_SPACING_FLAG_SET_BIT_KHR |
                            VK_VIDEO_ENCODE_AV1_STD_SKIP_MODE_PRESENT_UNSET_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeAV1SuperblockSizeFlagsKHR",
     [](uint64_t value) {
         return Flags::VideoEncodeAV1SuperblockSizeFlagsKHR(static_cast<VkVideoEncodeAV1SuperblockSizeFlagsKHR>(value));
     },
     [](uint64_t value) {
         return string_VkVideoEncodeAV1SuperblockSizeFlagsKHR(static_cast<VkVideoEncodeAV1SuperblockSizeFlagsKHR>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_AV1_SUPERBLOCK_SIZE_64_BIT_KHR | VK_VIDEO_ENCODE_AV1_SUPERBLOCK_SIZE_128_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeAV1RateControlFlagsKHR",
     [](uint64_t value) {
         return Flags::VideoEncodeAV1RateControlFlagsKHR(static_cast<VkVideoEncodeAV1RateControlFlagsKHR>(value));
     },
     [](uint64_t value) {
         return string_VkVideoEncodeAV1RateControlFlagsKHR(static_cast<VkVideoEncodeAV1RateControlFlagsKHR>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_AV1_RATE_CONTROL_REGULAR_GOP_BIT_KHR |
                            VK_VIDEO_ENCODE_AV1_RATE_CONTROL_TEMPORAL_LAYER_PATTERN_DYADIC_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkAddressCopyFlagsKHR",
     [](uint64_t value) { return Flags::AddressCopyFlagsKHR(static_cast<VkAddressCopyFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkAddressCopyFlagsKHR(static_cast<VkAddressCopyFlagsKHR>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_ADDRESS_COPY_DEVICE_LOCAL_BIT_KHR | VK_ADDRESS_COPY_SPARSE_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeIntraRefreshModeFlagsKHR",
     [](uint64_t value) {
         return Flags::VideoEncodeIntraRefreshModeFlagsKHR(static_cast<VkVideoEncodeIntraRefreshModeFlagsKHR>(value));
     },
     [](uint64_t value) {
         return string_VkVideoEncodeIntraRefreshModeFlagsKHR(static_cast<VkVideoEncodeIntraRefreshModeFlagsKHR>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_INTRA_REFRESH_MODE_PER_PICTURE_PARTITION_BIT_KHR |
                            VK_VIDEO_ENCODE_INTRA_REFRESH_MODE_BLOCK_BASED_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkDeviceFaultFlagsKHR",
     [](uint64_t value) { return Flags::DeviceFaultFlagsKHR(static_cast<VkDeviceFaultFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkDeviceFaultFlagsKHR(static_cast<VkDeviceFaultFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_DEVICE_FAULT_FLAG_DEVICE_LOST_KHR | VK_DEVICE_FAULT_FLAG_MEMORY_ADDRESS_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkAccessFlags3KHR",
     [](uint64_t value) { return Flags::AccessFlags3KHR(static_cast<VkAccessFlags3KHR>(value)); },
     [](uint64_t value) { return string_VkAccessFlags3KHR(static_cast<VkAccessFlags3KHR>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 63)}},
    {"VkVideoEncodePerPartitionFeedbackFlagsKHR",
     [](uint64_t value) {
         return Flags::VideoEncodePerPartitionFeedbackFlagsKHR(static_cast<VkVideoEncodePerPartitionFeedbackFlagsKHR>(value));
     },
     [](uint64_t value) {
         return string_VkVideoEncodePerPartitionFeedbackFlagsKHR(static_cast<VkVideoEncodePerPartitionFeedbackFlagsKHR>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_PER_PARTITION_FEEDBACK_STATUS_BIT_KHR |
                            VK_VIDEO_ENCODE_PER_PARTITION_FEEDBACK_BITSTREAM_BUFFER_OFFSET_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkRenderingAttachmentFlagsKHR",
     [](uint64_t value) { return Flags::RenderingAttachmentFlagsKHR(static_cast<VkRenderingAttachmentFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkRenderingAttachmentFlagsKHR(static_cast<VkRenderingAttachmentFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_RENDERING_ATTACHMENT_INPUT_ATTACHMENT_FEEDBACK_BIT_KHR |
                            VK_RENDERING_ATTACHMENT_RESOLVE_SKIP_TRANSFER_FUNCTION_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkResolveImageFlagsKHR",
     [](uint64_t value) { return Flags::ResolveImageFlagsKHR(static_cast<VkResolveImageFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkResolveImageFlagsKHR(static_cast<VkResolveImageFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_RESOLVE_IMAGE_SKIP_TRANSFER_FUNCTION_BIT_KHR | VK_RESOLVE_IMAGE_ENABLE_TRANSFER_FUNCTION_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkImageUsageFlags2KHR",
     [](uint64_t value) { return Flags::ImageUsageFlags2KHR(static_cast<VkImageUsageFlags2KHR>(value)); },
     [](uint64_t value) { return string_VkImageUsageFlags2KHR(static_cast<VkImageUsageFlags2KHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_IMAGE_USAGE_2_TRANSFER_SRC_BIT_KHR | VK_IMAGE_USAGE_2_TRANSFER_DST_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 63)}},
    {"VkImageCreateFlags2KHR",
     [](uint64_t value) { return Flags::ImageCreateFlags2KHR(static_cast<VkImageCreateFlags2KHR>(value)); },
     [](uint64_t value) { return string_VkImageCreateFlags2KHR(static_cast<VkImageCreateFlags2KHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_IMAGE_CREATE_2_SPARSE_BINDING_BIT_KHR | VK_IMAGE_CREATE_2_SPARSE_RESIDENCY_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 63)}},
    {"VkDebugReportFlagsEXT",
     [](uint64_t value) { return Flags::DebugReportFlagsEXT(static_cast<VkDebugReportFlagsEXT>(value)); },
     [](uint64_t value) { return string_VkDebugReportFlagsEXT(static_cast<VkDebugReportFlagsEXT>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_DEBUG_REPORT_INFORMATION_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkExternalMemoryHandleTypeFlagsNV",
     [](uint64_t value) { return Flags::ExternalMemoryHandleTypeFlagsNV(static_cast<VkExternalMemoryHandleTypeFlagsNV>(value)); },
     [](uint64_t value) { return string_VkExternalMemoryHandleTypeFlagsNV(static_cast<VkExternalMemoryHandleTypeFlagsNV>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT_NV |
                            VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT_NV),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkExternalMemoryFeatureFlagsNV",
     [](uint64_t value) { return Flags::ExternalMemoryFeatureFlagsNV(static_cast<VkExternalMemoryFeatureFlagsNV>(value)); },
     [](uint64_t value) { return string_VkExternalMemoryFeatureFlagsNV(static_cast<VkExternalMemoryFeatureFlagsNV>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT_NV | VK_EXTERNAL_MEMORY_FEATURE_EXPORTABLE_BIT_NV),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkSurfaceCounterFlagsEXT",
     [](uint64_t value) { return Flags::SurfaceCounterFlagsEXT(static_cast<VkSurfaceCounterFlagsEXT>(value)); },
     [](uint64_t value) { return string_VkSurfaceCounterFlagsEXT(static_cast<VkSurfaceCounterFlagsEXT>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkDebugUtilsMessageSeverityFlagsEXT",
     [](uint64_t value) {
         return Flags::DebugUtilsMessageSeverityFlagsEXT(static_cast<VkDebugUtilsMessageSeverityFlagsEXT>(value));
     },
     [](uint64_t value) {
         return string_VkDebugUtilsMessageSeverityFlagsEXT(static_cast<VkDebugUtilsMessageSeverityFlagsEXT>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkDebugUtilsMessageTypeFlagsEXT",
     [](uint64_t value) { return Flags::DebugUtilsMessageTypeFlagsEXT(static_cast<VkDebugUtilsMessageTypeFlagsEXT>(value)); },
     [](uint64_t value) { return string_VkDebugUtilsMessageTypeFlagsEXT(static_cast<VkDebugUtilsMessageTypeFlagsEXT>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkGpaSqShaderStageFlagsAMD",
     [](uint64_t value) { return Flags::GpaSqShaderStageFlagsAMD(static_cast<VkGpaSqShaderStageFlagsAMD>(value)); },
     [](uint64_t value) { return string_VkGpaSqShaderStageFlagsAMD(static_cast<VkGpaSqShaderStageFlagsAMD>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_GPA_SQ_SHADER_STAGE_PS_BIT_AMD | VK_GPA_SQ_SHADER_STAGE_VS_BIT_AMD),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkTensorViewCreateFlagsARM",
     [](uint64_t value) { return Flags::TensorViewCreateFlagsARM(static_cast<VkTensorViewCreateFlagsARM>(value)); },
     [](uint64_t value) { return string_VkTensorViewCreateFlagsARM(static_cast<VkTensorViewCreateFlagsARM>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 63)}},
    {"VkSpirvResourceTypeFlagsEXT",
     [](uint64_t value) { return Flags::SpirvResourceTypeFlagsEXT(static_cast<VkSpirvResourceTypeFlagsEXT>(value)); },
     [](uint64_t value) { return string_VkSpirvResourceTypeFlagsEXT(static_cast<VkSpirvResourceTypeFlagsEXT>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_SPIRV_RESOURCE_TYPE_ALL_EXT),
      static_cast<uint64_t>(VK_SPIRV_RESOURCE_TYPE_ALL_EXT | (uint64_t(1) << 31)),
      static_cast<uint64_t>(VK_SPIRV_RESOURCE_TYPE_SAMPLER_BIT_EXT | VK_SPIRV_RESOURCE_TYPE_SAMPLED_IMAGE_BIT_EXT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkGeometryFlagsKHR",
     [](uint64_t value) { return Flags::GeometryFlagsKHR(static_cast<VkGeometryFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkGeometryFlagsKHR(static_cast<VkGeometryFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_GEOMETRY_OPAQUE_BIT_KHR | VK_GEOMETRY_NO_DUPLICATE_ANY_HIT_INVOCATION_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkGeometryInstanceFlagsKHR",
     [](uint64_t value) { return Flags::GeometryInstanceFlagsKHR(static_cast<VkGeometryInstanceFlagsKHR>(value)); },
     [](uint64_t value) { return string_VkGeometryInstanceFlagsKHR(static_cast<VkGeometryInstanceFlagsKHR>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_GEOMETRY_INSTANCE_TRIANGLE_FACING_CULL_DISABLE_BIT_KHR |
                            VK_GEOMETRY_INSTANCE_TRIANGLE_FLIP_FACING_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkBuildAccelerationStructureFlagsKHR",
     [](uint64_t value) {
         return Flags::BuildAccelerationStructureFlagsKHR(static_cast<VkBuildAccelerationStructureFlagsKHR>(value));
     },
     [](uint64_t value) {
         return string_VkBuildAccelerationStructureFlagsKHR(static_cast<VkBuildAccelerationStructureFlagsKHR>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR |
                            VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkPresentStageFlagsEXT",
     [](uint64_t value) { return Flags::PresentStageFlagsEXT(static_cast<VkPresentStageFlagsEXT>(value)); },
     [](uint64_t value) { return string_VkPresentStageFlagsEXT(static_cast<VkPresentStageFlagsEXT>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_PRESENT_STAGE_QUEUE_OPERATIONS_END_BIT_EXT | VK_PRESENT_STAGE_REQUEST_DEQUEUED_BIT_EXT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkPastPresentationTimingFlagsEXT",
     [](uint64_t value) { return Flags::PastPresentationTimingFlagsEXT(static_cast<VkPastPresentationTimingFlagsEXT>(value)); },
     [](uint64_t value) { return string_VkPastPresentationTimingFlagsEXT(static_cast<VkPastPresentationTimingFlagsEXT>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_PAST_PRESENTATION_TIMING_ALLOW_PARTIAL_RESULTS_BIT_EXT |
                            VK_PAST_PRESENTATION_TIMING_ALLOW_OUT_OF_ORDER_RESULTS_BIT_EXT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkPresentTimingInfoFlagsEXT",
     [](uint64_t value) { return Flags::PresentTimingInfoFlagsEXT(static_cast<VkPresentTimingInfoFlagsEXT>(value)); },
     [](uint64_t value) { return string_VkPresentTimingInfoFlagsEXT(static_cast<VkPresentTimingInfoFlagsEXT>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_PRESENT_TIMING_INFO_PRESENT_AT_RELATIVE_TIME_BIT_EXT |
                            VK_PRESENT_TIMING_INFO_PRESENT_AT_NEAREST_REFRESH_CYCLE_BIT_EXT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkIndirectStateFlagsNV",
     [](uint64_t value) { return Flags::IndirectStateFlagsNV(static_cast<VkIndirectStateFlagsNV>(value)); },
     [](uint64_t value) { return string_VkIndirectStateFlagsNV(static_cast<VkIndirectStateFlagsNV>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkIndirectCommandsLayoutUsageFlagsNV",
     [](uint64_t value) {
         return Flags::IndirectCommandsLayoutUsageFlagsNV(static_cast<VkIndirectCommandsLayoutUsageFlagsNV>(value));
     },
     [](uint64_t value) {
         return string_VkIndirectCommandsLayoutUsageFlagsNV(static_cast<VkIndirectCommandsLayoutUsageFlagsNV>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_INDIRECT_COMMANDS_LAYOUT_USAGE_EXPLICIT_PREPROCESS_BIT_NV |
                            VK_INDIRECT_COMMANDS_LAYOUT_USAGE_INDEXED_SEQUENCES_BIT_NV),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkDeviceDiagnosticsConfigFlagsNV",
     [](uint64_t value) { return Flags::DeviceDiagnosticsConfigFlagsNV(static_cast<VkDeviceDiagnosticsConfigFlagsNV>(value)); },
     [](uint64_t value) { return string_VkDeviceDiagnosticsConfigFlagsNV(static_cast<VkDeviceDiagnosticsConfigFlagsNV>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_SHADER_DEBUG_INFO_BIT_NV |
                            VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_RESOURCE_TRACKING_BIT_NV),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkTileShadingRenderPassFlagsQCOM",
     [](uint64_t value) { return Flags::TileShadingRenderPassFlagsQCOM(static_cast<VkTileShadingRenderPassFlagsQCOM>(value)); },
     [](uint64_t value) { return string_VkTileShadingRenderPassFlagsQCOM(static_cast<VkTileShadingRenderPassFlagsQCOM>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_TILE_SHADING_RENDER_PASS_ENABLE_BIT_QCOM | VK_TILE_SHADING_RENDER_PASS_PER_TILE_EXECUTION_BIT_QCOM),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
#ifdef VK_USE_PLATFORM_METAL_EXT
    {"VkExportMetalObjectTypeFlagsEXT",
     [](uint64_t value) { return Flags::ExportMetalObjectTypeFlagsEXT(static_cast<VkExportMetalObjectTypeFlagsEXT>(value)); },
     [](uint64_t value) { return string_VkExportMetalObjectTypeFlagsEXT(static_cast<VkExportMetalObjectTypeFlagsEXT>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_BIT_EXT |
                            VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_QUEUE_BIT_EXT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
#endif  // VK_USE_PLATFORM_METAL_EXT
    {"VkGraphicsPipelineLibraryFlagsEXT",
     [](uint64_t value) { return Flags::GraphicsPipelineLibraryFlagsEXT(static_cast<VkGraphicsPipelineLibraryFlagsEXT>(value)); },
     [](uint64_t value) { return string_VkGraphicsPipelineLibraryFlagsEXT(static_cast<VkGraphicsPipelineLibraryFlagsEXT>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_GRAPHICS_PIPELINE_LIBRARY_VERTEX_INPUT_INTERFACE_BIT_EXT |
                            VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkImageCompressionFlagsEXT",
     [](uint64_t value) { return Flags::ImageCompressionFlagsEXT(static_cast<VkImageCompressionFlagsEXT>(value)); },
     [](uint64_t value) { return string_VkImageCompressionFlagsEXT(static_cast<VkImageCompressionFlagsEXT>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_IMAGE_COMPRESSION_FIXED_RATE_DEFAULT_EXT | VK_IMAGE_COMPRESSION_FIXED_RATE_EXPLICIT_EXT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkImageCompressionFixedRateFlagsEXT",
     [](uint64_t value) {
         return Flags::ImageCompressionFixedRateFlagsEXT(static_cast<VkImageCompressionFixedRateFlagsEXT>(value));
     },
     [](uint64_t value) {
         return string_VkImageCompressionFixedRateFlagsEXT(static_cast<VkImageCompressionFixedRateFlagsEXT>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_IMAGE_COMPRESSION_FIXED_RATE_1BPC_BIT_EXT | VK_IMAGE_COMPRESSION_FIXED_RATE_2BPC_BIT_EXT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkDeviceAddressBindingFlagsEXT",
     [](uint64_t value) { return Flags::DeviceAddressBindingFlagsEXT(static_cast<VkDeviceAddressBindingFlagsEXT>(value)); },
     [](uint64_t value) { return string_VkDeviceAddressBindingFlagsEXT(static_cast<VkDeviceAddressBindingFlagsEXT>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
#ifdef VK_USE_PLATFORM_FUCHSIA
    {"VkImageConstraintsInfoFlagsFUCHSIA",
     [](uint64_t value) { return Flags::ImageConstraintsInfoFlagsFUCHSIA(static_cast<VkImageConstraintsInfoFlagsFUCHSIA>(value)); },
     [](uint64_t value) {
         return string_VkImageConstraintsInfoFlagsFUCHSIA(static_cast<VkImageConstraintsInfoFlagsFUCHSIA>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_RARELY_FUCHSIA | VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_OFTEN_FUCHSIA),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
#endif  // VK_USE_PLATFORM_FUCHSIA
    {"VkFrameBoundaryFlagsEXT",
     [](uint64_t value) { return Flags::FrameBoundaryFlagsEXT(static_cast<VkFrameBoundaryFlagsEXT>(value)); },
     [](uint64_t value) { return string_VkFrameBoundaryFlagsEXT(static_cast<VkFrameBoundaryFlagsEXT>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeRgbModelConversionFlagsVALVE",
     [](uint64_t value) {
         return Flags::VideoEncodeRgbModelConversionFlagsVALVE(static_cast<VkVideoEncodeRgbModelConversionFlagsVALVE>(value));
     },
     [](uint64_t value) {
         return string_VkVideoEncodeRgbModelConversionFlagsVALVE(static_cast<VkVideoEncodeRgbModelConversionFlagsVALVE>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_RGB_MODEL_CONVERSION_RGB_IDENTITY_BIT_VALVE |
                            VK_VIDEO_ENCODE_RGB_MODEL_CONVERSION_YCBCR_IDENTITY_BIT_VALVE),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeRgbRangeCompressionFlagsVALVE",
     [](uint64_t value) {
         return Flags::VideoEncodeRgbRangeCompressionFlagsVALVE(static_cast<VkVideoEncodeRgbRangeCompressionFlagsVALVE>(value));
     },
     [](uint64_t value) {
         return string_VkVideoEncodeRgbRangeCompressionFlagsVALVE(static_cast<VkVideoEncodeRgbRangeCompressionFlagsVALVE>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_RGB_RANGE_COMPRESSION_FULL_RANGE_BIT_VALVE |
                            VK_VIDEO_ENCODE_RGB_RANGE_COMPRESSION_NARROW_RANGE_BIT_VALVE),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkVideoEncodeRgbChromaOffsetFlagsVALVE",
     [](uint64_t value) {
         return Flags::VideoEncodeRgbChromaOffsetFlagsVALVE(static_cast<VkVideoEncodeRgbChromaOffsetFlagsVALVE>(value));
     },
     [](uint64_t value) {
         return string_VkVideoEncodeRgbChromaOffsetFlagsVALVE(static_cast<VkVideoEncodeRgbChromaOffsetFlagsVALVE>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_VIDEO_ENCODE_RGB_CHROMA_OFFSET_COSITED_EVEN_BIT_VALVE |
                            VK_VIDEO_ENCODE_RGB_CHROMA_OFFSET_MIDPOINT_BIT_VALVE),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkBuildMicromapFlagsEXT",
     [](uint64_t value) { return Flags::BuildMicromapFlagsEXT(static_cast<VkBuildMicromapFlagsEXT>(value)); },
     [](uint64_t value) { return string_VkBuildMicromapFlagsEXT(static_cast<VkBuildMicromapFlagsEXT>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_BUILD_MICROMAP_PREFER_FAST_TRACE_BIT_EXT | VK_BUILD_MICROMAP_PREFER_FAST_BUILD_BIT_EXT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkMicromapCreateFlagsEXT",
     [](uint64_t value) { return Flags::MicromapCreateFlagsEXT(static_cast<VkMicromapCreateFlagsEXT>(value)); },
     [](uint64_t value) { return string_VkMicromapCreateFlagsEXT(static_cast<VkMicromapCreateFlagsEXT>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkPhysicalDeviceSchedulingControlsFlagsARM",
     [](uint64_t value) {
         return Flags::PhysicalDeviceSchedulingControlsFlagsARM(static_cast<VkPhysicalDeviceSchedulingControlsFlagsARM>(value));
     },
     [](uint64_t value) {
         return string_VkPhysicalDeviceSchedulingControlsFlagsARM(static_cast<VkPhysicalDeviceSchedulingControlsFlagsARM>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_PHYSICAL_DEVICE_SCHEDULING_CONTROLS_SHADER_CORE_COUNT_ARM |
                            VK_PHYSICAL_DEVICE_SCHEDULING_CONTROLS_DISPATCH_PARAMETERS_ARM),
      static_cast<uint64_t>(uint64_t(1) << 63)}},
    {"VkMemoryDecompressionMethodFlagsEXT",
     [](uint64_t value) {
         return Flags::MemoryDecompressionMethodFlagsEXT(static_cast<VkMemoryDecompressionMethodFlagsEXT>(value));
     },
     [](uint64_t value) {
         return string_VkMemoryDecompressionMethodFlagsEXT(static_cast<VkMemoryDecompressionMethodFlagsEXT>(value));
     },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 63)}},
    {"VkTensorCreateFlagsARM",
     [](uint64_t value) { return Flags::TensorCreateFlagsARM(static_cast<VkTensorCreateFlagsARM>(value)); },
     [](uint64_t value) { return string_VkTensorCreateFlagsARM(static_cast<VkTensorCreateFlagsARM>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_TENSOR_CREATE_MUTABLE_FORMAT_BIT_ARM | VK_TENSOR_CREATE_PROTECTED_BIT_ARM),
      static_cast<uint64_t>(uint64_t(1) << 63)}},
    {"VkTensorUsageFlagsARM",
     [](uint64_t value) { return Flags::TensorUsageFlagsARM(static_cast<VkTensorUsageFlagsARM>(value)); },
     [](uint64_t value) { return string_VkTensorUsageFlagsARM(static_cast<VkTensorUsageFlagsARM>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_TENSOR_USAGE_SHADER_BIT_ARM | VK_TENSOR_USAGE_TRANSFER_SRC_BIT_ARM),
      static_cast<uint64_t>(uint64_t(1) << 63)}},
    {"VkOpticalFlowGridSizeFlagsNV",
     [](uint64_t value) { return Flags::OpticalFlowGridSizeFlagsNV(static_cast<VkOpticalFlowGridSizeFlagsNV>(value)); },
     [](uint64_t value) { return string_VkOpticalFlowGridSizeFlagsNV(static_cast<VkOpticalFlowGridSizeFlagsNV>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_OPTICAL_FLOW_GRID_SIZE_1X1_BIT_NV | VK_OPTICAL_FLOW_GRID_SIZE_2X2_BIT_NV),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkOpticalFlowUsageFlagsNV",
     [](uint64_t value) { return Flags::OpticalFlowUsageFlagsNV(static_cast<VkOpticalFlowUsageFlagsNV>(value)); },
     [](uint64_t value) { return string_VkOpticalFlowUsageFlagsNV(static_cast<VkOpticalFlowUsageFlagsNV>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(VK_OPTICAL_FLOW_USAGE_INPUT_BIT_NV | VK_OPTICAL_FLOW_USAGE_OUTPUT_BIT_NV),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkOpticalFlowSessionCreateFlagsNV",
     [](uint64_t value) { return Flags::OpticalFlowSessionCreateFlagsNV(static_cast<VkOpticalFlowSessionCreateFlagsNV>(value)); },
     [](uint64_t value) { return string_VkOpticalFlowSessionCreateFlagsNV(static_cast<VkOpticalFlowSessionCreateFlagsNV>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_HINT_BIT_NV | VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_COST_BIT_NV),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkOpticalFlowExecuteFlagsNV",
     [](uint64_t value) { return Flags::OpticalFlowExecuteFlagsNV(static_cast<VkOpticalFlowExecuteFlagsNV>(value)); },
     [](uint64_t value) { return string_VkOpticalFlowExecuteFlagsNV(static_cast<VkOpticalFlowExecuteFlagsNV>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkShaderCreateFlagsEXT",
     [](uint64_t value) { return Flags::ShaderCreateFlagsEXT(static_cast<VkShaderCreateFlagsEXT>(value)); },
     [](uint64_t value) { return string_VkShaderCreateFlagsEXT(static_cast<VkShaderCreateFlagsEXT>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_SHADER_CREATE_LINK_STAGE_BIT_EXT | VK_SHADER_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT_EXT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkDataGraphPipelineSessionCreateFlagsARM",
     [](uint64_t value) {
         return Flags::DataGraphPipelineSessionCreateFlagsARM(static_cast<VkDataGraphPipelineSessionCreateFlagsARM>(value));
     },
     [](uint64_t value) {
         return string_VkDataGraphPipelineSessionCreateFlagsARM(static_cast<VkDataGraphPipelineSessionCreateFlagsARM>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_DATA_GRAPH_PIPELINE_SESSION_CREATE_PROTECTED_BIT_ARM |
                            VK_DATA_GRAPH_PIPELINE_SESSION_CREATE_OPTICAL_FLOW_CACHE_BIT_ARM),
      static_cast<uint64_t>(uint64_t(1) << 63)}},
    {"VkDataGraphTOSAQualityFlagsARM",
     [](uint64_t value) { return Flags::DataGraphTOSAQualityFlagsARM(static_cast<VkDataGraphTOSAQualityFlagsARM>(value)); },
     [](uint64_t value) { return string_VkDataGraphTOSAQualityFlagsARM(static_cast<VkDataGraphTOSAQualityFlagsARM>(value)); },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_DATA_GRAPH_TOSA_QUALITY_ACCELERATED_ARM | VK_DATA_GRAPH_TOSA_QUALITY_CONFORMANT_ARM),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkClusterAccelerationStructureAddressResolutionFlagsNV",
     [](uint64_t value) {
         return Flags::ClusterAccelerationStructureAddressResolutionFlagsNV(
             static_cast<VkClusterAccelerationStructureAddressResolutionFlagsNV>(value));
     },
     [](uint64_t value) {
         return string_VkClusterAccelerationStructureAddressResolutionFlagsNV(
             static_cast<VkClusterAccelerationStructureAddressResolutionFlagsNV>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_CLUSTER_ACCELERATION_STRUCTURE_ADDRESS_RESOLUTION_INDIRECTED_DST_IMPLICIT_DATA_BIT_NV |
                            VK_CLUSTER_ACCELERATION_STRUCTURE_ADDRESS_RESOLUTION_INDIRECTED_SCRATCH_DATA_BIT_NV),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkClusterAccelerationStructureClusterFlagsNV",
     [](uint64_t value) {
         return Flags::ClusterAccelerationStructureClusterFlagsNV(static_cast<VkClusterAccelerationStructureClusterFlagsNV>(value));
     },
     [](uint64_t value) {
         return string_VkClusterAccelerationStructureClusterFlagsNV(
             static_cast<VkClusterAccelerationStructureClusterFlagsNV>(value));
     },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkClusterAccelerationStructureGeometryFlagsNV",
     [](uint64_t value) {
         return Flags::ClusterAccelerationStructureGeometryFlagsNV(
             static_cast<VkClusterAccelerationStructureGeometryFlagsNV>(value));
     },
     [](uint64_t value) {
         return string_VkClusterAccelerationStructureGeometryFlagsNV(
             static_cast<VkClusterAccelerationStructureGeometryFlagsNV>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_CLUSTER_ACCELERATION_STRUCTURE_GEOMETRY_CULL_DISABLE_BIT_NV |
                            VK_CLUSTER_ACCELERATION_STRUCTURE_GEOMETRY_NO_DUPLICATE_ANYHIT_INVOCATION_BIT_NV),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkClusterAccelerationStructureIndexFormatFlagsNV",
     [](uint64_t value) {
         return Flags::ClusterAccelerationStructureIndexFormatFlagsNV(
             static_cast<VkClusterAccelerationStructureIndexFormatFlagsNV>(value));
     },
     [](uint64_t value) {
         return string_VkClusterAccelerationStructureIndexFormatFlagsNV(
             static_cast<VkClusterAccelerationStructureIndexFormatFlagsNV>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_CLUSTER_ACCELERATION_STRUCTURE_INDEX_FORMAT_8BIT_NV |
                            VK_CLUSTER_ACCELERATION_STRUCTURE_INDEX_FORMAT_16BIT_NV),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkPartitionedAccelerationStructureInstanceFlagsNV",
     [](uint64_t value) {
         return Flags::PartitionedAccelerationStructureInstanceFlagsNV(
             static_cast<VkPartitionedAccelerationStructureInstanceFlagsNV>(value));
     },
     [](uint64_t value) {
         return string_VkPartitionedAccelerationStructureInstanceFlagsNV(
             static_cast<VkPartitionedAccelerationStructureInstanceFlagsNV>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_PARTITIONED_ACCELERATION_STRUCTURE_INSTANCE_FLAG_TRIANGLE_FACING_CULL_DISABLE_BIT_NV |
                            VK_PARTITIONED_ACCELERATION_STRUCTURE_INSTANCE_FLAG_TRIANGLE_FLIP_FACING_BIT_NV),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkIndirectCommandsInputModeFlagsEXT",
     [](uint64_t value) {
         return Flags::IndirectCommandsInputModeFlagsEXT(static_cast<VkIndirectCommandsInputModeFlagsEXT>(value));
     },
     [](uint64_t value) {
         return string_VkIndirectCommandsInputModeFlagsEXT(static_cast<VkIndirectCommandsInputModeFlagsEXT>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_INDIRECT_COMMANDS_INPUT_MODE_VULKAN_INDEX_BUFFER_EXT |
                            VK_INDIRECT_COMMANDS_INPUT_MODE_DXGI_INDEX_BUFFER_EXT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkIndirectCommandsLayoutUsageFlagsEXT",
     [](uint64_t value) {
         return Flags::IndirectCommandsLayoutUsageFlagsEXT(static_cast<VkIndirectCommandsLayoutUsageFlagsEXT>(value));
     },
     [](uint64_t value) {
         return string_VkIndirectCommandsLayoutUsageFlagsEXT(static_cast<VkIndirectCommandsLayoutUsageFlagsEXT>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_INDIRECT_COMMANDS_LAYOUT_USAGE_EXPLICIT_PREPROCESS_BIT_EXT |
                            VK_INDIRECT_COMMANDS_LAYOUT_USAGE_UNORDERED_SEQUENCES_BIT_EXT),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkDataGraphOpticalFlowGridSizeFlagsARM",
     [](uint64_t value) {
         return Flags::DataGraphOpticalFlowGridSizeFlagsARM(static_cast<VkDataGraphOpticalFlowGridSizeFlagsARM>(value));
     },
     [](uint64_t value) {
         return string_VkDataGraphOpticalFlowGridSizeFlagsARM(static_cast<VkDataGraphOpticalFlowGridSizeFlagsARM>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_DATA_GRAPH_OPTICAL_FLOW_GRID_SIZE_1X1_BIT_ARM | VK_DATA_GRAPH_OPTICAL_FLOW_GRID_SIZE_2X2_BIT_ARM),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkDataGraphOpticalFlowCreateFlagsARM",
     [](uint64_t value) {
         return Flags::DataGraphOpticalFlowCreateFlagsARM(static_cast<VkDataGraphOpticalFlowCreateFlagsARM>(value));
     },
     [](uint64_t value) {
         return string_VkDataGraphOpticalFlowCreateFlagsARM(static_cast<VkDataGraphOpticalFlowCreateFlagsARM>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_DATA_GRAPH_OPTICAL_FLOW_CREATE_ENABLE_HINT_BIT_ARM |
                            VK_DATA_GRAPH_OPTICAL_FLOW_CREATE_ENABLE_COST_BIT_ARM),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkDataGraphOpticalFlowImageUsageFlagsARM",
     [](uint64_t value) {
         return Flags::DataGraphOpticalFlowImageUsageFlagsARM(static_cast<VkDataGraphOpticalFlowImageUsageFlagsARM>(value));
     },
     [](uint64_t value) {
         return string_VkDataGraphOpticalFlowImageUsageFlagsARM(static_cast<VkDataGraphOpticalFlowImageUsageFlagsARM>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_DATA_GRAPH_OPTICAL_FLOW_IMAGE_USAGE_INPUT_BIT_ARM |
                            VK_DATA_GRAPH_OPTICAL_FLOW_IMAGE_USAGE_OUTPUT_BIT_ARM),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkDataGraphOpticalFlowExecuteFlagsARM",
     [](uint64_t value) {
         return Flags::DataGraphOpticalFlowExecuteFlagsARM(static_cast<VkDataGraphOpticalFlowExecuteFlagsARM>(value));
     },
     [](uint64_t value) {
         return string_VkDataGraphOpticalFlowExecuteFlagsARM(static_cast<VkDataGraphOpticalFlowExecuteFlagsARM>(value));
     },
     {static_cast<uint64_t>(0),
      static_cast<uint64_t>(VK_DATA_GRAPH_OPTICAL_FLOW_EXECUTE_DISABLE_TEMPORAL_HINTS_BIT_ARM |
                            VK_DATA_GRAPH_OPTICAL_FLOW_EXECUTE_INPUT_UNCHANGED_BIT_ARM),
      static_cast<uint64_t>(uint64_t(1) << 31)}},
    {"VkCooperativeMatrixFlagsEXT",
     [](uint64_t value) { return Flags::CooperativeMatrixFlagsEXT(static_cast<VkCooperativeMatrixFlagsEXT>(value)); },
     [](uint64_t value) { return string_VkCooperativeMatrixFlagsEXT(static_cast<VkCooperativeMatrixFlagsEXT>(value)); },
     {static_cast<uint64_t>(0), static_cast<uint64_t>(uint64_t(1) << 31)}},
};
}  // namespace vvl
// NOLINTEND
