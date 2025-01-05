#ifndef LABA3_DICTIONARY_H
#define LABA3_DICTIONARY_H

#include "../../../collectionunqptr/linkedlist/LinkedListUP.h"
#include "Pair.h"
#include "../../../data/Person.h"
#include "HashMap.h"
#include <functional>

template <class K, class V>
class Dictionary {
private:
    //просто V
    HashMap<K, DynamicArray<V>> data;
    HashMap<K, V> statistic;

public:
    Dictionary(): data(HashMap<K,DynamicArray<V>>()), statistic(HashMap<K, V>()) {}

    void add(Pair<K, V> pair) {
        DynamicArray<V> tmp;
        if (!data.contains(pair.getKey())) {
            tmp = Array<V>();
        } else {
            tmp = data.get(pair.getKey());
        }
        tmp.add(pair.getValue());
        data.insert(pair.getKey(), tmp);
    }

    void addStatistic(K key, std::function<V(V, V)> predicate) {
        if (data.contains(key)) {
            V avg = data[key][0];
            V tt = data[key][data[key].size() - 1];
            for (int i = 0;i<data[key].size();i++) {
                auto p = data[key][i];
                avg = predicate(p, avg);
            }
            statistic.insert(key, avg);
        }
    }

    std::vector<V> get(const K &key) {
        if (data.contains(key)) {
            return data[key];
        } else {
            return std::vector<V>();
        }
    }

    HashMap<K, DynamicArray<V>> getData() {
        return data;
    }

    HashMap<K, V> getStatistic() {
        return statistic;
    }
};


#endif //LABA3_DICTIONARY_H
