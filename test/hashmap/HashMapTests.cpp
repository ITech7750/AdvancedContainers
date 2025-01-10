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

    HashMap<int, std::string> map;

    map.insert(1, "One");
    map.insert(2, "Two");
    map.insert(3, "Three");

    assert(map.get(1) == "One");
    assert(map.get(2) == "Two");
    assert(map.get(3) == "Three");
    std::cout << "testInsertAndGet passed.\n";
}

void HashMapTests::testInsertDuplicateKey() {

    HashMap<int, std::string> map;
    map.insert(1, "One");

    map.insert(1, "Uno");

    assert(map.get(1) == "Uno");
    std::cout << "testInsertDuplicateKey passed.\n";
}

void HashMapTests::testContains() {

    HashMap<int, std::string> map;
    map.insert(1, "One");

    assert(map.contains(1) == true);
    assert(map.contains(2) == false);
    std::cout << "testContains passed.\n";
}

void HashMapTests::testOperatorAccess() {

    HashMap<int, std::string> map;
    map.insert(1, "One");
    map.insert(2, "Two");
    assert(map[1] == "One");
    assert(map[2] == "Two");
    std::cout << "testOperatorAccess passed.\n";
}

void HashMapTests::testGetKeys() {

    HashMap<int, std::string> map;
    map.insert(1, "One");
    map.insert(2, "Two");
    map.insert(3, "Three");

    DynamicArray<int> keys = map.getKeys();

    assert(keys.size() == 3);
    assert(keys.contains(1));
    assert(keys.contains(2));
    assert(keys.contains(3));
    std::cout << "testGetKeys passed.\n";
}

void HashMapTests::testGetNonExistentKey() {

    HashMap<int, std::string> map;
    try {
        map.get(1);
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }
    std::cout << "testGetNonExistentKey passed.\n";
}
