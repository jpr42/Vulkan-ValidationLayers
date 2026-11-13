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

#include <vulkan/vulkan.h>
#include "error_message/log_flags.h"

// For the Log* functions: "{}" with vvl::Flags::ShaderStageFlags(stages) prints like
// string_VkShaderStageFlags(stages), but formats only if the message is delivered and never allocates
namespace vvl::Flags {
FlagsRef FormatFeatureFlags(VkFormatFeatureFlags value);
FlagsRef ImageCreateFlags(VkImageCreateFlags value);
FlagsRef SampleCountFlags(VkSampleCountFlags value);
FlagsRef ImageUsageFlags(VkImageUsageFlags value);
FlagsRef InstanceCreateFlags(VkInstanceCreateFlags value);
FlagsRef MemoryHeapFlags(VkMemoryHeapFlags value);
FlagsRef MemoryPropertyFlags(VkMemoryPropertyFlags value);
FlagsRef QueueFlags(VkQueueFlags value);
FlagsRef ShaderStageFlags(VkShaderStageFlags value);
FlagsRef DeviceQueueCreateFlags(VkDeviceQueueCreateFlags value);
FlagsRef PipelineStageFlags(VkPipelineStageFlags value);
FlagsRef MemoryMapFlags(VkMemoryMapFlags value);
FlagsRef ImageAspectFlags(VkImageAspectFlags value);
FlagsRef SparseImageFormatFlags(VkSparseImageFormatFlags value);
FlagsRef SparseMemoryBindFlags(VkSparseMemoryBindFlags value);
FlagsRef FenceCreateFlags(VkFenceCreateFlags value);
FlagsRef QueryPoolCreateFlags(VkQueryPoolCreateFlags value);
FlagsRef QueryPipelineStatisticFlags(VkQueryPipelineStatisticFlags value);
FlagsRef QueryResultFlags(VkQueryResultFlags value);
FlagsRef BufferCreateFlags(VkBufferCreateFlags value);
FlagsRef BufferUsageFlags(VkBufferUsageFlags value);
FlagsRef ImageViewCreateFlags(VkImageViewCreateFlags value);
FlagsRef AccessFlags(VkAccessFlags value);
FlagsRef DependencyFlags(VkDependencyFlags value);
FlagsRef CommandPoolCreateFlags(VkCommandPoolCreateFlags value);
FlagsRef CommandPoolResetFlags(VkCommandPoolResetFlags value);
FlagsRef QueryControlFlags(VkQueryControlFlags value);
FlagsRef CommandBufferUsageFlags(VkCommandBufferUsageFlags value);
FlagsRef CommandBufferResetFlags(VkCommandBufferResetFlags value);
FlagsRef EventCreateFlags(VkEventCreateFlags value);
FlagsRef PipelineCacheCreateFlags(VkPipelineCacheCreateFlags value);
FlagsRef PipelineCreateFlags(VkPipelineCreateFlags value);
FlagsRef PipelineLayoutCreateFlags(VkPipelineLayoutCreateFlags value);
FlagsRef PipelineShaderStageCreateFlags(VkPipelineShaderStageCreateFlags value);
FlagsRef SamplerCreateFlags(VkSamplerCreateFlags value);
FlagsRef DescriptorPoolCreateFlags(VkDescriptorPoolCreateFlags value);
FlagsRef DescriptorSetLayoutCreateFlags(VkDescriptorSetLayoutCreateFlags value);
FlagsRef ColorComponentFlags(VkColorComponentFlags value);
FlagsRef CullModeFlags(VkCullModeFlags value);
FlagsRef PipelineColorBlendStateCreateFlags(VkPipelineColorBlendStateCreateFlags value);
FlagsRef PipelineDepthStencilStateCreateFlags(VkPipelineDepthStencilStateCreateFlags value);
FlagsRef AttachmentDescriptionFlags(VkAttachmentDescriptionFlags value);
FlagsRef FramebufferCreateFlags(VkFramebufferCreateFlags value);
FlagsRef RenderPassCreateFlags(VkRenderPassCreateFlags value);
FlagsRef SubpassDescriptionFlags(VkSubpassDescriptionFlags value);
FlagsRef StencilFaceFlags(VkStencilFaceFlags value);
FlagsRef SubgroupFeatureFlags(VkSubgroupFeatureFlags value);
FlagsRef PeerMemoryFeatureFlags(VkPeerMemoryFeatureFlags value);
FlagsRef MemoryAllocateFlags(VkMemoryAllocateFlags value);
FlagsRef ExternalMemoryHandleTypeFlags(VkExternalMemoryHandleTypeFlags value);
FlagsRef ExternalMemoryFeatureFlags(VkExternalMemoryFeatureFlags value);
FlagsRef ExternalFenceHandleTypeFlags(VkExternalFenceHandleTypeFlags value);
FlagsRef ExternalFenceFeatureFlags(VkExternalFenceFeatureFlags value);
FlagsRef FenceImportFlags(VkFenceImportFlags value);
FlagsRef SemaphoreImportFlags(VkSemaphoreImportFlags value);
FlagsRef ExternalSemaphoreHandleTypeFlags(VkExternalSemaphoreHandleTypeFlags value);
FlagsRef ExternalSemaphoreFeatureFlags(VkExternalSemaphoreFeatureFlags value);
FlagsRef ResolveModeFlags(VkResolveModeFlags value);
FlagsRef SemaphoreWaitFlags(VkSemaphoreWaitFlags value);
FlagsRef DescriptorBindingFlags(VkDescriptorBindingFlags value);
FlagsRef ToolPurposeFlags(VkToolPurposeFlags value);
FlagsRef PrivateDataSlotCreateFlags(VkPrivateDataSlotCreateFlags value);
FlagsRef PipelineStageFlags2(VkPipelineStageFlags2 value);
FlagsRef AccessFlags2(VkAccessFlags2 value);
FlagsRef SubmitFlags(VkSubmitFlags value);
FlagsRef FormatFeatureFlags2(VkFormatFeatureFlags2 value);
FlagsRef PipelineCreationFeedbackFlags(VkPipelineCreationFeedbackFlags value);
FlagsRef RenderingFlags(VkRenderingFlags value);
FlagsRef MemoryUnmapFlags(VkMemoryUnmapFlags value);
FlagsRef BufferUsageFlags2(VkBufferUsageFlags2 value);
FlagsRef HostImageCopyFlags(VkHostImageCopyFlags value);
FlagsRef PipelineCreateFlags2(VkPipelineCreateFlags2 value);
FlagsRef SurfaceTransformFlagsKHR(VkSurfaceTransformFlagsKHR value);
FlagsRef CompositeAlphaFlagsKHR(VkCompositeAlphaFlagsKHR value);
FlagsRef SwapchainCreateFlagsKHR(VkSwapchainCreateFlagsKHR value);
FlagsRef DeviceGroupPresentModeFlagsKHR(VkDeviceGroupPresentModeFlagsKHR value);
FlagsRef DisplayPlaneAlphaFlagsKHR(VkDisplayPlaneAlphaFlagsKHR value);
FlagsRef VideoCodecOperationFlagsKHR(VkVideoCodecOperationFlagsKHR value);
FlagsRef VideoChromaSubsamplingFlagsKHR(VkVideoChromaSubsamplingFlagsKHR value);
FlagsRef VideoComponentBitDepthFlagsKHR(VkVideoComponentBitDepthFlagsKHR value);
FlagsRef VideoCapabilityFlagsKHR(VkVideoCapabilityFlagsKHR value);
FlagsRef VideoSessionCreateFlagsKHR(VkVideoSessionCreateFlagsKHR value);
FlagsRef VideoSessionParametersCreateFlagsKHR(VkVideoSessionParametersCreateFlagsKHR value);
FlagsRef VideoCodingControlFlagsKHR(VkVideoCodingControlFlagsKHR value);
FlagsRef VideoDecodeCapabilityFlagsKHR(VkVideoDecodeCapabilityFlagsKHR value);
FlagsRef VideoDecodeUsageFlagsKHR(VkVideoDecodeUsageFlagsKHR value);
FlagsRef VideoEncodeH264CapabilityFlagsKHR(VkVideoEncodeH264CapabilityFlagsKHR value);
FlagsRef VideoEncodeH264StdFlagsKHR(VkVideoEncodeH264StdFlagsKHR value);
FlagsRef VideoEncodeH264RateControlFlagsKHR(VkVideoEncodeH264RateControlFlagsKHR value);
FlagsRef VideoEncodeH265CapabilityFlagsKHR(VkVideoEncodeH265CapabilityFlagsKHR value);
FlagsRef VideoEncodeH265StdFlagsKHR(VkVideoEncodeH265StdFlagsKHR value);
FlagsRef VideoEncodeH265CtbSizeFlagsKHR(VkVideoEncodeH265CtbSizeFlagsKHR value);
FlagsRef VideoEncodeH265TransformBlockSizeFlagsKHR(VkVideoEncodeH265TransformBlockSizeFlagsKHR value);
FlagsRef VideoEncodeH265RateControlFlagsKHR(VkVideoEncodeH265RateControlFlagsKHR value);
FlagsRef VideoDecodeH264PictureLayoutFlagsKHR(VkVideoDecodeH264PictureLayoutFlagsKHR value);
FlagsRef PerformanceCounterDescriptionFlagsKHR(VkPerformanceCounterDescriptionFlagsKHR value);
FlagsRef VideoEncodeFlagsKHR(VkVideoEncodeFlagsKHR value);
FlagsRef VideoEncodeCapabilityFlagsKHR(VkVideoEncodeCapabilityFlagsKHR value);
FlagsRef VideoEncodeRateControlModeFlagsKHR(VkVideoEncodeRateControlModeFlagsKHR value);
FlagsRef VideoEncodeFeedbackFlagsKHR(VkVideoEncodeFeedbackFlagsKHR value);
FlagsRef VideoEncodeUsageFlagsKHR(VkVideoEncodeUsageFlagsKHR value);
FlagsRef VideoEncodeContentFlagsKHR(VkVideoEncodeContentFlagsKHR value);
FlagsRef AddressCommandFlagsKHR(VkAddressCommandFlagsKHR value);
FlagsRef ConditionalRenderingFlagsEXT(VkConditionalRenderingFlagsEXT value);
FlagsRef AccelerationStructureCreateFlagsKHR(VkAccelerationStructureCreateFlagsKHR value);
FlagsRef PresentScalingFlagsKHR(VkPresentScalingFlagsKHR value);
FlagsRef PresentGravityFlagsKHR(VkPresentGravityFlagsKHR value);
FlagsRef VideoEncodeAV1CapabilityFlagsKHR(VkVideoEncodeAV1CapabilityFlagsKHR value);
FlagsRef VideoEncodeAV1StdFlagsKHR(VkVideoEncodeAV1StdFlagsKHR value);
FlagsRef VideoEncodeAV1SuperblockSizeFlagsKHR(VkVideoEncodeAV1SuperblockSizeFlagsKHR value);
FlagsRef VideoEncodeAV1RateControlFlagsKHR(VkVideoEncodeAV1RateControlFlagsKHR value);
FlagsRef AddressCopyFlagsKHR(VkAddressCopyFlagsKHR value);
FlagsRef VideoEncodeIntraRefreshModeFlagsKHR(VkVideoEncodeIntraRefreshModeFlagsKHR value);
FlagsRef DeviceFaultFlagsKHR(VkDeviceFaultFlagsKHR value);
FlagsRef AccessFlags3KHR(VkAccessFlags3KHR value);
FlagsRef VideoEncodePerPartitionFeedbackFlagsKHR(VkVideoEncodePerPartitionFeedbackFlagsKHR value);
FlagsRef RenderingAttachmentFlagsKHR(VkRenderingAttachmentFlagsKHR value);
FlagsRef ResolveImageFlagsKHR(VkResolveImageFlagsKHR value);
FlagsRef ImageUsageFlags2KHR(VkImageUsageFlags2KHR value);
FlagsRef ImageCreateFlags2KHR(VkImageCreateFlags2KHR value);
FlagsRef DebugReportFlagsEXT(VkDebugReportFlagsEXT value);
FlagsRef ExternalMemoryHandleTypeFlagsNV(VkExternalMemoryHandleTypeFlagsNV value);
FlagsRef ExternalMemoryFeatureFlagsNV(VkExternalMemoryFeatureFlagsNV value);
FlagsRef SurfaceCounterFlagsEXT(VkSurfaceCounterFlagsEXT value);
FlagsRef DebugUtilsMessageSeverityFlagsEXT(VkDebugUtilsMessageSeverityFlagsEXT value);
FlagsRef DebugUtilsMessageTypeFlagsEXT(VkDebugUtilsMessageTypeFlagsEXT value);
FlagsRef GpaSqShaderStageFlagsAMD(VkGpaSqShaderStageFlagsAMD value);
FlagsRef TensorViewCreateFlagsARM(VkTensorViewCreateFlagsARM value);
FlagsRef SpirvResourceTypeFlagsEXT(VkSpirvResourceTypeFlagsEXT value);
FlagsRef GeometryFlagsKHR(VkGeometryFlagsKHR value);
FlagsRef GeometryInstanceFlagsKHR(VkGeometryInstanceFlagsKHR value);
FlagsRef BuildAccelerationStructureFlagsKHR(VkBuildAccelerationStructureFlagsKHR value);
FlagsRef PresentStageFlagsEXT(VkPresentStageFlagsEXT value);
FlagsRef PastPresentationTimingFlagsEXT(VkPastPresentationTimingFlagsEXT value);
FlagsRef PresentTimingInfoFlagsEXT(VkPresentTimingInfoFlagsEXT value);
FlagsRef IndirectStateFlagsNV(VkIndirectStateFlagsNV value);
FlagsRef IndirectCommandsLayoutUsageFlagsNV(VkIndirectCommandsLayoutUsageFlagsNV value);
FlagsRef DeviceDiagnosticsConfigFlagsNV(VkDeviceDiagnosticsConfigFlagsNV value);
FlagsRef TileShadingRenderPassFlagsQCOM(VkTileShadingRenderPassFlagsQCOM value);
#ifdef VK_USE_PLATFORM_METAL_EXT
FlagsRef ExportMetalObjectTypeFlagsEXT(VkExportMetalObjectTypeFlagsEXT value);
#endif  // VK_USE_PLATFORM_METAL_EXT
FlagsRef GraphicsPipelineLibraryFlagsEXT(VkGraphicsPipelineLibraryFlagsEXT value);
FlagsRef ImageCompressionFlagsEXT(VkImageCompressionFlagsEXT value);
FlagsRef ImageCompressionFixedRateFlagsEXT(VkImageCompressionFixedRateFlagsEXT value);
FlagsRef DeviceAddressBindingFlagsEXT(VkDeviceAddressBindingFlagsEXT value);
#ifdef VK_USE_PLATFORM_FUCHSIA
FlagsRef ImageConstraintsInfoFlagsFUCHSIA(VkImageConstraintsInfoFlagsFUCHSIA value);
#endif  // VK_USE_PLATFORM_FUCHSIA
FlagsRef FrameBoundaryFlagsEXT(VkFrameBoundaryFlagsEXT value);
FlagsRef VideoEncodeRgbModelConversionFlagsVALVE(VkVideoEncodeRgbModelConversionFlagsVALVE value);
FlagsRef VideoEncodeRgbRangeCompressionFlagsVALVE(VkVideoEncodeRgbRangeCompressionFlagsVALVE value);
FlagsRef VideoEncodeRgbChromaOffsetFlagsVALVE(VkVideoEncodeRgbChromaOffsetFlagsVALVE value);
FlagsRef BuildMicromapFlagsEXT(VkBuildMicromapFlagsEXT value);
FlagsRef MicromapCreateFlagsEXT(VkMicromapCreateFlagsEXT value);
FlagsRef PhysicalDeviceSchedulingControlsFlagsARM(VkPhysicalDeviceSchedulingControlsFlagsARM value);
FlagsRef MemoryDecompressionMethodFlagsEXT(VkMemoryDecompressionMethodFlagsEXT value);
FlagsRef TensorCreateFlagsARM(VkTensorCreateFlagsARM value);
FlagsRef TensorUsageFlagsARM(VkTensorUsageFlagsARM value);
FlagsRef OpticalFlowGridSizeFlagsNV(VkOpticalFlowGridSizeFlagsNV value);
FlagsRef OpticalFlowUsageFlagsNV(VkOpticalFlowUsageFlagsNV value);
FlagsRef OpticalFlowSessionCreateFlagsNV(VkOpticalFlowSessionCreateFlagsNV value);
FlagsRef OpticalFlowExecuteFlagsNV(VkOpticalFlowExecuteFlagsNV value);
FlagsRef ShaderCreateFlagsEXT(VkShaderCreateFlagsEXT value);
FlagsRef DataGraphPipelineSessionCreateFlagsARM(VkDataGraphPipelineSessionCreateFlagsARM value);
FlagsRef DataGraphTOSAQualityFlagsARM(VkDataGraphTOSAQualityFlagsARM value);
FlagsRef ClusterAccelerationStructureAddressResolutionFlagsNV(VkClusterAccelerationStructureAddressResolutionFlagsNV value);
FlagsRef ClusterAccelerationStructureClusterFlagsNV(VkClusterAccelerationStructureClusterFlagsNV value);
FlagsRef ClusterAccelerationStructureGeometryFlagsNV(VkClusterAccelerationStructureGeometryFlagsNV value);
FlagsRef ClusterAccelerationStructureIndexFormatFlagsNV(VkClusterAccelerationStructureIndexFormatFlagsNV value);
FlagsRef PartitionedAccelerationStructureInstanceFlagsNV(VkPartitionedAccelerationStructureInstanceFlagsNV value);
FlagsRef IndirectCommandsInputModeFlagsEXT(VkIndirectCommandsInputModeFlagsEXT value);
FlagsRef IndirectCommandsLayoutUsageFlagsEXT(VkIndirectCommandsLayoutUsageFlagsEXT value);
FlagsRef DataGraphOpticalFlowGridSizeFlagsARM(VkDataGraphOpticalFlowGridSizeFlagsARM value);
FlagsRef DataGraphOpticalFlowCreateFlagsARM(VkDataGraphOpticalFlowCreateFlagsARM value);
FlagsRef DataGraphOpticalFlowImageUsageFlagsARM(VkDataGraphOpticalFlowImageUsageFlagsARM value);
FlagsRef DataGraphOpticalFlowExecuteFlagsARM(VkDataGraphOpticalFlowExecuteFlagsARM value);
FlagsRef CooperativeMatrixFlagsEXT(VkCooperativeMatrixFlagsEXT value);
}  // namespace vvl::Flags
// NOLINTEND
