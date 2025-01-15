#include "DictionaryTests.h"
#include "../../gistogram/model/dictionary/Dictionary.h"
#include <iostream>
#include <cassert>
#include <cstdlib>

void DictionaryTests::runAllTests() {
    testAdd();
    testAddStatistic();
    testGet();
    testContainsKey();
    testRemove();
    testClear();
    testSize();
    testIteratorHasNext();
    testIsEmpty();
    testEmptyDictionaryIterator();
    testSingleKeyMultipleValues();
    testMultipleKeys();
    testIteratorOutOfBounds();
    testBeginAndEnd();
    testIteratorEndBoundary();
}

void DictionaryTests::testAdd() {
    Dictionary<int, std::string> dict;
    Pair<int, std::string> pair(1, "one");
    dict.add(pair);
    assert(dict.containsKey(1));
    assert(dict.get(1).size() == 1);
    assert(dict.get(1)[0] == "one");
    std::cout << "testAdd passed.\n";
}

void DictionaryTests::testAddStatistic() {
    Dictionary<int, int> dict;
    dict.add(Pair<int, int>(1, 10));
    dict.add(Pair<int, int>(1, 20));
    dict.add(Pair<int, int>(1, 30));
    dict.addStatistic(1, [](int a, int b) { return a + b; });
    int statisticValue;
    assert(dict.getStatistic().get(1, statisticValue));
    assert(statisticValue == 60);
    std::cout << "testAddStatistic passed.\n";
}

void DictionaryTests::testGet() {
    Dictionary<int, std::string> dict;
    dict.add(Pair<int, std::string>(1, "one"));
    dict.add(Pair<int, std::string>(1, "uno"));
    DynamicArray<std::string> values = dict.get(1);
    assert(values.size() == 2);
    assert(values[0] == "one");
    assert(values[1] == "uno");
    std::cout << "testGet passed.\n";
}

void DictionaryTests::testContainsKey() {
    Dictionary<int, std::string> dict;
    dict.add(Pair<int, std::string>(1, "one"));
    assert(dict.containsKey(1));
    assert(!dict.containsKey(2));
    std::cout << "testContainsKey passed.\n";
}

void DictionaryTests::testRemove() {
    Dictionary<int, std::string> dict;
    dict.add(Pair<int, std::string>(1, "one"));
    dict.remove(1);
    assert(!dict.containsKey(1));
    assert(dict.isEmpty());
    std::cout << "testRemove passed.\n";
}

void DictionaryTests::testClear() {
    Dictionary<int, std::string> dict;
    dict.add(Pair<int, std::string>(1, "one"));
    dict.add(Pair<int, std::string>(2, "two"));
    dict.clear();
    assert(dict.isEmpty());
    std::cout << "testClear passed.\n";
}

void DictionaryTests::testSize() {
    Dictionary<int, std::string> dict;
    assert(dict.size() == 0);
    dict.add(Pair<int, std::string>(1, "one"));
    assert(dict.size() == 1);
    dict.add(Pair<int, std::string>(2, "two"));
    assert(dict.size() == 2);
    std::cout << "testSize passed.\n";
}

void DictionaryTests::testIsEmpty() {
    Dictionary<int, std::string> dict;
    assert(dict.isEmpty());
    dict.add(Pair<int, std::string>(1, "one"));
    assert(!dict.isEmpty());
    std::cout << "testIsEmpty passed.\n";
}

void DictionaryTests::testIteratorHasNext() {
    Dictionary<int, std::string> dict;
    dict.add(Pair<int, std::string>(1, "one"));
    dict.add(Pair<int, std::string>(2, "two"));
    auto it = dict.begin();
    assert(it.hasNext());
    it.next();
    assert(it.hasNext());
    it.next();
    assert(!it.hasNext());
    std::cout << "testIteratorHasNext passed.\n";
}

void DictionaryTests::testEmptyDictionaryIterator() {
    Dictionary<int, std::string> dict;
    auto it = dict.begin();
    assert(!it.hasNext());
    std::cout << "testEmptyDictionaryIterator passed.\n";
}

void DictionaryTests::testSingleKeyMultipleValues() {
    Dictionary<int, std::string> dict;
    dict.add(Pair<int, std::string>(1, "one"));
    dict.add(Pair<int, std::string>(1, "uno"));
    auto it = dict.begin();
    assert(it.hasNext());
    assert(it.current().getValue() == "one");
    it.next();
    assert(it.hasNext());
    assert(it.current().getValue() == "uno");
    it.next();
    assert(!it.hasNext());
    std::cout << "testSingleKeyMultipleValues passed.\n";
}

void DictionaryTests::testMultipleKeys() {
    Dictionary<int, std::string> dict;
    dict.add(Pair<int, std::string>(1, "one"));
    dict.add(Pair<int, std::string>(2, "two"));
    dict.add(Pair<int, std::string>(1, "uno"));
    auto it = dict.begin();
    assert(it.hasNext());
    it.next();
    assert(it.hasNext());
    it.next();
    assert(it.hasNext());
    it.next();
    assert(!it.hasNext());
    std::cout << "testMultipleKeys passed.\n";
}

void DictionaryTests::testIteratorOutOfBounds() {
    Dictionary<int, std::string> dict;
    dict.add(Pair<int, std::string>(1, "one"));
    auto it = dict.begin();
    try {
        it.next();
        it.next();
        assert(false); // Should not reach here
    } catch (const std::out_of_range&) {
        std::cout << "testIteratorOutOfBounds passed.\n";
    }
}

void DictionaryTests::testBeginAndEnd() {
    Dictionary<int, std::string> dict;
    dict.add(Pair<int, std::string>(1, "one"));
    auto it = dict.begin();
    assert(it.hasNext());
    it.next();
    assert(!it.hasNext());
    std::cout << "testBeginAndEnd passed.\n";
}

void DictionaryTests::testIteratorEndBoundary() {
    Dictionary<int, std::string> dict;
    dict.add(Pair<int, std::string>(1, "one"));
    auto it = dict.begin();
    it.next();
    assert(!it.hasNext());
    try {
        it.current();
        assert(false); // Should not reach here
    } catch (const std::out_of_range&) {
        std::cout << "testIteratorEndBoundary passed.\n";
    }
}

std::string DictionaryTests::generateRandomString(size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string result;
    for (size_t i = 0; i < length; ++i) {
        result += charset[rand() % (sizeof(charset) - 1)];
    }
    return result;
}
