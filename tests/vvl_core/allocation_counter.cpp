/*
 * Copyright (c) 2026 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

#include "allocation_counter.h"

#include <cstdlib>
#include <new>

#if defined(__SANITIZE_ADDRESS__) || defined(__SANITIZE_THREAD__)
#define VVL_TEST_SANITIZED 1
#elif defined(__has_feature)
#if __has_feature(address_sanitizer) || __has_feature(thread_sanitizer)
#define VVL_TEST_SANITIZED 1
#endif
#endif

namespace vvl_test {

#if defined(VVL_TEST_SANITIZED)

bool AllocationCountingAvailable() { return false; }

uint64_t CountAllocations(const std::function<void()>& fn) {
    fn();
    return 0;
}

bool CountingAllocations() { return false; }

#else

namespace {
// Trivially destructible on purpose: thread_local objects with destructors run at thread exit, after which this
// allocator may still be called
thread_local bool counting = false;
thread_local uint64_t count = 0;

void* Allocate(std::size_t size) {
    if (counting) {
        ++count;
    }
    // malloc(0) may return null, operator new may not
    if (void* ptr = std::malloc(size ? size : 1)) {
        return ptr;
    }
    throw std::bad_alloc();
}
}  // namespace

bool AllocationCountingAvailable() { return true; }

bool CountingAllocations() { return counting; }

uint64_t CountAllocations(const std::function<void()>& fn) {
    // Counting must stop however fn exits, or every later allocation on this thread would be counted
    struct StopCounting {
        ~StopCounting() { counting = false; }
    } stop;
    count = 0;
    counting = true;
    fn();
    return count;
}

#endif

}  // namespace vvl_test

#if !defined(VVL_TEST_SANITIZED)

// Replacements of the global non-aligned operator new/delete for the whole test binary. They forward to malloc/free and
// only count while CountAllocations runs on the same thread. Over-aligned allocations keep the default implementation.
void* operator new(std::size_t size) { return vvl_test::Allocate(size); }
void* operator new[](std::size_t size) { return vvl_test::Allocate(size); }
void* operator new(std::size_t size, const std::nothrow_t&) noexcept {
    try {
        return vvl_test::Allocate(size);
    } catch (...) {
        return nullptr;
    }
}
void* operator new[](std::size_t size, const std::nothrow_t&) noexcept {
    try {
        return vvl_test::Allocate(size);
    } catch (...) {
        return nullptr;
    }
}
void operator delete(void* ptr) noexcept { std::free(ptr); }
void operator delete[](void* ptr) noexcept { std::free(ptr); }
void operator delete(void* ptr, std::size_t) noexcept { std::free(ptr); }
void operator delete[](void* ptr, std::size_t) noexcept { std::free(ptr); }
void operator delete(void* ptr, const std::nothrow_t&) noexcept { std::free(ptr); }
void operator delete[](void* ptr, const std::nothrow_t&) noexcept { std::free(ptr); }

#endif
