
#ifndef LAB2_SEGMENTEDLIST_H
#define LAB2_SEGMENTEDLIST_H

#include "../linkedlist/LinkedListUP.h"

template<typename T>
class SegmentedList {
private:
    Element<LinkedList<T> *> *head;

public:
    explicit SegmentedList() : head(nullptr) {}

    SegmentedList(int count, T *items) : SegmentedList() {
        for (int i = 0; i < count; i++) {
            add(items[i]);
        }
    }

    explicit SegmentedList(LinkedList<T> &list) : SegmentedList() {
        addSegment();
        for (int i = 0; i < list.getLength(); i++) {
            add(list[i]);
        }
    }

    // добавление сегмента
    void addSegment() {
        auto *newList = new LinkedList<T>();
        auto *seg = new Element<LinkedList<T> *>(newList);
        if (head == nullptr) {
            head = seg;
        } else {
            Element<LinkedList<T> *> *buf = head;
            while (buf->getNext() != nullptr) {
                buf = buf->getNext();
            }
            buf->setNext(seg);
        }
    }

    // добавление элемента в последний сегмент
    void add(T value) {
        if (head == nullptr) {
            auto *newList = new LinkedList<T>();
            newList->append(value);
            auto *newNode = new Element<LinkedList<T> *>(newList);
            head = newNode;
        } else {
            Element<LinkedList<T> *> *buf = head;
            while (buf->getNext() != nullptr) {
                buf = buf->getNext();
            }
            buf->get()->append(value);
        }
    }

    int size() {
        int size = 0;
        Element<LinkedList<T> *> *buf = head;
        while (buf != nullptr) {
            size += (*(*buf).get()).getLength();
            buf = buf->getNext();
        }
        return size;
    }

    LinkedList<T> *get(int index) {
        Element<LinkedList<T> *> *buf = head;
        while (index--) {
            buf = buf->getNext();
        }
        return buf->get();
    }

    void println() {
        if (head == nullptr) {
            std::cout << "{}" << "\n";
            return;
        }
        Element<LinkedList<T> *> *buf = head;
        std::cout << "{";
        buf->get()->print();
        while (buf->getNext() != nullptr) {
            std::cout << ", ";
            buf = buf->getNext();
            buf->get()->print();
        }
        std::cout << "}";
        std::cout << std::endl;
    }

    void print() {
        if (head == nullptr) {
            std::cout << "{}";
            return;
        }
        Element<LinkedList<T> *> *buf = head;
        std::cout << "{";
        buf->get()->print();
        while (buf->getNext() != nullptr) {
            std::cout << ", ";
            buf = buf->getNext();
            buf->get()->print();
        }
        std::cout << "}";
    }

    ~SegmentedList() {
        Element<LinkedList<T> *> *buf = head;
        while (buf != nullptr) {
            Element<LinkedList<T> *> *next = buf->getNext();
            delete buf;
            buf = next;
        }
    }
};


#endif //LAB2_SEGMENTEDLIST_H
