package demo;

import jni.JniWrapper;

public class HelloJni {
    public void dummyCall() {
        JniWrapper.get().dummyCall(new long[]{0, 1, 2, 3});
    }

    public static void main(String[] args) {
        new HelloJni().dummyCall();
    }
}
