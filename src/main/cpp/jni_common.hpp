#pragma once

#include <jni.h>

#include <stdexcept>

namespace {

class JniPendingException : public std::runtime_error {
 public:
  explicit JniPendingException(const std::string& arg) : std::runtime_error(arg) {}
};

void ThrowPendingException(const std::string& message) {
  throw JniPendingException(message);
}

void JniThrow(std::string message) { ThrowPendingException(message); }

jclass CreateGlobalClassReference(JNIEnv* env, const char* class_name) {
  jclass local_class = env->FindClass(class_name);
  if (!local_class) {
    std::string message = "Could not find class ";
    message += class_name;
    ThrowPendingException(message);
  }
  jclass global_class = (jclass)env->NewGlobalRef(local_class);
  if (!global_class) {
    std::string message = "Could not create global reference to class ";
    message += class_name;
    ThrowPendingException(message);
  }
  env->DeleteLocalRef(local_class);
  return global_class;
}

jmethodID GetMethodID(JNIEnv* env, jclass this_class, const char* name, const char* sig) {
  jmethodID ret = env->GetMethodID(this_class, name, sig);
  if (ret == nullptr) {
    std::string error_message = "Unable to find method " + std::string(name) +
                                " with signature " + std::string(sig);
    ThrowPendingException(error_message);
  }
  return ret;
}

jfieldID GetFieldID(JNIEnv* env, jclass this_class, const char* name, const char* sig) {
  jfieldID fieldId = env->GetFieldID(this_class, name, sig);
  if (fieldId == nullptr) {
    std::string error_message = "Unable to find field " + std::string(name) +
                                " with signature " + std::string(sig);
    ThrowPendingException(error_message);
  }
  return fieldId;
}

class JNIEnvGuard {
 public:
  explicit JNIEnvGuard(JavaVM* vm) : vm_(vm), should_detach_(false) {
    JNIEnv* env;
    jint code = vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION);
    if (code == JNI_EDETACHED) {
      JavaVMAttachArgs args;
      args.version = JNI_VERSION;
      args.name = NULL;
      args.group = NULL;
      code = vm->AttachCurrentThread(reinterpret_cast<void**>(&env), &args);
      should_detach_ = (code == JNI_OK);
    }
    if (code != JNI_OK) {
      ThrowPendingException("Failed to attach the current thread to a Java VM");
    }
    env_ = env;
  }

  JNIEnv* env() { return env_; }

  ~JNIEnvGuard() {
    if (should_detach_) {
      vm_->DetachCurrentThread();
      should_detach_ = false;
    }
  }

 private:
  JavaVM* vm_;
  bool should_detach_;
  JNIEnv* env_;
};

} // namespace

#define JNI_METHOD_START try {
// macro ended

#define JNI_METHOD_END(fallback_expr)                \
  }                                                  \
  catch (JniPendingException & e) {                  \
    env->ThrowNew(kRuntimeExceptionClass, e.what()); \
    return fallback_expr;                            \
  }
// macro ended