#ifndef LAB2_MERGESORTER_H
#define LAB2_MERGESORTER_H

#include "../BaseSorter.h"
#include <stdexcept>

#include <iostream>
template<typename T>
class MergeSorter : public BaseSorter<T> {
public:
    void Sort(MutableSequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        if (!seq || seq->size() == 0) return;
        mergeSort(seq, 0, seq->size() - 1, cmp);
    }

    void SortStepByStep(MutableSequence<T>* seq, int (*cmp)(const T&, const T&), void (*callback)(MutableSequence<T>*)) override  {
        if (!seq || seq->size() == 0) return;
        mergeSortStepByStep(seq, 0, seq->size() - 1, cmp, callback);
    }

private:
    void mergeSort(MutableSequence<T>* seq, int left, int right, int (*cmp)(const T&, const T&)) {
        if (left >= right) return;

        int mid = left + (right - left) / 2;

        mergeSort(seq, left, mid, cmp);
        mergeSort(seq, mid + 1, right, cmp);
        merge(seq, left, mid, right, cmp);
    }

    void mergeSortStepByStep(MutableSequence<T>* seq, int left, int right, int (*cmp)(const T&, const T&), void (*callback)(MutableSequence<T>*)) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSortStepByStep(seq, left, mid, cmp, callback);
        mergeSortStepByStep(seq, mid + 1, right, cmp, callback);
        merge(seq, left, mid, right, cmp);
        if (callback) callback(seq);
    }

    void merge(MutableSequence<T>* seq, int left, int mid, int right, int (*cmp)(const T&, const T&)) {
        auto leftSeq = seq->getSubsequence(left, mid);
        auto rightSeq = seq->getSubsequence(mid + 1, right);

        int i = 0, j = 0, k = left;

        while (i < leftSeq->size() && j < rightSeq->size()) {
            if (cmp(leftSeq->get(i), rightSeq->get(j)) <= 0) {
                seq->set(k++, leftSeq->get(i++));
            } else {
                seq->set(k++, rightSeq->get(j++));
            }
        }

        while (i < leftSeq->size()) {
            seq->set(k++, leftSeq->get(i++));
        }

        while (j < rightSeq->size()) {
            seq->set(k++, rightSeq->get(j++));
        }
    }
};

#endif
