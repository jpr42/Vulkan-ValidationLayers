/* Copyright (c) 2015-2026 The Khronos Group Inc.
 * Copyright (c) 2015-2026 Valve Corporation
 * Copyright (c) 2015-2026 LunarG, Inc.
 * Copyright (c) 2026 RasterGrid Kft.
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
#include "logging.h"

#include <csignal>
#include <algorithm>
#include <atomic>
#include <iterator>
#include <shared_mutex>
#include <type_traits>
#ifdef VK_USE_PLATFORM_WIN32_KHR
#include <debugapi.h>
#endif
#ifdef VK_USE_PLATFORM_ANDROID_KHR
#include "vk_layer_config.h"
#endif

#include <vulkan/vk_enum_string_helper.h>
#include <vulkan/utility/vk_safe_struct.hpp>
#include "generated/vk_object_types.h"
#include "generated/vk_validation_error_messages.h"
#include "error_location.h"
#include "utils/hash_util.h"
#include "utils/text_utils.h"
#include "error_message/log_message_type.h"

[[maybe_unused]] const char* kVUIDUndefined = "VUID_Undefined";

static inline void DebugReportFlagsToAnnotFlags(VkDebugReportFlagsEXT dr_flags, VkDebugUtilsMessageSeverityFlagsEXT* da_severity,
                                                VkDebugUtilsMessageTypeFlagsEXT* da_type) {
    *da_severity = 0;
    *da_type = 0;
    // If it's explicitly listed as a performance warning, treat it as a performance message. Otherwise, treat it as a validation
    // issue.
    if ((dr_flags & kPerformanceWarningBit) != 0) {
        *da_type |= VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        *da_severity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
    }
    if ((dr_flags & kVerboseBit) != 0) {
        *da_type |= VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
        *da_severity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;
    }
    if ((dr_flags & kInformationBit) != 0) {
        *da_type |= VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
        *da_severity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
    }
    if ((dr_flags & kWarningBit) != 0) {
        *da_type |= VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
        *da_severity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
    }
    if ((dr_flags & kErrorBit) != 0) {
        *da_type |= VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
        *da_severity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    }
}

void DebugReport::SetDebugUtilsSeverityFlags(std::vector<VkLayerDbgFunctionState>& callbacks) {
    // For all callback in list, return their complete set of severities and modes
    for (const auto& item : callbacks) {
        if (item.IsUtils()) {
            active_msg_severities |= item.debug_utils_msg_flags;
            active_msg_types |= item.debug_utils_msg_type;
        } else {
            VkFlags severities = 0;
            VkFlags types = 0;
            DebugReportFlagsToAnnotFlags(item.debug_report_msg_flags, &severities, &types);
            active_msg_severities |= severities;
            active_msg_types |= types;
        }
    }
}

void DebugReport::RemoveDebugUtilsCallback(uint64_t callback) {
    std::vector<VkLayerDbgFunctionState>& callbacks = debug_callback_list;
    auto item = callbacks.begin();
    for (; item != callbacks.end(); item++) {
        if (item->IsUtils()) {
            if (item->debug_utils_callback_object == CastToHandle<VkDebugUtilsMessengerEXT>(callback)) break;
        } else {
            if (item->debug_report_callback_object == CastToHandle<VkDebugReportCallbackEXT>(callback)) break;
        }
    }
    if (item != callbacks.end()) {
        callbacks.erase(item);
    }
    SetDebugUtilsSeverityFlags(callbacks);
}

namespace {
// Handle() resolves through the same VkHandleInfo traits as FormatHandle(). On 32-bit every non-dispatchable handle is a
// uint64_t, so both must fall back to the generic non-dispatchable type name. Checked in the layer so that 32-bit builds
// without tests compile it.
template <typename T>
constexpr VkObjectType HandleObjectType(HandleRef (DebugReport::*)(T) const) {
    return VkHandleInfo<T>::kVkObjectType;
}
#ifdef TYPESAFE_NONDISPATCHABLE_HANDLES
static_assert(HandleObjectType(&DebugReport::Handle<VkBuffer>) == VK_OBJECT_TYPE_BUFFER);
#else
static_assert(HandleObjectType(&DebugReport::Handle<VkBuffer>) == VK_OBJECT_TYPE_UNKNOWN);
#endif

// Per-thread buffers reused across messages. Never freed: thread_local destructors bring destruction-order and library
// unloading problems (see thread_safety_validation.cpp), so each thread that ever logged leaks one set.
struct FormatBuffers {
    std::string message;       // the formatted main message
    std::string full_message;  // the assembled text or JSON the callbacks receive
    std::string fields;        // Location fields for JSON
    std::string names;         // the object names, each followed by '\0'
    std::vector<uint32_t> name_offsets;
    std::vector<VkDebugUtilsObjectNameInfoEXT> object_name_infos;
    std::vector<VkDebugUtilsLabelEXT> queue_labels;
    std::vector<VkDebugUtilsLabelEXT> cmd_buf_labels;
    FormatBuffers* next = nullptr;
};

// Keeps every thread's buffers reachable, so leak checkers do not report the buffers of threads that have exited
std::atomic<FormatBuffers*> all_format_buffers{nullptr};

FormatBuffers& ThreadFormatBuffers() {
    thread_local FormatBuffers* buffers = nullptr;
    static_assert(std::is_trivially_destructible_v<decltype(buffers)>);
    if (!buffers) {
        buffers = new FormatBuffers();
        buffers->next = all_format_buffers.load(std::memory_order_relaxed);
        while (!all_format_buffers.compare_exchange_weak(buffers->next, buffers, std::memory_order_release,
                                                         std::memory_order_relaxed)) {
        }
    }
    return *buffers;
}
}  // namespace

bool DebugReport::LogMessage(VkFlags msg_flags, std::string_view vuid_text, const LogObjectList& objects, const Location& loc,
                             std::string_view format, vvl::format::format_args args) {
    const std::optional<PassedFilters> passed = FilterMessage(msg_flags, vuid_text);
    if (!passed) {
        return false;  // never formatted
    }
    // Formatted outside debug_output_mutex, so threads that log at the same time only serialize on delivery
    std::string& main_message = ThreadFormatBuffers().message;
    main_message.clear();
    vvl::format::VFormatTo(main_message, format, args);
    return DeliverMessage(*passed, msg_flags, vuid_text, objects, loc, main_message);
}

bool DebugReport::LogMessage(VkFlags msg_flags, std::string_view vuid_text, const LogObjectList& objects, const Location& loc,
                             std::string_view main_message) {
    const std::optional<PassedFilters> passed = FilterMessage(msg_flags, vuid_text);
    if (!passed) {
        return false;
    }
    return DeliverMessage(*passed, msg_flags, vuid_text, objects, loc, main_message);
}

// We try to return as early as we can if we know we don't need to spend time logging the message
std::optional<DebugReport::PassedFilters> DebugReport::FilterMessage(VkFlags msg_flags, std::string_view vuid_text) {
    // Convert the info to the VK_EXT_debug_utils format
    VkDebugUtilsMessageSeverityFlagsEXT msg_severity;
    VkDebugUtilsMessageTypeFlagsEXT msg_type;
    DebugReportFlagsToAnnotFlags(msg_flags, &msg_severity, &msg_type);
    if (!(active_msg_severities & msg_severity) || !(active_msg_types & msg_type)) {
        return std::nullopt;
    }

    // If message is in filter list, bail out very early
    const uint32_t vuid_hash = hash_util::VuidHash(vuid_text);
    if (filter_message_ids.find(vuid_hash) != filter_message_ids.end()) {
        return std::nullopt;
    }

    // We have a few special VUID we never actually want to suppress.
    // If a new VUID is added here, make sure to add it in NegativeOther.VuidHashStability test as well.
    const bool skip_checking_limit =
        // "VVL-DEBUG-PRINTF"
        // We want to print DebugPrintf message forever, otherwise user will mistake duplicate limit for things not printing
        (vuid_hash == 0x4fe1fef9) ||
        // "GPU-DUMP"
        // Want to always keep dumping, similar to DebugPrintf
        (vuid_hash == 0xe5c5edc1);

    // Count for this particular message is over the limit, ignore it
    bool at_message_limit = false;
    if (duplicate_message_limit > 0 && !skip_checking_limit) {
        // duplicate_message_count_map is not safe to update on multiple threads
        // see https://issues.angleproject.org/issues/450466850
        std::lock_guard<std::mutex> lock(duplicate_message_count_mutex);
        auto vuid_count_it = duplicate_message_count_map.find(vuid_hash);
        if (vuid_count_it == duplicate_message_count_map.end()) {
            duplicate_message_count_map.emplace(vuid_hash, 1);
            if (duplicate_message_limit == 1) {
                at_message_limit = true;
            }
        } else if (vuid_count_it->second >= duplicate_message_limit) {
            return std::nullopt;
        } else {
            vuid_count_it->second++;
            if (vuid_count_it->second >= duplicate_message_limit) {
                at_message_limit = true;
            }
        }
    }
    return PassedFilters{msg_severity, msg_type, vuid_hash, at_message_limit};
}

bool DebugReport::DeliverMessage(const PassedFilters& passed, VkFlags msg_flags, std::string_view vuid_text,
                                 const LogObjectList& objects, const Location& loc, std::string_view main_message) {
    const VkDebugUtilsMessageSeverityFlagsEXT msg_severity = passed.severity;
    const VkDebugUtilsMessageTypeFlagsEXT msg_type = passed.type;
    const uint32_t vuid_hash = passed.vuid_hash;

    FormatBuffers& buffers = ThreadFormatBuffers();
    std::vector<VkDebugUtilsObjectNameInfoEXT>& object_name_infos = buffers.object_name_infos;
    object_name_infos.clear();
    buffers.names.clear();
    buffers.name_offsets.clear();
    constexpr uint32_t kNoName = vvl::kU32Max;
    {
        // Copy the names out under the leaf lock, and release it before anything else is locked. Most applications never
        // name an object; they skip the lock.
        std::shared_lock<std::shared_mutex> name_lock(object_name_mutex, std::defer_lock);
        const bool has_names = has_object_names.load();
        if (has_names) {
            name_lock.lock();
        }
        for (const VulkanTypedHandle& current_object : objects.object_list) {
            // If only one VkDevice was created, it is just noise to print it out in the error message.
            // Also avoid printing unknown objects, likely if new function is calling error with null LogObjectList
            if ((current_object.type == kVulkanObjectTypeDevice && device_created <= 1) ||
                (current_object.type == kVulkanObjectTypeUnknown) || (current_object.handle == 0)) {
                continue;
            }

            VkDebugUtilsObjectNameInfoEXT object_name_info = vku::InitStructHelper();
            object_name_info.objectType = ConvertVulkanObjectToCoreObject(current_object.type);
            object_name_info.objectHandle = current_object.handle;
            object_name_info.pObjectName = nullptr;
            object_name_infos.push_back(object_name_info);

            // Look for any debug utils or marker names to use for this object
            const std::string* name = has_names ? FindObjectNameNoLock(current_object.handle) : nullptr;
            if (name) {
                buffers.name_offsets.push_back(static_cast<uint32_t>(buffers.names.size()));
                buffers.names.append(*name).push_back('\0');
            } else {
                buffers.name_offsets.push_back(kNoName);
            }
        }
    }
    // Only now: appending names may have moved the buffer
    for (size_t i = 0; i < object_name_infos.size(); ++i) {
        if (buffers.name_offsets[i] != kNoName) {
            object_name_infos[i].pObjectName = buffers.names.c_str() + buffers.name_offsets[i];
        }
    }

    // The text format is more minimal and will have other information in the callback, the JSON is designed to contain everything.
    // Assembly only reads per-thread copies and settings, so it runs before debug_output_mutex is taken.
    std::string& full_message = buffers.full_message;
    full_message.clear();
    if (message_format_settings.json) {
        AppendMessageJson(full_message, buffers.fields, msg_flags, loc, object_name_infos, vuid_hash, vuid_text, main_message,
                          passed.at_message_limit);
    } else {
        AppendMessageText(full_message, loc, vuid_text, main_message, passed.at_message_limit);
    }

    // Labels and the callback list are read under this lock, and callbacks are called under it
    std::unique_lock<std::mutex> lock(debug_output_mutex);

    std::vector<VkDebugUtilsLabelEXT>& queue_labels = buffers.queue_labels;
    std::vector<VkDebugUtilsLabelEXT>& cmd_buf_labels = buffers.cmd_buf_labels;
    queue_labels.clear();
    cmd_buf_labels.clear();
    for (const VkDebugUtilsObjectNameInfoEXT& object_name_info : object_name_infos) {
        // If this is a queue, add any queue labels to the callback data.
        if (VK_OBJECT_TYPE_QUEUE == object_name_info.objectType) {
            auto label_iter = debug_utils_queue_labels.find(reinterpret_cast<VkQueue>(object_name_info.objectHandle));
            if (label_iter != debug_utils_queue_labels.end()) {
                label_iter->second->Export(queue_labels);
            }
            // If this is a command buffer, add any command buffer labels to the callback data.
            // Only consider first found command buffer, to avoid mixing unrelated label stacks
        } else if (VK_OBJECT_TYPE_COMMAND_BUFFER == object_name_info.objectType && cmd_buf_labels.empty()) {
            auto label_iter = debug_utils_cmd_buffer_labels.find(reinterpret_cast<VkCommandBuffer>(object_name_info.objectHandle));
            if (label_iter != debug_utils_cmd_buffer_labels.end()) {
                label_iter->second->Export(cmd_buf_labels);
            }
        }
    }

    VkDebugUtilsMessengerCallbackDataEXT callback_data = vku::InitStructHelper();
    callback_data.flags = 0;
    callback_data.pMessageIdName = vuid_text.data();
    callback_data.messageIdNumber = vvl_bit_cast<int32_t>(vuid_hash);
    callback_data.pMessage = nullptr;
    callback_data.queueLabelCount = static_cast<uint32_t>(queue_labels.size());
    callback_data.pQueueLabels = queue_labels.empty() ? nullptr : queue_labels.data();
    callback_data.cmdBufLabelCount = static_cast<uint32_t>(cmd_buf_labels.size());
    callback_data.pCmdBufLabels = cmd_buf_labels.empty() ? nullptr : cmd_buf_labels.data();
    callback_data.objectCount = static_cast<uint32_t>(object_name_infos.size());
    callback_data.pObjects = object_name_infos.data();

    const auto callback_list = &debug_callback_list;
    // We only output to default callbacks if there are no non-default callbacks
    bool use_default_callbacks = true;
    for (const auto& current_callback : *callback_list) {
        use_default_callbacks &= current_callback.IsDefault();
    }

#ifdef VK_USE_PLATFORM_ANDROID_KHR
    if (force_default_log_callback) {
        use_default_callbacks = true;
    }
#endif

    const char* layer_prefix = "Validation";
    bool bail = false;
    for (const auto& current_callback : *callback_list) {
        // Skip callback if it's a default callback and there are non-default callbacks present
        if (current_callback.IsDefault() && !use_default_callbacks) continue;

        // VK_EXT_debug_utils callback
        if (current_callback.IsUtils() && (current_callback.debug_utils_msg_flags & msg_severity) &&
            (current_callback.debug_utils_msg_type & msg_type)) {
            callback_data.pMessage = full_message.c_str();
            if (current_callback.debug_utils_callback_function_ptr(
                    static_cast<VkDebugUtilsMessageSeverityFlagBitsEXT>(msg_severity), msg_type, &callback_data,
                    current_callback.pUserData)) {
                bail = true;
            }
        } else if (!current_callback.IsUtils() && (current_callback.debug_report_msg_flags & msg_flags)) {
            // VK_EXT_debug_report callback (deprecated)
            if (object_name_infos.empty()) {
                VkDebugUtilsObjectNameInfoEXT null_object_name = {VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT, nullptr,
                                                                  VK_OBJECT_TYPE_UNKNOWN, 0, nullptr};
                // need to have at least one object
                object_name_infos.emplace_back(null_object_name);
            }
            if (current_callback.debug_report_callback_function_ptr(
                    msg_flags, ConvertCoreObjectToDebugReportObject(object_name_infos[0].objectType),
                    object_name_infos[0].objectHandle, vuid_hash, 0, layer_prefix, full_message.c_str(),
                    current_callback.pUserData)) {
                bail = true;
            }
        }
    }
    return bail;
}

void DebugReport::AppendMessageText(std::string& out, const Location& loc, std::string_view vuid_text,
                                    std::string_view main_message, bool at_message_limit) const {
#if defined(BUILD_SELF_VVL)
    out += "[Self Validation] ";  // How we know if the error is from Self Validation when debugging GPU-AV
#endif

    if (message_format_settings.display_application_name && !message_format_settings.application_name.empty()) {
        out += "[AppName: ";
        out += message_format_settings.application_name;
        out += "] ";
    }

    if (at_message_limit) {
        VVL_FMT_NS::format_to(std::back_inserter(out),
                              "(Warning - This VUID has now been reported {} times, which is the duplicate_message_limit value, "
                              "this will be the last time reporting it).\n",
                              duplicate_message_limit);
    }

    loc.AppendMessage(out);
    out += ' ';
    out += main_message;

    // Append the spec error text to the error message, unless it contains a word treated as special
    if ((vuid_text.find("VUID-") != std::string::npos)) {
        const char* spec_text = nullptr;
        // Only the Antora site will make use of the sections
        const char* spec_url_section = nullptr;
        const auto found_vuid = GetVuidMap().find(vuid_text);
        if (found_vuid != GetVuidMap().end()) {
            spec_text = found_vuid->second.spec_text.data();
            spec_url_section = found_vuid->second.url_id.data();
        }

        // Construct and append the specification text and link to the appropriate version of the spec
        if (spec_text && spec_url_section) {
#ifdef ANNOTATED_SPEC_LINK
            const char* spec_url_base = ANNOTATED_SPEC_LINK;
#else
            const char* spec_url_base = "https://docs.vulkan.org/spec/latest/";
#endif

            assert(!main_message.empty());
            const auto last_char = main_message.back();
            // Add period at end if forgotten
            // This provides better separation between error message and spec text
            // (Don't add if end with a number, otherwise it looks like a floating point number)
            if (last_char != '.' && last_char != '\n' && (last_char < '0' || last_char > '9')) {
                out += '.';
            }

            // Start Vulkan spec text with a new line to make it easier visually
            if (last_char != '\n') {
                out += '\n';
            }

            VVL_FMT_NS::format_to(std::back_inserter(out), "The Vulkan spec states: {} ({}{}#{})", spec_text, spec_url_base,
                                  spec_url_section, vuid_text);
        }
    }
}

// Anything that ends up inside a JSON string has to be escaped
static void AppendJsonEscaped(std::string& out, std::string_view text) {
    // clang-format off
    for (char c : text) {
        switch (c) {
            case '"':  out += "\\\""; break;
            case '\\': out += "\\\\"; break;
            case '\n': out += "\\n";  break;
            case '\r': out += "\\r";  break;
            case '\t': out += "\\t";  break;
            case '\b': out += "\\b";  break;
            case '\f': out += "\\f";  break;
            default:
                if (static_cast<unsigned char>(c) < 0x20) {
                    // JSON requires the remaining control characters use the \u form
                    const char* hex_digits = "0123456789abcdef";
                    out += "\\u00";
                    out += hex_digits[(c >> 4) & 0xf];
                    out += hex_digits[c & 0xf];
                } else {
                    out += c;
                }
                break;
        }
    }
    // clang-format on
}

void DebugReport::AppendMessageJson(std::string& out, std::string& fields, VkFlags msg_flags, const Location& loc,
                                    const std::vector<VkDebugUtilsObjectNameInfoEXT>& object_name_infos, const uint32_t vuid_hash,
                                    std::string_view vuid_text, std::string_view main_message, bool at_message_limit) const {
    // For now we just list each JSON field as a new line as it is "pretty-print enough".
    // For Android, things get logged in logcat and having the JSON as a single line is easier to grab from the terminal.
#ifdef VK_USE_PLATFORM_ANDROID_KHR
    const char new_line = ' ';
    const char line_start = ' ';
#else
    const char new_line = '\n';
    const char line_start = '\t';
#endif
    auto field_start = [&](const char* name) {
        out += line_start;
        out += '"';
        out += name;
        out += "\" : \"";
    };
    auto field_end = [&](bool last = false) {
        out += last ? "\"" : "\",";
        out += new_line;
    };

    out += '{';
    out += new_line;

    if (message_format_settings.display_application_name && !message_format_settings.application_name.empty()) {
        field_start("AppName");
        AppendJsonEscaped(out, message_format_settings.application_name);
        field_end();
    }

    field_start("Severity");
    if (msg_flags & kErrorBit) {
        out += "Error";
    } else if (msg_flags & kWarningBit) {
        out += "Warning";
    } else if (msg_flags & kPerformanceWarningBit) {
        out += "Performance Warning";
    } else if (msg_flags & kInformationBit) {
        out += "Information";
    } else if (msg_flags & kVerboseBit) {
        out += "Verbose";
    }
    field_end();

    field_start("VUID");
    AppendJsonEscaped(out, vuid_text);
    field_end();

    out += line_start;
    out += "\"Objects\" : [";
    out += new_line;
    for (uint32_t i = 0; i < object_name_infos.size(); i++) {
        const VkDebugUtilsObjectNameInfoEXT& src_object = object_name_infos[i];

        out += line_start;
        out += line_start;
        out += "{\"type\" : \"";
        out += string_VkObjectTypeHandleName(src_object.objectType);
        out += "\", \"handle\" : \"";
        if (0 != src_object.objectHandle) {
            VVL_FMT_NS::format_to(std::back_inserter(out), "0x{:x}", src_object.objectHandle);
            out += "\", \"name\" : \"";
            if (src_object.pObjectName) {
                AppendJsonEscaped(out, src_object.pObjectName);
            }
            out += "\"}";
        } else {
            out += "VK_NULL_HANDLE\", \"name\" : \"\"}";
        }
        if (i + 1 != object_name_infos.size()) {
            out += ',';
        }
        out += new_line;
    }
    out += line_start;
    out += "],";
    out += new_line;

    field_start("MessageID");
    VVL_FMT_NS::format_to(std::back_inserter(out), "0x{:x}", vuid_hash);
    field_end();

    field_start("Function");
    out += loc.StringFunc();
    field_end();

    field_start("Location");
    fields.clear();
    loc.AppendFields(fields);
    AppendJsonEscaped(out, fields);
    field_end();

    field_start("MainMessage");
    if (at_message_limit) {
        VVL_FMT_NS::format_to(std::back_inserter(out),
                              "(Warning - This VUID has now been reported {} times, which is the duplicate_message_limit value, "
                              "this will be the last time reporting it). ",
                              duplicate_message_limit);
    }
    // For cases where we have multi-lines in the message, we need to escape them.
    // The idea is the JSON is machine readable and when someone prints the value out, the new lines will resolve then.
    AppendJsonEscaped(out, main_message);
    field_end();

    field_start("VkFrameBoundaryEXT::frameID");
    if (loc.frame_id != vvl::kNoIndex64) {
        VVL_FMT_NS::format_to(std::back_inserter(out), "{}", loc.frame_id);
    }
    field_end();

    field_start("DebugRegion");
    if (loc.debug_region && !loc.debug_region->empty()) {
        AppendJsonEscaped(out, *loc.debug_region);
    }
    field_end();

    const char* spec_text = nullptr;
    // Only the Antora site will make use of the sections
    const char* spec_url_section = nullptr;
    if ((vuid_text.find("VUID-") != std::string::npos)) {
        const auto found_vuid = GetVuidMap().find(vuid_text);
        if (found_vuid != GetVuidMap().end()) {
            spec_text = found_vuid->second.spec_text.data();
            spec_url_section = found_vuid->second.url_id.data();
        }
    }
    field_start("SpecText");
    if (spec_text) {
        AppendJsonEscaped(out, spec_text);
    }
    field_end();

    // Construct and append the specification text and link to the appropriate version of the spec
    field_start("SpecUrl");
    if (spec_text && spec_url_section) {
#ifdef ANNOTATED_SPEC_LINK
        out += ANNOTATED_SPEC_LINK;
#else
        out += "https://docs.vulkan.org/spec/latest/";
#endif
        out += spec_url_section;
        out += '#';
        AppendJsonEscaped(out, vuid_text);
    }
    field_end(true);
    out += '}';
}

void DebugReport::SetUtilsObjectName(const VkDebugUtilsObjectNameInfoEXT* pNameInfo) {
    std::unique_lock<std::shared_mutex> lock(object_name_mutex);
    if (pNameInfo->pObjectName) {
        debug_utils_object_name_map[pNameInfo->objectHandle] = pNameInfo->pObjectName;
        has_object_names.store(true);
    } else {
        debug_utils_object_name_map.erase(pNameInfo->objectHandle);
    }
}

void DebugReport::SetMarkerObjectName(const VkDebugMarkerObjectNameInfoEXT* pNameInfo) {
    std::unique_lock<std::shared_mutex> lock(object_name_mutex);
    if (pNameInfo->pObjectName) {
        debug_object_name_map[pNameInfo->object] = pNameInfo->pObjectName;
        has_object_names.store(true);
    } else {
        debug_object_name_map.erase(pNameInfo->object);
    }
}

void DebugReport::EraseObjectName(uint64_t object_handle) {
    // Skip using the |object_name_mutex| lock for a fast return if there is no name
    if (has_object_names.load()) {
        std::unique_lock<std::shared_mutex> lock(object_name_mutex);
        debug_utils_object_name_map.erase(object_handle);
        debug_object_name_map.erase(object_handle);
    }
}

std::string DebugReport::GetUtilsObjectName(uint64_t object) const {
    std::shared_lock<std::shared_mutex> lock(object_name_mutex);
    return GetUtilsObjectNameNoLock(object);
}

std::string DebugReport::GetMarkerObjectName(uint64_t object) const {
    std::shared_lock<std::shared_mutex> lock(object_name_mutex);
    return GetMarkerObjectNameNoLock(object);
}

const std::string* DebugReport::FindObjectNameNoLock(uint64_t object) const {
    const auto utils_name_iter = debug_utils_object_name_map.find(object);
    if (utils_name_iter != debug_utils_object_name_map.end() && !utils_name_iter->second.empty()) {
        return &utils_name_iter->second;
    }
    const auto marker_name_iter = debug_object_name_map.find(object);
    if (marker_name_iter != debug_object_name_map.end() && !marker_name_iter->second.empty()) {
        return &marker_name_iter->second;
    }
    return nullptr;
}

// NoLock suffix means that the function itself does not hold object_name_mutex,
// and it's **mandatory responsibility** of the caller to hold this lock.
std::string DebugReport::GetUtilsObjectNameNoLock(const uint64_t object) const {
    std::string label = "";
    const auto utils_name_iter = debug_utils_object_name_map.find(object);
    if (utils_name_iter != debug_utils_object_name_map.end()) {
        label = utils_name_iter->second;
    }
    return label;
}

// NoLock suffix means that the function itself does not hold object_name_mutex,
// and it's **mandatory responsibility** of the caller to hold this lock.
std::string DebugReport::GetMarkerObjectNameNoLock(const uint64_t object) const {
    std::string label = "";
    const auto marker_name_iter = debug_object_name_map.find(object);
    if (marker_name_iter != debug_object_name_map.end()) {
        label = marker_name_iter->second;
    }
    return label;
}

std::string DebugReport::FormatHandle(const char* handle_type_name, uint64_t handle) const {
    std::string handle_name;
    WithObjectName(handle, [&handle_name](const std::string& name) { handle_name = name; });

    std::ostringstream str;
    str << handle_type_name << " ";
    str << "0x" << std::hex << handle;

    if (!handle_name.empty()) {
        str << "[" << handle_name.c_str() << "]";
    }
    return str.str();
}

LoggingLabel::LoggingLabel(const VkDebugUtilsLabelEXT* label_info) {
    if (label_info && label_info->pLabelName) {
        name = label_info->pLabelName;
        std::copy_n(std::begin(label_info->color), 4, color.begin());
    }
}

template <typename Map>
static LoggingLabelState* GetLoggingLabelState(Map* map, typename Map::key_type key, bool insert) {
    auto iter = map->find(key);
    LoggingLabelState* label_state = nullptr;
    if (iter == map->end()) {
        if (insert) {
            // Add a label state if not present
            auto inserted = map->emplace(key, std::unique_ptr<LoggingLabelState>(new LoggingLabelState()));
            assert(inserted.second);
            iter = inserted.first;
            label_state = iter->second.get();
        }
    } else {
        label_state = iter->second.get();
    }
    return label_state;
}

void DebugReport::BeginQueueDebugUtilsLabel(VkQueue queue, const VkDebugUtilsLabelEXT* label_info) {
    std::unique_lock<std::mutex> lock(debug_output_mutex);
    if (nullptr != label_info && nullptr != label_info->pLabelName) {
        auto* label_state = GetLoggingLabelState(&debug_utils_queue_labels, queue, /* insert */ true);
        assert(label_state);
        label_state->labels.push_back(label_info);

        // TODO: Determine if this is the correct semantics for insert label vs. begin/end, preserving existing semantics for now
        label_state->insert_label.Reset();
    }
}

