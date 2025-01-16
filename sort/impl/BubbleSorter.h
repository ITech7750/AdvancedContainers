#ifndef LAB2_BUBBLESORTER_H
#define LAB2_BUBBLESORTER_H

#include "../BaseSorter.h"

template<typename T>
class BubbleSorter : public BaseSorter<T> {
public:
    void Sort(MutableSequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        bubbleSort(seq, cmp, nullptr);
    }

    void SortStepByStep(MutableSequence<T>* seq, int (*cmp)(const T&, const T&), void (*callback)(MutableSequence<T>*)) override  {
        bubbleSort(seq, cmp, callback);
    }

private:
    void bubbleSort(MutableSequence<T>* seq, int (*cmp)(const T&, const T&), void (*callback)(MutableSequence<T>*)) {
        int n = seq->size();
        bool swapped;
        do {
            swapped = false;
            for (int i = 0; i < n - 1; ++i) {
                if (cmp(seq->get(i), seq->get(i + 1)) > 0) {
                    this->swap(seq, i, i + 1);
                    swapped = true;
                }
            }
            if (callback) callback(seq);
        } while (swapped);
    }
};

#endif
