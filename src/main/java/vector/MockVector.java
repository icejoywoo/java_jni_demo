package vector;

import sun.nio.ch.DirectBuffer;

import java.nio.ByteBuffer;

public class MockVector {

    public static int DEFAULT_CAPACITY = 1024;
    private int capacity;
    private ByteBuffer byteBuffer;

    public MockVector() {
        this(DEFAULT_CAPACITY);
    }

    public MockVector(int capacity) {
        this.capacity = capacity;
        byteBuffer = ByteBuffer.allocateDirect(capacity);
    }

    public ByteBuffer getByteBuffer() {
        return byteBuffer;
    }

    public int capacity() {
        return capacity;
    }

    public void realloc() {
        capacity *= 2;
        ByteBuffer oldByteBuffer = byteBuffer;
        byteBuffer = ByteBuffer.allocateDirect(capacity);
        oldByteBuffer.rewind();
        byteBuffer.put(oldByteBuffer);
    }

    public long memoryAddress() {
        assert byteBuffer.isDirect();
        return ((DirectBuffer) byteBuffer).address();
    }
}
