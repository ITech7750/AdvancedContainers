#include "MutableArraySequenceUnqPtrTests.h"
#include "../../collectionunqptr/sequence/arraysequence/MutableArraySequenceUnqPtr.h"
#include <cassert>
#include <iostream>


void MutableArraySequenceUnqPtrTests::testDefaultConstructor() {
    MutableArraySequenceUnqPtr<int> sequence;
    assert(sequence.size() == 0);
    assert(sequence.isEmpty());
    std::cout << "testDefaultConstructor passed.\n";
}

void MutableArraySequenceUnqPtrTests::testParameterizedConstructor() {
    int items[] = {1, 2, 3};
    MutableArraySequenceUnqPtr<int> sequence(items, 3);
    assert(sequence.size() == 3);
    assert(sequence.get(0) == 1);
    assert(sequence.get(1) == 2);
    assert(sequence.get(2) == 3);
    std::cout << "testParameterizedConstructor passed.\n";
}

void MutableArraySequenceUnqPtrTests::testDynamicArrayConstructor() {
    int items[] = {1, 2, 3};
    DynamicArray<int> array(3, items);
    MutableArraySequenceUnqPtr<int> sequence(array);
    assert(sequence.size() == 3);
    assert(sequence.get(0) == 1);
    assert(sequence.get(1) == 2);
    assert(sequence.get(2) == 3);
    std::cout << "testDynamicArrayConstructor passed.\n";
}

void MutableArraySequenceUnqPtrTests::testMutableSequenceConstructor() {
    int items[] = {1, 2, 3};
    MutableArraySequenceUnqPtr<int> source(items, 3);
    MutableArraySequenceUnqPtr<int> sequence(std::move(source));
    assert(sequence.size() == 3);
    assert(sequence.get(0) == 1);
    assert(sequence.get(1) == 2);
    assert(sequence.get(2) == 3);
    std::cout << "testMutableSequenceConstructor passed.\n";
}

void MutableArraySequenceUnqPtrTests::testOperatorPlusEquals() {
    int items[] = {1, 2};
    MutableArraySequenceUnqPtr<int> sequence(items, 2);
    int additionalItems[] = {3, 4};
    DynamicArray<int> additionalArray(2, additionalItems);

    for (size_t i = 0; i < additionalArray.size(); i++) {
        sequence.append(additionalArray.get(i));
    }

    assert(sequence.size() == 4);
    assert(sequence.get(2) == 3);
    assert(sequence.get(3) == 4);
    std::cout << "testOperatorPlusEquals passed.\n";
}

void MutableArraySequenceUnqPtrTests::testGetFirstAndLast() {
    int items[] = {1, 2, 3};
    MutableArraySequenceUnqPtr<int> sequence(items, 3);
    assert(sequence.getFirst() == 1);
    assert(sequence.getLast() == 3);
    std::cout << "testGetFirstAndLast passed.\n";
}

void MutableArraySequenceUnqPtrTests::testGetAndSize() {
    int items[] = {1, 2, 3};
    MutableArraySequenceUnqPtr<int> sequence(items, 3);
    assert(sequence.size() == 3);
    assert(sequence.get(1) == 2);
    std::cout << "testGetAndSize passed.\n";
}

void MutableArraySequenceUnqPtrTests::testIsEmpty() {
    MutableArraySequenceUnqPtr<int> sequence;
    assert(sequence.isEmpty());
    int item = 1;
    sequence.append(item);
    assert(!sequence.isEmpty());
    std::cout << "testIsEmpty passed.\n";
}

void MutableArraySequenceUnqPtrTests::testGetSubsequence() {
    int items[] = {1, 2, 3, 4, 5};
    MutableArraySequenceUnqPtr<int> sequence(items, 5);
    auto subsequence = sequence.getSubsequence(1, 4);
    assert(subsequence->size() == 3);
    assert(subsequence->get(0) == 2);
    assert(subsequence->get(1) == 3);
    assert(subsequence->get(2) == 4);
    std::cout << "testGetSubsequence passed.\n";
}

void MutableArraySequenceUnqPtrTests::testConcat() {
    int items1[] = {1, 2};
    int items2[] = {3, 4};
    MutableArraySequenceUnqPtr<int> sequence1(items1, 2);
    MutableArraySequenceUnqPtr<int> sequence2(items2, 2);
    auto concatenated = sequence1.concat(sequence2);
    assert(concatenated->size() == 4);
    assert(concatenated->get(0) == 1);
    assert(concatenated->get(3) == 4);
    std::cout << "testConcat passed.\n";
}

void MutableArraySequenceUnqPtrTests::testAppend() {
    MutableArraySequenceUnqPtr<int> sequence;
    sequence.append(1);
    sequence.append(2);
    assert(sequence.size() == 2);
    assert(sequence.get(1) == 2);
    std::cout << "testAppend passed.\n";
}

void MutableArraySequenceUnqPtrTests::testPrepend() {
    MutableArraySequenceUnqPtr<int> sequence;
    sequence.append(2);
    sequence.prepend(1);
    assert(sequence.size() == 2);
    assert(sequence.get(0) == 1);
    std::cout << "testPrepend passed.\n";
}

void MutableArraySequenceUnqPtrTests::testInsertAt() {
    MutableArraySequenceUnqPtr<int> sequence;
    sequence.append(1);
    sequence.append(3);
    sequence.insertAt(1, 2);
    assert(sequence.size() == 3);
    assert(sequence.get(1) == 2);
    assert(sequence.get(2) == 3);
    std::cout << "testInsertAt passed.\n";
}

void MutableArraySequenceUnqPtrTests::testOutOfRangeAccess() {
    MutableArraySequenceUnqPtr<int> sequence;
    sequence.append(1);
    try {
        sequence.get(10);
        assert(false);
    } catch (const std::runtime_error&) {
        assert(true);
    }
    std::cout << "testOutOfRangeAccess passed.\n";
}

void MutableArraySequenceUnqPtrTests::runAllTests() {
    testDefaultConstructor();
    testParameterizedConstructor();
    testDynamicArrayConstructor();
    testMutableSequenceConstructor();
    testGetFirstAndLast();
    testGetAndSize();
    testIsEmpty();
    testGetSubsequence();
    testConcat();
    testOperatorPlusEquals();
    testAppend();
    testPrepend();
    testInsertAt();
    testOutOfRangeAccess();
    std::cout << "All tests passed!\n";
}
