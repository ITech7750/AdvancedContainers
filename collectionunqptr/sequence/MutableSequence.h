#ifndef LAB2_MUTABLESEQUENCE_H
#define LAB2_MUTABLESEQUENCE_H


#include "Sequence.h"
#include "../../pointer/UnqPtr.h"

template<class T>
class MutableSequence: public Iterable<T> {
public:
    virtual T getFirst() = 0;

    virtual T getLast() = 0;

    virtual void append(T value) = 0;

    virtual void prepend(T value) = 0;

    virtual void insertAt(size_t index, T item) = 0;

    virtual void operator+=(const Iterable<T> &list) = 0;

    virtual UnqPtr<MutableSequence<T>> getSubsequence(size_t start, size_t end) = 0;

    virtual   UnqPtr<MutableSequence<T>> concat(const Iterable<T> &iterable) = 0;

};


#endif //LAB2_MUTABLESEQUENCE_H
