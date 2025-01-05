#ifndef LABA3_PAIR_H
#define LABA3_PAIR_H

#include <typeindex>

template <class K, class V>
class Pair {
private:
    K _key;
    V _value;
public:
    Pair(const K &key, const V &value): _key(key), _value(value) {
    }

    K getKey() {
        return _key;
    }

    V getValue() {
        return _value;
    }

    Pair<K, V> copy(V value) {
        return Pair(_key, value);
    }

    bool equal(const Pair<K, V>& other) {
        return _value == other._value;
    }

    bool operator==(const Pair<K, V>& other) {
        return equal(other);
    }

};

#endif //LABA3_PAIR_H
