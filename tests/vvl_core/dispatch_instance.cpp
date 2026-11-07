/*
 * Copyright (c) 2026 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

// Tests vvl::DispatchInstance directly. Constructing one needs no driver: it only reads settings and creates the
// validation objects.

#include "../framework/test_common.h"

#include "chassis/dispatch_object.h"

TEST(VvlCoreDispatchInstance, HandleWrappingIsPerInstance) {
    // Settings also come from the environment and vk_layer_settings.txt, so compare against what a default instance gets
    // here instead of assuming wrapping is on
    VkInstanceCreateInfo default_info = vku::InitStructHelper();
    vvl::DispatchInstance first_default(&default_info);
    const bool default_wrap_handles = first_default.wrap_handles;

    VkValidationFeatureDisableEXT disable = VK_VALIDATION_FEATURE_DISABLE_UNIQUE_HANDLES_EXT;
    VkValidationFeaturesEXT features = vku::InitStructHelper();
    features.disabledValidationFeatureCount = 1;
    features.pDisabledValidationFeatures = &disable;
    VkInstanceCreateInfo without_wrapping_info = vku::InitStructHelper(&features);
    vvl::DispatchInstance without_wrapping(&without_wrapping_info);
    EXPECT_FALSE(without_wrapping.wrap_handles);

    // Turning handle wrapping off for one instance used to turn it off for every instance in the process, existing or new
    vvl::DispatchInstance second_default(&default_info);
    EXPECT_EQ(first_default.wrap_handles, default_wrap_handles);
    EXPECT_EQ(second_default.wrap_handles, default_wrap_handles);
}