void DebugReport::EndQueueDebugUtilsLabel(VkQueue queue) {
    std::unique_lock<std::mutex> lock(debug_output_mutex);
    auto* label_state = GetLoggingLabelState(&debug_utils_queue_labels, queue, /* insert */ false);
    if (label_state) {
        // Pop the normal item
        if (!label_state->labels.empty()) {
            label_state->labels.pop_back();
        }

        // TODO: Determine if this is the correct semantics for insert label vs. begin/end, preserving existing semantics for now
        label_state->insert_label.Reset();
    }
}

void DebugReport::InsertQueueDebugUtilsLabel(VkQueue queue, const VkDebugUtilsLabelEXT* label_info) {
    std::unique_lock<std::mutex> lock(debug_output_mutex);
    auto* label_state = GetLoggingLabelState(&debug_utils_queue_labels, queue, /* insert */ true);

    // TODO: Determine if this is the correct semantics for insert label vs. begin/end, preserving existing semantics for now
    label_state->insert_label = LoggingLabel(label_info);
}

void DebugReport::BeginCmdDebugUtilsLabel(VkCommandBuffer command_buffer, const VkDebugUtilsLabelEXT* label_info) {
    std::unique_lock<std::mutex> lock(debug_output_mutex);
    if (nullptr != label_info && nullptr != label_info->pLabelName) {
        auto* label_state = GetLoggingLabelState(&debug_utils_cmd_buffer_labels, command_buffer, /* insert */ true);
        assert(label_state);
        label_state->labels.push_back(label_info);

        // TODO: Determine if this is the correct semantics for insert label vs. begin/end, preserving existing semantics for now
        label_state->insert_label.Reset();
    }
}

