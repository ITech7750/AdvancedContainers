#ifndef LAB2_ARRAYSEQUENCE_H
#define LAB2_ARRAYSEQUENCE_H

#include "../Sequence.h"
#include "../../dynamicarray/DynamicArray.h"

template<class T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T> *items;
public:
    ArraySequence() {
        items = new DynamicArray<T>();
    }

    ArraySequence(T *it, int count) {
        items = new DynamicArray<T>(count, it);
    }

    explicit ArraySequence(DynamicArray<T> &list) {
        items = new DynamicArray<T>();
        for (int i = 0; i < list.getSize(); i++) {
            (*items).add(list[i]);
        }
    }

    T getFirst() override {
        return (*items)[0];
    }

    T getLast() override {
        return (*items)[getLength() - 1];
    }

    T get(int index) {
        return (*items)[index];
    };

    T operator[](int index) {
        return get(index);
    }

    int getLength() override {
        return (*items).getSize();
    }

    ArraySequence<T> *getSubsequence(int start, int end) override {
        auto *buf = new DynamicArray<T>();
        for (int i = start; i < end; i++) {
            (*buf).add((*items)[i]);
        }
        auto *arr = new ArraySequence<T>(*buf);
        return arr;
    };

    ArraySequence<T> *append(T value) override {
        DynamicArray<T> *nItems = new DynamicArray((*items));
        (*nItems).add(value);
        auto *buf = new ArraySequence<T>(*nItems);
        return buf;
    };

    ArraySequence<T> *prepend(T value) override {
        DynamicArray<T> *nItems = new DynamicArray(1, new T[]{value});
        for (int i = 0; i < getLength(); i++) {
            nItems->add((*items)[i]);
        }
        auto *buf = new ArraySequence<T>(*nItems);
        return buf;
    };

    ArraySequence<T> *insertAt(int index, T value) override {
        DynamicArray<T> *nItems = new DynamicArray((*items));
        (*nItems).set(index, value);
        auto *buf = new ArraySequence<T>(*nItems);
        return buf;
    };

    ArraySequence<T> *concat(Sequence<T> *list) override {
        auto *buf = new DynamicArray<T>();
        for (int i = 0; i < getLength(); i++) {
            (*buf).add((*items)[i]);
        }
        for (int i = 0; i < (*list).getLength(); i++) {
            (*buf).add((*list)[i]);
        }
        auto *processed = new ArraySequence<T>(*buf);
        return processed;
    };

    ArraySequence<T> *operator+(Sequence<T> *list) override {
        return concat(list);
    }

    void print() {
        items->println();
    }
};

#endif //LAB2_ARRAYSEQUENCE_H
