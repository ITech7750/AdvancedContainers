#include "DataTestSuiteArray.h"
#include "../helper/TestDataManagerArray.h"
#include "../../sort/SorterServiceArray.h"
#include <iostream>
#include <cassert>
#include <vector>

void DataTestSuiteArray::testSortByAgeFromFile(const std::string& filename, bool isJson) {
    auto data = isJson ? TestDataManagerArray::loadFromJson(filename)
                       :TestDataManagerArray::loadFromTxt(filename);

    SorterService<Person>::sort(*data, compareByAge, "quick");

    for (size_t i = 1; i < data->size(); ++i) {
        assert(data->get(i - 1).age <= data->get(i).age);
    }

    std::cout << "testSortByAgeFromFile passed for file: " << filename << "\n";
    delete data;
}

void DataTestSuiteArray::testSortByNameFromFile(const std::string& filename, bool isJson) {
    auto data = isJson ? TestDataManagerArray::loadFromJson(filename)
                       : TestDataManagerArray::loadFromTxt(filename);

    SorterService<Person>::sort(*data, compareByName, "bubble");

    for (size_t i = 1; i < data->size(); ++i) {
        assert(data->get(i - 1).firstName <= data->get(i).firstName);
    }

    std::cout << "testSortByNameFromFile passed for file: " << filename << "\n";
    delete data;
}

void DataTestSuiteArray::testSortByAgeGenerated(size_t dataSize) {
    auto data = TestDataManagerArray::generateTestData(dataSize);

    SorterService<Person>::sort(*data, compareByAge, "insertion");

    for (size_t i = 1; i < data->size(); ++i) {
        assert(data->get(i - 1).age <= data->get(i).age);
    }

    std::cout << "testSortByAgeGenerated passed for data size: " << dataSize << "\n";
    delete data;
}

void DataTestSuiteArray::testSortByNameGenerated(size_t dataSize) {
    auto data = TestDataManagerArray::generateTestData(dataSize);

    SorterService<Person>::sort(*data, compareByName, "heap");

    for (size_t i = 1; i < data->size(); ++i) {
        assert(data->get(i - 1).firstName <= data->get(i).firstName);
    }

    std::cout << "testSortByNameGenerated passed for data size: " << dataSize << "\n";
    delete data;
}

void DataTestSuiteArray::testSortPerformanceForAllAlgorithms(size_t dataSize) {
    auto dataQuick = TestDataManagerArray::generateTestData(dataSize);
    auto dataMerge = TestDataManagerArray::generateTestData(dataSize);
    auto dataBubble = TestDataManagerArray::generateTestData(dataSize);
    auto dataInsertion = TestDataManagerArray::generateTestData(dataSize);
    auto dataHeap = TestDataManagerArray::generateTestData(dataSize);

    double quickSortTime = SorterService<Person>::measureSortTime(*dataQuick, compareByAge, "quick");
    double mergeSortTime = SorterService<Person>::measureSortTime(*dataMerge, compareByAge, "merge");
    double bubbleSortTime = SorterService<Person>::measureSortTime(*dataBubble, compareByAge, "bubble");
    double insertionSortTime = SorterService<Person>::measureSortTime(*dataInsertion, compareByAge, "insertion");
    double heapSortTime = SorterService<Person>::measureSortTime(*dataHeap, compareByAge, "heap");

    delete dataQuick;
    //delete dataMerge;
    delete dataBubble;
    delete dataInsertion;
    delete dataHeap;

}

void DataTestSuiteArray::runAllTests() {
    testSortByAgeFromFile("data.json", true);
    testSortByNameFromFile("data.txt", false);

    std::vector<size_t> sizes = {10, 100, 1000, 10000};
    for (size_t size : sizes) {
        testSortByAgeGenerated(size);
        testSortByNameGenerated(size);
        testSortPerformanceForAllAlgorithms(size);
    }
}
