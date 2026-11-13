/* Copyright (c) 2015-2026 The Khronos Group Inc.
 * Copyright (c) 2015-2026 Valve Corporation
 * Copyright (c) 2015-2026 LunarG, Inc.
 * Copyright (C) 2015-2026 Google Inc.
 * Modifications Copyright (C) 2020-2022 Advanced Micro Devices, Inc. All rights reserved.
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
 */

#include <sstream>
#include <string>

#include <vulkan/vk_enum_string_helper.h>
#include <vulkan/utility/vk_format_utils.h>
#include <vulkan/vulkan_core.h>
#include "containers/container_utils.h"
#include "error_message/error_location.h"
#include "core_validation.h"
#include "cc_buffer_address.h"
#include "state_tracker/buffer_state.h"
#include "state_tracker/cmd_buffer_state.h"
#include "generated/dispatch_functions.h"
#include "utils/math_utils.h"
#include "utils/image_utils.h"
#include "cc_vuid_maps.h"

// Helper function to validate usage flags for buffers. For given buffer_state send actual vs. desired usage off to helper above
// where an error will be flagged if usage is not correct
bool CoreChecks::ValidateBufferUsageFlags(const LogObjectList& objlist, vvl::Buffer const& buffer_state,
                                          VkBufferUsageFlags2 desired, bool strict, const char* vuid,
                                          const Location& buffer_loc) const {
    bool skip = false;
    bool correct_usage = false;
    if (strict) {
        correct_usage = ((buffer_state.usage & desired) == desired);
    } else {
        correct_usage = ((buffer_state.usage & desired) != 0);
    }

    if (!correct_usage) {
        skip |= LogError(vuid, objlist, buffer_loc, "({}) was created with {} but requires {}{}.", Handle(buffer_state.Handle()),
                         vvl::Flags::BufferUsageFlags2(buffer_state.usage), strict ? "" : "at least one of ",
                         vvl::Flags::BufferUsageFlags2(desired));
    }
    return skip;
}

bool CoreChecks::ValidateBufferViewRange(const vvl::Buffer& buffer_state, const VkBufferViewCreateInfo& create_info,
                                         const Location& loc) const {
    bool skip = false;

    const VkDeviceSize& range = create_info.range;
    if (range != VK_WHOLE_SIZE) {
        // The sum of range and offset must be less than or equal to the size of buffer
        if (range + create_info.offset > buffer_state.GetSize()) {
            const VkDeviceSize remaining_space =
                (create_info.offset <= buffer_state.GetSize()) ? (buffer_state.GetSize() - create_info.offset) : 0;
            skip |= LogError("VUID-VkBufferViewCreateInfo-offset-00931", buffer_state.Handle(), loc.dot(Field::range),
                             "({}"
                             ") does not equal VK_WHOLE_SIZE, so the sum of offset ({}"
                             ") and range must be less than or equal to the size of {} ({}"
                             "), which allows a maximum range of ({}"
                             ") at this offset.",
                             range, create_info.offset, Handle(buffer_state.Handle()), buffer_state.GetSize(), remaining_space);
        }
    } else if (create_info.offset < buffer_state.GetSize()) {
        // If offset is over, will be caught elsewhere (00925)
        const VkFormat format = create_info.format;
        // will be 1 because  block-compressed format are not supported for Texe l Buffer
        const VkDeviceSize texels_per_block = static_cast<VkDeviceSize>(vkuFormatTexelsPerBlock(format));
        const VkDeviceSize texel_block_size = static_cast<VkDeviceSize>(GetTexelBufferFormatSize(format));
        const VkDeviceSize offset_range = buffer_state.GetSize() - create_info.offset;
        const VkDeviceSize texels = SafeDivision(offset_range, texel_block_size) * texels_per_block;
        if (texels > static_cast<VkDeviceSize>(phys_dev_props.limits.maxTexelBufferElements)) {
            skip |= LogError("VUID-VkBufferViewCreateInfo-range-04059", buffer_state.Handle(), loc.dot(Field::range),
                             "is VK_WHOLE_SIZE, but the buffer's size ({}"
                             "), offset ({}"
                             "), {} texel block size ({}"
                             "), and texels per block ({}"
                             ") is a total of ({}"
                             ") texels which is more than VkPhysicalDeviceLimits::maxTexelBufferElements ({}"
                             ").",
                             buffer_state.GetSize(), create_info.offset, string_VkFormat(format), texel_block_size,
                             texels_per_block, texels, phys_dev_props.limits.maxTexelBufferElements);
        }
    }
    return skip;
}

