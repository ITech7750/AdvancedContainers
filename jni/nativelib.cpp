#include <jni.h>
#include <string>
#include "../graph/presentation/logistic/logistic.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_tech_nativelib_NativeLib_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_tech_nativelib_NativeLib_buildLogistic(
        JNIEnv *env,
        jobject thiz,
        jstring resultFilePath,
        jint cityAmount,
        jint roadAmount,
        jint cargo
) {
    Logisitc<Road, City> l{};
    const char *cstr = env->GetStringUTFChars(resultFilePath, nullptr);
    std::string resultPath = std::string(cstr);
    l.buildLogistic(resultPath, cityAmount, roadAmount, cargo);
}

extern "C" JNIEXPORT void JNICALL
Java_com_tech_nativelib_NativeLib_buildLogisticFromFile(
        JNIEnv *env,
        jobject thiz,
        jstring dataFilePath,
        jstring resultFilePath,
        jstring startCity,
        jstring endCity,
        jint cargo
) {
    Logisitc<Road, City> l{};
    const char *cstr = env->GetStringUTFChars(resultFilePath, nullptr);
    std::string resultPath = std::string(cstr);

    const char *cstr1 = env->GetStringUTFChars(dataFilePath, nullptr);
    std::string dataPath = std::string(cstr1);

    const char *cstr2 = env->GetStringUTFChars(startCity, nullptr);
    std::string start = std::string(cstr2);

    const char *cstr3 = env->GetStringUTFChars(endCity, nullptr);
    std::string end = std::string(cstr3);

    l.buildLogisticFromFile(start, end, resultPath, dataPath, cargo);
}

extern "C" JNIEXPORT void JNICALL
Java_com_tech_nativelib_NativeLib_buildLogisticVertex(
        JNIEnv *env,
        jobject thiz,
        jstring resultFilePath,
        jint cityAmount,
        jint roadAmount
) {
    Logisitc<Road, City> l{};
    const char *cstr = env->GetStringUTFChars(resultFilePath, nullptr);
    std::string resultPath = std::string(cstr);
    l.buildLogisticShortestVertex(resultPath, cityAmount, roadAmount);
}

extern "C" JNIEXPORT void JNICALL
Java_com_tech_nativelib_NativeLib_buildLogisticFromFileVertex(
        JNIEnv *env,
        jobject thiz,
        jstring dataFilePath,
        jstring resultFilePath,
        jstring startCity,
        jstring endCity
) {
    Logisitc<Road, City> l{};
    const char *cstr = env->GetStringUTFChars(resultFilePath, nullptr);
    std::string resultPath = std::string(cstr);

    const char *cstr1 = env->GetStringUTFChars(dataFilePath, nullptr);
    std::string dataPath = std::string(cstr1);

    const char *cstr2 = env->GetStringUTFChars(startCity, nullptr);
    std::string start = std::string(cstr2);

    const char *cstr3 = env->GetStringUTFChars(endCity, nullptr);
    std::string end = std::string(cstr3);

    l.buildLogisticFromFileShortestVertex(start, end, resultPath, dataPath);
}

extern "C" JNIEXPORT void JNICALL
Java_com_tech_nativelib_NativeLib_buildLogisticUndirected(
        JNIEnv *env,
        jobject thiz,
        jstring resultFilePath,
        jint cityAmount,
        jint roadAmount,
        jint cargo
) {
    Logisitc<Road, City> l{};
    const char *cstr = env->GetStringUTFChars(resultFilePath, nullptr);
    std::string resultPath = std::string(cstr);
    l.buildLogisticUndirected(resultPath, cityAmount, roadAmount, cargo);
}

extern "C" JNIEXPORT void JNICALL
Java_com_tech_nativelib_NativeLib_buildLogisticFromFileUndirected(
        JNIEnv *env,
        jobject thiz,
        jstring dataFilePath,
        jstring resultFilePath,
        jstring startCity,
        jstring endCity,
        jint cargo
) {
    Logisitc<Road, City> l{};
    const char *cstr = env->GetStringUTFChars(resultFilePath, nullptr);
    std::string resultPath = std::string(cstr);

    const char *cstr1 = env->GetStringUTFChars(dataFilePath, nullptr);
    std::string dataPath = std::string(cstr1);

    const char *cstr2 = env->GetStringUTFChars(startCity, nullptr);
    std::string start = std::string(cstr2);

    const char *cstr3 = env->GetStringUTFChars(endCity, nullptr);
    std::string end = std::string(cstr3);

    l.buildLogisticFromFileUndirected(start, end, resultPath, dataPath, cargo);
}

