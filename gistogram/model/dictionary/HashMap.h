#ifndef LABA3_HASHMAP_H
#define LABA3_HASHMAP_H

#include "../../../collectionunqptr/dinamicarray/DynamicArray.h"
#include "Pair.h"
#include "utils/HashUtil.h"
#include <functional>

constexpr double MAX_LOAD_FACTOR = 0.75;
constexpr double MIN_LOAD_FACTOR = 0.25;
constexpr size_t INITIAL_CAPACITY = 8;

template<class K, class V>
class HashMap {
private:
    class Node {
    public:
        Pair<K, V> pair;
        UnqPtr<Node> next;

        Node(const Pair<K, V>& pair, UnqPtr<Node>&& next = nullptr)
            : pair(pair), next(std::move(next)) {}
    };

    DynamicArray<UnqPtr<Node>> buckets;

    size_t size_;

    size_t hashFunction(const K& key) const {
        return HashUtil::hashValue(key);
    }

    void resize(size_t newCapacity) {
        DynamicArray<UnqPtr<Node>> newBuckets(newCapacity);
        for (size_t i = 0; i < newBuckets.size(); ++i) {
            newBuckets.set(i, nullptr);
        }

        for (size_t i = 0; i < buckets.size(); ++i) {
            UnqPtr<Node> current = std::move(buckets[i]);
            while (current) {
                size_t newIndex = hashFunction(current->pair.getKey()) % newCapacity;
                UnqPtr<Node> nextNode = std::move(current->next);
                current->next = std::move(newBuckets[newIndex]);
                newBuckets.set(newIndex, std::move(current));
                current = std::move(nextNode);
            }
        }

        buckets = std::move(newBuckets);
    }

    void ensureCapacity() {
        if (static_cast<double>(size_) / buckets.size() > MAX_LOAD_FACTOR) {
            resize(buckets.size() * 2);
        }
    }

    void shrinkCapacity() {
        if (static_cast<double>(size_) / buckets.size() < MIN_LOAD_FACTOR && buckets.size() > INITIAL_CAPACITY) {
            resize(buckets.size() / 2);
        }
    }

public:
    HashMap() : buckets(INITIAL_CAPACITY), size_(0) {
        for (size_t i = 0; i < buckets.size(); ++i) {
            buckets.set(i, nullptr);
        }
    }

    ~HashMap() {
        clear();
    }

    void put(const K& key, const V& value) {
        size_t index = hashFunction(key) % buckets.size();
        Node* current = buckets[index].getValue();
        while (current) {
            if (current->pair.getKey() == key) {
                current->pair = Pair<K, V>(key, value);
                return;
            }
            current = current->next.getValue();
        }

        buckets.set(index, new Node(Pair<K, V>(key, value), std::move(buckets[index])));
        ++size_;
        ensureCapacity();
    }

    bool get(const K& key, V& value) const {
        size_t index = hashFunction(key) % buckets.size();
        Node* current = buckets[index].getValue();
        while (current) {
            if (current->pair.getKey() == key) {
                value = current->pair.getValue();
                return true;
            }
            current = current->next.getValue();
        }
        return false;
    }

    V get(const K& key) const {
        V value;
        if (get(key, value)) {
            return value;
        }
        throw std::runtime_error("Key not found");
    }

    bool containsKey(const K& key) const {
        size_t index = hashFunction(key) % buckets.size();
        Node* current = buckets[index].getValue();
        while (current) {
            if (current->pair.getKey() == key) {
                return true;
            }
            current = current->next.getValue();
        }
        return false;
    }

    void remove(const K& key) {
        size_t index = hashFunction(key) % buckets.size();
        Node* current = buckets[index].getValue();
        Node* prev = nullptr;

        while (current) {
            if (current->pair.getKey() == key) {
                if (prev) {
                    prev->next = std::move(current->next);
                } else {
                    buckets.set(index, std::move(current->next));
                }
                --size_;
                shrinkCapacity();
                return;
            }
            prev = current;
            current = current->next.getValue();
        }
    }

    size_t size() const {
        return size_;
    }

    bool isEmpty() const {
        return size_ == 0;
    }

    V operator[](const K& key) const {
        return get(key);
    }




    DynamicArray<K> getKeys() const {
        DynamicArray<K> keys;
        for (size_t i = 0; i < buckets.size(); ++i) {
            Node* current = buckets[i].getValue();
            while (current) {
                keys.add(current->pair.getKey());
                current = current->next.getValue();
            }
        }
        return keys;
    }

    DynamicArray<V> getValues() const {
        DynamicArray<V> values;
        for (size_t i = 0; i < buckets.size(); ++i) {
            Node* current = buckets[i].getValue();
            while (current) {
                values.add(current->pair.getValue());
                current = current->next.getValue();
            }
        }
        return values;
    }


    class Iterator {
    private:
        const DynamicArray<UnqPtr<Node>>& buckets;
        size_t bucketIndex;
        Node* currentNode;

        void advanceToNextValidBucket() {
            while (bucketIndex < buckets.size() && !buckets[bucketIndex]) {
                ++bucketIndex;
            }
            currentNode = (bucketIndex < buckets.size()) ? buckets[bucketIndex].getValue() : nullptr;
        }

    public:
        Iterator(const DynamicArray<UnqPtr<Node>>& buckets, size_t start = 0)
            : buckets(buckets), bucketIndex(start), currentNode(nullptr) {
            advanceToNextValidBucket();
        }

        bool hasNext() const {
            return currentNode != nullptr;
        }

        void next() {
            if (!hasNext()) {
                throw std::out_of_range("Iterator out of range");
            }
            currentNode = currentNode->next ? currentNode->next.getValue() : nullptr;
            if (!currentNode) {
                ++bucketIndex;
                advanceToNextValidBucket();
            }
        }


        const Pair<K, V>& current() const {
            if (!currentNode) {
                throw std::out_of_range("Iterator out of range");
            }
            return currentNode->pair;
        }


        Iterator& operator++() {
            next();
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            next();
            return temp;
        }

        const Pair<K, V>& operator*() const {
            return current();
        }

        const Pair<K, V>* operator->() const {
            return &current();
        }

        bool operator==(const Iterator& other) const {
            return currentNode == other.currentNode && bucketIndex == other.bucketIndex;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

    };

    Iterator begin() const {
        return Iterator(buckets, 0);
    }

    Iterator end() const {
        return Iterator(buckets, buckets.size());
    }



    void clear() {
        for (size_t i = 0; i < buckets.size(); ++i) {
            buckets.set(i, nullptr);
        }
        size_ = 0;
    }
};

#endif // LABA3_HASHMAP_H
