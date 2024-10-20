#ifndef LAB2_DYNAMICARRAY_H
#define LAB2_DYNAMICARRAY_H

#include <cstdlib>
#include <algorithm>
#include "../../util/exception/IndexOutOfRange.h"

template<class T>
class DynamicArray {
private:
    int _length; // количество элементов, которое можно поместить в массив
    int _size; // количество элементов в мссиве
    T *_items;

public:
    DynamicArray() {
        _length = 0;
        _size = 0;
        _items = new T[0];
    }

    DynamicArray(int count, T *items) {
        _length = count;
        _size = count;
        _items = items;
    }

    explicit DynamicArray(int size) {
        _length = size;
        _size = size;
        _items = new T[size];
    }

    DynamicArray(const DynamicArray<T> &array) {
        _length = array.getSize();
        _size = array.getSize();
        _items = new T[_length];
        for (int i = 0; i < _size; i++) {
            _items[i] = array.get(i);
        }
    }

    int getSize() const {
        return _size;
    }

    int getLength() {
        return _length;
    }

    T get(int index) const {
        if (index >= _size || index < 0) {
            throw IndexOutOfRange();
        }
        return _items[index];
    }

    T operator[](int index) const {
        return get(index);
    }

    void set(int index, T value) {
        if (index >= _length)
            throw IndexOutOfRange();

        _items[index] = value;
    }

    void add(T value) {
        if (_length == _size) {
            resize(_length + 5);
        }
        _items[_size] = value;
        _size++;
    }

    void resize(int newSize) {
        _length = newSize;
        T *tmp = new T[_length];
        std::copy(_items, _items + _size, tmp);
        if (_size > _length) _size = _length;
        delete[] _items;
        _items = tmp;
    }

    void println() {
        std::cout << "[";
        if (_size > 0) std::cout << _items[0];
        for (int i = 1; i < _size; i++) {
            std::cout << ", ";
            std::cout << _items[i];
        }
        std::cout << "]" << "\n";
    }

    void print() {
        std::cout << "[";
        if (_size > 0) std::cout << _items[0];
        for (int i = 1; i < _size; i++) {
            std::cout << ", ";
            std::cout << _items[i];
        }
        std::cout << "]";
    }

    ~DynamicArray() { delete[] _items; }

};

#endif //LAB2_DYNAMICARRAY_H
