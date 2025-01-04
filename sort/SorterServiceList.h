#ifndef LAB2_SORTERSERVICE_LIST_H
#define LAB2_SORTERSERVICE_LIST_H

#include "SorterFactory.h"
#include "../collectionunqptr/sequence/linkedlistsequence/MutableListSequenceUnqPtr.h"
#include <chrono>
#include <iostream>

template<typename T>
class SorterServiceList {
public:
    static void sort(
            MutableListSequenceUnqPtr<T>& seq,
            int (*cmp)(const T&, const T&),
            const std::string& sorterType)
    {
        ISorter<T>* sorter = SorterFactory<T>::createSorter(sorterType);
        sorter->Sort(&seq, cmp);
        delete sorter;
    }

    static double measureSortTime(
            MutableListSequenceUnqPtr<T>& seq,
            int (*cmp)(const T&, const T&),
            const std::string& sorterType)
    {
        auto start = std::chrono::high_resolution_clock::now();
        sort(seq, cmp, sorterType);
        auto end = std::chrono::high_resolution_clock::now();

        double duration = std::chrono::duration<double, std::milli>(end - start).count();
        std::cout << "Sorting with " << sorterType << " took " << duration << " ms." << std::endl;

        return duration;
    }
};

#endif