bool CoreChecks::ValidateCreateBufferDescriptorBuffer(const VkBufferCreateInfo& create_info, const VkBufferUsageFlags2& usage,
                                                      const Location& create_info_loc) const {
    bool skip = false;

    if (usage & VK_BUFFER_USAGE_2_SAMPLER_DESCRIPTOR_BUFFER_BIT_EXT) {
        if (create_info.size + device_state->descriptor_buffer_address_space.sampler >
            phys_dev_ext_props.descriptor_buffer_props.samplerDescriptorBufferAddressSpaceSize) {
            skip |= LogError("VUID-VkBufferCreateInfo-usage-08097", device, create_info_loc.dot(Field::size),
                             "({}"
                             ") + current total ({}"
                             ") is greater than specified in properties field samplerDescriptorBufferAddressSpaceSize ({}"
                             ").",
                             create_info.size, device_state->descriptor_buffer_address_space.sampler.load(),
                             phys_dev_ext_props.descriptor_buffer_props.samplerDescriptorBufferAddressSpaceSize);
        } else if (create_info.size + device_state->descriptor_buffer_address_space.all >
                   phys_dev_ext_props.descriptor_buffer_props.descriptorBufferAddressSpaceSize) {
            skip |= LogError("VUID-VkBufferCreateInfo-usage-08097", device, create_info_loc.dot(Field::size),
                             "({}"
                             ") + current total ({}"
                             ") is greater than specified in properties field descriptorBufferAddressSpaceSize ({}"
                             ")",
                             create_info.size, device_state->descriptor_buffer_address_space.all.load(),
                             phys_dev_ext_props.descriptor_buffer_props.descriptorBufferAddressSpaceSize);
        }
    }

    if (usage & VK_BUFFER_USAGE_2_RESOURCE_DESCRIPTOR_BUFFER_BIT_EXT) {
        if (create_info.size + device_state->descriptor_buffer_address_space.resource >
            phys_dev_ext_props.descriptor_buffer_props.resourceDescriptorBufferAddressSpaceSize) {
            skip |= LogError("VUID-VkBufferCreateInfo-usage-08098", device, create_info_loc.dot(Field::size),
                             "({}"
                             ") + current total ({}"
                             ") is greater than specified in properties field resourceDescriptorBufferAddressSpaceSize ({}"
                             ").",
                             create_info.size, device_state->descriptor_buffer_address_space.resource.load(),
                             phys_dev_ext_props.descriptor_buffer_props.resourceDescriptorBufferAddressSpaceSize);
        } else if (create_info.size + device_state->descriptor_buffer_address_space.all >
                   phys_dev_ext_props.descriptor_buffer_props.descriptorBufferAddressSpaceSize) {
            skip |= LogError("VUID-VkBufferCreateInfo-usage-08098", device, create_info_loc.dot(Field::size),
                             "({}"
                             ") + current total ({}"
                             ") is greater than specified in properties field descriptorBufferAddressSpaceSize ({}"
                             ").",
                             create_info.size, device_state->descriptor_buffer_address_space.all.load(),
                             phys_dev_ext_props.descriptor_buffer_props.descriptorBufferAddressSpaceSize);
        }
    }

    if ((create_info.flags & VK_BUFFER_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT) &&
        !enabled_features.descriptorBufferCaptureReplay) {
        skip |= LogError("VUID-VkBufferCreateInfo-flags-08099", device, create_info_loc.dot(Field::flags),
                         "has VK_BUFFER_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT set but the descriptorBufferCaptureReplay "
                         "device feature is not enabled.");
    }

    if (vku::FindStructInPNextChain<VkOpaqueCaptureDescriptorDataCreateInfoEXT>(create_info.pNext)) {
        if (!(create_info.flags & VK_BUFFER_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT)) {
            skip |= LogError("VUID-VkBufferCreateInfo-pNext-08100", device, create_info_loc.dot(Field::flags),
                             "({}) is missing VK_BUFFER_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT but "
                             "VkOpaqueCaptureDescriptorDataCreateInfoEXT is in pNext chain.\n{}",
                             vvl::Flags::BufferCreateFlags(create_info.flags),
                             PrintPNextChain(Struct::VkBufferCreateInfo, create_info.pNext).c_str());
        }
    }

    if (usage & VK_BUFFER_USAGE_2_PUSH_DESCRIPTORS_DESCRIPTOR_BUFFER_BIT_EXT) {
        if (!enabled_features.descriptorBufferPushDescriptors) {
            skip |= LogError("VUID-VkBufferCreateInfo-usage-08101", device, create_info_loc.dot(Field::usage),
                             "has VK_BUFFER_USAGE_2_PUSH_DESCRIPTORS_DESCRIPTOR_BUFFER_BIT_EXT set but the "
                             "descriptorBufferPushDescriptors device feature is not enabled.");
        }

        if (phys_dev_ext_props.descriptor_buffer_props.bufferlessPushDescriptors) {
            skip |=
                LogError("VUID-VkBufferCreateInfo-usage-08102", device, create_info_loc.dot(Field::usage),
                         "has VK_BUFFER_USAGE_2_PUSH_DESCRIPTORS_DESCRIPTOR_BUFFER_BIT_EXT set but the bufferlessPushDescriptors "
                         "device property is VK_TRUE.");
        }

        if (!(usage &
              (VK_BUFFER_USAGE_2_RESOURCE_DESCRIPTOR_BUFFER_BIT_EXT | VK_BUFFER_USAGE_2_SAMPLER_DESCRIPTOR_BUFFER_BIT_EXT))) {
            skip |= LogError("VUID-VkBufferCreateInfo-usage-08103", device, create_info_loc.dot(Field::usage), "is ({}).",
                             vvl::Flags::BufferUsageFlags2(usage));
        }
    }

    return skip;
}

