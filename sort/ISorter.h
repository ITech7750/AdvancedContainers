#ifndef LAB2_ISORTER_H
#define LAB2_ISORTER_H

#include "../collectionunqptr/sequence/linkedlistsequence/MutableListSequenceUnqPtr.h"

template<typename T>
class ISorter {
public:
    virtual void Sort(MutableSequence<T>* seq, int (*cmp)(const T&, const T&)) = 0;
    virtual void SortStepByStep(MutableSequence<T>* seq, int (*cmp)(const T&, const T&), void (*callback)(MutableSequence<T>*)) = 0;
    virtual ~ISorter() = default;
};

#endif