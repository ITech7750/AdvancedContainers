#include "DictionaryTests.h"
#include <iostream>
#include "../../data/Person.h"
//#include "../../../collectionunqptr/linkedlist/LinkedListUP.h"
#include "../../gistogram/model/dictionary/Dictionary.h"
#include "../../gistogram/model/dictionary/Pair.h"
#include <cassert>

void DictionaryTests::runAllTests() {
    testAdd();
    testAddStatistic();
    testGet();
    testGetData();
    testGetStatistic();
    std::cout << "All tests passed successfully!" << std::endl;
}

void DictionaryTests::testAdd() { Dictionary<int, int> dict;
    Pair<int, int> pair(1, 42);
 dict.add(pair);
    auto data = dict.get(1);
    assert(data.size() == 1);
    assert(data[0] == 42);
}

void DictionaryTests::testAddStatistic() { Dictionary<int, int> dict;
    dict.add(Pair<int, int>(1, 10));
    dict.add(Pair<int, int>(1, 20));
    dict.add(Pair<int, int>(1, 30));
    auto sum = [](int a, int b) { return a + b; };
 dict.addStatistic(1, sum);
    auto stat = dict.getStatistic();
    assert(stat.contains(1));
}

void DictionaryTests::testGet() { Dictionary<int, int> dict;
    dict.add(Pair<int, int>(1, 100));
    dict.add(Pair<int, int>(2, 200));
 auto data1 = dict.get(1);
    auto data2 = dict.get(2);
    assert(data1.size() == 1);
    assert(data1[0] == 100);
    assert(data2.size() == 1);
    assert(data2[0] == 200);
}

void DictionaryTests::testGetData() { Dictionary<int, int> dict;
    dict.add(Pair<int, int>(1, 10));
    dict.add(Pair<int, int>(2, 20));
 auto data = dict.getData();
    assert(data.contains(1));
    assert(data.contains(2));
    assert(data[1].size() == 1 && data[1][0] == 10);
    assert(data[2].size() == 1 && data[2][0] == 20);
}

void DictionaryTests::testGetStatistic() { Dictionary<int, int> dict;
    dict.add(Pair<int, int>(1, 10));
    dict.add(Pair<int, int>(1, 20));
    auto max = [](int a, int b) { return a > b ? a : b; };
 dict.addStatistic(1, max);
    auto stats = dict.getStatistic();
    assert(stats.contains(1));
    assert(stats[1] == 20);
}