bool CoreChecks::PreCallValidateCreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo,
                                             const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer,
                                             const ErrorObject& error_obj) const {
    bool skip = false;
    skip |= ValidateDeviceQueueSupport(error_obj.location);
    const Location create_info_loc = error_obj.location.dot(Field::pCreateInfo);

    if (pCreateInfo->sharingMode == VK_SHARING_MODE_CONCURRENT && pCreateInfo->pQueueFamilyIndices) {
        skip |= ValidatePhysicalDeviceQueueFamilies(pCreateInfo->queueFamilyIndexCount, pCreateInfo->pQueueFamilyIndices,
                                                    create_info_loc, "VUID-VkBufferCreateInfo-sharingMode-01419");
    }

    const auto* usage_flags2 = vku::FindStructInPNextChain<VkBufferUsageFlags2CreateInfo>(pCreateInfo->pNext);
    const VkBufferUsageFlags2 usage = usage_flags2 ? usage_flags2->usage : pCreateInfo->usage;

    const bool has_decode_usage = usage & (VK_BUFFER_USAGE_2_VIDEO_DECODE_SRC_BIT_KHR | VK_BUFFER_USAGE_2_VIDEO_DECODE_DST_BIT_KHR);
    const bool has_encode_usage = usage & (VK_BUFFER_USAGE_2_VIDEO_ENCODE_SRC_BIT_KHR | VK_BUFFER_USAGE_2_VIDEO_ENCODE_DST_BIT_KHR);
    const bool video_profile_independent = pCreateInfo->flags & VK_BUFFER_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR;

    if (video_profile_independent && !enabled_features.videoMaintenance1) {
        skip |= LogError("VUID-VkBufferCreateInfo-flags-08325", device, create_info_loc.dot(Field::flags),
                         "has VK_BUFFER_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR set but the videoMaintenance1 "
                         "device feature is not enabled.");
    }

    if (has_decode_usage || has_encode_usage) {
        const bool expect_decode_profile = has_decode_usage && !video_profile_independent;
        const bool expect_encode_profile = has_encode_usage && !video_profile_independent;

        const auto* video_profiles = vku::FindStructInPNextChain<VkVideoProfileListInfoKHR>(pCreateInfo->pNext);
        skip |= core::ValidateVideoProfileListInfo(
            *this, video_profiles, error_obj, create_info_loc.pNext(Struct::VkVideoProfileListInfoKHR), expect_decode_profile,
            "VUID-VkBufferCreateInfo-usage-04813", expect_encode_profile, "VUID-VkBufferCreateInfo-usage-04814");
    }

    auto external_memory_info = vku::FindStructInPNextChain<VkExternalMemoryBufferCreateInfo>(pCreateInfo->pNext);
    if (external_memory_info && external_memory_info->handleTypes) {
        const uint32_t any_type = 1u << MostSignificantBit(external_memory_info->handleTypes);
        VkPhysicalDeviceExternalBufferInfo external_buffer_info = vku::InitStructHelper();
        external_buffer_info.flags = pCreateInfo->flags;
        // for now no VkBufferUsageFlags2 flag can be used, so safe to pass in as 32-bit version
        external_buffer_info.usage = VkBufferUsageFlags(pCreateInfo->usage);
        external_buffer_info.handleType = static_cast<VkExternalMemoryHandleTypeFlagBits>(any_type);
        VkExternalBufferProperties external_buffer_properties = vku::InitStructHelper();
        DispatchGetPhysicalDeviceExternalBufferPropertiesHelper(api_version, physical_device, &external_buffer_info,
                                                                &external_buffer_properties);
        const auto compatible_types = external_buffer_properties.externalMemoryProperties.compatibleHandleTypes;

        if ((external_memory_info->handleTypes & compatible_types) != external_memory_info->handleTypes) {
            skip |= LogError("VUID-VkBufferCreateInfo-pNext-00920", device,
                             create_info_loc.pNext(Struct::VkExternalMemoryBufferCreateInfo, Field::handleTypes),
                             "({}) is not reported as compatible by vkGetPhysicalDeviceExternalBufferProperties.",
                             vvl::Flags::ExternalMemoryHandleTypeFlags(external_memory_info->handleTypes));
        }
    }

    skip |= ValidateCreateBufferDescriptorBuffer(*pCreateInfo, usage, create_info_loc);

    return skip;
}

