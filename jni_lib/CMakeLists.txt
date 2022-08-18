cmake_minimum_required(VERSION 3.5)

project(jni-lib LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "None")
    set (CMAKE_BUILD_TYPE "RelWithDebInfo")
    message (STATUS "CMAKE_BUILD_TYPE is not set, set to default = ${CMAKE_BUILD_TYPE}")
endif ()
message (STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# https://cmake.org/cmake/help/latest/module/FindJNI.html
find_package(JNI REQUIRED)
include_directories(${JAVA_INCLUDE_PATH})
include_directories(${JAVA_INCLUDE_PATH2})

execute_process(
        COMMAND
        bash -c
        "( bash ${CMAKE_CURRENT_SOURCE_DIR}/../gen_jni_headers.sh )"
        OUTPUT_VARIABLE COMMAND_OUTPUT
        RESULT_VARIABLE COMMAND_STATUS)

add_library(hello_jni SHARED jni_common.cc)
