#ifndef HASHMAPJNI_H
#define HASHMAPJNI_H

#include <jni.h>

extern "C" {
  JNIEXPORT void JNICALL Java_nativelib_NativeHashMap_put
    (JNIEnv *, jobject, jobject, jobject);

  JNIEXPORT jobject JNICALL Java_nativelib_NativeHashMap_get
    (JNIEnv *, jobject, jobject);

  JNIEXPORT jboolean JNICALL Java_nativelib_NativeHashMap_containsKey
    (JNIEnv *, jobject, jobject);

  JNIEXPORT void JNICALL Java_nativelib_NativeHashMap_remove
    (JNIEnv *, jobject, jobject);

  JNIEXPORT jint JNICALL Java_nativelib_NativeHashMap_size
    (JNIEnv *, jobject);

  JNIEXPORT jboolean JNICALL Java_nativelib_NativeHashMap_isEmpty
    (JNIEnv *, jobject);

  JNIEXPORT jobject JNICALL Java_nativelib_NativeHashMap_getKeys
    (JNIEnv *, jobject);

  JNIEXPORT jobject JNICALL Java_nativelib_NativeHashMap_getValues
    (JNIEnv *, jobject);

  JNIEXPORT void JNICALL Java_nativelib_NativeHashMap_clear
    (JNIEnv *, jobject);
}

#endif // HASHMAPJNI_H