bool CoreChecks::PreCallValidateCreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo,
                                                 const VkAllocationCallbacks* pAllocator, VkBufferView* pView,
                                                 const ErrorObject& error_obj) const {
    bool skip = false;
    skip |= ValidateDeviceQueueSupport(error_obj.location);
    auto buffer_state_ptr = Get<vvl::Buffer>(pCreateInfo->buffer);
    const Location create_info_loc = error_obj.location.dot(Field::pCreateInfo);
    if (!buffer_state_ptr) {
        return skip;
    }

    const auto& buffer_state = *buffer_state_ptr;
    const LogObjectList objlist(device, pCreateInfo->buffer);

    // If this isn't a sparse buffer, it needs to have memory backing it at CreateBufferView time
    skip |= ValidateMemoryIsBoundToBuffer(device, buffer_state, create_info_loc.dot(Field::buffer),
                                          "VUID-VkBufferViewCreateInfo-buffer-00935");
    // In order to create a valid buffer view, the buffer must have been created with at least one of the following flags:
    // UNIFORM_TEXEL_BUFFER_BIT or STORAGE_TEXEL_BUFFER_BIT
    skip |= ValidateBufferUsageFlags(objlist, buffer_state,
                                     VK_BUFFER_USAGE_2_UNIFORM_TEXEL_BUFFER_BIT | VK_BUFFER_USAGE_2_STORAGE_TEXEL_BUFFER_BIT, false,
                                     "VUID-VkBufferViewCreateInfo-buffer-00932", create_info_loc.dot(Field::buffer));

    // Buffer view offset must be less than the size of buffer
    if (pCreateInfo->offset >= buffer_state.GetSize()) {
        skip |= LogError("VUID-VkBufferViewCreateInfo-offset-00925", buffer_state.Handle(), create_info_loc.dot(Field::offset),
                         "({}"
                         ") must be less than the size of the buffer ({}"
                         ").",
                         pCreateInfo->offset, buffer_state.GetSize());
    }

    if (enabled_features.texelBufferAlignment) {
        VkDeviceSize texel_block_size = GetTexelBufferFormatSize(pCreateInfo->format);
        bool texel_size_of_three = false;
        if ((texel_block_size % 3) == 0) {
            texel_size_of_three = true;
            texel_block_size /= 3;
        }
        if (buffer_state.usage & VK_BUFFER_USAGE_2_STORAGE_TEXEL_BUFFER_BIT) {
            VkDeviceSize alignment_requirement = phys_dev_props_core13.storageTexelBufferOffsetAlignmentBytes;
            if (phys_dev_props_core13.storageTexelBufferOffsetSingleTexelAlignment) {
                alignment_requirement = std::min(alignment_requirement, texel_block_size);
            }
            if (!IsIntegerMultipleOf(pCreateInfo->offset, alignment_requirement)) {
                std::ostringstream ss;
                ss << "was created with VK_BUFFER_USAGE_2_STORAGE_TEXEL_BUFFER_BIT, so the offset (" << pCreateInfo->offset
                   << ") must be a multiple of " << alignment_requirement << "\n";
                if (phys_dev_props_core13.storageTexelBufferOffsetSingleTexelAlignment) {
                    ss << "storageTexelBufferOffsetSingleTexelAlignment is VK_TRUE, so we take "
                          "min(storageTexelBufferOffsetAlignmentBytes, texelBlockSize("
                       << string_VkFormat(pCreateInfo->format) << ")) which is min("
                       << phys_dev_props_core13.storageTexelBufferOffsetAlignmentBytes << ", " << texel_block_size << ")";
                    if (texel_size_of_three) {
                        ss << "\nThe size of a texel " << (texel_block_size * 3)
                           << " was a multiple of three bytes, so the size of a single component of "
                           << string_VkFormat(pCreateInfo->format) << " was used instead";
                    }
                } else {
                    ss << "storageTexelBufferOffsetSingleTexelAlignment is VK_FALSE and storageTexelBufferOffsetAlignmentBytes is "
                       << phys_dev_props_core13.storageTexelBufferOffsetAlignmentBytes;
                }

                skip |= LogError("VUID-VkBufferViewCreateInfo-buffer-02750", objlist, create_info_loc.dot(Field::buffer), "{}",
                                 ss.str().c_str());
            }
        }
        if (buffer_state.usage & VK_BUFFER_USAGE_2_UNIFORM_TEXEL_BUFFER_BIT) {
            VkDeviceSize alignment_requirement = phys_dev_props_core13.uniformTexelBufferOffsetAlignmentBytes;
            if (phys_dev_props_core13.uniformTexelBufferOffsetSingleTexelAlignment) {
                alignment_requirement = std::min(alignment_requirement, texel_block_size);
            }
            if (!IsIntegerMultipleOf(pCreateInfo->offset, alignment_requirement)) {
                std::ostringstream ss;
                ss << "was created with VK_BUFFER_USAGE_2_UNIFORM_TEXEL_BUFFER_BIT, so the offset (" << pCreateInfo->offset
                   << ") must be a multiple of " << alignment_requirement << "\n";
                if (phys_dev_props_core13.uniformTexelBufferOffsetSingleTexelAlignment) {
                    ss << "uniformTexelBufferOffsetSingleTexelAlignment is VK_TRUE, so we take "
                          "min(uniformTexelBufferOffsetAlignmentBytes, texelBlockSize("
                       << string_VkFormat(pCreateInfo->format) << ")) which is min("
                       << phys_dev_props_core13.uniformTexelBufferOffsetAlignmentBytes << ", " << texel_block_size << ")";
                    if (texel_size_of_three) {
                        ss << "\nThe size of a texel " << (texel_block_size * 3)
                           << " was a multiple of three bytes, so the size of a single component of "
                           << string_VkFormat(pCreateInfo->format) << " was used instead";
                    }
                } else {
                    ss << "uniformTexelBufferOffsetSingleTexelAlignment is VK_FALSE and uniformTexelBufferOffsetAlignmentBytes is "
                       << phys_dev_props_core13.uniformTexelBufferOffsetAlignmentBytes;
                }

                skip |= LogError("VUID-VkBufferViewCreateInfo-buffer-02751", objlist, create_info_loc.dot(Field::buffer), "{}",
                                 ss.str().c_str());
            }
        }
    } else if (!IsIntegerMultipleOf(pCreateInfo->offset, phys_dev_props.limits.minTexelBufferOffsetAlignment)) {
        const char* vuid = (buffer_state.usage & VK_BUFFER_USAGE_2_STORAGE_TEXEL_BUFFER_BIT)
                               ? "VUID-VkBufferViewCreateInfo-buffer-02750"
                               : "VUID-VkBufferViewCreateInfo-buffer-02751";
        skip |= LogError(vuid, pCreateInfo->buffer, create_info_loc.dot(Field::offset),
                         "({}"
                         ") must be a multiple of VkPhysicalDeviceLimits::minTexelBufferOffsetAlignment ({}"
                         ").",
                         pCreateInfo->offset, phys_dev_props.limits.minTexelBufferOffsetAlignment);
    }

    // vkspec.html#resources-buffer-views-usage
    auto usage_flags2 = vku::FindStructInPNextChain<VkBufferUsageFlags2CreateInfo>(pCreateInfo->pNext);
    VkBufferUsageFlags2 buffer_view_usage = usage_flags2 ? usage_flags2->usage : buffer_state.usage;

    if (usage_flags2) {
        if ((buffer_view_usage & ~(VK_BUFFER_USAGE_2_UNIFORM_TEXEL_BUFFER_BIT | VK_BUFFER_USAGE_2_STORAGE_TEXEL_BUFFER_BIT)) != 0) {
            skip |= LogError("VUID-VkBufferViewCreateInfo-pNext-08780", objlist,
                             create_info_loc.pNext(Struct::VkBufferUsageFlags2CreateInfo, Field::usage), "is {}.",
                             vvl::Flags::BufferUsageFlags2(buffer_view_usage));
        } else if ((buffer_view_usage & buffer_state.usage) != buffer_view_usage) {
            skip |= LogError("VUID-VkBufferViewCreateInfo-pNext-08781", objlist,
                             create_info_loc.pNext(Struct::VkBufferUsageFlags2CreateInfo, Field::usage),
                             "({}) is not a subset of the buffer's usage ({}).", vvl::Flags::BufferUsageFlags2(buffer_view_usage),
                             vvl::Flags::BufferUsageFlags2(buffer_state.usage));
        }
    }

    const VkFormatProperties3 format_properties = GetPDFormatProperties(pCreateInfo->format);
    if ((buffer_view_usage & VK_BUFFER_USAGE_2_UNIFORM_TEXEL_BUFFER_BIT) &&
        !(format_properties.bufferFeatures & VK_FORMAT_FEATURE_2_UNIFORM_TEXEL_BUFFER_BIT)) {
        const Location usage_loc = usage_flags2 ? create_info_loc.pNext(Struct::VkBufferUsageFlags2CreateInfo, Field::usage)
                                                : create_info_loc.dot(Field::buffer);
        skip |= LogError("VUID-VkBufferViewCreateInfo-format-08778", objlist, usage_loc,
                         "{}({}) containing VK_BUFFER_USAGE_2_UNIFORM_TEXEL_BUFFER_BIT.\n"
                         "Format ({}) doesn't support VK_BUFFER_USAGE_2_UNIFORM_TEXEL_BUFFER_BIT.\n"
                         "(supported bufferFeatures: {})",
                         usage_flags2 ? "" : "was created with usage ", vvl::Flags::BufferUsageFlags2(buffer_view_usage),
                         string_VkFormat(pCreateInfo->format), vvl::Flags::FormatFeatureFlags2(format_properties.bufferFeatures));
    }
    if ((buffer_view_usage & VK_BUFFER_USAGE_2_STORAGE_TEXEL_BUFFER_BIT) &&
        !(format_properties.bufferFeatures & VK_FORMAT_FEATURE_2_STORAGE_TEXEL_BUFFER_BIT)) {
        const Location usage_loc = usage_flags2 ? create_info_loc.pNext(Struct::VkBufferUsageFlags2CreateInfo, Field::usage)
                                                : create_info_loc.dot(Field::buffer);
        skip |= LogError("VUID-VkBufferViewCreateInfo-format-08779", objlist, usage_loc,
                         "{}({}) containing VK_BUFFER_USAGE_2_STORAGE_TEXEL_BUFFER_BIT.\n"
                         "Format ({}) doesn't support VK_BUFFER_USAGE_2_STORAGE_TEXEL_BUFFER_BIT.\n"
                         "(supported bufferFeatures: {})",
                         usage_flags2 ? "" : "was created with usage ", vvl::Flags::BufferUsageFlags2(buffer_view_usage),
                         string_VkFormat(pCreateInfo->format), vvl::Flags::FormatFeatureFlags2(format_properties.bufferFeatures));
    }

    skip |= ValidateBufferViewRange(buffer_state, *pCreateInfo, create_info_loc);

    return skip;
}

