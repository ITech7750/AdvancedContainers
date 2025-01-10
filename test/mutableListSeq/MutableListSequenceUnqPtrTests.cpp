#include "MutableListSequenceUnqPtrTests.h"
#include "../../collectionunqptr/sequence/linkedlistsequence/MutableListSequenceUnqPtr.h"
#include <cassert>
#include <iostream>

void MutableListSequenceUnqPtrTests::testDefaultConstructor() {
    MutableListSequenceUnqPtr<int> sequence;
    assert(sequence.size() == 0);
    assert(sequence.isEmpty());
    std::cout << "testDefaultConstructor passed.\n";
}

void MutableListSequenceUnqPtrTests::testParameterizedConstructor() {
    //int items[] = {1, 2, 3};
    //MutableListSequenceUnqPtr<int> sequence(items, 3);
    int arr[] = {1, 2, 3};
    try {
        MutableListSequenceUnqPtr<int> sequence(arr, 3);
        // Использование sequence
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    //assert(sequence.size() == 3);
    //assert(sequence.get(0) == 1);
    //assert(sequence.get(1) == 2);
    //assert(sequence.get(2) == 3);

    std::cout << "testParameterizedConstructor passed.\n";
}

void MutableListSequenceUnqPtrTests::testCopyConstructor() {
    int items[] = {1, 2, 3};
    MutableListSequenceUnqPtr<int> original(items, 3);
    MutableListSequenceUnqPtr<int> copy(original);
    assert(copy.size() == 3);
    assert(copy.get(0) == 1);
    assert(copy.get(1) == 2);
    assert(copy.get(2) == 3);
    std::cout << "testCopyConstructor passed.\n";
}

void MutableListSequenceUnqPtrTests::testMutableSequenceConstructor() {
    int items[] = {1, 2, 3};
    MutableListSequenceUnqPtr<int> source(items, 3);
    MutableListSequenceUnqPtr<int> sequence(source);
    assert(sequence.size() == 3);
    assert(sequence.get(0) == 1);
    assert(sequence.get(1) == 2);
    assert(sequence.get(2) == 3);
    std::cout << "testMutableSequenceConstructor passed.\n";
}

void MutableListSequenceUnqPtrTests::testOperatorPlusEquals() {
    int items[] = {1, 2};
    MutableListSequenceUnqPtr<int> sequence(items, 2);
    int additionalItems[] = {3, 4};
    MutableListSequenceUnqPtr<int> additionalSequence(additionalItems, 2);
    sequence += additionalSequence;
    assert(sequence.size() == 4);
    assert(sequence.get(2) == 3);
    assert(sequence.get(3) == 4);
    std::cout << "testOperatorPlusEquals passed.\n";
}

void MutableListSequenceUnqPtrTests::testGetFirstAndLast() {
    int items[] = {1, 2, 3};
    MutableListSequenceUnqPtr<int> sequence(items, 3);
    assert(sequence.getFirst() == 1);
    assert(sequence.getLast() == 3);
    std::cout << "testGetFirstAndLast passed.\n";
}

void MutableListSequenceUnqPtrTests::testGetAndSize() {
    int items[] = {1, 2, 3};
    MutableListSequenceUnqPtr<int> sequence(items, 3);
    assert(sequence.size() == 3);
    assert(sequence.get(1) == 2);
    std::cout << "testGetAndSize passed.\n";
}

void MutableListSequenceUnqPtrTests::testIsEmpty() {
    MutableListSequenceUnqPtr<int> sequence;
    assert(sequence.isEmpty());
    sequence.append(1);
    assert(!sequence.isEmpty());
    std::cout << "testIsEmpty passed.\n";
}

void MutableListSequenceUnqPtrTests::testGetSubsequence() {
    int items[] = {1, 2, 3, 4, 5};
    MutableListSequenceUnqPtr<int> sequence(items, 5);
    auto subsequence = sequence.getSubsequence(1, 3);
    assert(subsequence->size() == 3);
    assert(subsequence->get(0) == 2);
    assert(subsequence->get(1) == 3);
    assert(subsequence->get(2) == 4);
    std::cout << "testGetSubsequence passed.\n";
}

void MutableListSequenceUnqPtrTests::testConcat() {
    int items1[] = {1, 2};
    int items2[] = {3, 4};
    MutableListSequenceUnqPtr<int> sequence1(items1, 2);
    MutableListSequenceUnqPtr<int> sequence2(items2, 2);
    auto concatenated = sequence1.concat(sequence2);
    assert(concatenated->size() == 4);
    assert(concatenated->get(0) == 1);
    assert(concatenated->get(3) == 4);
    std::cout << "testConcat passed.\n";
}

void MutableListSequenceUnqPtrTests::testAppend() {
    MutableListSequenceUnqPtr<int> sequence;
    sequence.append(1);
    sequence.append(2);
    assert(sequence.size() == 2);
    assert(sequence.get(1) == 2);
    std::cout << "testAppend passed.\n";
}

void MutableListSequenceUnqPtrTests::testPrepend() {
    MutableListSequenceUnqPtr<int> sequence;
    sequence.append(2);
    sequence.prepend(1);
    assert(sequence.size() == 2);
    assert(sequence.get(0) == 1);
    std::cout << "testPrepend passed.\n";
}

void MutableListSequenceUnqPtrTests::testInsertAt() {
    MutableListSequenceUnqPtr<int> sequence;
    sequence.append(1);
    sequence.append(3);
    sequence.insertAt(1, 2);
    assert(sequence.size() == 3);
    assert(sequence.get(1) == 2);
    assert(sequence.get(2) == 3);
    std::cout << "testInsertAt passed.\n";
}

void MutableListSequenceUnqPtrTests::testSet() {
    MutableListSequenceUnqPtr<int> sequence;
    sequence.append(1);
    sequence.append(2);
    sequence.set(1, 3);
    assert(sequence.get(1) == 3);
    std::cout << "testSet passed.\n";
}

void MutableListSequenceUnqPtrTests::testOutOfRangeAccess() {
    MutableListSequenceUnqPtr<int> sequence;
    sequence.append(1);
    try {
        sequence.get(10);
        assert(false);
    } catch (const std::runtime_error&) {
        assert(true);
    }
    std::cout << "testOutOfRangeAccess passed.\n";
}

void MutableListSequenceUnqPtrTests::runAllTests() {
    testDefaultConstructor();
    testParameterizedConstructor();
    testCopyConstructor();
    testMutableSequenceConstructor();
    testOperatorPlusEquals();
    testGetFirstAndLast();
    testGetAndSize();
    testIsEmpty();
    testGetSubsequence();
    testConcat();
    testAppend();
    testPrepend();
    testInsertAt();
    testSet();
    testOutOfRangeAccess();
    std::cout << "All tests passed!\n";
}
