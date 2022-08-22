#include "jni_JniDemo.h"

JNIEXPORT void JNICALL Java_jni_JniDemo_nativeMethod
  (JNIEnv *env, jobject obj) {
  printf("native method in jni\n");
}