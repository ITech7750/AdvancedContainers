#ifndef INTERACTIVE_TEST_SUITE_H
#define INTERACTIVE_TEST_SUITE_H

#include <string>
#include "../testClasses/Person.h"
#include "../../collectionunqptr/sequence/arraysequence/MutableArraySequenceUnqPtr.h"

class InteractiveTestSuiteArray {
public:
    static MutableArraySequenceUnqPtr<Person>* generateTestData(size_t count);

    static std::string saveTestData(MutableArraySequenceUnqPtr<Person>* data, int formatChoice, const std::string& filename = "");

    static MutableArraySequenceUnqPtr<Person>* loadTestData(int formatChoice, const std::string& filename);
};

#endif