bool CoreChecks::PreCallValidateDestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator,
                                              const ErrorObject& error_obj) const {
    bool skip = false;
    if (auto buffer_state = Get<vvl::Buffer>(buffer)) {
        skip |= ValidateObjectNotInUse(buffer_state.get(), error_obj.location, "VUID-vkDestroyBuffer-buffer-00922");
    }
    return skip;
}

void CoreChecks::PreCallRecordDestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator,
                                            const RecordObject& record_obj) {
    // Ownership transfer releases that were never acquired
    qfo_release_buffer_barrier_map.erase(buffer);
}

bool CoreChecks::PreCallValidateDestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks* pAllocator,
                                                  const ErrorObject& error_obj) const {
    bool skip = false;
    if (auto buffer_view_state = Get<vvl::BufferView>(bufferView)) {
        skip |= ValidateObjectNotInUse(buffer_view_state.get(), error_obj.location, "VUID-vkDestroyBufferView-bufferView-00936");
    }
    return skip;
}

bool CoreChecks::PreCallValidateCmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset,
                                              VkDeviceSize size, uint32_t data, const ErrorObject& error_obj) const {
    bool skip = false;
    auto cb_state_ptr = GetRead<vvl::CommandBuffer>(commandBuffer);
    auto buffer_state = Get<vvl::Buffer>(dstBuffer);
    ASSERT_AND_RETURN_SKIP(cb_state_ptr && buffer_state);

    const LogObjectList objlist(commandBuffer, dstBuffer);
    const vvl::CommandBuffer& cb_state = *cb_state_ptr;
    const Location buffer_loc = error_obj.location.dot(Field::dstBuffer);
    skip |= ValidateMemoryIsBoundToBuffer(commandBuffer, *buffer_state, buffer_loc, "VUID-vkCmdFillBuffer-dstBuffer-00031");
    skip |= ValidateCmd(cb_state, error_obj.location);
    // Validate that DST buffer has correct usage flags set
    skip |= ValidateBufferUsageFlags(objlist, *buffer_state, VK_BUFFER_USAGE_2_TRANSFER_DST_BIT, true,
                                     "VUID-vkCmdFillBuffer-dstBuffer-00029", buffer_loc);

    skip |= ValidateProtectedBuffer(cb_state, *buffer_state, buffer_loc);
    skip |= ValidateUnprotectedBuffer(cb_state, *buffer_state, buffer_loc);

    if (dstOffset >= buffer_state->GetSize()) {
        skip |= LogError("VUID-vkCmdFillBuffer-dstOffset-00024", objlist, error_obj.location.dot(Field::dstOffset),
                         "({}"
                         ") is not less than destination buffer ({}) size ({}"
                         ").",
                         dstOffset, Handle(dstBuffer), buffer_state->GetSize());
    }

    if ((size != VK_WHOLE_SIZE) && (size > (buffer_state->GetSize() - dstOffset))) {
        skip |= LogError("VUID-vkCmdFillBuffer-size-00027", objlist, error_obj.location.dot(Field::size),
                         "({}"
                         ") is greater than dstBuffer ({}) size ({}"
                         ") minus dstOffset ({}"
                         ").",
                         size, Handle(dstBuffer), buffer_state->GetSize(), dstOffset);
    }

    if (!IsExtEnabled(extensions.vk_khr_maintenance1)) {
        const VkQueueFlags required_flags = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT;
        if (!HasRequiredQueueFlags(cb_state, *physical_device_state, required_flags)) {
            const LogObjectList objlist_pool(cb_state.Handle(), cb_state.command_pool.Handle());
            skip |= LogError("VUID-vkCmdFillBuffer-apiVersion-07894", objlist_pool, error_obj.location,
                             "{}\nHint: This can be allowed in some cases if VK_KHR_maintenance1 (or Vulkan 1.1) is enabled.",
                             DescribeRequiredQueueFlag(cb_state, *physical_device_state, required_flags).c_str());
        }
    }

    return skip;
}

