package jni;

/**
 * jni type signature refer: <a href="https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/types.html">JNI Types</a>
 * JNI names:
 * 1. class name: {package}_{className}
 * 2. method name: Java_{package}_{className}_{methodName}[__{overloadPostFix}]
 */
public class JniSignatureDemo {
    /*
     * Class:     jni_JniSignatureDemo
     * Method:    call
     * Signature: (J[J[J)V
     */
    // JNIEXPORT void JNICALL Java_jni_JniSignatureDemo_call
    //        (JNIEnv *, jobject, jlong, jlongArray, jlongArray);
    public native void call(long index, long[] schemaMemoryAddresses, long[] dataMemoryAddresses);

    /*
     * Class:     jni_JniSignatureDemo
     * Method:    stringCall
     * Signature: (Ljava/lang/String;[Ljava/lang/String;)V
     */
    // JNIEXPORT void JNICALL Java_jni_JniSignatureDemo_stringCall
    //        (JNIEnv *, jobject, jstring, jobjectArray);
    public native void stringCall(String name, String[] strings);
}
