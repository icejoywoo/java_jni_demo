package jni;

class JniDemo {
    static {
        // 这里是加载一个名叫 libjnidemo 的动态库，后缀会根据OS不同而不同
        System.loadLibrary("jnidemo");
    }

    public native void nativeMethod();

    public static void main(String[] args) {
        new JniDemo().nativeMethod();
    }
}
