#ifndef LAB2_BUBBLESORTER_H
#define LAB2_BUBBLESORTER_H

#include "../BaseSorter.h"

template<typename T>
class BubbleSorter : public BaseSorter<T> {
public:
    /*
     *до до -i элеиента
     */
    void Sort(MutableSequence<T>* seq, int (*cmp)(const T&, const T&)) override {
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
        } while (swapped);
    }
};

#endif