void DebugReport::EndCmdDebugUtilsLabel(VkCommandBuffer command_buffer) {
    std::unique_lock<std::mutex> lock(debug_output_mutex);
    auto* label_state = GetLoggingLabelState(&debug_utils_cmd_buffer_labels, command_buffer, /* insert */ false);
    if (label_state) {
        // Pop the normal item
        if (!label_state->labels.empty()) {
            label_state->labels.pop_back();
        }

        // TODO: Determine if this is the correct semantics for insert label vs. begin/end, preserving existing semantics for now
        label_state->insert_label.Reset();
    }
}

void DebugReport::InsertCmdDebugUtilsLabel(VkCommandBuffer command_buffer, const VkDebugUtilsLabelEXT* label_info) {
    std::unique_lock<std::mutex> lock(debug_output_mutex);
    auto* label_state = GetLoggingLabelState(&debug_utils_cmd_buffer_labels, command_buffer, /* insert */ true);
    assert(label_state);

    // TODO: Determine if this is the correct semantics for insert label vs. begin/end, preserving existing semantics for now
    label_state->insert_label = LoggingLabel(label_info);
}

// Current tracking beyond a single command buffer scope is incorrect, and even when it is we need to be able to clean up
void DebugReport::ResetCmdDebugUtilsLabel(VkCommandBuffer command_buffer) {
    std::unique_lock<std::mutex> lock(debug_output_mutex);
    auto* label_state = GetLoggingLabelState(&debug_utils_cmd_buffer_labels, command_buffer, /* insert */ false);
    if (label_state) {
        label_state->labels.clear();
        label_state->insert_label.Reset();
    }
}

