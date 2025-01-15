#include "DictionaryTest.h"

#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <random>
#include "../../gistogram/model/dictionary/Dictionary.h"

DictionaryTest::DictionaryTest(size_t testSize, size_t stringLength)
    : _testSize(testSize), _stringLength(stringLength) {}

std::string DictionaryTest::generateRandomString(size_t length) {
    static std::mt19937 generator(std::random_device{}());
    static const char charset[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static std::uniform_int_distribution<size_t> dist(0, sizeof(charset) - 2);
    std::string result;
    result.reserve(length);
    for (size_t i = 0; i < length; ++i) {
        result += charset[dist(generator)];
    }
    return result;
}

void DictionaryTest::testAdd() {
    std::vector<Pair<std::string, int>> testData;
    for (size_t i = 0; i < _testSize; ++i) {
        testData.emplace_back(generateRandomString(_stringLength), rand() % 1000);
    }

    Dictionary<std::string, int> customDictionary;
    std::unordered_map<std::string, std::vector<int>> stdMap;

    auto start = std::chrono::high_resolution_clock::now();
    for (const auto& pair : testData) {
        customDictionary.add(pair);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Custom Dictionary add time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    for (const auto& pair : testData) {
        stdMap[pair.getKey()].push_back(pair.getValue());
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "std::unordered_map add time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}

void DictionaryTest::testGet() {
    std::vector<Pair<std::string, int>> testData;
    for (size_t i = 0; i < _testSize; ++i) {
        testData.emplace_back(generateRandomString(_stringLength), rand() % 1000);
    }

    Dictionary<std::string, int> customDictionary;
    std::unordered_map<std::string, std::vector<int>> stdMap;

    for (const auto& pair : testData) {
        customDictionary.add(pair);
        stdMap[pair.getKey()].push_back(pair.getValue());
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (const auto& pair : testData) {
        customDictionary.get(pair.getKey());
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Custom Dictionary get time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    for (const auto& pair : testData) {
        auto it = stdMap.find(pair.getKey());
        if (it != stdMap.end()) {
            auto value = it->second;
        }
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "std::unordered_map get time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}

void DictionaryTest::testStatistic() {
    std::vector<Pair<std::string, int>> testData;
    for (size_t i = 0; i < _testSize; ++i) {
        testData.emplace_back(generateRandomString(_stringLength), rand() % 1000);
    }

    Dictionary<std::string, int> customDictionary;

    for (const auto& pair : testData) {
        customDictionary.add(pair);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (const auto& pair : testData) {
        customDictionary.addStatistic(pair.getKey(), [](int a, int b) { return a + b; });
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Custom Dictionary statistic calculation time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    // Testing for all statistics
    start = std::chrono::high_resolution_clock::now();
    customDictionary.addStatisticForAll([](int a, int b) { return a + b; });
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Custom Dictionary all statistics calculation time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}