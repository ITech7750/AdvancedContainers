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
    LinkedListUP(): _first(nullptr), _last(nullptr), _length(0) {}

    LinkedListUP(const size_t &count, const T *items) : LinkedListUP() {
        for (size_t i = 0; i < count; i++) {
            append(items[i]);
        }
    }

    LinkedListUP(const LinkedListUP<T> &list) : LinkedListUP() {
        for (size_t i = 0; i < list.size(); i++) {
            append(list.get(i));
        }
    }

    ~LinkedListUP() {
        _clear_();
    }

    T getFirst() {
        if (_first.getValue() != nullptr) {
            return _first->get();
        } else {
            throw IndexOutOfRange();
        }

    }

    T getLast() {
        if (_last.getValue() != nullptr) {
            return _last->get();
        } else {
            throw IndexOutOfRange();
        }

    }

    T get(size_t index) const {
        size_t i = 0;
        if (index < 0 || index >= _length) {
            throw IndexOutOfRange();
        }
        ShrdPtr<ElementUP<T>> buf(&_first);
        while (i < index) {
            i++;
            buf = buf->getNext();
        }
        return buf->get();
    }

    size_t size() const {
        return _length;
    }

    bool isEmpty() {
        return _length == 0;
    }

    LinkedListUP<T> *getSublist(size_t start, size_t end) {
        if (start >= _length || start >= end) {
            throw std::runtime_error("error");
        }
        auto *buf = new LinkedListUP<T>();
        for (size_t i = 0; i < _length; i++) {
            if (i >= start && i < end) {
                buf->append(get(i));
            }
        }
        return buf;
    }

    void append(T value) {
        if (_first.getValue() == nullptr) {
            _first = new ElementUP<T>(value);
        } else if (_last.getValue() == nullptr) {
            _last = new ElementUP<T>(value, ShrdPtr<ElementUP<T>>(&_first), ShrdPtr<ElementUP<T>>());
            _first->setNext(ShrdPtr(&_last));
        } else {
            auto nptr = new UnqPtr<ElementUP<T>>(*(_last.getValue()));
            _last->getPrevious()->setNext(ShrdPtr(nptr));
            auto buf = UnqPtr(ElementUP<T>(value, ShrdPtr<ElementUP<T>>(nptr), ShrdPtr<ElementUP<T>>()));
            _last = std::move(buf);
            _last->getPrevious()->setNext(ShrdPtr(&_last));
        }
        _length++;
    }

    void prepend(T value) {
        if (_first.getValue() == nullptr) {
            _first = new ElementUP<T>(value);
        } else if (_last.getValue() == nullptr) {
            _last = std::move(_first);
            _first = new ElementUP<T>(value, ShrdPtr<ElementUP<T>>(), ShrdPtr<ElementUP<T>>(&_last));
        } else {
            auto nptr = new UnqPtr<ElementUP<T>>(*(_first.getValue()));
            _first->getNext()->setPrevious(ShrdPtr(nptr));
            auto buf = UnqPtr(ElementUP<T>(value, ShrdPtr<ElementUP<T>>(), ShrdPtr<ElementUP<T>>(nptr)));
            _first = std::move(buf);
            _first->getNext()->setPrevious(ShrdPtr(&_first));
        }
        _length++;

    }

    LinkedListUP<T> *insertAt(size_t index, T value) {
        if (index >= _length || index < 0) {
            throw IndexOutOfRange();
        }
        ShrdPtr<ElementUP<T>> buf(&_first);
        for (size_t i = 0; i < index; i++) {
            buf = buf->getNext();
        }
        buf->set(value);
        return this;
    }

    LinkedListUP<T> *concat(LinkedListUP<T> *list) {
        auto *buf = new LinkedListUP<T>(this);
        for (size_t i = 0; i < (*list).getLength(); i++) {
            (*buf).append((*list).get(i));
        }
        return buf;
    }

    T operator[](size_t index) const {
        return get(index);
    }

    LinkedListUP<T> *operator+(T item) {
        append(item);
    }

    LinkedListUP<T> *operator+(LinkedListUP<T> *list) {
        return concat(list);
    }


    void remove(size_t index) {
        if (index > _length || index < 0) {
            return;
        }
        if (index == _length - 1) {
            ShrdPtr<ElementUP<T>> prv = _last->getPrevious();
            delete _last;
            if (_length != 2) {
                _last = UnqPtr<ElementUP<T>>(prv.operator->());
                if (_last.value != nullptr) {
                    _last->setNext(ShrdPtr<ElementUP<T>>());
                }
            }
        } else {
            ShrdPtr<ElementUP<T>> buf = _first->getNext();
            for (size_t i = 0; i < index; i++) {
                buf = buf->getNext();
            }
            ShrdPtr<ElementUP<T>> nxt = buf->getNext();
            ShrdPtr<ElementUP<T>> prv = buf->getPrevious();
            delete buf.operator->();
            prv->setNext(nxt);
            nxt->setPrevious(prv);
        }
        _length--;
    }

    void removeAll() {
        _clear_();
    }

private:
    void _clear_() {
        _length = 0;

        ShrdPtr<ElementUP<T>> buf(&_first);
        while (buf->getNext().getOrigin() != nullptr) {
            buf = buf->getNext();
            buf->getPrevious().clearOrigin();
        }
        buf.clearOrigin();
        _first = nullptr;
        _last = nullptr;
    }
};

#endif //LAB2_LINKEDLISTUP_H
