#ifndef LAB2_MUTABLEARRAYSEQUENCE_H
#define LAB2_MUTABLEARRAYSEQUENCE_H

#include "../MutableSequence.h"
#include "../../dinamicarray/DynamicArray.h"
#include "ArraySequence.h"

template<class T>
class MutableArraySequence : public MutableSequence<T> {
private:
    DynamicArray<T> *items;
public:
    MutableArraySequence() {
        items = new DynamicArray<T>();
    }

    MutableArraySequence(T *_items, int count) {
        items = new DynamicArray<T>(count, _items);
    }

    explicit MutableArraySequence(DynamicArray<T> &list) : MutableArraySequence() {
        for (int i = 0; i < list.getSize(); i++) {
            append(list[i]);
        }
    }

    explicit MutableArraySequence(Sequence<T> sequence) : MutableArraySequence() {
        for (int i = 0; i < sequence.getLength(); i++) {
            append(sequence[i]);
        }
    }

    T getFirst() override {
        return (*items)[0];
    }

    T getLast() override {
        return (*items)[getLength() - 1];
    }

    T get(int index) override {
        return (*items)[index];
    };

    T operator[](int index) override {
        return get(index);
    }

    MutableArraySequence<T> *getSubsequence(int start, int end) override {
        auto *buf = new DynamicArray<T>(0);
        for (int i = start; i < end; i++) {
            (*buf).add((*items)[i]);
        }
        return new MutableArraySequence<T>(*buf);
    };

    int getLength() override {
        return (*items).getSize();
    }

    void append(T value) override {
        (*items).add(value);
    };

    void prepend(T value) override {
        auto *buf = new DynamicArray<T>(1, new T[]{value});
        for (int i = 0; i < getLength(); i++) {
            buf->add((*items)[i]);
        }
    };

    void insertAt(int index, T item) override {
        (*items).set(index, item);
    };

    MutableArraySequence<T> *concat(MutableSequence<T> *list) override {
        auto *buf = new DynamicArray<T>(0);
        for (int i = 0; i < getLength(); i++) {
            (*buf).add((*items)[i]);
        }
        for (int i = 0; i < (*list).getLength(); i++) {
            (*buf).add((*items)[i]);
        }
        auto *processed = new MutableArraySequence<T>(*buf);
        return processed;
    };

    MutableArraySequence<T> *operator+(MutableSequence<T> *list) {
        return concat(list);
    }

    void print() {
        items->println();
    }
};

#endif //LAB2_MUTABLEARRAYSEQUENCE_H
