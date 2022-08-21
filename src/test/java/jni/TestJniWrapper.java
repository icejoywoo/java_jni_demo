package jni;

import org.junit.Test;
import vector.MockVector;
import vector.VectorExpander;

import static org.junit.Assert.*;
import static vector.MockVector.DEFAULT_CAPACITY;

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

    @Test
    public void testDummyData() {
        DummyData input = new DummyData();
        JniWrapper jni = JniWrapper.get();
        DummyData output = jni.objectCall(input);
        assertEquals(true, output.aBoolean);
        assertEquals(1, output.aByte);
        assertEquals(1, output.aChar);
        assertEquals(1, output.aShort);
        assertEquals(1, output.anInt);
        assertEquals(1, output.aLong);
        assertEquals(1, output.aFloat, 0.0001);
        assertEquals(1, output.aDouble, 0.0001);
        assertEquals("_", output.aString);
    }

    @Test
    public void testCallVectorExpander() {
        JniWrapper jni = JniWrapper.get();

        MockVector[] vectors = new MockVector[5];
        for (int i = 0; i < 5; i++) {
            vectors[i] = new MockVector();
        }
        VectorExpander expander = new VectorExpander(vectors);
        for (int i = 0; i < 5; i++) {
            jni.callVectorExpander(expander, vectors[i].memoryAddress(), vectors[i].capacity(), i, DEFAULT_CAPACITY * 10L);
        }
    }
}
