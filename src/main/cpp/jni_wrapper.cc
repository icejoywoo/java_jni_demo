#include "jni_JniWrapper.h"

#include <cstdio>
#include <string>

static jint JNI_VERSION = JNI_VERSION_1_6;

// just to include common code
#include "jni_common.hpp"

jclass kObjectClass;
jclass kRuntimeExceptionClass;
jclass kDummyDataClass;
jclass kJniExceptionClass;

// copied from arrow gandiva cpp jni_common.cc
static jclass vector_expander_class_;
static jclass vector_expander_ret_class_;
static jmethodID vector_expander_method_;
static jfieldID vector_expander_ret_address_;
static jfieldID vector_expander_ret_capacity_;


/// copied from arrow gandiva jni_common.cc
///
/// \brief Resizable buffer which resizes by doing a callback into java.
///
class JavaResizableBuffer {
 public:
  JavaResizableBuffer(JNIEnv* env, jobject jexpander, int32_t vector_idx, uint8_t* buffer,
                      int32_t len)
      : env_(env),
        jexpander_(jexpander),
        vector_idx_(vector_idx),
        data_(buffer),
        capacity_(len) {
    size_ = 0;
  }

  int Resize(const int64_t new_size, bool shrink_to_fit);

  int Reserve(const int64_t new_capacity) {
    ThrowPendingException("reserve not implemented");
    return -1;
  }

  int32_t capacity() {
    return capacity_;
  }

 private:
  JNIEnv* env_;
  jobject jexpander_;
  int32_t vector_idx_;
  uint8_t* data_;
  int32_t capacity_;
  int32_t size_;
};

int JavaResizableBuffer::Resize(const int64_t new_size, bool shrink_to_fit) {
  if (shrink_to_fit == true) {
    JniThrow("shrink not implemented");
    return -1;
  }

  if (new_size < capacity()) {
    // no need to expand.
    size_ = new_size;
    return 0;
  }

  // callback into java to expand the buffer
  jobject ret =
      env_->CallObjectMethod(jexpander_, vector_expander_method_, vector_idx_, new_size);
  if (env_->ExceptionCheck()) {
    env_->ExceptionDescribe();
    env_->ExceptionClear();
    JniThrow("buffer expand failed in java");
    return -1;
  }

  jlong ret_address = env_->GetLongField(ret, vector_expander_ret_address_);
  jlong ret_capacity = env_->GetLongField(ret, vector_expander_ret_capacity_);
  assert(ret_capacity > new_size);

  data_ = reinterpret_cast<uint8_t*>(ret_address);
  size_ = new_size;
  capacity_ = ret_capacity;
  return 0;
}

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

  vector_expander_class_ = CreateGlobalClassReference(env, "Lvector/VectorExpander;");
  vector_expander_ret_class_ = CreateGlobalClassReference(env, "Lvector/VectorExpander$ExpandResult;");
  vector_expander_method_ =
       GetMethodID(env, vector_expander_class_, "expandOutputVectorAtIndex", "(IJ)Lvector/VectorExpander$ExpandResult;");
  vector_expander_ret_address_ = GetFieldID(env, vector_expander_ret_class_, "address", "J");
  vector_expander_ret_capacity_ = GetFieldID(env, vector_expander_ret_class_, "capacity", "J");

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

  // iterate byte array and plus 1 in every element
  for (int i = 0; i < array_len; i++) {
    raw_array[i] += 1;
  }

  // build a byte array to return
  jbyteArray ret = env->NewByteArray(array_len);
  env->SetByteArrayRegion(ret, 0, array_len, raw_array);
  return ret;
  JNI_METHOD_END(nullptr)
}

JNIEXPORT jcharArray JNICALL Java_jni_JniWrapper_dummyCall___3C
  (JNIEnv *env, jobject obj, jcharArray array) {
  JNI_METHOD_START
  jsize array_len = env->GetArrayLength(array);
  jchar* raw_array = env->GetCharArrayElements(array, 0);

  // iterate char array and plus 1 in every element
  for (int i = 0; i < array_len; i++) {
    raw_array[i] += 1;
  }

  // build a char array to return
  jcharArray ret = env->NewCharArray(array_len);
  env->SetCharArrayRegion(ret, 0, array_len, raw_array);
  return ret;
  JNI_METHOD_END(nullptr)
}

JNIEXPORT jintArray JNICALL Java_jni_JniWrapper_dummyCall___3I
  (JNIEnv *env, jobject obj, jintArray array) {
  JNI_METHOD_START
  jsize array_len = env->GetArrayLength(array);
  jint* raw_array = env->GetIntArrayElements(array, 0);

  // iterate int array and plus 1 in every element
  for (int i = 0; i < array_len; i++) {
    raw_array[i] += 1;
  }

  // build a int array to return
  jintArray ret = env->NewIntArray(array_len);
  env->SetIntArrayRegion(ret, 0, array_len, raw_array);
  return ret;
  JNI_METHOD_END(nullptr)
}

JNIEXPORT jlongArray JNICALL Java_jni_JniWrapper_dummyCall___3J
  (JNIEnv *env, jobject obj, jlongArray array) {
  JNI_METHOD_START
  jsize array_len = env->GetArrayLength(array);
  jlong* raw_array = env->GetLongArrayElements(array, 0);

  // iterate long array and plus 1 in every element
  for (int i = 0; i < array_len; i++) {
    raw_array[i] += 1;
  }

  // build a long array to return
  jlongArray ret = env->NewLongArray(array_len);
  env->SetLongArrayRegion(ret, 0, array_len, raw_array);
  return ret;
  JNI_METHOD_END(nullptr)
}

JNIEXPORT jobjectArray JNICALL Java_jni_JniWrapper_dummyCall___3Ljava_lang_String_2
  (JNIEnv* env, jobject obj, jobjectArray array) {
  JNI_METHOD_START
  jsize array_len = env->GetArrayLength(array);

  // iterate object array and build result
  jobjectArray ret = env->NewObjectArray(array_len, env->FindClass("java/lang/String"), nullptr);
  for (int i = 0; i < array_len; i++) {
    jstring element = (jstring) env->GetObjectArrayElement(array, i);
    const char *str = env->GetStringUTFChars(element, 0);
    char tmp[128];
    snprintf(tmp, sizeof(tmp), "%s_", str);
    env->ReleaseStringUTFChars(element, str);

    jstring jstr = env->NewStringUTF(tmp);
    env->SetObjectArrayElement(ret, i, jstr);
  }

  return ret;
  JNI_METHOD_END(nullptr)
}

JNIEXPORT jlong JNICALL Java_jni_JniWrapper_buildProjector
  (JNIEnv *env, jobject obj, jbyteArray, jbyteArray, jint, jlong) {
  JNI_METHOD_START
  JniThrow("Not Implemented yet");
  JNI_METHOD_END(-1)
}

JNIEXPORT void JNICALL Java_jni_JniWrapper_evaluateProjector
  (JNIEnv *env, jobject obj, jobject, jlong, jint, jlongArray, jlongArray, jint, jint, jlong, jlong, jlongArray, jlongArray) {
  JNI_METHOD_START
  JniThrow("Not Implemented yet");
  JNI_METHOD_END()
}

JNIEXPORT void JNICALL Java_jni_JniWrapper_closeProjector
  (JNIEnv *env, jobject obj, jlong) {
  JNI_METHOD_START
  JniThrow("Not Implemented yet");
  JNI_METHOD_END()
}