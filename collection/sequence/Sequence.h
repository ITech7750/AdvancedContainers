#ifndef LAB2_SEQUENCE_H
#define LAB2_SEQUENCE_H

#include "../Iterable.h"

template<class T>
class Sequence: public Iterable<T> {
public:
    virtual T getFirst() = 0;

    virtual T getLast() = 0;

    virtual Sequence<T> *getSubsequence(size_t start, size_t end) = 0;

    virtual Sequence<T> *concat(const Iterable<T> *list) = 0;

    virtual Sequence<T> *append(T value) = 0;

    virtual Sequence<T> *prepend(T value) = 0;

    virtual Sequence<T> *insertAt(size_t index, T value) = 0;

    virtual Sequence<T> *operator+(const Iterable<T> *list) {
        return concat(list);
    }

    virtual T operator[](size_t index) {
        return this->get(index);
    }
};

#endif //LAB2_SEQUENCE_H
