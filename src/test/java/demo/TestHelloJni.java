package demo;

import org.junit.Test;

public class TestHelloJni {
    @Test
    public void test() {
        new HelloJni().dummyCall();
    }
}
