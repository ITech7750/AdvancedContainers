#ifndef DYNAMICARRAYADAPTER_H
#define DYNAMICARRAYADAPTER_H

#include "../sequence/MutableSequence.h"
#include "DynamicArray.h"

template<typename T>
class DynamicArrayAdapter : public MutableSequence<T> {
private:
    DynamicArray<T>& dynamicArray;
public:
    explicit DynamicArrayAdapter(DynamicArray<T>& array) : dynamicArray(array) {}

    T get(size_t index) const override {
        return dynamicArray.get(index);
    }

    void set(size_t index, T value) override {
        dynamicArray.set(index, value);
    }

    size_t size() const override {
        return dynamicArray.size();
    }

    bool isEmpty() override {
        return dynamicArray.isEmpty();
    }

    T getFirst() override {
        if (dynamicArray.isEmpty()) throw std::runtime_error("Array is empty");
        return dynamicArray.get(0);
    }

    T getLast() override {
        if (dynamicArray.isEmpty()) throw std::runtime_error("Array is empty");
        return dynamicArray.get(dynamicArray.size() - 1);
    }

    void append(T value) override {
        dynamicArray.add(value);
    }

    void prepend(T value) override {
        dynamicArray.prepend(value);
    }

    void insertAt(size_t index, T value) override {
        dynamicArray.insertAt(index, value);
    }

    void operator+=(const Iterable<T>& iterable) override {
        for (size_t i = 0; i < iterable.size(); ++i) {
            dynamicArray.add(iterable[i]);
        }
    }

    UnqPtr<MutableSequence<T>> getSubsequence(size_t start, size_t end) override {
        auto subArray = dynamicArray.getSubarray(start, end);
        return UnqPtr<MutableSequence<T>>(new DynamicArrayAdapter<T>(*subArray));
    }

    UnqPtr<MutableSequence<T>> concat(const Iterable<T>& iterable) override {
        DynamicArray<T> newArray(dynamicArray.size() + iterable.size());
        for (size_t i = 0; i < dynamicArray.size(); ++i) {
            newArray.add(dynamicArray.get(i));
        }
        for (size_t i = 0; i < iterable.size(); ++i) {
            newArray.add(iterable[i]);
        }
        return UnqPtr<MutableSequence<T>>(new DynamicArrayAdapter<T>(newArray));
    }

    void removeAt(size_t index) {
        dynamicArray.removeAt(index);
    }

    T* begin() {
        return dynamicArray.begin();
    }

    T* end() {
        return dynamicArray.end();
    }
};

#endif //DYNAMICARRAYADAPTER_H
