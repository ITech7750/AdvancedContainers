#include "GistogramTests.h"
#include "../../gistogram/model/Gistogram.h"
#include <cassert>
#include <iostream>

void GistogramTests::runAllTests() {
    testAddData();
    testAddParameter();
    testCalculate();
    testPrint();
    testGetMostFrequent();
    testCountInRange();
    testFindMatchingValues();
    testCalculateStatisticsForAll();
    testClearData();
    testClearParameters();
    testClearAll();
    testEmptyGistogram();
}

void GistogramTests::testAddData() {
    Gistogram<std::string, int> gistogram;
    gistogram.addData(5);
    gistogram.addData(10);
    assert(gistogram.getData().size() == 2);
    assert(gistogram.getData()[0] == 5);
    assert(gistogram.getData()[1] == 10);
}

void GistogramTests::testAddParameter() {
    Gistogram<std::string, int> gistogram;
    Parameter<std::string, int> param("age", [](int value) { return value > 18; });
    gistogram.addParameter(param);
    assert(gistogram.getParameters().size() == 1);
    assert(gistogram.getParameters()[0].name == "age");
}

void GistogramTests::testCalculate() {
    Gistogram<std::string, int> gistogram;
    gistogram.addData(5);
    gistogram.addData(10);
    Parameter<std::string, int> param("age", [](int value) { return value > 0; });
    gistogram.addParameter(param);
    gistogram.calculate(true, std::plus<int>());
    assert(gistogram.getData().size() == 2);
}

void GistogramTests::testPrint() {
    Gistogram<std::string, int> gistogram;
    gistogram.addData(5);
    gistogram.addData(10);
    Parameter<std::string, int> param("age", [](int value) { return value > 0; });
    gistogram.addParameter(param);
}

void GistogramTests::testGetMostFrequent() {
    Gistogram<std::string, int> gistogram;
    gistogram.addData(5);
    gistogram.addData(10);
    gistogram.addData(5);
    int mostFrequent = gistogram.getMostFrequent();
    assert(mostFrequent == 5);
}

void GistogramTests::testCountInRange() {
    Gistogram<std::string, int> gistogram;
    gistogram.addData(5);
    gistogram.addData(10);
    gistogram.addData(15);
    size_t count = gistogram.countInRange(5, 10);
    assert(count == 2);
}

void GistogramTests::testFindMatchingValues() {
    Gistogram<std::string, int> gistogram;
    gistogram.addData(5);
    gistogram.addData(10);
    gistogram.addData(15);
    auto result = gistogram.findMatchingValues([](const int& value) { return value > 5; });
    assert(result.size() == 2);
    assert(result[0] == 10);
    assert(result[1] == 15);
}

void GistogramTests::testCalculateStatisticsForAll() {
    Gistogram<std::string, int> gistogram;
    gistogram.addData(5);
    gistogram.addData(10);
    gistogram.addData(15);
    gistogram.calculateStatisticsForAll([](int a, int b) { return a + b; });
}

void GistogramTests::testClearData() {
    Gistogram<std::string, int> gistogram;
    gistogram.addData(5);
    gistogram.addData(10);
    gistogram.clearData();
    assert(gistogram.getData().size() == 0);
}

void GistogramTests::testClearParameters() {
    Gistogram<std::string, int> gistogram;
    Parameter<std::string, int> param("age", [](int value) { return value > 0; });
    gistogram.addParameter(param);
    gistogram.clearParameters();
    assert(gistogram.getParameters().size() == 0);
}

void GistogramTests::testClearAll() {
    Gistogram<std::string, int> gistogram;
    gistogram.addData(5);
    gistogram.addData(10);
    Parameter<std::string, int> param("age", [](int value) { return value > 0; });
    gistogram.addParameter(param);
    gistogram.clearAll();
    assert(gistogram.getData().size() == 0);
    assert(gistogram.getParameters().size() == 0);
}

void GistogramTests::testEmptyGistogram() {
    Gistogram<std::string, int> gistogram;
    assert(gistogram.getData().size() == 0);
    assert(gistogram.getParameters().size() == 0);
}

std::string GistogramTests::generateRandomString(size_t length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string randomStr;
    for (size_t i = 0; i < length; ++i) {
        randomStr += charset[rand() % (sizeof(charset) - 1)];
    }
    return randomStr;
}
