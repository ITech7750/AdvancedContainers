#ifndef LABA3_GISTOGRAM_H
#define LABA3_GISTOGRAM_H

#include "dictionary/Dictionary.h"
#include "Parameter.h"
#include "../../collectionunqptr/linkedlist/LinkedListUP.h"
#include <iostream>
#include "../../data/Person.h"

template<class K, class V>
class Gistogram {
private:
    Dictionary<K, V> dict;
    std::vector<V> data;
    std::vector<Parameter<K, V>> parameters;
public:
    Gistogram() : dict(Dictionary<K, V>()),
                  data(std::vector<V>()),
                  parameters(std::vector<Parameter<K, V>>()) {}

    void addParameter(Parameter<K, V> param) {
        parameters.push_back(param);
    }

    void addData(V item) {
        data.push_back(item);
    }

    void calculate(bool statistic, std::function<V(V, V)> statPredicate) {
        for (int j = 0; j < parameters.size(); j++) {
            auto name = parameters[j].name;
            auto predicate = parameters[j].predicate;

            for (int i = 0; i < data.size(); i++) {

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

    void print(std::ostream &os) {
        os << "Gistogram:\n";
        os << "| data: ";
        for (auto item : this->data) {
            os << item << " ";
        }
        os << "\n| gistogram: " << "\n";
        auto hashMap = this->dict.getData();
        auto stat = this->dict.getStatistic();
        DynamicArray<K> keys = hashMap.getKeys();
        for (size_t i = 0;i<keys.size();i++) {
            K key = keys[i];
            DynamicArray<V> values = hashMap[key];
            os << "  - " << key << " : statistic: " << stat[key] << "\n";
            for (int j = 0;j< values.size();j++) {
                os << values[j] << " ";
            }
            os << "\n";
        }
    }
};

#endif //LABA3_GISTOGRAM_H
