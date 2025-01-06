#ifndef SORTERSERVICEDYNAMICARRAY_H
#define SORTERSERVICEDYNAMICARRAY_H

#include "SorterFactory.h"
#include "../collectionunqptr/dinamicarray/DynamicArrayAdapter.h"
#include <chrono>
#include <iostream>

template<typename T>
class SorterServiceArrayAdapter {
public:
    static void sort(
             DynamicArrayAdapter<T>& seq,
            int (*cmp)(const T&, const T&),
            const std::string& sorterType)
    {
        ISorter<T>* sorter = SorterFactory<T>::createSorter(sorterType);
        sorter->Sort(&seq, cmp);
        delete sorter;
    }

};
template<typename VertexType, typename TimeTable>
struct ComparatorHelper {
    TimeTable& timetable;

    ComparatorHelper(TimeTable& timetable) : timetable(timetable) {}

    static int compare(const VertexType& left, const VertexType& right, TimeTable& timetable) {
        return timetable[left] < timetable[right] ? -1 :
               (timetable[left] > timetable[right] ? 1 : 0);
    }

    static int wrapper(const VertexType& left, const VertexType& right) {
        TimeTable& timetable = *reinterpret_cast<TimeTable*>(context);
        return compare(left, right, timetable);
    }

    static void* context;
};


// Инициализация статического члена
template<typename VertexType, typename TimeTable>
void* ComparatorHelper<VertexType, TimeTable>::context = nullptr;


#endif