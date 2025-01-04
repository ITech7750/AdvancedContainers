#include "DataTestSuiteList.h"
#include "../helper/TestDataManagerList.h"
#include "../../sort/SorterServiceList.h"
#include <iostream>
#include <cassert>
#include "../../collectionunqptr/dinamicarray/DynamicArray.h"
#include <vector>

void DataTestSuiteList::testSortByAgeFromFile(const std::string& filename, bool isJson) {
    auto data = isJson ? TestDataManagerList::loadFromJson(filename)
                       : TestDataManagerList::loadFromTxt(filename);

    SorterServiceList<Person>::sort(*data, compareByAge, "quick");

    for (size_t i = 1; i < data->size(); ++i) {
        assert(data->get(i - 1).age <= data->get(i).age);
    }

    std::cout << "testSortByAgeFromFile passed for file: " << filename << "\n";
    delete data;
}

void DataTestSuiteList::testSortByNameFromFile(const std::string& filename, bool isJson) {
    auto data = isJson ? TestDataManagerList::loadFromJson(filename)
                       : TestDataManagerList::loadFromTxt(filename);

    SorterServiceList<Person>::sort(*data, compareByName, "bubble");

    for (size_t i = 1; i < data->size(); ++i) {
        assert(data->get(i - 1).firstName <= data->get(i).firstName);
    }

    std::cout << "testSortByNameFromFile passed for file: " << filename << "\n";
    delete data;
}

void DataTestSuiteList::testSortByAgeGenerated(size_t dataSize) {
    auto data = TestDataManagerList::generateTestData(dataSize);

    SorterServiceList<Person>::sort(*data, compareByAge, "insertion");

    for (size_t i = 1; i < data->size(); ++i) {
        assert(data->get(i - 1).age <= data->get(i).age);
    }

    std::cout << "testSortByAgeGenerated passed for data size: " << dataSize << "\n";
    delete data;
}

void DataTestSuiteList::testSortByNameGenerated(size_t dataSize) {
    auto data = TestDataManagerList::generateTestData(dataSize);

    SorterServiceList<Person>::sort(*data, compareByName, "heap");

    for (size_t i = 1; i < data->size(); ++i) {
        assert(data->get(i - 1).firstName <= data->get(i).firstName);
    }

    std::cout << "testSortByNameGenerated passed for data size: " << dataSize << "\n";
    delete data;
}

void DataTestSuiteList::testSortPerformanceForAllAlgorithms(size_t dataSize) {
    auto dataQuick = TestDataManagerList::generateTestData(dataSize);
    auto dataMerge = TestDataManagerList::generateTestData(dataSize);
    auto dataBubble = TestDataManagerList::generateTestData(dataSize);
    auto dataInsertion = TestDataManagerList::generateTestData(dataSize);
    auto dataHeap = TestDataManagerList::generateTestData(dataSize);

    /*std::cout << "Before sort:\n";
    for (size_t i = 0; i < dataQuick->size(); ++i) {
        std::cout << dataQuick->get(i).firstName << "\n";
    }*/


    double quickSortTime = SorterServiceList<Person>::measureSortTime(*dataQuick, compareByAge, "quick");
    double mergeSortTime = SorterServiceList<Person>::measureSortTime(*dataMerge, compareByAge, "merge");
    double bubbleSortTime = SorterServiceList<Person>::measureSortTime(*dataBubble, compareByAge, "bubble");
    double insertionSortTime = SorterServiceList<Person>::measureSortTime(*dataInsertion, compareByAge, "insertion");
    double heapSortTime = SorterServiceList<Person>::measureSortTime(*dataHeap, compareByAge, "heap");

    /*std::cout << "After sort:\n";
    for (size_t i = 0; i < dataQuick->size(); ++i) {
        std::cout << dataQuick->get(i).firstName << "\n";
    }*/

    delete dataQuick;
    delete dataMerge;
    delete dataBubble;
    delete dataInsertion;
    delete dataHeap;
}

void DataTestSuiteList::runAllTests() {
    testSortByAgeFromFile("data.json", true);
    testSortByNameFromFile("data.json", false);

    DynamicArray<size_t> sizes = {10, 100, 1000, 10000};
    for (size_t i = 0; i < sizes.size(); ++i) {
        testSortByAgeGenerated(sizes.get(i));
        testSortByNameGenerated(sizes.get(i));
        testSortPerformanceForAllAlgorithms(sizes.get(i));
    }
}
