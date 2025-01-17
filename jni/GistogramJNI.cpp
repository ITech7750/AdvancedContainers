#include "GistogramJNI.h"
#include "../gistogram/model/Gistogram.h"
#include <string>
#include <sstream>
#include <stdexcept>

// Пример использования Gistogram с типами string и int
static Gistogram<std::string, int> globalGistogram;

template <typename T>
T convertJObjectToNative(JNIEnv *env, jobject obj);

template <>
std::string convertJObjectToNative<std::string>(JNIEnv *env, jobject obj) {
    const char *str = env->GetStringUTFChars((jstring)obj, nullptr);
    std::string result(str);
    env->ReleaseStringUTFChars((jstring)obj, str);
    return result;
}

template <>
int convertJObjectToNative<int>(JNIEnv *env, jobject obj) {
    jclass integerClass = env->FindClass("java/lang/Integer");
    jmethodID intValueMethod = env->GetMethodID(integerClass, "intValue", "()I");
    return env->CallIntMethod(obj, intValueMethod);
}

template <typename T>
jobject convertNativeToJObject(JNIEnv *env, T value);

template <>
jobject convertNativeToJObject<int>(JNIEnv *env, int value) {
    jclass integerClass = env->FindClass("java/lang/Integer");
    jmethodID constructor = env->GetMethodID(integerClass, "<init>", "(I)V");
    return env->NewObject(integerClass, constructor, value);
}

JNIEXPORT void JNICALL Java_nativelib_NativeGistogram_addParameter
(JNIEnv *env, jobject obj, jobject parameter) {
    // Для параметра потребуется отдельная обработка.
    throw std::runtime_error("Method not implemented yet.");
}

JNIEXPORT void JNICALL Java_nativelib_NativeGistogram_addData
(JNIEnv *env, jobject obj, jobject data) {
    int value = convertJObjectToNative<int>(env, data);
    globalGistogram.addData(value);
}

JNIEXPORT jobject JNICALL Java_nativelib_NativeGistogram_getMostFrequent
(JNIEnv *env, jobject obj) {
    try {
        int mostFrequent = globalGistogram.getMostFrequent();
        return convertNativeToJObject(env, mostFrequent);
    } catch (const std::runtime_error &e) {
        return nullptr;
    }
}

JNIEXPORT jint JNICALL Java_nativelib_NativeGistogram_countInRange
(JNIEnv *env, jobject obj, jobject lowerBound, jobject upperBound) {
    int lower = convertJObjectToNative<int>(env, lowerBound);
    int upper = convertJObjectToNative<int>(env, upperBound);
    return static_cast<jint>(globalGistogram.countInRange(lower, upper));
}

JNIEXPORT void JNICALL Java_nativelib_NativeGistogram_clearAll
(JNIEnv *env, jobject obj) {
    globalGistogram.clearAll();
}

JNIEXPORT jobject JNICALL Java_nativelib_NativeGistogram_findMatchingValues
(JNIEnv *env, jobject obj, jobject condition) {
    // Условие требует сложной обработки через Java лямбды
    throw std::runtime_error("Method not implemented yet.");
}
