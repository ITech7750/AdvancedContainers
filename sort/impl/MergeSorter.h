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

private:
    void mergeSort(MutableSequence<T>* seq, int left, int right, int (*cmp)(const T&, const T&)) {
        if (left >= right) return;

        int mid = left + (right - left) / 2;

        mergeSort(seq, left, mid, cmp);
        mergeSort(seq, mid + 1, right, cmp);
        merge(seq, left, mid, right, cmp);
    }

    void merge(MutableSequence<T>* seq, int left, int mid, int right, int (*cmp)(const T&, const T&)) {
        if (!seq || left < 0 || right >= seq->size() || left > mid || mid > right) {
            throw std::runtime_error("Invalid parameters in merge");
        }

        auto leftSeq = seq->getSubsequence(left, mid);
        auto rightSeq = seq->getSubsequence(mid + 1, right);

        int i = 0, j = 0, k = left;

        while (i < leftSeq->size() && j < rightSeq->size()) {
            try {
                if (cmp(leftSeq->get(i), rightSeq->get(j)) <= 0) {
                    seq->operator[](k++) = leftSeq->get(i++);
                } else {
                    seq->operator[](k++) = rightSeq->get(j++);
                }
            } catch (const std::out_of_range& e) {
                throw std::runtime_error("Index out of range during merge operation");
            }
        }

        while (i < leftSeq->size()) {
            try {
                seq->operator[](k++) = leftSeq->get(i++);
            } catch (const std::out_of_range& e) {
                throw std::runtime_error("Index out of range during merge operation");
            }
        }

        while (j < rightSeq->size()) {
            try {
                seq->operator[](k++) = rightSeq->get(j++);
            } catch (const std::out_of_range& e) {
                throw std::runtime_error("Index out of range during merge operation");
            }
        }
    }
};

#endif
