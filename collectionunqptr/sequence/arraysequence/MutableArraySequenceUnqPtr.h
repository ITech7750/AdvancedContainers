#ifndef LAB2_MUTABLEARRAYSEQUENCEUNQPTR_H
#define LAB2_MUTABLEARRAYSEQUENCEUNQPTR_H

#include "../MutableSequence.h"
#include "../../../collectionunqptr/dinamicarray/DynamicArrayUP.h"

template<class T>
class MutableArraySequenceUnqPtr : public MutableSequence<T> {
private:
    UnqPtr<DynamicArrayUP<T>> items;

public:
    MutableArraySequenceUnqPtr() : items(new DynamicArrayUP<T>()) {}

    MutableArraySequenceUnqPtr(T* _items, size_t count)
        : items(new DynamicArrayUP<T>(_items, count)) {}

    T getFirst() override {
        if (items->isEmpty()) {
            throw std::runtime_error("Sequence is empty");
        }
        return items->get(0);
    }

    T getLast() override {
        if (items->isEmpty()) {
            throw std::runtime_error("Sequence is empty");
        }
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

    void append(T value) override {
        items->append(std::move(value));
    }

    void prepend(T value) override {
        items->prepend(std::move(value));
    }

    void insertAt(size_t index, T value) override {
        if (index > items->size()) {
            throw std::out_of_range("Index out of range");
        }
        items->insertAt(index, std::move(value));
    }

    UnqPtr<MutableSequence<T>> getSubsequence(size_t start, size_t end) override {
        if (start >= items->size() || end >= items->size() || start > end) {
            throw std::runtime_error("Invalid subsequence range");
        }
        auto subarray = items->subarray(start, end - start + 1);
        return UnqPtr<MutableSequence<T>>(new MutableArraySequenceUnqPtr<T>(subarray->getData(), subarray->size()));
    }

    UnqPtr<MutableSequence<T>> concat(const Iterable<T>& iterable) override {
        auto result = new MutableArraySequenceUnqPtr<T>();
        for (size_t i = 0; i < items->size(); ++i) {
            result->append(items->get(i));
        }
        for (size_t i = 0; i < iterable.size(); ++i) {
            result->append(iterable.get(i));
        }
        return UnqPtr<MutableSequence<T>>(result);
    }

    void operator+=(const Iterable<T>& iterable) override {
        for (size_t i = 0; i < iterable.size(); ++i) {
            items->append(iterable.get(i));
        }
    }
};

#endif //LAB2_MUTABLEARRAYSEQUENCEUNQPTR_H
