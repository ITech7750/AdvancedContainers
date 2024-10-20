#ifndef LAB2_MUTABLELISTSEQUENCEUNQPTR_H
#define LAB2_MUTABLELISTSEQUENCEUNQPTR_H

#include "../MutableSequence.h"
#include "../../linkedlist/LinkedListUP.h"

template<class T>
class MutableListSequenceUnqPtr : public MutableSequence<T> {
private:
    UnqPtr<LinkedListUP<T>> items;
public:
    MutableListSequenceUnqPtr() : items(UnqPtr(new LinkedListUP<T>())) {}

    MutableListSequenceUnqPtr(T *_items, size_t count) : items(UnqPtr(new LinkedListUP<T>(count, _items))) {}

    explicit MutableListSequenceUnqPtr(const LinkedListUP<T> &list) : items(UnqPtr(new LinkedListUP(list))) {}

    MutableListSequenceUnqPtr(const MutableListSequenceUnqPtr<T> &other) : items(
            UnqPtr(new LinkedListUP(*(other.items)))) {}

    T getFirst() {
        return items->getFirst();
    };

    T getLast() {
        return items->getLast();
    };

    T get(size_t index) const {
        if (index >= size()) throw IndexOutOfRange();
        return items->get(index);
    };

    T operator[](size_t index) const {
        return get(index);
    }

    size_t size() const {
        return items->size();
    }

    bool isEmpty() {
        return items->isEmpty();
    }

    UnqPtr<MutableListSequenceUnqPtr<T>> getSubsequence(size_t start, size_t end) {
        LinkedListUP<T> *subItems = items->getSublist(start, end);
        auto subSequence = UnqPtr(new MutableListSequenceUnqPtr(*subItems));
        return subSequence;
    };

    UnqPtr<MutableListSequenceUnqPtr<T>> concat(const Iterable<T> &iterable) {
        auto nItems = LinkedListUP<T>();
        for (size_t i = 0; i < size(); i++) {
            nItems.append((*items)[i]);
        }
        for (size_t i = 0; i < iterable.size(); i++) {
            nItems.append(iterable[i]);
        }
        auto buf = UnqPtr(new MutableListSequenceUnqPtr(nItems));
        return buf;
    };

    UnqPtr<MutableListSequenceUnqPtr<T>> operator+(const Iterable<T> &iterable) {
        return concat(iterable);
    }

    MutableListSequenceUnqPtr<T> &operator=(const MutableListSequenceUnqPtr<T> &other) {
        items->removeAll();
        for (size_t i = 0; i < other.size(); i++) {
            items->append(other.get(i));
        }
        return *this;
    }

    void operator+=(const Iterable<T> &iterable) {
        for (size_t i = 0; i < iterable.size(); i++) {
            items->append(iterable[i]);
        }
    }

    void append(T value) override {
        items->append(value);
    };

    void prepend(T value) override {
        items->prepend(value);
    };

    void insertAt(size_t index, T value) override {
        items->insertAt(index, value);
    };
};


#endif //LAB2_MUTABLELISTSEQUENCE_H
