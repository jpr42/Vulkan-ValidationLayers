# ~~~
# Copyright (c) 2024-2025 LunarG, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ~~~

if (ANDROID OR MINGW OR APPLE)
    return()
endif()

# These variables enable downstream users to customize the CMake targets
# based on the target API variant (e.g. Vulkan SC)
set(ICD_NAME VVL_Test_ICD)

add_library(VVL_Test_ICD MODULE)

target_sources(VVL_Test_ICD PRIVATE
    test_icd.h
    test_icd.cpp)

# Header-only: the generated test_icd_helper.h and the Vulkan headers. Nothing from the layer itself.
target_link_libraries(VVL_Test_ICD PRIVATE
    vvl_defines
    Vulkan::Headers
    Vulkan::UtilityHeaders
)

target_include_directories(VVL_Test_ICD PRIVATE
    ${VVL_SOURCE_DIR}/layers/${API_TYPE}/generated
    .
)

# The platform defines come from vvl_defines, except for the mock Android setup (see tests/CMakeLists.txt)
if (VVL_MOCK_ANDROID)
    target_compile_definitions(VVL_Test_ICD PRIVATE VK_USE_PLATFORM_ANDROID_KHR)
endif()

if (WIN32)
    target_sources(VVL_Test_ICD PRIVATE ${ICD_NAME}.def)
endif()

# The generated test_icd_helper.h is hundreds of stub entry points that ignore their parameters
target_compile_options(VVL_Test_ICD PRIVATE "$<IF:$<CXX_COMPILER_ID:MSVC>,/wd4100,-Wno-unused-parameter>")

set_target_properties(VVL_Test_ICD PROPERTIES OUTPUT_NAME ${ICD_NAME})

if (DEFINED GIT_BRANCH_NAME AND DEFINED GIT_TAG_INFO)
    target_compile_definitions(VVL_Test_ICD PRIVATE GIT_BRANCH_NAME="${GIT_BRANCH_NAME}" GIT_TAG_INFO="${GIT_TAG_INFO}")
endif()

# There are 2 primary deliverables for the Test driver.
# - The actual library (lib)VVL_Test_ICD.(dll|so|dylib)
# - The respective json file, VVL_Test_ICD.json
# This code generates the appropriate json for both local testing and the installation.
# NOTE: For WIN32 the JSON and dll MUST be placed in the same location, due to Win32 using a relative path for installation.
set(INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/${ICD_NAME}.json.in")
set(INTERMEDIATE_FILE "${CMAKE_CURRENT_BINARY_DIR}/json/test_icd.json")
set(OUTPUT_FILE_FINAL_NAME "${ICD_NAME}.json")
set(LAYER_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR})
if (WIN32)
    set(LAYER_INSTALL_DIR ${CMAKE_INSTALL_BINDIR}) # WIN32 expect the dll in the `bin` dir, this matches our WIN32 SDK process
endif()

if (WIN32)
    set(JSON_LIBRARY_PATH ".\\\\${ICD_NAME}.dll")
else()
    set(JSON_LIBRARY_PATH "./lib${ICD_NAME}.so")
endif()

configure_file(${INPUT_FILE} ${INTERMEDIATE_FILE} @ONLY)

# To support both multi/single configuration generators just copy the json to the correct directory
add_custom_command(TARGET VVL_Test_ICD POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${INTERMEDIATE_FILE} $<TARGET_FILE_DIR:VVL_Test_ICD>/${OUTPUT_FILE_FINAL_NAME}
)

# Installing the Test ICD to system directories is probably not desired since this ICD is not a very complete implementation.
# Require the user to ask that it be installed if they really want it.
option(INSTALL_VVL_TEST_ICD "Install Test icd")
if (INSTALL_VVL_TEST_ICD)
    message(NOTICE "INSTALL_ICD enabled!")
else()
    return()
endif()

# For UNIX-based systems, `library_path` should not contain a relative path (indicated by "./") before installing to system directories
# This json isn't used for regular local development, it's used for installation
if (UNIX)
    set(UNIX_INTERMEDIATE_FILE "${CMAKE_CURRENT_BINARY_DIR}/json/unix_install_test_icd.json")
    set(JSON_LIBRARY_PATH "lib${ICD_NAME}.so")

    configure_file(${INPUT_FILE} ${UNIX_INTERMEDIATE_FILE} @ONLY)
    install(FILES ${UNIX_INTERMEDIATE_FILE} DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${API_TYPE}/icd.d RENAME ${OUTPUT_FILE_FINAL_NAME})
elseif (WIN32)
    install(FILES ${INTERMEDIATE_FILE} DESTINATION ${LAYER_INSTALL_DIR} RENAME ${OUTPUT_FILE_FINAL_NAME})
endif()

install(TARGETS VVL_Test_ICD DESTINATION ${LAYER_INSTALL_DIR})
