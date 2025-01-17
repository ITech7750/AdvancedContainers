#include "HashMapJNI.h"
#include "../gistogram/model/dictionary/HashMap.h"
#include <string>
#include <jni.h>
#include <type_traits>
#include <sstream>

static HashMap<std::string, std::string> globalHashMap;

template <typename T>
std::string toString(T value) {
    if constexpr (std::is_same_v<T, std::string>) {
        return value;
    } else if constexpr (std::is_arithmetic_v<T>) {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }
    return "";
}

template <typename T>
T fromString(const std::string &value);

template <>
std::string fromString<std::string>(const std::string &value) {
    return value;
}

template <>
int fromString<int>(const std::string &value) {
    return std::stoi(value);
}

template <>
double fromString<double>(const std::string &value) {
    return std::stod(value);
}


std::string convertJObjectToString(JNIEnv *env, jobject obj) {
    if (env->IsInstanceOf(obj, env->FindClass("java/lang/String"))) {
        const char *str = env->GetStringUTFChars((jstring)obj, nullptr);
        std::string result(str);
        env->ReleaseStringUTFChars((jstring)obj, str);
        return result;
    } else if (env->IsInstanceOf(obj, env->FindClass("java/lang/Integer"))) {
        jclass integerClass = env->FindClass("java/lang/Integer");
        jmethodID intValueMethod = env->GetMethodID(integerClass, "intValue", "()I");
        jint intValue = env->CallIntMethod(obj, intValueMethod);
        return std::to_string(intValue);
    } else if (env->IsInstanceOf(obj, env->FindClass("java/lang/Double"))) {
        jclass doubleClass = env->FindClass("java/lang/Double");
        jmethodID doubleValueMethod = env->GetMethodID(doubleClass, "doubleValue", "()D");
        jdouble doubleValue = env->CallDoubleMethod(obj, doubleValueMethod);
        return std::to_string(doubleValue);
    }
    return "";
}

JNIEXPORT void JNICALL Java_nativelib_NativeHashMap_put
(JNIEnv *env, jobject obj, jobject key, jobject value) {
    std::string keyStr = convertJObjectToString(env, key);
    std::string valueStr = convertJObjectToString(env, value);

    globalHashMap.put(keyStr, valueStr);
}

JNIEXPORT jobject JNICALL Java_nativelib_NativeHashMap_get
(JNIEnv *env, jobject obj, jobject key) {
    std::string keyStr = convertJObjectToString(env, key);
    std::string result;

    if (globalHashMap.get(keyStr, result)) {
        return env->NewStringUTF(result.c_str());
    }

    return nullptr;
}

JNIEXPORT jboolean JNICALL Java_nativelib_NativeHashMap_containsKey
(JNIEnv *env, jobject obj, jobject key) {
    std::string keyStr = convertJObjectToString(env, key);
    return globalHashMap.containsKey(keyStr);
}

JNIEXPORT void JNICALL Java_nativelib_NativeHashMap_remove
(JNIEnv *env, jobject obj, jobject key) {
    std::string keyStr = convertJObjectToString(env, key);
    globalHashMap.remove(keyStr);
}

JNIEXPORT jint JNICALL Java_nativelib_NativeHashMap_size
(JNIEnv *env, jobject obj) {
    return static_cast<jint>(globalHashMap.size());
}

JNIEXPORT jboolean JNICALL Java_nativelib_NativeHashMap_isEmpty
(JNIEnv *env, jobject obj) {
    return globalHashMap.isEmpty();
}

JNIEXPORT jobject JNICALL Java_nativelib_NativeHashMap_getKeys
(JNIEnv *env, jobject obj) {
    DynamicArray<std::string> keys = globalHashMap.getKeys();
    jclass arrayListClass = env->FindClass("java/util/ArrayList");
    jmethodID arrayListInit = env->GetMethodID(arrayListClass, "<init>", "()V");
    jobject arrayListObj = env->NewObject(arrayListClass, arrayListInit);

    jmethodID arrayListAdd = env->GetMethodID(arrayListClass, "add", "(Ljava/lang/Object;)Z");

    for (size_t i = 0; i < keys.size(); ++i) {
        jstring keyStr = env->NewStringUTF(keys[i].c_str());
        env->CallBooleanMethod(arrayListObj, arrayListAdd, keyStr);
        env->DeleteLocalRef(keyStr);
    }

    return arrayListObj;
}

JNIEXPORT jobject JNICALL Java_nativelib_NativeHashMap_getValues
(JNIEnv *env, jobject obj) {
    DynamicArray<std::string> values = globalHashMap.getValues();
    jclass arrayListClass = env->FindClass("java/util/ArrayList");
    jmethodID arrayListInit = env->GetMethodID(arrayListClass, "<init>", "()V");
    jobject arrayListObj = env->NewObject(arrayListClass, arrayListInit);

    jmethodID arrayListAdd = env->GetMethodID(arrayListClass, "add", "(Ljava/lang/Object;)Z");

    for (size_t i = 0; i < values.size(); ++i) {
        jstring valueStr = env->NewStringUTF(values[i].c_str());
        env->CallBooleanMethod(arrayListObj, arrayListAdd, valueStr);
        env->DeleteLocalRef(valueStr);
    }

    return arrayListObj;
}

JNIEXPORT void JNICALL Java_nativelib_NativeHashMap_clear
(JNIEnv *env, jobject obj) {
    globalHashMap.clear();
}
