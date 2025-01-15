#ifndef LAB2_HEAPSORTER_H
#define LAB2_HEAPSORTER_H

#include "../BaseSorter.h"

//что такое двоичная куча?
template<typename T>
class HeapSorter : public BaseSorter<T> {
public:
    void Sort(MutableSequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        buildHeap(seq, cmp);
        for (int i = seq->size() - 1; i > 0; --i) {
            this->swap(seq, 0, i);
            heapify(seq, i, 0, cmp);
        }
    }

private:
    void heapify(MutableSequence<T>* seq, int n, int i, int (*cmp)(const T&, const T&)) {
        int largest = i, left = 2 * i + 1, right = 2 * i + 2;

        if (left < n && cmp(seq->get(left), seq->get(largest)) > 0) largest = left;
        if (right < n && cmp(seq->get(right), seq->get(largest)) > 0) largest = right;

        if (largest != i) {
            this->swap(seq, i, largest);
            heapify(seq, n, largest, cmp);
        }
    }

    void buildHeap(MutableSequence<T>* seq, int (*cmp)(const T&, const T&)) {
        for (int i = seq->size() / 2 - 1; i >= 0; --i) {
            heapify(seq, seq->size(), i, cmp);
        }
    }
};

#endif