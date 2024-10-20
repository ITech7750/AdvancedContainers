#ifndef LAB2_MUTABLESEQUENCE_H
#define LAB2_MUTABLESEQUENCE_H


#include "Sequence.h"

template<class T>
class MutableSequence: public Iterable<T> {
public:
    virtual T getFirst() = 0;

    virtual T getLast() = 0;

    virtual void append(T value) = 0;

    virtual void prepend(T value) = 0;

    virtual void insertAt(size_t index, T item) = 0;

    virtual void operator+=(const Iterable<T> &list) = 0;

    virtual T operator[](size_t index) {
        return this->get(index);
    }
};


#endif //LAB2_MUTABLESEQUENCE_H
