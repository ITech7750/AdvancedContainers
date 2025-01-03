#ifndef LAB2_MUTABLEARRAYSEQUENCEUNQPTR_H
#define LAB2_MUTABLEARRAYSEQUENCEUNQPTR_H

#include "../MutableSequence.h"
#include "../../dinamicarray/DynamicArray.h"

template<class T>
class MutableArraySequenceUnqPtr : public MutableSequence<T> {
private:
    UnqPtr<DynamicArray<T>> items;
public:
    MutableArraySequenceUnqPtr() : items(UnqPtr<DynamicArray<T>>(new DynamicArray<T>())) {}

    MutableArraySequenceUnqPtr(T *_items, size_t count)
        : items(UnqPtr<DynamicArray<T>>(new DynamicArray<T>(count, _items))) {}

    explicit MutableArraySequenceUnqPtr(DynamicArray<T>& array)
        : items(UnqPtr<DynamicArray<T>>(new DynamicArray<T>(array))) {}

    explicit MutableArraySequenceUnqPtr(MutableSequence<T>& sequence)
        : items(UnqPtr<DynamicArray<T>>(new DynamicArray<T>(sequence.size()))) {
        for (size_t i = 0; i < sequence.size(); i++) {
            items->add(sequence.get(i));
        }
    }

    T getFirst() override {
        return items->get(0);
    }

    T getLast() override {
        return items->get(items->size() - 1);
    }

    T get(size_t index) const override {
        return items->get(index);
    }

    size_t size() const override {
        return items->size();
    }

    bool isEmpty() override {
        return items->isEmpty();
    }

    UnqPtr<MutableSequence<T>> getSubsequence(size_t start, size_t end) override {
        if (start >= size() || end > size() || start > end) {
            throw std::runtime_error("Invalid range for subsequence");
        }
        auto subArray = items->getSubarray(start, end);
        return UnqPtr<MutableSequence<T>>(new MutableArraySequenceUnqPtr<T>(*subArray));
    }

    UnqPtr<MutableSequence<T>> concat(const Iterable<T>& iterable) override {
        auto newArray = UnqPtr<DynamicArray<T>>(new DynamicArray<T>(items->size() + iterable.size()));
        for (size_t i = 0; i < items->size(); i++) {
            newArray->add(items->get(i));
        }
        for (size_t i = 0; i < iterable.size(); i++) {
            newArray->add(iterable[i]);
        }
        return UnqPtr<MutableSequence<T>>(new MutableArraySequenceUnqPtr<T>(*newArray));
    }

    void operator+=(const Iterable<T>& iterable) override {
        for (size_t i = 0; i < iterable.size(); i++) {
            items->add(iterable[i]);
        }
    }

    void append(T value) override {
        items->add(value);
    }

    void prepend(T value) override {
        items->prepend(value);
    }

    void insertAt(size_t index, T value) override {
        items->insertAt(index, value);
    }
};

#endif //LAB2_MUTABLEARRAYSEQUENCEUNQPTR_H
