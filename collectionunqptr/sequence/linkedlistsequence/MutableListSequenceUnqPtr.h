#ifndef LAB2_MUTABLELISTSEQUENCEUNQPTR_H
#define LAB2_MUTABLELISTSEQUENCEUNQPTR_H

#include "../MutableSequence.h"
#include "../../linkedlist/LinkedListUP.h"
#include "../../../collection/sequence/linkedlistsequence/MutableListSequence.h"

template<class T>
class MutableListSequenceUnqPtr : public MutableSequence<T> {
private:
    UnqPtr<LinkedListUP<T>> items;
public:
    MutableListSequenceUnqPtr() : items(UnqPtr(new LinkedListUP<T>())) {}

    MutableListSequenceUnqPtr(T *_items, size_t count) : items(UnqPtr(new LinkedListUP<T>(count, _items))) {}

    explicit MutableListSequenceUnqPtr(const LinkedListUP<T> &list) : items(UnqPtr(new LinkedListUP(list))) {}

    explicit MutableListSequenceUnqPtr(MutableSequence<T>& sequence) : items(UnqPtr(new LinkedListUP<T>())) {
        for (size_t i = 0; i < sequence.size(); ++i) {
            items->append(sequence.get(i));
        }
    }


    MutableListSequenceUnqPtr(const MutableListSequenceUnqPtr<T> &other) : items(
            UnqPtr(new LinkedListUP(*(other.items)))) {}

    T getFirst() override{
        return items->getFirst();
    };

    T getLast() override {
        return items->getLast();
    };

    T get(size_t index) const override{
        if (index >= size()) throw IndexOutOfRange();
        return items->get(index);
    };


    size_t size() const override {
        return items->size();
    }

    bool isEmpty() override {
        return items->isEmpty();
    }

    UnqPtr<MutableSequence<T>> getSubsequence(size_t start, size_t end) override{
        if (start >= size() || end >= size() || start > end) {
            throw std::runtime_error("error");
        }
        auto subItems = items->getSublist(start, end + 1);
        return UnqPtr<MutableSequence<T>>(new MutableListSequenceUnqPtr(std::move(*subItems)));
    }

    UnqPtr<MutableSequence<T>> concat(const Iterable<T> &iterable) override{
        auto nItems = LinkedListUP<T>();
        for (size_t i = 0; i < size(); i++) {
            nItems.append((*items)[i]);
        }
        for (size_t i = 0; i < iterable.size(); i++) {
            nItems.append(iterable[i]);
        }
        auto buf = UnqPtr<MutableSequence<T>>(new MutableListSequenceUnqPtr(nItems));
        return buf;
    };

    UnqPtr<MutableListSequenceUnqPtr<T>> operator+(const Iterable<T> &iterable) {
        return (MutableListSequenceUnqPtr<int> *) concat(iterable);
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
