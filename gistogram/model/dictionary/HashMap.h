#ifndef LABA3_HASHMAP_H
#define LABA3_HASHMAP_H

#include "../../../collectionunqptr/dinamicarray/DynamicArray.h"

template <class K, class V>
class HashMap {
private:
    DynamicArray<DynamicArray<V>> _values;
    DynamicArray<DynamicArray<K>> _keys;
    size_t _size;

    size_t hashCode(const K &key) const {
        size_t hash = 0;
        K k = key;
        String *raw = reinterpret_cast<String*>(&k);
        for (char c: *raw) {
            hash = hash * 31 + c;
        }
        return hash % _size;
    }

public:
    HashMap(): _size(1001) {
        _keys.resize(1001);
        _values.resize(1001);
        _keys.setSize(1001);
        _values.setSize(1001);
    }

    HashMap(size_t size): _size(size) {
        _keys.resize(size);
        _values.resize(size);
        _keys.setSize(size);
        _values.setSize(size);
    }

    // по ссылке менять значение
    void insert(const K &key, const V &value) {
        size_t hash = hashCode(key);
        auto hashKeys = _keys.get(hash);
        auto hashValues = _values.get(hash);
        bool presented = false;
        for (int i = 0;i<hashKeys.size();i++) {
            if (hashKeys[i] == key) {
                hashValues.set(i, value);
                presented = true;
            }
        }
        if (!presented) {
            hashKeys.add(key);
            hashValues.add(value);
        }
        _keys.set(hash, hashKeys);
        _values.set(hash, hashValues);
    }

    //возвращать указатель на узел
    V get(const K& key) {
        size_t hash = hashCode(key);
        auto hashKeys = _keys.get(hash);
        for (int i = 0;i<hashKeys.size();i++) {
            if (hashKeys[i] == key) {
                return _values.get(hash)[i];
            }
        }
        throw std::exception();
    }

    V operator[](const K& key) {
        size_t hash = hashCode(key);
        auto hashKeys = _keys.get(hash);
        for (int i = 0;i<hashKeys.size();i++) {
            if (hashKeys[i] == key) {
                V tmp = _values.get(hash)[i];
                return tmp;
            }
        }
        throw std::exception();
    }

    bool contains(const K& key) {
        size_t hash = hashCode(key);
        auto hashKeys = _keys.get(hash);
        for (int i = 0;i<hashKeys.size();i++) {
            if (hashKeys[i] == key) {
                return true;
            }
        }
        return false;
    }

    DynamicArray<K> getKeys() {
        DynamicArray<K> tmp;
        for (size_t i = 0;i<_size;i++) {
            DynamicArray<K> k = _keys[i];
            for (size_t j = 0;j<k.size();j++) {
                tmp.add(k[j]);
            }
        }
        return tmp;
    }


};

#endif //LABA3_HASHMAP_H
