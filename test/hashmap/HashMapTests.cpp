#include "HashMapTests.h"
#include "../../gistogram/model/dictionary/HashMap.h"
#include <iostream>
#include <cassert>

void HashMapTests::runAllTests() {
    testPut();
    testGet();
    testContainsKey();
    testRemove();
    testSize();
    testIsEmpty();
    testClear();
    testRehashing();
    testIterator();
    testIteratorEmptyMap();
    testIteratorAfterClear();
    testIteratorRehashing();
}

void HashMapTests::testPut() {
    HashMap<int, std::string> map;
    map.put(1, "one");
    std::string value;
    assert(map.get(1, value) && value == "one");
    map.put(1, "uno");
    assert(map.get(1, value) && value == "uno");
    std::cout << "testPut passed.\n";
}

void HashMapTests::testGet() {
    HashMap<int, std::string> map;
    map.put(2, "two");
    std::string value;
    assert(map.get(2, value) && value == "two");
    assert(!map.get(3, value));
    std::cout << "testGet passed.\n";
}

void HashMapTests::testContainsKey() {
    HashMap<int, std::string> map;
    map.put(3, "three");
    assert(map.containsKey(3));
    assert(!map.containsKey(4));
    std::cout << "testContainsKey passed.\n";
}

void HashMapTests::testRemove() {
    HashMap<int, std::string> map;
    map.put(4, "four");
    map.remove(4);
    std::string value;
    assert(!map.get(4, value));
    assert(map.isEmpty());
    std::cout << "testRemove passed.\n";
}

void HashMapTests::testSize() {
    HashMap<int, std::string> map;
    assert(map.size() == 0);
    map.put(5, "five");
    assert(map.size() == 1);
    map.put(6, "six");
    assert(map.size() == 2);
    std::cout << "testSize passed.\n";
}

void HashMapTests::testIsEmpty() {
    HashMap<int, std::string> map;
    assert(map.isEmpty());
    map.put(7, "seven");
    assert(!map.isEmpty());
    std::cout << "testIsEmpty passed.\n";
}

void HashMapTests::testClear() {
    HashMap<int, std::string> map;
    map.put(8, "eight");
    map.put(9, "nine");
    map.clear();
    assert(map.isEmpty());
    std::cout << "testClear passed.\n";
}

void HashMapTests::testRehashing() {
    HashMap<int, std::string> map;
    for (int i = 0; i < 20; ++i) {
        map.put(i, "value" + std::to_string(i));
    }
    assert(map.size() == 20);
    std::string value;
    for (int i = 0; i < 20; ++i) {
        assert(map.get(i, value) && value == "value" + std::to_string(i));
    }
    std::cout << "testRehashing passed.\n";
}


void HashMapTests::testIterator() {
    HashMap<int, std::string> map;
    map.put(1, "one");
    map.put(2, "two");
    map.put(3, "three");

    auto it = map.begin();
    std::unordered_map<int, std::string> result;

    while (it.hasNext()) {
        const auto& pair = it.current();
        result[pair.getKey()] = pair.getValue();
        it.next();
    }

    assert(result.size() == 3);
    assert(result[1] == "one");
    assert(result[2] == "two");
    assert(result[3] == "three");

    std::cout << "testIterator passed.\n";
}

void HashMapTests::testIteratorEmptyMap() {
    HashMap<int, std::string> map;

    auto it = map.begin();
    assert(!it.hasNext());

    std::cout << "testIteratorEmptyMap passed.\n";
}

void HashMapTests::testIteratorAfterClear() {
    HashMap<int, std::string> map;
    map.put(1, "one");
    map.put(2, "two");
    map.clear();

    auto it = map.begin();
    assert(!it.hasNext());

    std::cout << "testIteratorAfterClear passed.\n";
}

void HashMapTests::testIteratorRehashing() {
    HashMap<int, std::string> map;
    for (int i = 0; i < 20; ++i) {
        map.put(i, "value" + std::to_string(i));
    }

    auto it = map.begin();
    std::unordered_map<int, std::string> result;

    while (it.hasNext()) {
        const auto& pair = it.current();
        result[pair.getKey()] = pair.getValue();
        it.next();
    }

    assert(result.size() == 20);
    for (int i = 0; i < 20; ++i) {
        assert(result[i] == "value" + std::to_string(i));
    }

    std::cout << "testIteratorRehashing passed.\n";
}