void DebugReport::EraseCmdDebugUtilsLabel(VkCommandBuffer command_buffer) {
    std::unique_lock<std::mutex> lock(debug_output_mutex);
    debug_utils_cmd_buffer_labels.erase(command_buffer);
}

template <typename TCreateInfo, typename TCallback>
static void LayerCreateCallback(DebugCallbackStatusFlags callback_status, DebugReport* debug_report, const TCreateInfo* create_info,
                                TCallback* callback) {
    std::unique_lock<std::mutex> lock(debug_report->debug_output_mutex);

    debug_report->debug_callback_list.emplace_back(VkLayerDbgFunctionState());
    auto& callback_state = debug_report->debug_callback_list.back();
    callback_state.callback_status = callback_status;
    callback_state.pUserData = create_info->pUserData;

    if (callback_state.IsUtils()) {
        auto utils_create_info = reinterpret_cast<const VkDebugUtilsMessengerCreateInfoEXT*>(create_info);
        auto utils_callback = reinterpret_cast<VkDebugUtilsMessengerEXT*>(callback);
        if (!(*utils_callback)) {
            // callback constructed default callbacks have no handle -- so use struct address as unique handle
            *utils_callback = reinterpret_cast<VkDebugUtilsMessengerEXT>(&callback_state);
        }
        callback_state.debug_utils_callback_object = *utils_callback;
        callback_state.debug_utils_callback_function_ptr = utils_create_info->pfnUserCallback;
        callback_state.debug_utils_msg_flags = utils_create_info->messageSeverity;
        callback_state.debug_utils_msg_type = utils_create_info->messageType;
    } else {  // Debug report callback
        auto report_create_info = reinterpret_cast<const VkDebugReportCallbackCreateInfoEXT*>(create_info);
        auto report_callback = reinterpret_cast<VkDebugReportCallbackEXT*>(callback);
        if (!(*report_callback)) {
            // Internally constructed default callbacks have no handle -- so use struct address as unique handle
            *report_callback = reinterpret_cast<VkDebugReportCallbackEXT>(&callback_state);
        }
        callback_state.debug_report_callback_object = *report_callback;
        callback_state.debug_report_callback_function_ptr = report_create_info->pfnCallback;
        callback_state.debug_report_msg_flags = report_create_info->flags;
    }

#ifdef VK_USE_PLATFORM_ANDROID_KHR
    // On Android, if the default callback system property is set, force the default callback to be printed
    std::string force_layer_log = GetEnvironment(kForceDefaultCallbackKey);
    int force_default_callback = atoi(force_layer_log.c_str());
    if (force_default_callback == 1) {
        debug_report->force_default_log_callback = true;
    }
#endif

    debug_report->SetDebugUtilsSeverityFlags(debug_report->debug_callback_list);
}

