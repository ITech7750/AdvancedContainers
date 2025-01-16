#ifndef LAB2_INSERTIONSORTER_H
#define LAB2_INSERTIONSORTER_H

#include "../BaseSorter.h"

template<typename T>
class InsertionSorter : public BaseSorter<T> {
public:
    void Sort(MutableSequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        int n = seq->size();
        for (int i = 1; i < n; ++i) {
            T key = seq->get(i);
            int j = i - 1;
            while (j >= 0 && cmp(seq->get(j), key) > 0) {
                seq->set(j + 1, seq->get(j));
                --j;
            }
            seq->set(j + 1, key);
        }
    }

    void SortStepByStep(MutableSequence<T>* seq, int (*cmp)(const T&, const T&), void (*callback)(MutableSequence<T>*)) override {
        int n = seq->size();
        for (int i = 1; i < n; ++i) {
            T key = seq->get(i);
            int j = i - 1;
            while (j >= 0 && cmp(seq->get(j), key) > 0) {
                seq->set(j + 1, seq->get(j));
                --j;
                callback(seq);
            }
            seq->set(j + 1, key);
            callback(seq);
        }
    }
};

#endif