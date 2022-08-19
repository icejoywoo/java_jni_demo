# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.

#
# copied from arrow arrow_cdata_java
#

cmake_minimum_required(VERSION 3.11)
message(STATUS "Building using CMake version: ${CMAKE_VERSION}")
project(java_jni_demo)

# Find java/jni
include(UseJava)

find_package(Java REQUIRED)
find_package(JNI REQUIRED)

set(JNI_HEADERS_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/
                    ${JNI_INCLUDE_DIRS} ${JNI_HEADERS_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fPIC -Wall")

add_jar(${PROJECT_NAME}
        src/main/java/jni/JniException.java
        src/main/java/jni/JniLoader.java
        src/main/java/jni/JniWrapper.java
        src/main/java/jni/DummyData.java
        GENERATE_NATIVE_HEADERS
        hello_jni-native
        DESTINATION
        ${JNI_HEADERS_DIR})

set(SOURCES src/main/cpp/jni_wrapper.cc)
add_library(hello_jni SHARED ${SOURCES})
target_link_libraries(hello_jni ${JAVA_JVM_LIBRARY})
add_dependencies(hello_jni ${PROJECT_NAME})

install(TARGETS hello_jni DESTINATION ${CMAKE_INSTALL_LIBDIR})
