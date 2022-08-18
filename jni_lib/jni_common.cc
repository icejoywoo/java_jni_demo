#include "jni/jni_JniWrapper.h"


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