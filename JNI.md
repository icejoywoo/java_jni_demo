---
layout: post
title: Java JNI 使用笔记
category: Java
tags: ['Java', 'JNI']
---

# 简介

JNI 的全称是 Java Native Interface，是一种 Java 的 Native 编程接口，支持 Java 与 C/C++ 直接相互调用，从 JDK 1.0 开始提供。

# 基本使用流程

## 1. native method

## 2. generate header

## 3. implemente header functions

## 4. compile and run

# JNI

## Java VM Type Signatures 

Java VM Type Signatures 的表格如下：

|       Type Signature      |       Java Type       |
|:-------------------------:|:---------------------:|
| Z                         | boolean               |
| B                         | byte                  |
| C                         | char                  |
| S                         | short                 |
| I                         | int                   |
| J                         | long                  |
| F                         | float                 |
| D                         | double                |
| L fully-qualified-class ; | fully-qualified-class |
| [ type                    | type[]                |
| ( arg-types ) ret-type    | method type           |

参考：[Chapter 3: JNI Types and Data Structures](https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/types.html)

## CMake 编译

这里的编译方法可以参考 Arrow 的 [c data api](https://github.com/apache/arrow/blob/master/java/c/CMakeLists.txt) 和 [gandiva](https://github.com/apache/arrow/blob/master/java/gandiva/CMakeLists.txt) 的编译。

下面是一个 CMake 的示例，通过 add_jar 来生成 jni 的头文件。

```cmake
# Find java/jni
include(UseJava) # for add_jar

find_package(Java REQUIRED)
find_package(JNI REQUIRED)

# add_jar DESTINATION：生成的 java native method 的头文件位置
set(JNI_HEADERS_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")

# 设置 jni 的头文件
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
                    ${JNI_INCLUDE_DIRS} ${JNI_HEADERS_DIR})

add_jar(${PROJECT_NAME}
        src/main/java/jni/JniException.java
        src/main/java/jni/JniWrapper.java
        GENERATE_NATIVE_HEADERS
        hello_jni-native
        DESTINATION
        ${JNI_HEADERS_DIR})

set(SOURCES src/main/cpp/jni_wrapper.cc)
add_library(hello_jni SHARED ${SOURCES})
target_link_libraries(hello_jni ${JAVA_JVM_LIBRARY})
```

## C/C++ API 差异

API 的差异主要是因为 C++ 支持 class（struct 与 class 的差异仅仅是可见性），C 只能用 struct + function pointer 来模拟。

jni.h 中，对 JNIEnv 的定义如下：

```c
#ifdef __cplusplus
typedef JNIEnv_ JNIEnv;
#else
typedef const struct JNINativeInterface_ *JNIEnv;
#endif
```

虽然同为 JNIEnv，但是其内部的实现是不同的，查看对应类即可知道 C/C++ API 的差异，这里以 GetStringUTFChars 为例举例说明其 API 的差异：

```cpp
// c api
const char *str = (*env)->GetStringUTFChars(env, jstr, 0);

// c++ api
const char *str = env->GetStringUTFChars(jstr, 0);
```

方法的名字都是一样的，C/C++ API 下的函数是一样的，仅使用方法不同。

# 参考资料

## Java

* [Java Native Interface Specification Contents](https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/jniTOC.html)

## CMake

* [CMake FindJNI](https://cmake.org/cmake/help/latest/module/FindJNI.html)
* [CMake UseJava](https://cmake.org/cmake/help/latest/module/UseJava.html)

## Arrow JNI

JNI 动态库的编译都是使用 CMake 来进行编译，JniLoader 用于加载动态库，JniWrapper 作为 native method 的类。

下面以 Arrow Gandiva 为例，简单分析下其 JNI 实现：
1. 数据传输的方式为 JVM 堆外内存（从 Netty 申请的），向 JNI 传递数据 input 和 output 的时候使用 buffer address + length 的方式
2. JVM 堆外内存本质是需要在 Java 侧进行内存的管理，所以在 JNI 中如果需要进行内存扩容（project 场景下，output 的内存可能需要扩容），会在 C++ 中调用 Java 的 VectorExpander 来进行扩容，保证内存全在 Java 中进行申请管理

相关主要代码如下：
* [Arrow C Data API](https://github.com/apache/arrow/blob/master/java/c/README.md)
    * [cpp](https://github.com/apache/arrow/blob/master/java/c/src/main/cpp/jni_wrapper.cc)
    * [java](https://github.com/apache/arrow/blob/master/java/c/src/main/java/org/apache/arrow/c/jni/JniWrapper.java)
* [Arrow Gandiva](https://github.com/apache/arrow/blob/master/java/gandiva/README.md)
    * [cpp](https://github.com/apache/arrow/blob/master/cpp/src/gandiva/jni/jni_common.cc)
    * [java](https://github.com/apache/arrow/blob/master/java/gandiva/src/main/java/org/apache/arrow/gandiva/evaluator/JniWrapper.java)