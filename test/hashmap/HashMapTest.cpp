#include "HashMapTest.h"
#include "../../gistogram/model/dictionary/HashMap.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <random>

HashMapTest::HashMapTest(size_t testSize, size_t stringLength)
    : _testSize(testSize), _stringLength(stringLength) {}

std::string HashMapTest::generateRandomString(size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const size_t maxIndex = sizeof(charset) - 1;
    std::string str;
    for (size_t i = 0; i < length; ++i) {
        str += charset[rand() % maxIndex];
    }
    return str;
}


void HashMapTest::testInsert() {
    std::vector<std::pair<std::string, int>> testData;
    for (size_t i = 0; i < _testSize; ++i) {
        testData.emplace_back(generateRandomString(_stringLength), rand() % 1000);
    }

    HashMap<std::string, int> customMap(_testSize);
    std::unordered_map<std::string, int> stdMap;

    auto start = std::chrono::high_resolution_clock::now();
    for (const auto& [key, value] : testData) {
        customMap.insert(key, value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Custom HashMap insert time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";


    start = std::chrono::high_resolution_clock::now();
    for (const auto& [key, value] : testData) {
        stdMap[key] = value;
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "std::unordered_map insert time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}


void HashMapTest::testGet() {
    std::vector<std::pair<std::string, int>> testData;
    for (size_t i = 0; i < _testSize; ++i) {
        testData.emplace_back(generateRandomString(_stringLength), rand() % 1000);
    }

    HashMap<std::string, int> customMap(_testSize);
    std::unordered_map<std::string, int> stdMap;

    for (const auto& [key, value] : testData) {
        customMap.insert(key, value);
        stdMap[key] = value;
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (const auto& [key, value] : testData) {
        customMap.get(key);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Custom HashMap get time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    for (const auto& [key, value] : testData) {
        stdMap.at(key);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "std::unordered_map get time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}

void HashMapTest::testContains() {
    std::vector<std::pair<std::string, int>> testData;
    for (size_t i = 0; i < _testSize; ++i) {
        testData.emplace_back(generateRandomString(_stringLength), rand() % 1000);
    }

    HashMap<std::string, int> customMap(_testSize);
    std::unordered_map<std::string, int> stdMap;

    for (const auto& [key, value] : testData) {
        customMap.insert(key, value);
        stdMap[key] = value;
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (const auto& [key, value] : testData) {
        customMap.contains(key);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Custom HashMap contains time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    for (const auto& [key, value] : testData) {
        stdMap.count(key);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "std::unordered_map contains time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}
