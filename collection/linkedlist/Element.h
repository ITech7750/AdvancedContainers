#ifndef LAB2_ELEMENTUP_H
#define LAB2_ELEMENTUP_H

#include <clocale>
#include "../../util/exception/WrongType.h"

template<class T>
class Element {
private:
    Element *_previous;
    Element *_next;
    T _value;
public:
    Element(T value, Element *previous, Element *next) {
        _value = value;
        _previous = previous;
        _next = next;
    }

    explicit Element(T value) : Element(value, nullptr, nullptr) {}

    T operator()() {
        if (this != nullptr) {
            return _value;
        }
    }

    T get() {
        return _value;
    }

    void set(T value) {
        _value = value;
    }

    Element *getPrevious() {
        return _previous;
    }

    Element *getNext() {
        return _next;
    }

    void setPrevious(Element *previous) {
        if (sizeof((*previous)._value) != sizeof(_value)) {
            throw WrongType();
        }
        _previous = previous;
    }

    void setNext(Element *next) {
        if (sizeof((*next)._value) != sizeof(_value)) {
            throw WrongType();
        }
        _next = next;
    }

};


#endif //LAB2_ELEMENTUP_H