bool CoreChecks::ValidateDeviceAddressCommands(const LogObjectList& objlist, VkDeviceAddress address, VkDeviceSize size,
                                               VkAddressCommandFlagsKHR flags, const Location loc) const {
    bool skip = false;

    // TODO - tl;dr - This is a stupid mess
    // https://gitlab.khronos.org/vulkan/vulkan/-/merge_requests/5322#note_591585
    //
    // Most times we are checking "if at least 1 buffer" matches the requirements for a given VkDeviceAddress.
    // These "seem" to be different where if "any are invalid" then everything is bad
    const auto buffers = GetBuffersByAddress(address);
    for (const vvl::Buffer* buffer : buffers) {
        ASSERT_AND_CONTINUE(buffer);
        if ((buffer->usage & VK_BUFFER_USAGE_2_STORAGE_BUFFER_BIT) != 0) {
            if ((flags & (VK_ADDRESS_COMMAND_STORAGE_BUFFER_USAGE_BIT_KHR |
                          VK_ADDRESS_COMMAND_UNKNOWN_STORAGE_BUFFER_USAGE_BIT_KHR)) == 0) {
                skip |= LogError(vvl::GetDeviceAddressCommandVUID(loc, vvl::DeviceAddressCommandError::Storage_13122), objlist,
                                 loc.dot(Field::address),
                                 "(0x{:x}"
                                 ") belongs to {}, which was created with VK_BUFFER_USAGE_2_STORAGE_BUFFER_BIT, but address "
                                 "flags ({}) do not contain VK_ADDRESS_COMMAND_STORAGE_BUFFER_USAGE_BIT_KHR or "
                                 "VK_ADDRESS_COMMAND_UNKNOWN_STORAGE_BUFFER_USAGE_BIT_KHR.",
                                 address, Handle(buffer->Handle()), vvl::Flags::AddressCommandFlagsKHR(flags));
            }
        } else {
            if ((flags & VK_ADDRESS_COMMAND_STORAGE_BUFFER_USAGE_BIT_KHR) != 0) {
                skip |= LogError(vvl::GetDeviceAddressCommandVUID(loc, vvl::DeviceAddressCommandError::Storage_13123), objlist,
                                 loc.dot(Field::address),
                                 "(0x{:x}"
                                 ") belongs to {}, which was created without VK_BUFFER_USAGE_2_STORAGE_BUFFER_BIT, but address "
                                 "flags ({}) contain VK_ADDRESS_COMMAND_STORAGE_BUFFER_USAGE_BIT_KHR.",
                                 address, Handle(buffer->Handle()), vvl::Flags::AddressCommandFlagsKHR(flags));
            }
        }

        if ((buffer->usage & VK_BUFFER_USAGE_2_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT) != 0) {
            if ((flags & (VK_ADDRESS_COMMAND_TRANSFORM_FEEDBACK_BUFFER_USAGE_BIT_KHR |
                          VK_ADDRESS_COMMAND_UNKNOWN_TRANSFORM_FEEDBACK_BUFFER_USAGE_BIT_KHR)) == 0) {
                skip |= LogError(vvl::GetDeviceAddressCommandVUID(loc, vvl::DeviceAddressCommandError::Xfb_13124), objlist,
                                 loc.dot(Field::address),
                                 "(0x{:x}"
                                 ") belongs to {}, which was created with "
                                 "VK_BUFFER_USAGE_2_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT, but address "
                                 "flags ({}) do not contain VK_ADDRESS_COMMAND_TRANSFORM_FEEDBACK_BUFFER_USAGE_BIT_KHR or "
                                 "VK_ADDRESS_COMMAND_UNKNOWN_TRANSFORM_FEEDBACK_BUFFER_USAGE_BIT_KHR.",
                                 address, Handle(buffer->Handle()), vvl::Flags::AddressCommandFlagsKHR(flags));
            }
        } else {
            if ((flags & VK_ADDRESS_COMMAND_TRANSFORM_FEEDBACK_BUFFER_USAGE_BIT_KHR) != 0) {
                skip |= LogError(vvl::GetDeviceAddressCommandVUID(loc, vvl::DeviceAddressCommandError::Xfb_13125), objlist,
                                 loc.dot(Field::address),
                                 "(0x{:x}"
                                 ") belongs to {}, which was created without "
                                 "VK_BUFFER_USAGE_2_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT, but address "
                                 "flags ({}) contain VK_ADDRESS_COMMAND_TRANSFORM_FEEDBACK_BUFFER_USAGE_BIT_KHR.",
                                 address, Handle(buffer->Handle()), vvl::Flags::AddressCommandFlagsKHR(flags));
            }
        }

        if (!phys_dev_props_core11.protectedNoFault) {
            if ((buffer->GetFlags() & VK_BUFFER_CREATE_PROTECTED_BIT) != 0) {
                if ((flags & VK_ADDRESS_COMMAND_PROTECTED_BIT_KHR) == 0) {
                    skip |= LogError(vvl::GetDeviceAddressCommandVUID(loc, vvl::DeviceAddressCommandError::Protected_13098),
                                     objlist, loc.dot(Field::address),
                                     "(0x{:x}"
                                     ") belongs to {}, which was created with "
                                     "VK_BUFFER_CREATE_PROTECTED_BIT, but address "
                                     "flags ({}) does not contain VK_ADDRESS_COMMAND_PROTECTED_BIT_KHR.\nHint: This is valid if "
                                     "protectedNoFault is supported.",
                                     address, Handle(buffer->Handle()), vvl::Flags::AddressCommandFlagsKHR(flags));
                }
            } else if ((flags & VK_ADDRESS_COMMAND_PROTECTED_BIT_KHR) != 0) {
                skip |= LogError(vvl::GetDeviceAddressCommandVUID(loc, vvl::DeviceAddressCommandError::Protected_13099), objlist,
                                 loc.dot(Field::address),
                                 "(0x{:x}"
                                 ") belongs to {}, which was created without "
                                 "VK_BUFFER_CREATE_PROTECTED_BIT, but address "
                                 "flags ({}) contains VK_ADDRESS_COMMAND_PROTECTED_BIT_KHR.\nHint: This is valid if "
                                 "protectedNoFault is supported.",
                                 address, Handle(buffer->Handle()), vvl::Flags::AddressCommandFlagsKHR(flags));
            }
        }

        if (flags & VK_ADDRESS_COMMAND_FULLY_BOUND_BIT_KHR) {
            if (!buffer->sparse) {
                // TODO - use VerifyBoundMemoryIsValid? Not obvious which function to use
                const std::string vuid_13097 =
                    vvl::GetDeviceAddressCommandVUID(loc, vvl::DeviceAddressCommandError::CompletelyBound_13097);
                skip |= ValidateMemoryIsBoundToBuffer(objlist, *buffer, loc, vuid_13097.c_str());
            } else {
                const VkDeviceSize offset = address - buffer->deviceAddress;
                const vvl::BindableMemoryTracker::BufferRange buffer_range(offset, offset + size);
                if (!buffer->IsRangeFullyBound(buffer_range)) {
                    skip |= LogError(vvl::GetDeviceAddressCommandVUID(loc, vvl::DeviceAddressCommandError::CompletelyBound_13097),
                                     objlist, loc.dot(Field::address),
                                     "(0x{:x}"
                                     ") with size ({}"
                                     ") is used with VK_ADDRESS_COMMAND_FULLY_BOUND_BIT_KHR, but the sparse {} is not fully backed "
                                     "by memory over the corresponding buffer range [{}"
                                     ", {}"
                                     ").",
                                     address, size, Handle(buffer->Handle()), offset, offset + size);
                    break;
                }
            }
        }
    }

    return skip;
}

