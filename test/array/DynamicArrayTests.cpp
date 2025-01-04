#include "DynamicArrayTests.h"
#include "../../collectionunqptr/dinamicarray/DynamicArray.h"
#include <cassert>
#include <iostream>

void DynamicArrayTests::testDefaultConstructor() {
    DynamicArray<int> array;
    assert(array.size() == 0);
    assert(array.capacity() == 1);
    assert(array.isEmpty());
    std::cout << "testDefaultConstructor passed.\n";
}

void DynamicArrayTests::testParameterizedConstructor() {
    int items[] = {1, 2, 3};
    DynamicArray<int> array(3, items);
    assert(array.size() == 3);
    assert(array[0] == 1);
    assert(array[1] == 2);
    assert(array[2] == 3);
    std::cout << "testParameterizedConstructor passed.\n";
}

void DynamicArrayTests::testCopyConstructor() {
    int items[] = {1, 2, 3};
    DynamicArray<int> array(3, items);
    DynamicArray<int> copy(array);
    assert(copy.size() == array.size());
    for (size_t i = 0; i < array.size(); ++i) {
        assert(copy[i] == array[i]);
    }
    std::cout << "testCopyConstructor passed.\n";
}

void DynamicArrayTests::testMoveConstructor() {
    int items[] = {1, 2, 3};
    DynamicArray<int> array(3, items);
    DynamicArray<int> moved(std::move(array));
    assert(moved.size() == 3);
    assert(array.size() == 0);
    std::cout << "testMoveConstructor passed.\n";
}

void DynamicArrayTests::testAssignmentOperator() {
    int items[] = {1, 2, 3};
    DynamicArray<int> array(3, items);
    DynamicArray<int> assigned = std::move(array);
    assert(assigned.size() == 3);
    assert(array.size() == 0);
    std::cout << "testAssignmentOperator passed.\n";
}

void DynamicArrayTests::testAdd() {
    DynamicArray<int> array;
    array.add(1);
    array.add(2);
    assert(array.size() == 2);
    assert(array[0] == 1);
    assert(array[1] == 2);
    std::cout << "testAdd passed.\n";
}

void DynamicArrayTests::testPrepend() {
    DynamicArray<int> array;
    array.add(2);
    array.prepend(1);
    assert(array.size() == 2);
    assert(array[0] == 1);
    assert(array[1] == 2);
    std::cout << "testPrepend passed.\n";
}

void DynamicArrayTests::testInsertAt() {
    DynamicArray<int> array;
    array.add(1);
    array.add(3);
    array.insertAt(1, 2);
    assert(array.size() == 3);
    assert(array[1] == 2);
    assert(array[2] == 3);
    std::cout << "testInsertAt passed.\n";
}

void DynamicArrayTests::testResize() {
    DynamicArray<int> array;
    array.add(1);
    array.resize(10);
    assert(array.capacity() == 10);
    assert(array.size() == 1);
    std::cout << "testResize passed.\n";
}

void DynamicArrayTests::testShrinkToFit() {
    DynamicArray<int> array;
    array.add(1);
    array.add(2);
    array.resize(10);
    array.shrink_to_fit();
    assert(array.capacity() == array.size());
    std::cout << "testShrinkToFit passed.\n";
}

void DynamicArrayTests::testGetSubarray() {
    int items[] = {1, 2, 3, 4, 5};
    DynamicArray<int> array(5, items);
    auto subArray = array.getSubarray(1, 4);
    assert(subArray->size() == 3);
    assert((*subArray)[0] == 2);
    assert((*subArray)[1] == 3);
    assert((*subArray)[2] == 4);
    std::cout << "testGetSubarray passed.\n";
}

void DynamicArrayTests::testSwap() {
    int items[] = {1, 2, 3};
    DynamicArray<int> array(3, items);
    array.swap(0, 2);
    assert(array[0] == 3);
    assert(array[2] == 1);
    std::cout << "testSwap passed.\n";
}

void DynamicArrayTests::testSet() {
    DynamicArray<int> array;
    array.add(1);
    array.set(0, 2);
    assert(array[0] == 2);
    std::cout << "testSet passed.\n";
}

void DynamicArrayTests::testGet() {
    DynamicArray<int> array;
    array.add(1);
    assert(array.get(0) == 1);
    std::cout << "testGet passed.\n";
}

void DynamicArrayTests::testOutOfRangeAccess() {
    DynamicArray<int> array;
    try {
        array.get(0);
        assert(false);
    } catch (const IndexOutOfRange&) {
        assert(true);
    }
    std::cout << "testOutOfRangeAccess passed.\n";
}

void DynamicArrayTests::testClear() {
    DynamicArray<int> array;
    array.add(1);
    array.add(2);
    array.clear();
    assert(array.size() == 0);
    assert(array.isEmpty());
    std::cout << "testClear passed.\n";
}

void DynamicArrayTests::runAllTests() {
    testDefaultConstructor();
    testParameterizedConstructor();
    testCopyConstructor();
    testMoveConstructor();
    testAssignmentOperator();
    testAdd();
    testPrepend();
    testInsertAt();
    testResize();
    testShrinkToFit();
    testGetSubarray();
    testSwap();
    testSet();
    testGet();
    testOutOfRangeAccess();
    testClear();
    std::cout << "All DynamicArray tests passed!\n";
}