extern "C" JNIEXPORT void JNICALL
Java_com_tech_nativelib_NativeLib_buildLogisticVertexUndirected(
        JNIEnv *env,
        jobject thiz,
        jstring resultFilePath,
        jint cityAmount,
        jint roadAmount
) {
    Logisitc<Road, City> l{};
    const char *cstr = env->GetStringUTFChars(resultFilePath, nullptr);
    std::string resultPath = std::string(cstr);
    l.buildLogisticShortestVertexUndirected(resultPath, cityAmount, roadAmount);
}

extern "C" JNIEXPORT void JNICALL
Java_com_tech_nativelib_NativeLib_buildLogisticFromFileVertexUndirected(
        JNIEnv *env,
        jobject thiz,
        jstring dataFilePath,
        jstring resultFilePath,
        jstring startCity,
        jstring endCity
) {
    Logisitc<Road, City> l{};
    const char *cstr = env->GetStringUTFChars(resultFilePath, nullptr);
    std::string resultPath = std::string(cstr);

    const char *cstr1 = env->GetStringUTFChars(dataFilePath, nullptr);
    std::string dataPath = std::string(cstr1);

    const char *cstr2 = env->GetStringUTFChars(startCity, nullptr);
    std::string start = std::string(cstr2);

    const char *cstr3 = env->GetStringUTFChars(endCity, nullptr);
    std::string end = std::string(cstr3);

    l.buildLogisticFromFileShortestVertexUndirected(start, end, resultPath, dataPath);
}

extern "C" JNIEXPORT void JNICALL
Java_com_tech_nativelib_NativeLib_buildGistogram(
        JNIEnv *env,
        jobject thiz,
        jstring path,
        jstring option,
        jint amount,
        jint enableStatistic,
        jint filter1,
        jint filter2,
        jint filter3,
        jint filter4,
        jint birthYear,
        jstring cityStartsWith
) {
    const char *cstr = env->GetStringUTFChars(option, NULL);
    std::string sort = std::string(cstr);

    const char *cstrpath = env->GetStringUTFChars(path, NULL);
    std::string filePath = std::string(cstrpath);


    const char *cstrcity = env->GetStringUTFChars(cityStartsWith, NULL);
    std::string city = std::string(cstrcity);


    env->ReleaseStringUTFChars(option, cstr);
    env->ReleaseStringUTFChars(path, cstrpath);
    env->ReleaseStringUTFChars(cityStartsWith, cstrcity);

}

extern "C" JNIEXPORT void JNICALL
Java_com_tech_nativelib_NativeLib_buildGistogramFromFile(
        JNIEnv *env,
        jobject thiz,
        jstring path,
        jstring filePath,
        jstring option,
        jint amount,
        jint enableStatistic,
        jint filter1,
        jint filter2,
        jint filter3,
        jint filter4,
        jint birthYear,
        jstring cityStartsWith
) {
    const char *cstr = env->GetStringUTFChars(option, NULL);
    std::string sort = std::string(cstr);

    const char *cstrpath = env->GetStringUTFChars(path, NULL);
    std::string pth = std::string(cstrpath);

    const char *cstrFilePath = env->GetStringUTFChars(filePath, NULL);
    std::string filePth = std::string(cstrFilePath);


    const char *cstrcity = env->GetStringUTFChars(cityStartsWith, NULL);
    std::string city = std::string(cstrcity);


    env->ReleaseStringUTFChars(option, cstr);
    env->ReleaseStringUTFChars(path, cstrpath);
    env->ReleaseStringUTFChars(cityStartsWith, cstrcity);

}

extern "C" JNIEXPORT void JNICALL
Java_com_tech_nativelib_NativeLib_buildBag(
        JNIEnv *env,
        jobject thiz,
        jstring path,
        jint amount,
        jint maxCapacity,
        jint maxVolume
) {
    const char *cstrpath = env->GetStringUTFChars(path, NULL);
    std::string filePath = std::string(cstrpath);


    env->ReleaseStringUTFChars(path, cstrpath);
}