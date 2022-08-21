# java jni demo project

refer arrow c-data jni (path: arrow/java/c)

## JNI docs

c api and c++ api is different.

c api:

```c
const char *str = (*env)->GetStringUTFChars(env, jstr, 0);
```

c++ api:

```c++
const char *str = env->GetStringUTFChars(jstr, 0);
```

* [JNI Types and Data Structures](https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/types.html)
* [Java Native Interface Specification Contents](https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/jniTOC.html)
* [Trail: Java Native Interface: Table of Contents](https://www.iitk.ac.in/esc101/05Aug/tutorial/native1.1/TOC.html)