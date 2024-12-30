#ifndef TEST_DATA_MANAGER_H
#define TEST_DATA_MANAGER_H

#include <string>
#include "../testClasses/Person.h"
#include "TestHelpers.h"
#include "../../collectionunqptr/sequence/arraysequence/MutableArraySequenceUnqPtr.h"

class TestDataManager {
public:
    static  MutableArraySequenceUnqPtr<Person>* generateTestData(size_t count);

    static void saveToJson(const  MutableArraySequenceUnqPtr<Person>& data, const std::string& filename);
    static  MutableArraySequenceUnqPtr<Person>* loadFromJson(const std::string& filename);

    static void saveToTxt(const  MutableArraySequenceUnqPtr<Person>& data, const std::string& filename);
    static  MutableArraySequenceUnqPtr<Person>* loadFromTxt(const std::string& filename);
};

#endif // TEST_DATA_MANAGER_H
