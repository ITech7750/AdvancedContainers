#ifndef LAB2_ARRAYSEQUENCE_H
#define LAB2_ARRAYSEQUENCE_H

#include "../Sequence.h"
#include "../../../unqptr/UnqPtr.h"
#include <algorithm>
#include <stdexcept>

template<class T>
class ArraySequence : public Sequence<T> {
private:
    UnqPtr<T[]> items;  // Используем UnqPtr для массива
    size_t length;

public:
    ArraySequence() : items(nullptr), length(0) {}

    ArraySequence(T* _items, size_t count)
        : items(new T[count]), length(count) {
        std::copy(_items, _items + count, items.getValue());
    }

    T getFirst() override {
        if (isEmpty()) throw std::runtime_error("Sequence is empty.");
        return items[0];
    }

    T getLast() override {
        if (isEmpty()) throw std::runtime_error("Sequence is empty.");
        return items[length - 1];
    }

    T get(size_t index) override {
        if (index >= length) throw std::runtime_error("Index out of range.");
        return items[index];
    }

    size_t size() const override {
        return length;
    }

    bool isEmpty() override {
        return length == 0;
    }

    ArraySequence<T>* getSubsequence(size_t start, size_t end) override {
        if (start > end || end >= length) throw std::runtime_error("Invalid range.");
        auto subItems = new T[end - start + 1];
        std::copy(items.getValue() + start, items.getValue() + end + 1, subItems);
        return new ArraySequence(subItems, end - start + 1);
    }

    ArraySequence<T>* concat(const Sequence<T>& other) override {
        size_t newLength = length + other.size();
        auto newItems = new T[newLength];
        std::copy(items.getValue(), items.getValue() + length, newItems);
        for (size_t i = 0; i < other.size(); ++i) {
            newItems[length + i] = other.get(i);
        }
        return new ArraySequence(newItems, newLength);
    }

    void sort() {
        std::sort(items.getValue(), items.getValue() + length);
    }
};

#endif // LAB2_ARRAYSEQUENCE_H
