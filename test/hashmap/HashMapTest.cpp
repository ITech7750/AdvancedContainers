#include "HashMapTest.h"
#include "../../gistogram/model/dictionary/HashMap.h"
#include <unordered_map>
#include <iostream>
#include <chrono>
#include <cassert>

HashMapTest::HashMapTest(size_t testSize, size_t stringLength)
    : _testSize(testSize), _stringLength(stringLength) {}

std::string HashMapTest::generateRandomString(size_t length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string result;
    result.resize(length);

    for (size_t i = 0; i < length; ++i) {
        result[i] = charset[rand() % (sizeof(charset) - 1)];
    }

    return result;
}

void HashMapTest::testInsert() {
    HashMap<int, std::string> map;
    for (size_t i = 0; i < _testSize; ++i) {
        map.put(i, generateRandomString(_stringLength));
    }
    std::cout << "Custom HashMap insert test completed.\n";
}

void HashMapTest::testGet() {
    HashMap<int, std::string> map;
    for (size_t i = 0; i < _testSize; ++i) {
        map.put(i, generateRandomString(_stringLength));
    }

    std::string value;
    for (size_t i = 0; i < _testSize; ++i) {
        assert(map.get(i, value));
    }
    std::cout << "Custom HashMap get test completed.\n";
}

void HashMapTest::testContains() {
    HashMap<int, std::string> map;
    for (size_t i = 0; i < _testSize; ++i) {
        map.put(i, generateRandomString(_stringLength));
    }

    for (size_t i = 0; i < _testSize; ++i) {
        assert(map.containsKey(i));
    }
    std::cout << "Custom HashMap contains test completed.\n";
}

void HashMapTest::testRemove() {
    HashMap<int, std::string> map;
    for (size_t i = 0; i < _testSize; ++i) {
        map.put(i, generateRandomString(_stringLength));
    }

    for (size_t i = 0; i < _testSize; ++i) {
        map.remove(i);
    }
    assert(map.isEmpty());
    std::cout << "Custom HashMap remove test completed.\n";
}

void HashMapTest::runAllTests() {
    testInsert();
    testGet();
    testContains();
    testRemove();
    compareWithStdUnorderedMap();
}

void HashMapTest::compareWithStdUnorderedMap() {
    std::unordered_map<int, std::string> stdMap;
    HashMap<int, std::string> customMap;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < _testSize; ++i) {
        stdMap[i] = generateRandomString(_stringLength);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> stdInsertTime = end - start;
    std::cout << "std::unordered_map insertion time: " << stdInsertTime.count() << " seconds\n";

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < _testSize; ++i) {
        customMap.put(i, generateRandomString(_stringLength));
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> customInsertTime = end - start;
    std::cout << "Custom HashMap insertion time: " << customInsertTime.count() << " seconds\n";
    
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < _testSize; ++i) {
        std::string value = stdMap[i];
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> stdGetTime = end - start;
    std::cout << "std::unordered_map retrieval time: " << stdGetTime.count() << " seconds\n";

    std::string value;
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < _testSize; ++i) {
        assert(customMap.get(i, value));
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> customGetTime = end - start;
    std::cout << "Custom HashMap retrieval time: " << customGetTime.count() << " seconds\n";
}
