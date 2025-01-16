#ifndef SORTERSERVICEJNI_H
#define SORTERSERVICEJNI_H

#include <jni.h>

extern "C" {
    JNIEXPORT void JNICALL Java_org_example_sorter_SorterService_sortByAge
      (JNIEnv *, jclass, jstring, jboolean, jstring);

    JNIEXPORT void JNICALL Java_org_example_sorter_SorterService_sortByName
      (JNIEnv *, jclass, jstring, jboolean, jstring);

    JNIEXPORT jdouble JNICALL Java_org_example_sorter_SorterService_sortByAgeAndGetTime
      (JNIEnv *, jclass, jstring, jboolean, jstring);

    JNIEXPORT jobject JNICALL Java_org_example_sorter_SorterService_getSortedByAge
      (JNIEnv *, jclass, jstring, jboolean, jstring);

    JNIEXPORT jobject JNICALL Java_org_example_sorter_SorterService_sortStepByStep
    (JNIEnv*, jclass, jobject, jstring);


}

#endif // SORTERSERVICEJNI_H
