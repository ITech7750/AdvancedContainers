#include "DataTestSuite.h"
#include "../helper/TestDataManager.h"
#include "../../sort/SorterService.h"
#include <iostream>
#include <cassert>
#include <vector>

void DataTestSuite::testSortByAgeFromFile(const std::string& filename, bool isJson) {
    auto data = isJson ? TestDataManager::loadFromJson(filename)
                       : TestDataManager::loadFromTxt(filename);

    SorterService<Person>::sort(*data, compareByAge, "quick");

    for (size_t i = 1; i < data->size(); ++i) {
        assert(data->get(i - 1).age <= data->get(i).age);
    }

    std::cout << "testSortByAgeFromFile passed for file: " << filename << "\n";
    delete data;
}

void DataTestSuite::testSortByNameFromFile(const std::string& filename, bool isJson) {
    auto data = isJson ? TestDataManager::loadFromJson(filename)
                       : TestDataManager::loadFromTxt(filename);

    SorterService<Person>::sort(*data, compareByName, "bubble");

    for (size_t i = 1; i < data->size(); ++i) {
        assert(data->get(i - 1).firstName <= data->get(i).firstName);
    }

    std::cout << "testSortByNameFromFile passed for file: " << filename << "\n";
    delete data;
}

void DataTestSuite::testSortByAgeGenerated(size_t dataSize) {
    auto data = TestDataManager::generateTestData(dataSize);

    SorterService<Person>::sort(*data, compareByAge, "insertion");

    for (size_t i = 1; i < data->size(); ++i) {
        assert(data->get(i - 1).age <= data->get(i).age);
    }

    std::cout << "testSortByAgeGenerated passed for data size: " << dataSize << "\n";
    delete data;
}

void DataTestSuite::testSortByNameGenerated(size_t dataSize) {
    auto data = TestDataManager::generateTestData(dataSize);

    SorterService<Person>::sort(*data, compareByName, "heap");

    for (size_t i = 1; i < data->size(); ++i) {
        assert(data->get(i - 1).firstName <= data->get(i).firstName);
    }

    std::cout << "testSortByNameGenerated passed for data size: " << dataSize << "\n";
    delete data;
}

void DataTestSuite::testSortPerformanceForAllAlgorithms(size_t dataSize) {
    auto dataQuick = TestDataManager::generateTestData(dataSize);
    auto dataMerge = TestDataManager::generateTestData(dataSize);
    auto dataBubble = TestDataManager::generateTestData(dataSize);
    auto dataInsertion = TestDataManager::generateTestData(dataSize);
    auto dataHeap = TestDataManager::generateTestData(dataSize);

    double quickSortTime = SorterService<Person>::measureSortTime(*dataQuick, compareByAge, "quick");
    double mergeSortTime = SorterService<Person>::measureSortTime(*dataMerge, compareByAge, "merge");
    double bubbleSortTime = SorterService<Person>::measureSortTime(*dataBubble, compareByAge, "bubble");
    double insertionSortTime = SorterService<Person>::measureSortTime(*dataInsertion, compareByAge, "insertion");
    double heapSortTime = SorterService<Person>::measureSortTime(*dataHeap, compareByAge, "heap");

    delete dataQuick;
    delete dataMerge;
    delete dataBubble;
    delete dataInsertion;
    delete dataHeap;
}

void DataTestSuite::runAllTests() {
    testSortByAgeFromFile("data.json", true);
    testSortByNameFromFile("data.txt", false);

    std::vector<size_t> sizes = {10, 100, 1000, 10000};
    for (size_t size : sizes) {
        testSortByAgeGenerated(size);
        testSortByNameGenerated(size);
        testSortPerformanceForAllAlgorithms(size);
    }
}
