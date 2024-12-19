#ifndef INTERACTIVE_TEST_SUITE_H
#define INTERACTIVE_TEST_SUITE_H

#include <string>
#include "../testClasses/Person.h"
#include "../../collectionunqptr/sequence/linkedlistsequence/MutableListSequenceUnqPtr.h"

class InteractiveTestSuite {
public:
    static MutableListSequenceUnqPtr<Person>* generateTestData(size_t count);

    static std::string saveTestData(MutableListSequenceUnqPtr<Person>* data, int formatChoice, const std::string& filename = "");

    static MutableListSequenceUnqPtr<Person>* loadTestData(int formatChoice, const std::string& filename);
};

#endif
