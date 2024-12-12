#ifndef LAB2_LINKEDLIST_H
#define LAB2_LINKEDLIST_H

#include "Element.h"
#include "../../util/exception/IndexOutOfRange.h"

#include "../../pointer/UnqPtr.h"
#include "../../pointer/ShrdPtr.h"

template<class T>
class LinkedList : public Iterable<T> {
private:
    Element<T> *_first = nullptr;
    Element<T> *_last = nullptr;
    size_t _length = 0;

public:
    LinkedList() {
        _length = 0;
        _first = nullptr;
        _last = nullptr;
    }

    LinkedList(const size_t &count, const T *items) : LinkedList() {
        for (size_t i = 0; i < count; i++) {
            append(items[i]);
        }
    }

    LinkedList(const LinkedList<T> &list) : LinkedList() {
        for (size_t i = 0; i < list.size(); i++) {
            append(list.get(i));
        }
    }

    ~LinkedList() {
        __clear__();
    }

    T getFirst() {
        if (_first != nullptr) {
            return (*_first)();
        } else {
            throw IndexOutOfRange();
        }

    }

    T getLast() {
        if (_last != nullptr) {
            return (*_last)();
        } else {
            throw IndexOutOfRange();
        }

    }

    T get(size_t index) const {
        size_t i = 0;
        if (index < 0 || index >= _length) {
            throw IndexOutOfRange();
        }
        Element<T> *buf = _first;
        while (i < index) {
            i++;
            buf = (*buf).getNext();
        }
        return (*buf)();
    }

    size_t size() const {
        return _length;
    }

    bool isEmpty() {
        return _length == 0;
    }

    LinkedList<T> *getSublist(size_t start, size_t end) {
        if (start >= _length || end >= _length || start < 0 || end < 0 || start >= end) {
            throw IndexOutOfRange();
        }
        auto *buf = new LinkedList<T>();
        for (size_t i = 0; i < _length; i++) {
            if (i >= start && i < end) {
                buf->append(get(i));
            }
        }
        return buf;
    }

    void append(T value) {
        if (_first == nullptr) {
            _first = new Element<T>(value);
        } else if (_last == nullptr) {
            _last = new Element<T>(value, _first, nullptr);
            _first->setNext(_last);
        } else {
            auto *buf = new Element<T>(value, _last, nullptr);
            _last->setNext(buf);
            _last = buf;
        }
        _length++;

    }

    void prepend(T value) {
        if (_first == nullptr) {
            _first = new Element<T>(value, nullptr, nullptr);
        } else if (_last == nullptr) {
            _last = new Element<T>((*_first).get(), _first, nullptr);
            _first = new Element<T>(value, nullptr, _last);
        } else {
            auto *buf = new Element<T>(value, nullptr, _first);
            _first->setPrevious(buf);
            _first = buf;
        }
        _length++;

    }

    LinkedList<T> *insertAt(size_t index, T value) {
        if (index >= _length || index < 0) {
            throw IndexOutOfRange();
        }
        Element<T> *buf = _first;
        for (size_t i = 0; i < index; i++) {
            buf = buf->getNext();
        }
        buf->set(value);
    }

    LinkedList<T> *concat(LinkedList<T> *list) {
        auto *buf = new LinkedList<T>(this);
        for (size_t i = 0; i < (*list).getLength(); i++) {
            (*buf).append((*list).get(i));
        }
        return buf;
    }

    T operator[](size_t index) const {
        return get(index);
    }

    LinkedList<T> *operator+(T item) {
        append(item);
    }

    LinkedList<T> *operator+(LinkedList<T> *list) {
        return concat(list);
    }


    void remove(size_t index) {
        if (index > _length || index < 0) {
            return;
        }
        if (index == 0) {
            Element<T> *nxt = (*_first).getNext();
            delete _first;
            _first = nxt;
            if (_first != nullptr) {
                (*_first).setPrevious(nullptr);
            }
            if (_length == 2) {
                _last = nullptr;
            }
        } else if (index == _length - 1) {
            Element<T> *prv = (*_last).getPrevious();
            delete _last;
            _last = prv;
            if (_last != nullptr) {
                (*_last).setNext(nullptr);
            }
            if (_length == 2) {
                (*_first) = (*_last);
                _last = nullptr;
            }
        } else {
            Element<T> *buf = (*_first).getNext();
            for (size_t i = 0; i < index; i++) {
                buf = (*buf).getNext();
            }
            Element<T> *nxt = (*buf).getNext();
            Element<T> *prv = (*buf).getPrevious();
            delete buf;
            (*prv).setNext(nxt);
            (*nxt).setPrevious(prv);
        }
        _length--;
    }

    void removeAll() {
        __clear__();
    }

private:
    void __clear__() {
        _length = 0;
        Element<T> *buf = _first;
        while (buf->getNext() != nullptr) {
            auto *tmp = buf->getNext();
            delete buf;
            buf = tmp;
        }
        _first = nullptr;
        _last = nullptr;
        delete buf;
    }
};

#endif //LAB2_LINKEDLIST_H
