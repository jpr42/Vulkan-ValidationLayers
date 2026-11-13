/* Copyright (c) 2015-2026 The Khronos Group Inc.
 * Copyright (c) 2015-2026 Valve Corporation
 * Copyright (c) 2015-2026 LunarG, Inc.
 * Copyright (C) 2015-2026 Google Inc.
 * Copyright (C) 2025-2026 Advanced Micro Devices, Inc. All rights reserved.
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

#include "stateless/stateless_validation.h"
#include "containers/container_utils.h"
#include "generated/enum_flag_bits.h"
#include "generated/extended_flags_helper_generator.h"
#include "utils/image_utils.h"
#include "utils/math_utils.h"
#include <vulkan/utility/vk_format_utils.h>

namespace stateless {

bool Device::manual_PreCallValidateCreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo,
                                                const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer,
                                                const stateless::Context& context) const {
    bool skip = false;
    const auto& error_obj = context.error_obj;

    const Location create_info_loc = error_obj.location.dot(Field::pCreateInfo);
    skip |= context.ValidateNotZero(pCreateInfo->size == 0, "VUID-VkBufferCreateInfo-size-00912", create_info_loc.dot(Field::size));

    if (pCreateInfo->sharingMode == VK_SHARING_MODE_CONCURRENT) {
        if (enabled_features.maintenance11) {
            if (pCreateInfo->queueFamilyIndexCount == 0) {
                skip |= LogError("VUID-VkBufferCreateInfo-maintenance11-13353", device, create_info_loc.dot(Field::sharingMode),
                                 "is VK_SHARING_MODE_CONCURRENT, but queueFamilyIndexCount is 0 (must be at least 1).");
            }
        } else if (pCreateInfo->queueFamilyIndexCount <= 1) {
            skip |= LogError("VUID-VkBufferCreateInfo-sharingMode-00914", device, create_info_loc.dot(Field::sharingMode),
                             "is VK_SHARING_MODE_CONCURRENT, but queueFamilyIndexCount is {}"
                             " (must be at least 2)\nHint: queueFamilyIndexCount can be 1 if the maintenance11 feature is enabled",
                             pCreateInfo->queueFamilyIndexCount);
        }

        if (pCreateInfo->pQueueFamilyIndices == nullptr) {
            skip |= LogError("VUID-VkBufferCreateInfo-sharingMode-00913", device, create_info_loc.dot(Field::sharingMode),
                             "is VK_SHARING_MODE_CONCURRENT, but pQueueFamilyIndices is NULL.");
        }
    }

    if (!vku::FindStructInPNextChain<VkBufferUsageFlags2CreateInfo>(pCreateInfo->pNext)) {
        skip |= context.ValidateFlags(create_info_loc.dot(Field::usage), vvl::FlagBitmask::VkBufferUsageFlagBits,
                                      AllVkBufferUsageFlagBits, pCreateInfo->usage, kRequiredFlags,
                                      "VUID-VkBufferCreateInfo-None-09499", "VUID-VkBufferCreateInfo-None-09500");
    }
    const VkBufferUsageFlags2 usage = GetBufferUsageFlags(*pCreateInfo);

    if (pCreateInfo->flags & VK_BUFFER_CREATE_PROTECTED_BIT) {
        const VkBufferUsageFlags2 invalid =
            ~(VK_BUFFER_USAGE_2_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_2_TRANSFER_DST_BIT | VK_BUFFER_USAGE_2_UNIFORM_TEXEL_BUFFER_BIT |
              VK_BUFFER_USAGE_2_STORAGE_TEXEL_BUFFER_BIT | VK_BUFFER_USAGE_2_UNIFORM_BUFFER_BIT |
              VK_BUFFER_USAGE_2_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_2_SHADER_DEVICE_ADDRESS_BIT |
              VK_BUFFER_USAGE_2_VIDEO_DECODE_SRC_BIT_KHR | VK_BUFFER_USAGE_2_VIDEO_ENCODE_DST_BIT_KHR |
              VK_BUFFER_USAGE_2_DESCRIPTOR_HEAP_BIT_EXT);
        if (usage & invalid) {
            skip |= LogError("VUID-VkBufferCreateInfo-flags-09641", device, create_info_loc.dot(Field::flags),
                             "includes VK_BUFFER_CREATE_PROTECTED_BIT, but the usage contains {}.",
                             vvl::Flags::BufferUsageFlags2(usage & invalid));
        }
        if ((usage & VK_BUFFER_USAGE_2_DESCRIPTOR_HEAP_BIT_EXT) != 0 &&
            !phys_dev_ext_props.descriptor_heap_props.protectedDescriptorHeaps) {
            skip |= LogError("VUID-VkBufferCreateInfo-flags-11277", device, create_info_loc.dot(Field::flags),
                             "includes VK_BUFFER_CREATE_PROTECTED_BIT, and the usage ({}) includes "
                             "VK_BUFFER_USAGE_2_DESCRIPTOR_HEAP_BIT_EXT, but protectedDescriptorHeaps is VK_FALSE.",
                             vvl::Flags::BufferUsageFlags2(usage));
        }
    }

    if ((pCreateInfo->flags & (VK_BUFFER_CREATE_SPARSE_BINDING_BIT | VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT |
                               VK_BUFFER_CREATE_SPARSE_ALIASED_BIT)) != 0) {
        auto dedicated_allocation_buffer = vku::FindStructInPNextChain<VkDedicatedAllocationBufferCreateInfoNV>(pCreateInfo->pNext);
        if (dedicated_allocation_buffer && dedicated_allocation_buffer->dedicatedAllocation == VK_TRUE) {
            skip |= LogError("VUID-VkBufferCreateInfo-pNext-01571", device, create_info_loc.dot(Field::flags),
                             "is {}, but VkDedicatedAllocationBufferCreateInfoNV::dedicatedAllocation is VK_TRUE.",
                             vvl::Flags::BufferCreateFlags(pCreateInfo->flags));
        }
        if ((usage & VK_BUFFER_USAGE_2_DESCRIPTOR_HEAP_BIT_EXT) != 0 &&
            !phys_dev_ext_props.descriptor_heap_props.sparseDescriptorHeaps) {
            skip |= LogError("VUID-VkBufferCreateInfo-flags-11279", device, create_info_loc.dot(Field::flags),
                             "({}) includes sparse flags, and usage is {}, but sparseDescriptorHeaps is VK_FALSE.",
                             vvl::Flags::BufferCreateFlags(pCreateInfo->flags), vvl::Flags::BufferUsageFlags2(usage));
        }
    }

    // From https://github.com/KhronosGroup/Vulkan-ValidationLayers/issues/11121
    // Likely issue with the features/versions using, but safely check for maxBufferSize being zero to help limit false positives
    if (enabled_features.maintenance4 && pCreateInfo->size > phys_dev_props_core13.maxBufferSize &&
        phys_dev_props_core13.maxBufferSize != 0) {
        skip |= LogError("VUID-VkBufferCreateInfo-size-06409", device, create_info_loc.dot(Field::size),
                         "({}"
                         ") is larger than the maximum allowed buffer size "
                         "VkPhysicalDeviceMaintenance4Properties.maxBufferSize ({}"
                         ").",
                         pCreateInfo->size, phys_dev_props_core13.maxBufferSize);
    }

    skip |= ValidateCreateBufferFlags(pCreateInfo->flags, create_info_loc.dot(Field::flags));
    skip |= ValidateCreateBufferBufferDeviceAddress(*pCreateInfo, create_info_loc);
    skip |= ValidateCreateBufferTileMemory(*pCreateInfo, create_info_loc);
    skip |= ValidateCreateBufferDeviceAddressAllocationAlignment(*pCreateInfo, create_info_loc);

    return skip;
}

bool Device::manual_PreCallValidateCreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo,
                                                    const VkAllocationCallbacks* pAllocator, VkBufferView* pBufferView,
                                                    const Context& context) const {
    bool skip = false;
#ifdef VK_USE_PLATFORM_METAL_EXT
    skip |= ExportMetalObjectsPNextUtil(VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_BIT_EXT,
                                        "VUID-VkBufferViewCreateInfo-pNext-06782", context.error_obj.location,
                                        "VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_BIT_EXT", pCreateInfo->pNext);
#endif  // VK_USE_PLATFORM_METAL_EXT

    const Location create_info_loc = context.error_obj.location.dot(Field::pCreateInfo);

    const VkDeviceSize& range = pCreateInfo->range;
    const VkFormat format = pCreateInfo->format;

    if (vkuFormatIsDepthOrStencil(format)) {
        // Should never hopefully get here, but there are known driver advertising the wrong feature flags
        // see https://gitlab.khronos.org/vulkan/vulkan/-/merge_requests/4849
        skip |= LogError("UNASSIGNED-VkBufferViewCreateInfo-depthStencil-format", pCreateInfo->buffer,
                         create_info_loc.dot(Field::format),
                         "is a depth/stencil format ({}), but depth/stencil formats do not have a "
                         "defined size for alignment, replace with a color format.",
                         string_VkFormat(format));
    }

    if (range != VK_WHOLE_SIZE) {
        // will be 1 because  block-compressed format are not supported for Texel Buffer
        const VkDeviceSize texels_per_block = static_cast<VkDeviceSize>(vkuFormatTexelsPerBlock(format));
        const VkDeviceSize texel_block_size = static_cast<VkDeviceSize>(GetTexelBufferFormatSize(format));

        if (range == 0) {
            skip |= LogError("VUID-VkBufferViewCreateInfo-range-00928", pCreateInfo->buffer, create_info_loc.dot(Field::range),
                             "is 0, but must either be greater than 0 or VK_WHOLE_SIZE.");
        }

        if (!IsIntegerMultipleOf(range, texel_block_size)) {
            skip |= LogError("VUID-VkBufferViewCreateInfo-range-00929", pCreateInfo->buffer, create_info_loc.dot(Field::range),
                             "({}"
                             ") does not equal VK_WHOLE_SIZE, so it must be a multiple of the texel block size ({}"
                             ") of {}.",
                             range, texel_block_size, string_VkFormat(format));
        }
        const VkDeviceSize texels = SafeDivision(range, texel_block_size) * texels_per_block;
        if (texels > static_cast<VkDeviceSize>(phys_dev_props.limits.maxTexelBufferElements)) {
            skip |= LogError("VUID-VkBufferViewCreateInfo-range-00930", pCreateInfo->buffer, create_info_loc.dot(Field::range),
                             "({}"
                             "), {} texel block size ({}"
                             "), and texels per block ({}"
                             ") is a total of {}"
                             " texels which is more than VkPhysicalDeviceLimits::maxTexelBufferElements ({}"
                             ").",
                             range, string_VkFormat(format), texel_block_size, texels_per_block, texels,
                             phys_dev_props.limits.maxTexelBufferElements);
        }
    }

    if (api_version < VK_API_VERSION_1_3 && !enabled_features.ycbcr2plane444Formats) {
        if (IsValueIn(pCreateInfo->format,
                      {VK_FORMAT_G8_B8R8_2PLANE_444_UNORM, VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16,
                       VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16, VK_FORMAT_G16_B16R16_2PLANE_444_UNORM})) {
            skip |= LogError(
                "VUID-VkBufferViewCreateInfo-None-12278", pCreateInfo->buffer, create_info_loc.dot(Field::format),
                "is {}.\nHint: This format can be used with Vulkan 1.3 or if the ycbcr2plane444Formats feature is enabled.",
                string_VkFormat(pCreateInfo->format));
        }
    }

    return skip;
}

bool Device::ValidateCreateBufferFlags(const VkBufferCreateFlags flags, const Location& flag_loc) const {
    bool skip = false;

    if ((flags & VK_BUFFER_CREATE_SPARSE_BINDING_BIT) && (!enabled_features.sparseBinding)) {
        skip |= LogError("VUID-VkBufferCreateInfo-flags-00915", device, flag_loc,
                         "includes VK_BUFFER_CREATE_SPARSE_BINDING_BIT, but the sparseBinding feature is not enabled.");
    }

    if ((flags & VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT) && (!enabled_features.sparseResidencyBuffer)) {
        skip |= LogError("VUID-VkBufferCreateInfo-flags-00916", device, flag_loc,
                         "includes VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT, but the sparseResidencyBuffer feature is not enabled.");
    }

    if ((flags & VK_BUFFER_CREATE_SPARSE_ALIASED_BIT) && (!enabled_features.sparseResidencyAliased)) {
        skip |= LogError("VUID-VkBufferCreateInfo-flags-00917", device, flag_loc,
                         "includes VK_BUFFER_CREATE_SPARSE_ALIASED_BIT, but the sparseResidencyAliased feature is not enabled.");
    }

    if (((flags & (VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT | VK_BUFFER_CREATE_SPARSE_ALIASED_BIT)) != 0) &&
        ((flags & VK_BUFFER_CREATE_SPARSE_BINDING_BIT) != VK_BUFFER_CREATE_SPARSE_BINDING_BIT)) {
        skip |= LogError("VUID-VkBufferCreateInfo-flags-00918", device, flag_loc, "is {}.", vvl::Flags::BufferCreateFlags(flags));
    }

    if ((flags & VK_BUFFER_CREATE_PROTECTED_BIT) != 0) {
        if (enabled_features.protectedMemory == VK_FALSE) {
            skip |= LogError("VUID-VkBufferCreateInfo-flags-01887", device, flag_loc,
                             "has VK_BUFFER_CREATE_PROTECTED_BIT set but the protectedMemory device feature is not enabled.");
        }
        const VkBufferCreateFlags invalid_flags =
            VK_BUFFER_CREATE_SPARSE_BINDING_BIT | VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT | VK_BUFFER_CREATE_SPARSE_ALIASED_BIT;
        if ((flags & invalid_flags) != 0) {
            skip |= LogError("VUID-VkBufferCreateInfo-None-01888", device, flag_loc,
                             "is {} but can't mix protected with sparse flags.", vvl::Flags::BufferCreateFlags(flags));
        }
    }

    return skip;
}

bool Device::ValidateCreateBufferBufferDeviceAddress(const VkBufferCreateInfo& create_info, const Location& create_info_loc) const {
    bool skip = false;

    if (auto chained_devaddr_struct = vku::FindStructInPNextChain<VkBufferDeviceAddressCreateInfoEXT>(create_info.pNext)) {
        if (!(create_info.flags & VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT) &&
            chained_devaddr_struct->deviceAddress != 0) {
            skip |= LogError("VUID-VkBufferCreateInfo-deviceAddress-02604", device,
                             create_info_loc.pNext(Struct::VkBufferDeviceAddressCreateInfoEXT, Field::deviceAddress),
                             "({}"
                             ") is non-zero but requires VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT.",
                             chained_devaddr_struct->deviceAddress);
        }
    }

    if (auto chained_opaqueaddr_struct = vku::FindStructInPNextChain<VkBufferOpaqueCaptureAddressCreateInfo>(create_info.pNext)) {
        if (!(create_info.flags & VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT) &&
            chained_opaqueaddr_struct->opaqueCaptureAddress != 0) {
            skip |= LogError("VUID-VkBufferCreateInfo-opaqueCaptureAddress-03337", device,
                             create_info_loc.pNext(Struct::VkBufferOpaqueCaptureAddressCreateInfo, Field::opaqueCaptureAddress),
                             "({}"
                             ") is non-zero but requires VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT.",
                             chained_opaqueaddr_struct->opaqueCaptureAddress);
        }
    }

    if ((create_info.flags & VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT) &&
        !enabled_features.bufferDeviceAddressCaptureReplay && !enabled_features.bufferDeviceAddressCaptureReplayEXT) {
        skip |= LogError("VUID-VkBufferCreateInfo-flags-03338", device, create_info_loc.dot(Field::flags),
                         "has VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT set but the bufferDeviceAddressCaptureReplay "
                         "device feature is not enabled.");
    }

    return skip;
}

bool Device::ValidateCreateBufferDeviceAddressAllocationAlignment(const VkBufferCreateInfo& create_info,
                                                                  const Location& create_info_loc) const {
    bool skip = false;

    const auto* alignment_info = vku::FindStructInPNextChain<VkBufferDeviceAddressAlignmentAllocateInfoVALVE>(create_info.pNext);
    if (!alignment_info) {
        return skip;
    }
    const Location alignment_loc = create_info_loc.pNext(Struct::VkBufferDeviceAddressAlignmentAllocateInfoVALVE, Field::alignment);
    skip |= ValidateBufferDeviceAddressAlignmentAllocateInfo(*alignment_info, alignment_loc);

    if (alignment_info->alignment == 0) {
        return skip;  // "If alignment is 0, this alignment request is ignored"
    }

    if ((create_info.flags & VK_BUFFER_CREATE_SPARSE_BINDING_BIT) == 0) {
        skip |= LogError("VUID-VkBufferCreateInfo-flags-12515", device, alignment_loc,
                         "is {}"
                         " (not zero), but VkBufferCreateInfo::flags ({}) does not include VK_BUFFER_CREATE_SPARSE_BINDING_BIT.",
                         alignment_info->alignment, vvl::Flags::BufferCreateFlags(create_info.flags));
    }

    const VkBufferUsageFlags2 usage = GetBufferUsageFlags(create_info);
    if ((usage & VK_BUFFER_USAGE_2_SHADER_DEVICE_ADDRESS_BIT) == 0) {
        skip |=
            LogError("VUID-VkBufferCreateInfo-alignment-12516", device, alignment_loc,
                     "is {}"
                     " (not zero), but the effective usage flags ({}) do not include VK_BUFFER_USAGE_2_SHADER_DEVICE_ADDRESS_BIT.",
                     alignment_info->alignment, vvl::Flags::BufferUsageFlags2(usage));
    }

    if (const auto* opaque_addr_info = vku::FindStructInPNextChain<VkBufferOpaqueCaptureAddressCreateInfo>(create_info.pNext)) {
        if (opaque_addr_info->opaqueCaptureAddress != 0) {
            skip |= LogError("VUID-VkBufferCreateInfo-alignment-12517", device, alignment_loc,
                             "is {}"
                             " (not zero), but VkBufferOpaqueCaptureAddressCreateInfo::opaqueCaptureAddress ({}"
                             ") is not 0.",
                             alignment_info->alignment, opaque_addr_info->opaqueCaptureAddress);
        }
    }

    return skip;
}

bool Device::ValidateBufferDeviceAddressAlignmentAllocateInfo(const VkBufferDeviceAddressAlignmentAllocateInfoVALVE& alignment_info,
                                                              const Location& alignment_loc) const {
    bool skip = false;
    if (alignment_info.alignment == 0) {
        return skip;  // "If alignment is 0, this alignment request is ignored"
    }
    if (!IsPowerOfTwo(alignment_info.alignment)) {
        skip |= LogError("VUID-VkBufferDeviceAddressAlignmentAllocateInfoVALVE-alignment-12512", device, alignment_loc,
                         "({}"
                         ") is not a power of two.",
                         alignment_info.alignment);
    }
    if (!enabled_features.bufferDeviceAddressAllocationAlignment) {
        skip |= LogError("VUID-VkBufferDeviceAddressAlignmentAllocateInfoVALVE-alignment-12513", device, alignment_loc,
                         "is {}"
                         " (not zero), but the bufferDeviceAddressAllocationAlignment feature is not enabled.",
                         alignment_info.alignment);
    } else {
        const uint32_t max_alignment =
            phys_dev_ext_props.buffer_device_address_allocation_alignment_props.maxBufferDeviceAddressAllocationAlignment;
        if (alignment_info.alignment > max_alignment) {
            skip |= LogError("VUID-VkBufferDeviceAddressAlignmentAllocateInfoVALVE-alignment-12514", device, alignment_loc,
                             "({}"
                             ") is greater than maxBufferDeviceAddressAllocationAlignment ({}"
                             ").",
                             alignment_info.alignment, max_alignment);
        }
    }
    return skip;
}

bool Device::ValidateCreateBufferTileMemory(const VkBufferCreateInfo& create_info, const Location& create_info_loc) const {
    bool skip = false;

    const VkBufferCreateFlags flags = create_info.flags;
    const VkBufferUsageFlags2 usage = GetBufferUsageFlags(create_info);
    const Location usage_loc = GetUsageLocation(create_info, create_info_loc);

    if (usage & VK_BUFFER_USAGE_TILE_MEMORY_BIT_QCOM) {
        const VkBufferCreateFlags invalid_flag_mask =
            VK_BUFFER_CREATE_SPARSE_BINDING_BIT | VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT | VK_BUFFER_CREATE_SPARSE_ALIASED_BIT |
            VK_BUFFER_CREATE_PROTECTED_BIT | VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT |
            VK_BUFFER_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR | VK_BUFFER_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT;
        VkBufferUsageFlags2 valid_usage_mask = VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT |
                                               VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT |
                                               VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_TILE_MEMORY_BIT_QCOM;

        if (phys_dev_ext_props.tile_memory_heap_props.tileBufferTransfers) {
            valid_usage_mask |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
        }

        const VkBufferCreateFlags invalid_flags = (flags & invalid_flag_mask);
        const VkBufferUsageFlags2 invalid_usage = (usage & ~valid_usage_mask);

        if (!enabled_features.tileMemoryHeap) {
            skip |= LogError("VUID-VkBufferCreateInfo-tileMemoryHeap-10762", device, usage_loc,
                             "has VK_BUFFER_USAGE_TILE_MEMORY_BIT_QCOM set but the "
                             "tileMemoryHeap device feature is not enabled.");
        }

        if (invalid_flags) {
            skip |= LogError("VUID-VkBufferCreateInfo-usage-10763", device, usage_loc,
                             "contains VK_BUFFER_USAGE_TILE_MEMORY_BIT_QCOM but flags contains {}\nAll create flags: ({})",
                             vvl::Flags::BufferCreateFlags(invalid_flags), vvl::Flags::BufferCreateFlags(flags));
        }

        if (invalid_usage) {
            skip |= LogError("VUID-VkBufferCreateInfo-usage-10764", device, usage_loc,
                             "contains VK_BUFFER_USAGE_TILE_MEMORY_BIT_QCOM but usage contains {}\nAll usage flags: ({})",
                             vvl::Flags::BufferUsageFlags2(invalid_usage), vvl::Flags::BufferUsageFlags2(usage));
        }
    }

    return skip;
}

}  // namespace stateless
