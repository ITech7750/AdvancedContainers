#ifndef SORTERSERVICEDYNAMICARRAY_H
#define SORTERSERVICEDYNAMICARRAY_H

#include "ISorter.h"
#include "SorterFactory.h"
#include <functional>

template<typename T>
class DynamicArray;

template<typename T>
class SorterServiceDynamicArray {
public:
    static void sort(
        DynamicArray<T>& array,
        const std::function<int(const T&, const T&)>& cmp,
        const std::string& sorterType)
    {
        ISorter<T>* sorter = SorterFactory<T>::createSorter(sorterType);
        sorter->Sort(&array, cmp);
        delete sorter;
    }
};

#endif //SORTERSERVICEDYNAMICARRAY_H