VKAPI_ATTR VkResult LayerCreateMessengerCallback(DebugReport* debug_report, bool default_callback,
                                                 const VkDebugUtilsMessengerCreateInfoEXT* create_info,
                                                 VkDebugUtilsMessengerEXT* messenger) {
    LayerCreateCallback((DEBUG_CALLBACK_UTILS | (default_callback ? DEBUG_CALLBACK_DEFAULT : 0)), debug_report, create_info,
                        messenger);
    return VK_SUCCESS;
}

VKAPI_ATTR VkResult LayerCreateReportCallback(DebugReport* debug_report, bool default_callback,
                                              const VkDebugReportCallbackCreateInfoEXT* create_info,
                                              VkDebugReportCallbackEXT* callback) {
    LayerCreateCallback((default_callback ? DEBUG_CALLBACK_DEFAULT : 0), debug_report, create_info, callback);
    return VK_SUCCESS;
}

VKAPI_ATTR void ActivateInstanceDebugCallbacks(DebugReport* debug_report) {
    // Only one of these callbacks is ever set, so current is only updated once
    auto current = debug_report->instance_pnext_chain;
    for (;;) {
        auto create_info = vku::FindStructInPNextChain<VkDebugUtilsMessengerCreateInfoEXT>(current);
        if (!create_info) break;
        current = create_info->pNext;
        VkDebugUtilsMessengerEXT utils_callback{};
        LayerCreateCallback((DEBUG_CALLBACK_UTILS | DEBUG_CALLBACK_INSTANCE), debug_report, create_info, &utils_callback);
    }
    for (;;) {
        auto create_info = vku::FindStructInPNextChain<VkDebugReportCallbackCreateInfoEXT>(current);
        if (!create_info) break;
        current = create_info->pNext;
        VkDebugReportCallbackEXT report_callback{};
        LayerCreateCallback(DEBUG_CALLBACK_INSTANCE, debug_report, create_info, &report_callback);
    }
}

