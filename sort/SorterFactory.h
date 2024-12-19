
// SorterFactory.h
#ifndef LAB2_SORTERFACTORY_H
#define LAB2_SORTERFACTORY_H

#include "impl/BubbleSorter.h"
#include "impl/InsertionSorter.h"
#include "impl/MergeSorter.h"
#include "impl/QuickSorter.h"
#include "impl/HeapSorter.h"
#include <stdexcept>
#include <string>

template<typename T>
class SorterFactory {
public:
    static ISorter<T>* createSorter(const std::string& sorterType) {
        if (sorterType == "bubble") {
            return new BubbleSorter<T>();
        }
        else if (sorterType == "insertion") {
            return new InsertionSorter<T>();
        } else if (sorterType == "merge") {
            return new MergeSorter<T>();
        } else if (sorterType == "quick") {
            return new QuickSorter<T>();
        } else if (sorterType == "heap") {
            return new HeapSorter<T>();
        } else {
            throw std::invalid_argument("Unknown sorter type: " + sorterType);
        }
    }
};

#endif