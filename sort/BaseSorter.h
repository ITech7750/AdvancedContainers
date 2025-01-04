#ifndef LAB2_BASESORTER_H
#define LAB2_BASESORTER_H

#include "ISorter.h"

template<typename T>
class BaseSorter : public ISorter<T> {
protected:
    void swap(MutableSequence<T>* seq, size_t i, size_t j) {
        T temp = seq->get(i);
        seq->set(i, seq->get(j));
        seq->set(j, temp);
    }
};

#endif