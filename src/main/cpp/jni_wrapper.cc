#include "jni_JniWrapper.h"

static jint JNI_VERSION = JNI_VERSION_1_6;

// extern refs - initialized for other modules.
jclass configuration_builder_class_;

// refs for self.
static jclass gandiva_exception_;
static jclass vector_expander_class_;
static jclass vector_expander_ret_class_;
static jmethodID vector_expander_method_;
static jfieldID vector_expander_ret_address_;
static jfieldID vector_expander_ret_capacity_;

JNIEXPORT void JNICALL Java_jni_JniWrapper_dummyCall
  (JNIEnv *, jobject, jlongArray) {
  printf("hello from jni dummy call\n");
  }


JNIEXPORT jlong JNICALL Java_jni_JniWrapper_buildProjector
  (JNIEnv *, jobject, jbyteArray, jbyteArray, jint, jlong) {
  return 0;
  }


JNIEXPORT void JNICALL Java_jni_JniWrapper_evaluateProjector
  (JNIEnv *, jobject, jobject, jlong, jint, jlongArray, jlongArray, jint, jint, jlong, jlong, jlongArray, jlongArray) {
  }


JNIEXPORT void JNICALL Java_jni_JniWrapper_closeProjector
  (JNIEnv *, jobject, jlong) {
  }