/*
 * Copyright (c) 2026 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

// Tests vvl::Fence directly, without a device or queue. With no queue attached, NotifyAndWait() retires the fence itself.
// These tests are mainly for thread sanitizer runs.

#include "../framework/test_common.h"

#include <memory>
#include <thread>

#include "error_message/error_location.h"
#include "error_message/logging.h"
#include "state_tracker/fence_state.h"
#include "utils/cast_utils.h"

class VvlCoreFence : public testing::Test {
  protected:
    void SetUp() override {
        VkFenceCreateInfo create_info = vku::InitStructHelper();
        fence_ = std::make_shared<vvl::Fence>(logger_, CastFromUint64<VkFence>(0x1234), &create_info);
    }

    DebugReport debug_report_;
    Logger logger_{&debug_report_};
    std::shared_ptr<vvl::Fence> fence_;
    const Location loc_{vvl::Func::vkWaitForFences};
};

TEST_F(VvlCoreFence, NotifyAndWaitRacesRetire) {
    // A host wait and the queue retiring the same submission can run at the same time. Only one of them may complete the
    // fence's promise, and the fence must end up retired either way.
    for (uint64_t seq = 1; seq <= 1000; ++seq) {
        fence_->EnqueueSignal(nullptr, seq);
        std::thread waiter([&] { fence_->NotifyAndWait(loc_); });
        fence_->Retire();
        waiter.join();
        ASSERT_EQ(fence_->State(), vvl::Fence::kRetired);
        fence_->Reset();
    }
}

TEST_F(VvlCoreFence, SetPresentWaitSemaphoresRacesNotifyAndWait) {
    // vkQueuePresentKHR records the semaphores a present fence waits on, while another thread may be waiting on the fence.
    // Both update the same list, so both must hold the fence's lock.
    std::thread waiter([&] {
        for (int i = 0; i < 1000; ++i) {
            fence_->NotifyAndWait(loc_);
        }
    });
    for (int i = 0; i < 1000; ++i) {
        fence_->SetPresentWaitSemaphores({});
    }
    waiter.join();
}
