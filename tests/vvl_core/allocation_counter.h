/*
 * Copyright (c) 2026 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */
#pragma once

#include <cstdint>
#include <functional>

// Counts heap allocations made through global operator new on the calling thread while `fn` runs.
// Not available under ASan or TSan, which replace the allocator themselves.
namespace vvl_test {

bool AllocationCountingAvailable();
uint64_t CountAllocations(const std::function<void()>& fn);
// Whether the calling thread is inside CountAllocations
bool CountingAllocations();

}  // namespace vvl_test
