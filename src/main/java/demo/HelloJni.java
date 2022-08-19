package demo;

import jni.JniWrapper;

public class HelloJni {
    public void dummyCall() {
        JniWrapper.get().dummyCall();
    }

    public static void main(String[] args) {
        new HelloJni().dummyCall();
    }
}
