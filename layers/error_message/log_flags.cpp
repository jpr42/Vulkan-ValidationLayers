/* Copyright (c) 2026 LunarG, Inc.
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
#include "error_message/log_flags.h"

namespace vvl {

// The same order of checks as the string_Vk*Flags*() helpers: whole-value names, then each set bit from the lowest,
// joined by '|', then the zero text
void VisitFlags(const FlagsRef& flags, FlagsEmitPiece emit, void* context) {
    const FlagsDescription& description = *flags.description;
    for (uint32_t i = 0; i < description.whole_value_count; ++i) {
        if (flags.value == description.whole_values[i].value) {
            emit(context, description.whole_values[i].name);
            return;
        }
    }
    if (flags.value == 0) {
        emit(context, description.zero_text);
        return;
    }
    bool first = true;
    for (uint64_t remaining = flags.value; remaining != 0; remaining &= remaining - 1) {
        const uint64_t bit = remaining & (~remaining + 1);  // lowest set bit
        if (!first) {
            emit(context, "|");
        }
        first = false;
        emit(context, description.bit_name(bit));
    }
}

}  // namespace vvl
