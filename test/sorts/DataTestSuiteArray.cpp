#include "DataTestSuiteArray.h"
#include "../helper/TestDataManagerArray.h"
#include "../../sort/SorterServiceArray.h"
#include <iostream>
#include <cassert>
#include <vector>

void DataTestSuiteArray::testSortByAgeFromFile(const std::string& filename, bool isJson) {
    auto data = isJson ? TestDataManagerArray::loadFromJson(filename)
                       :TestDataManagerArray::loadFromTxt(filename);
    /*std::cout << "Before sort:\n";
    for (size_t i = 0; i < data->size(); ++i) {
        std::cout << data->get(i).firstName << " (" << data->get(i).age << ")\n";
    }*/

    SorterServiceArray<Person>::sort(*data, compareByAge, "quick");
    //std::sort(data->begin(), data->end(), compareByAge);

    /*std::cout << "After sort:\n";
    for (size_t i = 0; i < data->size(); ++i) {
        std::cout << data->get(i).firstName << " (" << data->get(i).age << ")\n";
    }*/


    for (size_t i = 1; i < data->size(); ++i) {
        assert(data->get(i - 1).age <= data->get(i).age);
    }



    std::cout << "testSortByAgeFromFile passed for file: " << filename << "\n";
    delete data;
}

void DataTestSuiteArray::testSortByNameFromFile(const std::string& filename, bool isJson) {
    auto data = isJson ? TestDataManagerArray::loadFromJson(filename)
                       : TestDataManagerArray::loadFromTxt(filename);

    SorterServiceArray<Person>::sort(*data, compareByName, "bubble");

    for (size_t i = 1; i < data->size(); ++i) {
        assert(data->get(i - 1).firstName <= data->get(i).firstName);
    }

    std::cout << "testSortByNameFromFile passed for file: " << filename << "\n";
    delete data;
}

void DataTestSuiteArray::testSortByAgeGenerated(size_t dataSize) {
    auto data = TestDataManagerArray::generateTestData(dataSize);

    SorterServiceArray<Person>::sort(*data, compareByAge, "insertion");

    for (size_t i = 1; i < data->size(); ++i) {
        assert(data->get(i - 1).age <= data->get(i).age);
    }

    std::cout << "testSortByAgeGenerated passed for data size: " << dataSize << "\n";
    delete data;
}

void DataTestSuiteArray::testSortByNameGenerated(size_t dataSize) {
    auto data = TestDataManagerArray::generateTestData(dataSize);

    SorterServiceArray<Person>::sort(*data, compareByName, "heap");

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

    /*std::cout << "Before sort:\n";
    for (size_t i = 0; i < dataQuick->size(); ++i) {
        std::cout << dataQuick->get(i).firstName << "\n";
    }*/

    double quickSortTime = SorterServiceArray<Person>::measureSortTime(*dataQuick, compareByAge, "quick");
    double mergeSortTime = SorterServiceArray<Person>::measureSortTime(*dataMerge, compareByAge, "merge");
    double bubbleSortTime = SorterServiceArray<Person>::measureSortTime(*dataBubble, compareByAge, "bubble");
    double insertionSortTime = SorterServiceArray<Person>::measureSortTime(*dataInsertion, compareByAge, "insertion");
    double heapSortTime = SorterServiceArray<Person>::measureSortTime(*dataHeap, compareByAge, "heap");

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

void DataTestSuiteArray::runAllTests() {
    testSortByAgeFromFile("data.json", true);
    testSortByNameFromFile("data.txt", false);

    DynamicArray<size_t> sizes = {10, 100, 1000, 10000};
    for (size_t i = 0; i < sizes.size(); ++i) {
        testSortByAgeGenerated(sizes.get(i));
        testSortByNameGenerated(sizes.get(i));
        testSortPerformanceForAllAlgorithms(sizes.get(i));
    }
}