VKAPI_ATTR void DeactivateInstanceDebugCallbacks(DebugReport* debug_report) {
    if (!vku::FindStructInPNextChain<VkDebugUtilsMessengerCreateInfoEXT>(debug_report->instance_pnext_chain) &&
        !vku::FindStructInPNextChain<VkDebugReportCallbackCreateInfoEXT>(debug_report->instance_pnext_chain))
        return;
    std::vector<VkDebugUtilsMessengerEXT> instance_utils_callback_handles{};
    std::vector<VkDebugReportCallbackEXT> instance_report_callback_handles{};
    for (const auto& item : debug_report->debug_callback_list) {
        if (item.IsInstance()) {
            if (item.IsUtils()) {
                instance_utils_callback_handles.push_back(item.debug_utils_callback_object);
            } else {
                instance_report_callback_handles.push_back(item.debug_report_callback_object);
            }
        }
    }
    for (const auto& item : instance_utils_callback_handles) {
        LayerDestroyCallback(debug_report, item);
    }
    for (const auto& item : instance_report_callback_handles) {
        LayerDestroyCallback(debug_report, item);
    }
}

VKAPI_ATTR VkBool32 VKAPI_CALL MessengerBreakCallback([[maybe_unused]] VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
                                                      [[maybe_unused]] VkDebugUtilsMessageTypeFlagsEXT message_type,
                                                      const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
                                                      [[maybe_unused]] void* user_data) {
    // People use the break on warning/error to inspect THEIR code
    // It is annoying to break on some of our internal device creation warnings
    const uint32_t vuid_hash = callback_data ? (uint32_t)callback_data->messageIdNumber : 0;
    if (vuid_hash == 0x86fe6721 ||  // "WARNING-Setting-Limit-Adjusted"
        vuid_hash == 0x7f1922d7 ||  // "VALIDATION-SETTINGS"
        vuid_hash == 0xfd7b2292     // "CURRENT-VALIDATION-ENABLED"
    ) {
        return false;
    }

    // TODO: Consider to use https://github.com/scottt/debugbreak
#ifdef VK_USE_PLATFORM_WIN32_KHR
    DebugBreak();
#else
    raise(SIGTRAP);
#endif

    return false;
}

