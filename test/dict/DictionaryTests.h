#ifndef DICTIONARY_TESTS_H
#define DICTIONARY_TESTS_H

#include <string>

class DictionaryTests {
public:
    void runAllTests();

private:
    void testAdd();
    void testAddStatistic();
    void testGet();
    void testContainsKey();
    void testRemove();
    void testClear();
    void testSize();
    void testIteratorHasNext();
    void testIsEmpty();
    void testEmptyDictionaryIterator();
    void testSingleKeyMultipleValues();
    void testMultipleKeys();
    void testIteratorOutOfBounds();
    void testBeginAndEnd();
    void testIteratorEndBoundary();

    std::string generateRandomString(size_t length);
};

#endif // DICTIONARY_TESTS_H
