#ifndef LABA3_DICTIONARY_H
#define LABA3_DICTIONARY_H

#include "Pair.h"
//#include "../../../data/Person.h"
#include "HashMap.h"
#include <functional>
#include <stdexcept>
#include <string>

class DictionaryException : public std::exception {
private:
    std::string message;
public:
    explicit DictionaryException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

template <class K, class V>
class Dictionary {
private:
    HashMap<K, DynamicArray<V>> data;
    HashMap<K, V> statistic;

public:
    Dictionary() : data(), statistic() {}

    void add(const Pair<K, V>& pair) {
        DynamicArray<V> updatedValues = data.containsKey(pair.getKey())
            ? data[pair.getKey()]
            : DynamicArray<V>();
        updatedValues.add(pair.getValue());
        data.put(pair.getKey(), updatedValues);
    }

    void addStatistic(const K& key, std::function<V(const V&, const V&)> predicate) {
        if (data.containsKey(key)) {
            const DynamicArray<V>& values = data[key];
            if (values.size() == 0) {
                throw DictionaryException("No values to compute statistics for key.");
            }

            V result = values[0];
            for (size_t i = 1; i < values.size(); ++i) {
                result = predicate(result, values[i]);
            }
            statistic.put(key, result);
        } else {
            throw DictionaryException("Key not found in data for statistic computation.");
        }
    }

    void addStatisticForAll(std::function<V(const V&, const V&)> predicate) {
        auto keys = data.getKeys();
        for (size_t i = 0; i < keys.size(); ++i) {
            addStatistic(keys[i], predicate);
        }
    }

    DynamicArray<V> get(const K& key) const {
        if (data.containsKey(key)) {
            return data[key];
        } else {
            return DynamicArray<V>();
        }
    }

    HashMap<K, DynamicArray<V>> getData() const {
        return data;
    }


    const HashMap<K, V>& getStatistic() const {
        return statistic;
    }

    bool containsKey(const K& key) const {
        return data.containsKey(key);
    }

    void remove(const K& key) {
        if (data.containsKey(key)) {
            data.remove(key);
        }
        if (statistic.containsKey(key)) {
            statistic.remove(key);
        }
    }

    void clear() {
        data.clear();
        statistic.clear();
    }

    size_t size() const {
        return data.size();
    }

    bool isEmpty() const {
        return data.isEmpty();
    }

    DynamicArray<V>& operator[](const K& key) {
        if (!data.containsKey(key)) {
            data.put(key, DynamicArray<V>());
        }
        return data[key];
    }



public:
    class Iterator {
    private:
        typename HashMap<K, DynamicArray<V>>::Iterator mapIterator;
        const HashMap<K, DynamicArray<V>>& data;
        size_t valueIndex;
        bool atEnd;

        void advanceToNextValid() {
            while (mapIterator.hasNext() &&
                   (valueIndex >= mapIterator.current().getValue().size())) {
                mapIterator.next();
                valueIndex = 0;
                   }
            if (!mapIterator.hasNext()) {
                atEnd = true;
            }
        }


    public:
        Iterator(const HashMap<K, DynamicArray<V>>& data, bool isEnd = false)
            : data(data), mapIterator(isEnd ? data.end() : data.begin()),
              valueIndex(0), atEnd(isEnd) {
            if (!isEnd) {
                advanceToNextValid();
            }
        }

        bool hasNext() const {
            return !atEnd;
        }

        void next() {
            if (!hasNext()) {
                throw std::out_of_range("Iterator out of range");
            }

            ++valueIndex;
            advanceToNextValid();
        }

        Pair<K, V> current() const {
            if (!hasNext()) {
                throw std::out_of_range("Iterator out of range");
            }
            const auto& key = mapIterator.current().getKey();
            const auto& values = mapIterator.current().getValue();
            return Pair<K, V>(key, values[valueIndex]);
        }

        Iterator& operator++() {
            next();
            return *this;
        }

        Pair<K, V> operator*() const {
            return current();
        }

        bool operator==(const Iterator& other) const {
            return atEnd == other.atEnd && mapIterator == other.mapIterator && valueIndex == other.valueIndex;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }


    };


    Iterator begin() const {
        return Iterator(data);
    }

    Iterator end() const {
        return Iterator(data, true);
    }


};

#endif // LABA3_DICTIONARY_H