bool CoreChecks::PreCallValidateCmdFillMemoryKHR(VkCommandBuffer commandBuffer, const VkDeviceAddressRangeKHR* pDstRange,
                                                 VkAddressCommandFlagsKHR dstFlags, uint32_t data,
                                                 const ErrorObject& error_obj) const {
    bool skip = false;

    skip |= ValidateDeviceAddressRange(pDstRange->address, pDstRange->size, false, error_obj.location.dot(Field::pDstRange),
                                       LogObjectList(commandBuffer), VK_BUFFER_USAGE_2_TRANSFER_DST_BIT,
                                       "VUID-vkCmdFillMemoryKHR-dstRange-13000");

    auto cb_state_ptr = GetRead<vvl::CommandBuffer>(commandBuffer);
    const vvl::CommandBuffer& cb_state = *cb_state_ptr;
    if (!phys_dev_props_core11.protectedNoFault) {
        if (cb_state.unprotected) {
            if ((dstFlags & VK_ADDRESS_COMMAND_PROTECTED_BIT_KHR) != 0) {
                skip |=
                    LogError("VUID-vkCmdFillMemoryKHR-commandBuffer-13003", commandBuffer, error_obj.location.dot(Field::dstFlags),
                             "({}) contains VK_ADDRESS_COMMAND_PROTECTED_BIT_KHR, but command buffer ({}) is unprotected and "
                             "protectedNoFault is not supported.",
                             vvl::Flags::AddressCommandFlagsKHR(dstFlags), Handle(cb_state));
            }
        } else {
            if ((dstFlags & VK_ADDRESS_COMMAND_PROTECTED_BIT_KHR) == 0) {
                skip |=
                    LogError("VUID-vkCmdFillMemoryKHR-commandBuffer-13004", commandBuffer, error_obj.location.dot(Field::dstFlags),
                             "({}) does not include VK_ADDRESS_COMMAND_PROTECTED_BIT_KHR, but command buffer ({}) is protected and "
                             "protectedNoFault is not supported.",
                             vvl::Flags::AddressCommandFlagsKHR(dstFlags), Handle(cb_state));
            }
        }
    }

    skip |= ValidateDeviceAddressCommands(commandBuffer, pDstRange->address, pDstRange->size, dstFlags,
                                          error_obj.location.dot(Field::pDstRange));

    return skip;
}

