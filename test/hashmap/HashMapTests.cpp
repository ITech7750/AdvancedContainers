#include "HashMapTests.h"
#include <iostream>
#include <cassert>
#include "../../gistogram/model/dictionary/HashMap.h"

void HashMapTests::runAllTests() {
    testInsertAndGet();
    testInsertDuplicateKey();
    testContains();
    testOperatorAccess();
    testGetKeys();
    testGetNonExistentKey();

    std::cout << "All tests passed.\n";
}

void HashMapTests::testInsertAndGet() {
    // Arrange
    HashMap<int, std::string> map;

    // Act
    map.insert(1, "One");
    map.insert(2, "Two");
    map.insert(3, "Three");

    // Assert
    assert(map.get(1) == "One");
    assert(map.get(2) == "Two");
    assert(map.get(3) == "Three");
    std::cout << "testInsertAndGet passed.\n";
}

void HashMapTests::testInsertDuplicateKey() {
    // Arrange
    HashMap<int, std::string> map;
    map.insert(1, "One");

    // Act
    map.insert(1, "Uno");

    // Assert
    assert(map.get(1) == "Uno");
    std::cout << "testInsertDuplicateKey passed.\n";
}

void HashMapTests::testContains() {
    // Arrange
    HashMap<int, std::string> map;
    map.insert(1, "One");

    // Act & Assert
    assert(map.contains(1) == true);
    assert(map.contains(2) == false);
    std::cout << "testContains passed.\n";
}

void HashMapTests::testOperatorAccess() {
    // Arrange
    HashMap<int, std::string> map;
    map.insert(1, "One");
    map.insert(2, "Two");

    // Act & Assert
    assert(map[1] == "One");
    assert(map[2] == "Two");
    std::cout << "testOperatorAccess passed.\n";
}

void HashMapTests::testGetKeys() {
    // Arrange
    HashMap<int, std::string> map;
    map.insert(1, "One");
    map.insert(2, "Two");
    map.insert(3, "Three");

    // Act
    DynamicArray<int> keys = map.getKeys();

    // Assert
    assert(keys.size() == 3);
    assert(keys.contains(1));
    assert(keys.contains(2));
    assert(keys.contains(3));
    std::cout << "testGetKeys passed.\n";
}

void HashMapTests::testGetNonExistentKey() {
    // Arrange
    HashMap<int, std::string> map;

    // Act & Assert
    try {
        map.get(1);
        assert(false);  // This should not be reached
    } catch (const std::exception& e) {
        assert(true);  // Exception should be thrown
    }
    std::cout << "testGetNonExistentKey passed.\n";
}
