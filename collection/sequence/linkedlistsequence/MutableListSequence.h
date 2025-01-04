#ifndef LAB2_MUTABLELISTSEQUENCE_H
#define LAB2_MUTABLELISTSEQUENCE_H

#include "../../linkedlist/LinkedList.h"

template<class T>
class MutableListSequence : public MutableSequence<T> {
private:
    LinkedListUP<T>* items;
public:
    MutableListSequence(): items(new LinkedListUP<T>()) {}

    MutableListSequence(T *_items, size_t count): items(new LinkedListUP<T>(count, _items)) {}

    explicit MutableListSequence(const LinkedListUP<T> &list): items(new LinkedListUP(list)) {}

    MutableListSequence(const MutableListSequence<T>& other): items(new LinkedListUP(*(other.items))) {}

    ~MutableListSequence() {
        delete items;
    }

    T getFirst() {
        return items->getFirst();
    }

    T getLast() {
        return items->getLast();
    }

    T get(size_t index) const {
        if (index >= size()) throw IndexOutOfRange();
        return items->get(index);
    }

    T operator[](size_t index) const {
        return get(index);
    }

    size_t size() const {
        return items->size();
    }

    bool isEmpty() {
        return items->isEmpty();
    }

    void set(size_t index, T value) override {
        items->set(index, value);
    }

    UnqPtr<MutableSequence<T>> getSubsequence(size_t start, size_t end) override {
        if (start >= size() || end >= size() || start > end) {
            throw IndexOutOfRange();
        }
        LinkedListUP<T>* subItems = items->getSublist(start, end);
        auto* subSequence = new MutableListSequence(*subItems);
        return UnqPtr<MutableSequence<T>>(subSequence); // Оборачиваем в UnqPtr
    }

    UnqPtr<MutableSequence<T>> concat(const Iterable<T> &iterable) override {
        auto nItems = LinkedListUP<T>();
        for (size_t i = 0; i < size(); i++) {
            nItems.append((*items)[i]);
        }
        for (size_t i = 0; i < iterable.size(); i++) {
            nItems.append(iterable[i]);
        }
        auto* buf = new MutableListSequence(nItems);
        return UnqPtr<MutableSequence<T>>(buf); // Оборачиваем в UnqPtr
    }

    MutableListSequence<T> operator+(const Iterable<T> &iterable) {
        return *concat(iterable);
    }

    MutableListSequence<T>& operator=(const MutableListSequence<T>& other) {
        if (this != &other) {
            items->removeAll();
            for (size_t i = 0; i < other.size(); i++) {
                items->append(other.get(i));
            }
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
    }

    void prepend(T value) override {
        items->prepend(value);
    }

    void insertAt(size_t index, T value) override {
        items->insertAt(index, value);
    }
};

#endif //LAB2_MUTABLELISTSEQUENCE_H
