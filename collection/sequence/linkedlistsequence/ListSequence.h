#ifndef LAB2_LISTSEQUENCE_H
#define LAB2_LISTSEQUENCE_H

#include MutableListSequence"../Sequence.h"
#include "../../linkedlist/LinkedList.h"

template<class T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T> *items;
public:
    ListSequence() {
        items = new LinkedList<T>();
    }

    ListSequence(T *_items, int count) {
        items = new LinkedList<T>(count, _items);
    }

    explicit ListSequence(const LinkedList<T> &list) : ListSequence() {
        *items = list;
    }

    T getFirst() override {
        return items->getFirst();
    };

    T getLast() override {
        return items->getLast();
    };

    T get(int index) override {
        return items->get(index);
    };

    ListSequence<T> *getSubsequence(int start, int end) override {
        LinkedList<T> *subItems = items->getSublist(start, end);
        return ListSequence(*subItems);
    };

    int getLength() override {
        return items->getLength();
    };

    ListSequence<T> *concat(const Sequence<T> &list) override {
        auto *nItems = new LinkedList<T>();
        for (int i = 0; i < getLength(); i++) {
            (*nItems).append((*items)[i]);
        }
        for (int i = 0; i < (*list).getLength(); i++) {
            (*nItems).append((*list)[i]);
        }
        LinkedList<T> *tmp = *(items) + list;
        auto *buf = new ListSequence(*tmp);
        delete tmp;
        return buf;
    };

    ListSequence<T> *operator+(const Sequence<T> &list) override {
        return concat(list);
    }

    ListSequence<T> *append(T value) override {
        auto *nItems = new LinkedList<T>();
        for (int i = 0; i < getLength(); i++) {
            (*nItems).append((*items)[i]);
        }
        (*nItems).append(value);
        LinkedList<T> *tmp = *(items) + value;
        return new ListSequence(*nItems);
    };

    ListSequence<T> *prepend(T value) override {
        auto *nItems = new LinkedList<T>();
        for (int i = 0; i < getLength(); i++) {
            (*nItems).append((*items)[i]);
        }
        (*nItems).prepend(value);
        auto *buf = new ListSequence(*nItems);
        return buf;
    };

    ListSequence<T> *insertAt(int index, T value) override {
        auto *nItems = new LinkedList<T>();
        for (int i = 0; i < getLength(); i++) {
            (*nItems).append((*items)[i]);
        }
        (*nItems).insertAt(index, value);
        auto *buf = new ListSequence(*nItems);
        return buf;
    };

    void print() {
        items->println();
    }
};


#endif //LAB2_LISTSEQUENCE_H
