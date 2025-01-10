#ifndef LAB2_LINKEDLISTUP_H
#define LAB2_LINKEDLISTUP_H

#include "ElementUP.h"
#include "../../util/exception/IndexOutOfRange.h"
#include "../Iterable.h"
#include "../../pointer/UnqPtr.h"
#include "../../pointer/ShrdPtr.h"

template<class T>
class LinkedListUP : public Iterable<T> {
private:
    UnqPtr<ElementUP<T>> _first;
    UnqPtr<ElementUP<T>> _last;
    size_t _length = 0;

public:
    LinkedListUP() : _first(nullptr), _last(nullptr), _length(0) {}


    LinkedListUP(const size_t &count, const T *items) : LinkedListUP() {
        if (!items && count > 0) {
            throw std::invalid_argument("Items pointer is null while count is greater than 0");
        }
        for (size_t i = 0; i < count; i++) {
            append(items[i]);
        }
    }

    /*
    LinkedListUP(const size_t &count, const T *items) : LinkedListUP() {
        for (size_t i = 0; i < count; i++) {
            append(items[i]);
        }
    }
    */

    LinkedListUP(const LinkedListUP<T> &list) : LinkedListUP() {
        for (size_t i = 0; i < list.size(); i++) {
            append(list.get(i));
        }
    }

    ~LinkedListUP() {
        _clear_();
    }

    T getFirst() {
        if (_first) {
            return _first->get();
        } else {
            throw IndexOutOfRange();
        }
    }

    T getLast() {
        if (_last) {
            return _last->get();
        } else {
            throw IndexOutOfRange();
        }
    }

    T get(size_t index) const {
        if (index >= _length) {
            throw IndexOutOfRange();
        }

        auto current = _first.getValue();
        for (size_t i = 0; i < index; i++) {
            current = current->getNext().get();
        }
        return current->get();

    }

    size_t size() const {
        return _length;
    }

    bool isEmpty() override {
        return _length == 0;
    }

    void set(size_t index, T value) {
        if (index >= _length) {
            throw IndexOutOfRange();
        }

        auto current = _first.getValue();
        for (size_t i = 0; i < index; i++) {
            current = current->getNext().get();
        }

        current->set(value);
    }


    UnqPtr<LinkedListUP<T>> getSublist(size_t start, size_t end) const {
        if (start >= _length || end > _length || start >= end) {
            throw IndexOutOfRange();
        }

        auto sublist = UnqPtr<LinkedListUP<T>>(new LinkedListUP<T>());
        auto current = _first.getValue();
        for (size_t i = 0; i < end; ++i) {
            if (i >= start) {
                sublist->append(current->get());
            }
            current = current->getNext().get();
        }

        return sublist;
    }


    void append(T value) {
        UnqPtr<ElementUP<T>> newElement(new ElementUP<T>(value));
        if (!_first) {
            _first = std::move(newElement);
        } else if (!_last) {
            _last = std::move(newElement);
            _first->setNext(ShrdPtr<ElementUP<T>>(_last.getValue()));
            _last->setPrevious(ShrdPtr<ElementUP<T>>(_first.getValue()));
        } else {
            _last->setNext(ShrdPtr<ElementUP<T>>(newElement.release()));
            _last->getNext()->setPrevious(ShrdPtr<ElementUP<T>>(_last.getValue()));
            _last = std::move(newElement);
        }
        _length++;
    }

    void prepend(T value) {
        UnqPtr<ElementUP<T>> newElement(new ElementUP<T>(value));

        if (!_first) {
            _first = std::move(newElement);
        } else {
            newElement->setNext(ShrdPtr<ElementUP<T>>(_first.release()));
            _first->setPrevious(ShrdPtr<ElementUP<T>>(newElement.getValue()));
            _first = std::move(newElement);
        }
        _length++;
    }


    LinkedListUP<T> *insertAt(size_t index, T value) {
        if (index >= _length) {
            throw IndexOutOfRange();
        }

        if (index == 0) {
            prepend(value);
            return this;
        } else if (index == _length) {
            append(value);
            return this;
        }

        auto current = _first.getValue();
        for (size_t i = 0; i < index; i++) {
            current = current->getNext().get();
        }
        UnqPtr<ElementUP<T>> newElement(new ElementUP<T>(value, current->getPrevious(), ShrdPtr<ElementUP<T>>(current)));
        current->getPrevious()->setNext(ShrdPtr<ElementUP<T>>(newElement.getValue()));
        current->setPrevious(ShrdPtr<ElementUP<T>>(newElement.getValue()));


        _length++;

        return this;
    }

    void remove(size_t index) {
        if (index >= _length) {
            throw IndexOutOfRange();
        }

        ShrdPtr<ElementUP<T>> current = _first;
        for (size_t i = 0; i < index; i++) {
            current = current->getNext();
        }

        auto prev = current->getPrevious();
        auto next = current->getNext();

        if (prev) {
            prev->setNext(next);
        } else {
            _first = UnqPtr<ElementUP<T>>(next.get());
        }

        if (next) {
            next->setPrevious(prev);
        } else {
            _last = UnqPtr<ElementUP<T>>(prev.get());
        }

        _length--;
    }

    void removeAll() {
        _clear_();
    }

private:
    void _clear_() {
        _first = nullptr;
        _last = nullptr;
        _length = 0;
    }
};

#endif //LAB2_LINKEDLISTUP_H
