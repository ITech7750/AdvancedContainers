#ifndef GISTOGRAM_TESTS_H
#define GISTOGRAM_TESTS_H

#include <string>


class GistogramTests {
public:
    void runAllTests();

private:
    void testAddData();
    void testAddParameter();
    void testCalculate();
    void testPrint();
    void testGetMostFrequent();
    void testCountInRange();
    void testFindMatchingValues();
    void testCalculateStatisticsForAll();
    void testClearData();
    void testClearParameters();
    void testClearAll();
    void testEmptyGistogram();

    std::string generateRandomString(size_t length);
};

#endif // GISTOGRAM_TESTS_H
