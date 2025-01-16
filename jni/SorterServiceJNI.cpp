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
_org_example_sorter_SorterService_sortByNameJava(JNIEnv* env, jclass clazz, jstring fileName, jboolean isJson, jstring algorithm) {
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

class SortStepRecorder {
public:
    static DynamicArray<DynamicArray<int>> sortSteps;

    static void recordSortStep(MutableSequence<int>* seq) {
        DynamicArray<int> currentStep(seq->size());
        for (size_t i = 0; i < seq->size(); ++i) {
            currentStep.set(i, seq->get(i));
        }
        sortSteps.add(std::move(currentStep));
    }
};

DynamicArray<DynamicArray<int>> SortStepRecorder::sortSteps;


JNIEXPORT jobject JNICALL Java_org_example_sorter_SorterService_sortStepByStep
(JNIEnv* env, jclass clazz, jobject inputList, jstring algorithm) {
    const char* algorithmCStr = env->GetStringUTFChars(algorithm, nullptr);

    try {
        jclass listClass = env->FindClass("java/util/List");
        jmethodID sizeMethod = env->GetMethodID(listClass, "size", "()I");
        jmethodID getMethod = env->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;");

        jint listSize = env->CallIntMethod(inputList, sizeMethod);

        DynamicArray<int> inputArray(listSize);
        for (jint i = 0; i < listSize; ++i) {
            jobject element = env->CallObjectMethod(inputList, getMethod, i);
            jint value = env->CallIntMethod(element, env->GetMethodID(env->GetObjectClass(element), "intValue", "()I"));
            inputArray.set(i, value);
            env->DeleteLocalRef(element);
        }

        MutableArraySequenceUnqPtr<int> sequence(inputArray.getRawPointer(), listSize);

        SortStepRecorder::sortSteps.clear();

        SorterServiceArray<int>::sortStepByStep(sequence, compareInts, algorithmCStr, &SortStepRecorder::recordSortStep);

        jclass arrayListClass = env->FindClass("java/util/ArrayList");
        jmethodID arrayListInit = env->GetMethodID(arrayListClass, "<init>", "()V");
        jmethodID arrayListAdd = env->GetMethodID(arrayListClass, "add", "(Ljava/lang/Object;)Z");
        jobject stepList = env->NewObject(arrayListClass, arrayListInit);

        jclass integerClass = env->FindClass("java/lang/Integer");
        jmethodID integerConstructor = env->GetMethodID(integerClass, "<init>", "(I)V");

        for (size_t step = 0; step < SortStepRecorder::sortSteps.size(); ++step) {
            jobject stepArrayList = env->NewObject(arrayListClass, arrayListInit);

            for (size_t i = 0; i < SortStepRecorder::sortSteps[step].size(); ++i) {
                jobject value = env->NewObject(integerClass, integerConstructor, SortStepRecorder::sortSteps[step].get(i));
                env->CallBooleanMethod(stepArrayList, arrayListAdd, value);
                env->DeleteLocalRef(value);
            }

            env->CallBooleanMethod(stepList, arrayListAdd, stepArrayList);
            env->DeleteLocalRef(stepArrayList);
        }

        env->ReleaseStringUTFChars(algorithm, algorithmCStr);

        return stepList;
    } catch (const std::exception& e) {
        env->ReleaseStringUTFChars(algorithm, algorithmCStr);
        jclass exceptionClass = env->FindClass("java/lang/RuntimeException");
        env->ThrowNew(exceptionClass, e.what());
        return nullptr;
    }
}
