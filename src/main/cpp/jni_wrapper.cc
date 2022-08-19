#include "jni_JniWrapper.h"

#include <string>

static jint JNI_VERSION = JNI_VERSION_1_6;

// just to include common code
#include "jni_common.hpp"

jclass kObjectClass;
jclass kRuntimeExceptionClass;
jclass kDummyDataClass;
jclass kJniExceptionClass;

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
  JNIEnv* env;
  if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION) != JNI_OK) {
    return JNI_ERR;
  }

  JNI_METHOD_START
  kObjectClass = CreateGlobalClassReference(env, "Ljava/lang/Object;");
  kRuntimeExceptionClass =
      CreateGlobalClassReference(env, "Ljava/lang/RuntimeException;");
  kDummyDataClass =
      CreateGlobalClassReference(env, "Ljni/DummyData;");
  kJniExceptionClass =
      CreateGlobalClassReference(env, "Ljni/JniException;");

  // global init

  return JNI_VERSION;
  JNI_METHOD_END(JNI_ERR)
}

void JNI_OnUnload(JavaVM* vm, void* reserved) {
  JNIEnv* env;
  vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION);
  env->DeleteGlobalRef(kObjectClass);
  env->DeleteGlobalRef(kRuntimeExceptionClass);
  env->DeleteGlobalRef(kDummyDataClass);
  env->DeleteGlobalRef(kJniExceptionClass);
}

// jni types' signatures
// https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/types.html

JNIEXPORT void JNICALL Java_jni_JniWrapper_dummyCall__
  (JNIEnv *env, jobject obj) {
  JNI_METHOD_START
  printf("hello from jni dummy call\n");
  JNI_METHOD_END()
}

JNIEXPORT jbyteArray JNICALL Java_jni_JniWrapper_dummyCall___3B
  (JNIEnv *env, jobject obj, jbyteArray array) {
  JNI_METHOD_START
  jsize array_len = env->GetArrayLength(array);
  jbyte* raw_array = env->GetByteArrayElements(array, 0);
  return array;
  JNI_METHOD_END(nullptr)
}

JNIEXPORT jcharArray JNICALL Java_jni_JniWrapper_dummyCall___3C
  (JNIEnv *env, jobject obj, jcharArray array) {
  JNI_METHOD_START
  jsize array_len = env->GetArrayLength(array);
  jchar* raw_array = env->GetCharArrayElements(array, 0);
  return array;
  JNI_METHOD_END(nullptr)
}

JNIEXPORT jintArray JNICALL Java_jni_JniWrapper_dummyCall___3I
  (JNIEnv *env, jobject obj, jintArray array) {
  JNI_METHOD_START
  jsize array_len = env->GetArrayLength(array);
  jint* raw_array = env->GetIntArrayElements(array, 0);
  return array;
  JNI_METHOD_END(nullptr)
}

JNIEXPORT jlongArray JNICALL Java_jni_JniWrapper_dummyCall___3J
  (JNIEnv *env, jobject obj, jlongArray array) {
  JNI_METHOD_START
  jsize array_len = env->GetArrayLength(array);
  jlong* raw_array = env->GetLongArrayElements(array, 0);
  return array;
  JNI_METHOD_END(nullptr)
}

JNIEXPORT jobjectArray JNICALL Java_jni_JniWrapper_dummyCall___3Ljava_lang_String_2
  (JNIEnv* env, jobject obj, jobjectArray array) {
  JNI_METHOD_START
//  jsize array_len = env->GetArrayLength(array);
//  jstring* raw_array = env->GetStringArrayElements(array, 0);
  return array;
  JNI_METHOD_END(nullptr)
}

JNIEXPORT jlong JNICALL Java_jni_JniWrapper_buildProjector
  (JNIEnv *env, jobject obj, jbyteArray, jbyteArray, jint, jlong) {
  JNI_METHOD_START
  return 0;
  JNI_METHOD_END(-1)
}

JNIEXPORT void JNICALL Java_jni_JniWrapper_evaluateProjector
  (JNIEnv *env, jobject obj, jobject, jlong, jint, jlongArray, jlongArray, jint, jint, jlong, jlong, jlongArray, jlongArray) {
  JNI_METHOD_START
  return;
  JNI_METHOD_END()
}

JNIEXPORT void JNICALL Java_jni_JniWrapper_closeProjector
  (JNIEnv *env, jobject obj, jlong) {
  JNI_METHOD_START
  return;
  JNI_METHOD_END()
}