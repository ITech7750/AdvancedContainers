#ifndef TEST_DATA_MANAGER_H
#define TEST_DATA_MANAGER_H

#include <string>
#include "../testClasses/Person.h"
#include "TestHelpers.h"
#include "../../collectionunqptr/sequence/linkedlistsequence/MutableListSequenceUnqPtr.h"

class TestDataManager {
public:
    static MutableListSequenceUnqPtr<Person>* generateTestData(size_t count);

    static void saveToJson(const MutableListSequenceUnqPtr<Person>& data, const std::string& filename);
    static MutableListSequenceUnqPtr<Person>* loadFromJson(const std::string& filename);

    static void saveToTxt(const MutableListSequenceUnqPtr<Person>& data, const std::string& filename);
    static MutableListSequenceUnqPtr<Person>* loadFromTxt(const std::string& filename);
};

#endif // TEST_DATA_MANAGER_H