VKAPI_ATTR VkBool32 VKAPI_CALL MessengerFailCallback([[maybe_unused]] VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
                                                     [[maybe_unused]] VkDebugUtilsMessageTypeFlagsEXT message_type,
                                                     [[maybe_unused]] const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
                                                     [[maybe_unused]] void* user_data) {
    return true;
}

static std::string CreateDefaultCallbackMessage(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
                                                VkDebugUtilsMessageTypeFlagsEXT message_type,
                                                const VkDebugUtilsMessengerCallbackDataEXT& callback_data) {
    std::ostringstream oss;

    // The callback is in JSON (this is the only way the first char is '{')
    // If the user enables JSON, we only will print out JSON.
    if (callback_data.pMessage[0] == '{') {
        oss << callback_data.pMessage << '\n';
        return oss.str();
    }

    if (message_severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
        oss << "Validation Error: ";
    } else if (message_severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        if (message_type & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) {
            oss << "Validation Performance Warning: ";
        } else {
            oss << "Validation Warning: ";
        }
    } else if (message_severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
        oss << "Validation Information: ";
    } else if (message_severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
        oss << "Verbose Information: ";
    }

    oss << "[ " << callback_data.pMessageIdName << " ] | MessageID = 0x" << std::hex << callback_data.messageIdNumber << std::dec
        << '\n';

    oss << callback_data.pMessage << '\n';

    if (callback_data.objectCount > 0) {
        oss << "Objects: " << callback_data.objectCount << '\n';
        for (uint32_t i = 0; i < callback_data.objectCount; i++) {
            const auto& debug_object = callback_data.pObjects[i];
            oss << "    [" << i << "] " << string_VkObjectTypeHandleName(debug_object.objectType);
            if (debug_object.objectHandle) {
                oss << " 0x" << std::hex << debug_object.objectHandle << std::dec;
            } else {
                oss << " VK_NULL_HANDLE";
            }
            if (debug_object.pObjectName) {
                oss << "[" << debug_object.pObjectName << "]";
            }
            oss << '\n';
        }
    }

#ifndef VK_USE_PLATFORM_ANDROID_KHR
    oss << '\n';  // provide space between consecutive errors
#endif

    return oss.str();
}

