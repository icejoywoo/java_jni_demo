package jni;

import java.io.Closeable;
import java.io.IOException;

public class DummyData implements Closeable {
    public boolean aBoolean;
    public byte aByte;
    public char aChar;
    public short aShort;
    public int anInt;
    public long aLong;
    public float aFloat;
    public double aDouble;
    public String aString;

    @Override
    public void close() throws IOException {
        // reset all values
        aBoolean = false;
        aByte = 0;
        aChar = 0;
        aShort = 0;
        anInt = 0;
        aLong = 0;
        aFloat = 0;
        aDouble = 0;
        aString = null;
    }
}