// Validates the buffer is allowed to be protected
bool CoreChecks::ValidateProtectedBuffer(const vvl::CommandBuffer& cb_state, const vvl::Buffer& buffer_state,
                                         const Location& buffer_loc, const char* more_message) const {
    bool skip = false;

    // if driver supports protectedNoFault the operation is valid, just has undefined values
    if ((!phys_dev_props_core11.protectedNoFault) && (cb_state.unprotected == true) && (buffer_state.unprotected == false)) {
        const LogObjectList objlist(cb_state.Handle(), buffer_state.Handle());
        skip |= LogError(vvl::GetProtectedVUID(buffer_loc), objlist, buffer_loc,
                         "({}) is a protected buffer, but command buffer ({}) is unprotected.{}", Handle(buffer_state),
                         Handle(cb_state), more_message);
    }
    return skip;
}

// Validates the buffer is allowed to be unprotected
bool CoreChecks::ValidateUnprotectedBuffer(const vvl::CommandBuffer& cb_state, const vvl::Buffer& buffer_state,
                                           const Location& buffer_loc, const char* more_message) const {
    bool skip = false;

    // if driver supports protectedNoFault the operation is valid, just has undefined values
    if ((!phys_dev_props_core11.protectedNoFault) && (cb_state.unprotected == false) && (buffer_state.unprotected == true)) {
        const LogObjectList objlist(cb_state.Handle(), buffer_state.Handle());
        skip |= LogError(vvl::GetUnprotectedVUID(buffer_loc), objlist, buffer_loc,
                         "({}) is an unprotected buffer, but command buffer ({}) is protected.{}", Handle(buffer_state),
                         Handle(cb_state), more_message);
    }
    return skip;
}
