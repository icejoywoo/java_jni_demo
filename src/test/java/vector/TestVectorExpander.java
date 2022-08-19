package vector;

import org.junit.Test;

import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

import static org.junit.Assert.*;
import static vector.MockVector.DEFAULT_CAPACITY;

public class TestVectorExpander {
    @Test
    public void test() {
        MockVector[] vectors = new MockVector[5];
        for (int i = 0; i < 5; i++) {
            vectors[i] = new MockVector();
        }
        VectorExpander expander = new VectorExpander(vectors);
        assertEquals(DEFAULT_CAPACITY, vectors[0].capacity());
        expander.expandOutputVectorAtIndex(0, DEFAULT_CAPACITY * 10L);
        assertTrue(vectors[0].capacity() >= DEFAULT_CAPACITY * 10L);

        byte[] bytes = "Hello".getBytes(StandardCharsets.UTF_8);
        {
            ByteBuffer byteBuffer = vectors[0].getByteBuffer();
            byteBuffer.rewind();
            byteBuffer = byteBuffer.put(bytes);
            byteBuffer.flip();
            byte[] tmp = new byte[5];
            byteBuffer.get(tmp);
            assertArrayEquals(bytes, tmp);
        }

        vectors[0].realloc();

        {
            ByteBuffer byteBuffer = vectors[0].getByteBuffer();
            byteBuffer.rewind();
            byte[] tmp = new byte[5];
            byteBuffer.get(tmp);
            assertArrayEquals(bytes, tmp);
        }
    }
}
