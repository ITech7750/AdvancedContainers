#ifndef GISTOGRAMJNI_H
#define GISTOGRAMJNI_H

#include <jni.h>

extern "C" {
    JNIEXPORT void JNICALL Java_nativelib_NativeGistogram_addParameter
    (JNIEnv *, jobject, jobject);

    JNIEXPORT void JNICALL Java_nativelib_NativeGistogram_addData
    (JNIEnv *, jobject, jobject);

    JNIEXPORT jobject JNICALL Java_nativelib_NativeGistogram_getMostFrequent
    (JNIEnv *, jobject);

    JNIEXPORT jint JNICALL Java_nativelib_NativeGistogram_countInRange
    (JNIEnv *, jobject, jobject, jobject);

    JNIEXPORT void JNICALL Java_nativelib_NativeGistogram_clearAll
    (JNIEnv *, jobject);

    JNIEXPORT jobject JNICALL Java_nativelib_NativeGistogram_findMatchingValues
    (JNIEnv *, jobject, jobject);
}

#endif // GISTOGRAMJNI_H
