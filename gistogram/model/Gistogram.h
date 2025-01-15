#ifndef LABA3_GISTOGRAM_H
#define LABA3_GISTOGRAM_H

#include "dictionary/Dictionary.h"
#include "Parameter.h"
#include "../../collectionunqptr/linkedlist/LinkedListUP.h"
#include <iostream>
#include "../../data/Person.h"
#include <algorithm>

template<class K, class V>
class Gistogram {
private:
    Dictionary<K, V> dict;
    DynamicArray<V> data;
    DynamicArray<Parameter<K, V>> parameters;

public:
    Gistogram() : dict(Dictionary<K, V>()),
                  data(DynamicArray<V>()),
                  parameters(DynamicArray<Parameter<K, V>>()) {}

    DynamicArray<V> getData() const {
        return data;
    }

    DynamicArray<Parameter<K, V>> getParameters() const {
        return parameters;
    }

    void addParameter(Parameter<K, V> param) {
        parameters.add(param);
    }

    void addData(V item) {
        data.add(item);
    }

    void calculate(bool statistic, std::function<V(V, V)> statPredicate) {
        for (size_t j = 0; j < parameters.size(); j++) {
            auto name = parameters[j].name;
            auto predicate = parameters[j].predicate;

            for (size_t i = 0; i < data.size(); i++) {
                auto item = data[i];
                if (predicate(item)) {
                    dict.add(Pair(name, item));
                }
            }
            if (statistic) {
                dict.addStatistic(name, statPredicate);
            }
        }
    }

    void print(std::ostream& os) {
        os << "Gistogram:\n";
        os << "| data: ";

        for (const auto& item : this->data) {
            os << item << " ";
        }
        os << "\n| gistogram: \n";

        const auto& hashMap = this->dict.getData();
        const auto& stat = this->dict.getStatistic();
        DynamicArray<K> keys = hashMap.getKeys();
        for (size_t i = 0; i < keys.size(); i++) {
            const K& key = keys[i];
            const DynamicArray<V>& values = hashMap.get(key);
            os << "  - " << key << " : statistic: " << stat.get(key) << "\n";
            for (size_t j = 0; j < values.size(); j++) {
                os << values[j] << " ";
            }
            os << "\n";
        }
    }


    V getMostFrequent() const {
        if (data.isEmpty()) {
            throw std::runtime_error("Data is empty.");
        }

        HashMap<V, size_t> frequencyMap;
        for (size_t i = 0; i < data.size(); i++) {
            V value = data[i];
            size_t freq = frequencyMap.containsKey(value) ? frequencyMap[value] : 0;
            frequencyMap.put(value, freq + 1);
        }

        V mostFrequent = data[0];
        size_t maxFrequency = 0;
        for (const auto& pair : frequencyMap) {
            if (pair.getValue() > maxFrequency) {
                mostFrequent = pair.getKey();
                maxFrequency = pair.getValue();
            }
        }

        return mostFrequent;
    }

    size_t countInRange(V lowerBound, V upperBound) const {
        size_t count = 0;
        for (size_t i = 0; i < data.size(); i++) {
            V value = data[i];
            if (value >= lowerBound && value <= upperBound) {
                count++;
            }
        }
        return count;
    }

    DynamicArray<V> findMatchingValues(std::function<bool(const V&)> condition) const {
        DynamicArray<V> result;
        for (size_t i = 0; i < data.size(); i++) {
            if (condition(data[i])) {
                result.add(data[i]);
            }
        }
        return result;
    }

    void calculateStatisticsForAll(std::function<V(V, V)> statPredicate) {
        for (size_t i = 0; i < data.size(); i++) {
            V value = data[i];
            /* TODO */
        }
    }

    void clearData() {
        data.clear();
    }

    void clearParameters() {
        parameters.clear();
    }

    void clearAll() {
        data.clear();
        parameters.clear();
        dict.clear();
    }
};

#endif // LABA3_GISTOGRAM_H