VKAPI_ATTR VkBool32 VKAPI_CALL MessengerLogCallback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
                                                    VkDebugUtilsMessageTypeFlagsEXT message_type,
                                                    const VkDebugUtilsMessengerCallbackDataEXT* callback_data, void* user_data) {
    const std::string msg_buffer_str = CreateDefaultCallbackMessage(message_severity, message_type, *callback_data);

    // By default we are really just printing to stdout
    // Even if this is stdout, we still want to print for android
    // VVL testing (and probably other systems now) call freopen() to map stdout to dedicated file
    fprintf((FILE*)user_data, "%s", msg_buffer_str.c_str());
    fflush((FILE*)user_data);

#ifdef VK_USE_PLATFORM_ANDROID_KHR
    // If the user uses there own callback, we can let them fix the formatting, but as a default, some error messages will be way to
    // long for default logcat buffer. While one *can* adjust the logcat size, we assume 1024 is the max and chunk it up here. (note
    // that \n will automatically print a new line in logcat, but still counts towards the 1024 limit)
    const size_t chunk_size = 1024;
    const size_t total_size = msg_buffer_str.size();
    size_t offset = 0;
    while (offset < total_size) {
        const size_t bytes_to_print = std::min(chunk_size, total_size - offset);
        // If you just use "%s" it will re-print the whole remaining string on every iteration
        __android_log_print(ANDROID_LOG_INFO, "VALIDATION", "%.*s", static_cast<int>(bytes_to_print),
                            msg_buffer_str.c_str() + offset);
        offset += bytes_to_print;
    }
#endif

    return false;
}

#ifdef VK_USE_PLATFORM_WIN32_KHR
VKAPI_ATTR VkBool32 VKAPI_CALL MessengerWin32DebugOutputMsg(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
                                                            VkDebugUtilsMessageTypeFlagsEXT message_type,
                                                            const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
                                                            [[maybe_unused]] void* user_data) {
    const std::string msg_buffer_str = CreateDefaultCallbackMessage(message_severity, message_type, *callback_data);
    const char* cstr = msg_buffer_str.c_str();
    OutputDebugStringA(cstr);
    return false;
}
#endif
