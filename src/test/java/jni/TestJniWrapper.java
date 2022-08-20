package jni;

import org.junit.Test;

import static org.junit.Assert.assertArrayEquals;

public class TestJniWrapper {
    @Test
    public void test() {
        JniWrapper jni = JniWrapper.get();
        byte[] byteArray = {1, 2, 3};
        byte[] expectedByteArray = {2, 3, 4};
        assertArrayEquals(expectedByteArray, jni.dummyCall(byteArray));
        char[] charArray = {1, 2, 3};
        char[] expectedCharArray = {2, 3, 4};
        assertArrayEquals(expectedCharArray, jni.dummyCall(charArray));
        int[] intArray = {1, 2, 3, 100};
        int[] expectedIntArray = {2, 3, 4, 101};
        assertArrayEquals(expectedIntArray, jni.dummyCall(intArray));
        long[] longArray = {1, 2, 3, 9999};
        long[] expectedLongArray = {2, 3, 4, 10000};
        assertArrayEquals(expectedLongArray, jni.dummyCall(longArray));
        String[] stringArray = {"1", "2", "3"};
        String[] expectedStringArray = {"1_", "2_", "3_"};
        assertArrayEquals(expectedStringArray, jni.dummyCall(stringArray));
    }
}
