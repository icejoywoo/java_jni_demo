package jni;

import org.junit.Test;

import static org.junit.Assert.assertArrayEquals;

public class TestJniWrapper {
    @Test
    public void test() {
        JniWrapper jni = JniWrapper.get();
        byte[] b = {1, 2, 3};
        assertArrayEquals(b, jni.dummyCall(b));
        char[] c = {1, 2, 3};
        assertArrayEquals(c, jni.dummyCall(c));
        int[] i = {1, 2, 3};
        assertArrayEquals(i, jni.dummyCall(i));
        long[] l = {1, 2, 3};
        assertArrayEquals(l, jni.dummyCall(l));
        String[] s = {"1", "2", "3"};
        assertArrayEquals(s, jni.dummyCall(s));
    }
}
