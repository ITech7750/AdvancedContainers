#include "SorterServiceJNI.h"
#include <jni.h>
#include <string>
#include "../sort/SorterServiceArray.h"
#include "../test/helper/TestDataManagerArray.h"
#include "../test/testClasses/Person.h"

jobject convertToJavaList(JNIEnv* env, MutableArraySequenceUnqPtr<Person>& data) {
    jclass arrayListClass = env->FindClass("java/util/ArrayList");
    jmethodID arrayListInit = env->GetMethodID(arrayListClass, "<init>", "()V");
    jobject arrayListObj = env->NewObject(arrayListClass, arrayListInit);

    jmethodID arrayListAdd = env->GetMethodID(arrayListClass, "add", "(Ljava/lang/Object;)Z");

    jclass personClass = env->FindClass("org/example/model/Person");
    jmethodID personConstructor = env->GetMethodID(personClass, "<init>", "(Ljava/lang/String;Ljava/lang/String;ILjava/lang/String;DDILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

    for (size_t i = 0; i < data.size(); ++i) {
        const Person& person = data.get(i);
        jstring firstName = env->NewStringUTF(person.firstName.c_str());
        jstring lastName = env->NewStringUTF(person.lastName.c_str());
        jstring address = env->NewStringUTF(person.address.c_str());
        jstring phoneNumber = env->NewStringUTF(person.phoneNumber.c_str());
        jstring email = env->NewStringUTF(person.email.c_str());
        jstring jobTitle = env->NewStringUTF(person.jobTitle.c_str());

        jobject personObj = env->NewObject(personClass, personConstructor,
            firstName, lastName, person.age, address, person.height, person.weight,
            person.yearOfBirth, phoneNumber, email, jobTitle);

        env->CallBooleanMethod(arrayListObj, arrayListAdd, personObj);

        env->DeleteLocalRef(firstName);
        env->DeleteLocalRef(lastName);
        env->DeleteLocalRef(address);
        env->DeleteLocalRef(phoneNumber);
        env->DeleteLocalRef(email);
        env->DeleteLocalRef(jobTitle);
        env->DeleteLocalRef(personObj);
    }

    return arrayListObj;
}

JNIEXPORT jdouble JNICALL Java_org_example_sorter_SorterService_sortByAgeAndGetTime
(JNIEnv* env, jclass clazz, jstring fileName, jboolean isJson, jstring algorithm) {
    const char* fileNameCStr = env->GetStringUTFChars(fileName, nullptr);
    const char* algorithmCStr = env->GetStringUTFChars(algorithm, nullptr);

    try {
        auto data = isJson ? TestDataManagerArray::loadFromJson(fileNameCStr)
                                                         : TestDataManagerArray::loadFromTxt(fileNameCStr);

        double duration = SorterServiceArray<Person>::measureSortTime(*data, compareByAge, algorithmCStr);

        env->ReleaseStringUTFChars(fileName, fileNameCStr);
        env->ReleaseStringUTFChars(algorithm, algorithmCStr);

        return duration;
    } catch (const std::exception& e) {
        env->ReleaseStringUTFChars(fileName, fileNameCStr);
        env->ReleaseStringUTFChars(algorithm, algorithmCStr);
        jclass exceptionClass = env->FindClass("java/lang/RuntimeException");
        env->ThrowNew(exceptionClass, e.what());
        return -1;
    }
}

JNIEXPORT jobject JNICALL Java_org_example_sorter_SorterService_getSortedByAge
(JNIEnv* env, jclass clazz, jstring fileName, jboolean isJson, jstring algorithm) {
    const char* fileNameCStr = env->GetStringUTFChars(fileName, nullptr);
    const char* algorithmCStr = env->GetStringUTFChars(algorithm, nullptr);

    try {
        auto data = isJson ? TestDataManagerArray::loadFromJson(fileNameCStr)
                                                         : TestDataManagerArray::loadFromTxt(fileNameCStr);

        SorterServiceArray<Person>::sort(*data, compareByAge, algorithmCStr);

        env->ReleaseStringUTFChars(fileName, fileNameCStr);
        env->ReleaseStringUTFChars(algorithm, algorithmCStr);

        return convertToJavaList(env, *data);
    } catch (const std::exception& e) {
        env->ReleaseStringUTFChars(fileName, fileNameCStr);
        env->ReleaseStringUTFChars(algorithm, algorithmCStr);
        jclass exceptionClass = env->FindClass("java/lang/RuntimeException");
        env->ThrowNew(exceptionClass, e.what());
        return nullptr;
    }
}

extern "C" JNIEXPORT void JNICALL
Java_org_example_sorter_SorterService_sortByName(JNIEnv* env, jclass clazz, jstring fileName, jboolean isJson, jstring algorithm) {
    const char* fileNameCStr = env->GetStringUTFChars(fileName, nullptr);
    const char* algorithmCStr = env->GetStringUTFChars(algorithm, nullptr);

    try {
        auto data = isJson ? TestDataManagerArray::loadFromJson(fileNameCStr)
                                                         : TestDataManagerArray::loadFromTxt(fileNameCStr);

        double sortTime = SorterServiceArray<Person>::measureSortTime(*data, compareByName, algorithmCStr);

        for (size_t i = 0; i < data->size(); ++i) {
            std::cout << data->get(i).toString() << std::endl;
        }

        env->ReleaseStringUTFChars(fileName, fileNameCStr);
        env->ReleaseStringUTFChars(algorithm, algorithmCStr);

    } catch (const std::exception& e) {
        env->ReleaseStringUTFChars(fileName, fileNameCStr);
        env->ReleaseStringUTFChars(algorithm, algorithmCStr);
        jclass exceptionClass = env->FindClass("java/lang/RuntimeException");
        env->ThrowNew(exceptionClass, e.what());
    }
}

extern "C" JNIEXPORT void JNICALL
Java_org_example_sorter_SorterService_sortByAge(JNIEnv* env, jclass clazz, jstring fileName, jboolean isJson, jstring algorithm) {
    const char* fileNameCStr = env->GetStringUTFChars(fileName, nullptr);
    const char* algorithmCStr = env->GetStringUTFChars(algorithm, nullptr);

    try {
        auto data = isJson ? TestDataManagerArray::loadFromJson(fileNameCStr)
                                                         : TestDataManagerArray::loadFromTxt(fileNameCStr);

        double sortTime = SorterServiceArray<Person>::measureSortTime(*data, compareByAge, algorithmCStr);

        for (size_t i = 0; i < data->size(); ++i) {
            std::cout << data->get(i).toString() << std::endl;
        }

        env->ReleaseStringUTFChars(fileName, fileNameCStr);
        env->ReleaseStringUTFChars(algorithm, algorithmCStr);

    } catch (const std::exception& e) {
        env->ReleaseStringUTFChars(fileName, fileNameCStr);
        env->ReleaseStringUTFChars(algorithm, algorithmCStr);
        jclass exceptionClass = env->FindClass("java/lang/RuntimeException");
        env->ThrowNew(exceptionClass, e.what());
    }
}