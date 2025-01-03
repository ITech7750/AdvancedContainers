#ifndef LAB2_DYNAMICARRAY_H
#define LAB2_DYNAMICARRAY_H

#include <iostream>
#include <algorithm>
#include "../../pointer/UnqPtr.h"
#include "../../util/exception/IndexOutOfRange.h"

template<class T>
class DynamicArray {
private:
    size_t _capacity; // максимальная емкость массива
    size_t _size;     // текущий размер
    UnqPtr<T[]> _items;

    void ensureCapacity(size_t minCapacity) {
        if (_capacity < minCapacity) {
            resize(std::max(minCapacity, _capacity * 2)); // Удвоение емкости для эффективного роста
        }
    }

public:
    DynamicArray() : _capacity(1), _size(0), _items(UnqPtr<T[]>(new T[1])) {}

    DynamicArray(size_t count, T* items)
        : _capacity(count), _size(count), _items(UnqPtr<T[]>(new T[count])) {
        std::move(items, items + count, _items.getValue());
    }

    explicit DynamicArray(size_t size)
        : _capacity(size), _size(size), _items(UnqPtr<T[]>(new T[size])) {}

    DynamicArray(const DynamicArray<T>& other)
        : _capacity(other._capacity), _size(other._size), _items(UnqPtr<T[]>(new T[other._capacity])) {
        std::copy(other._items.getValue(), other._items.getValue() + other._size, _items.getValue());
    }

    DynamicArray(DynamicArray<T>&& other) noexcept
        : _capacity(other._capacity), _size(other._size), _items(std::move(other._items)) {
        other._capacity = 0;
        other._size = 0;
    }

    DynamicArray<T>& operator=(DynamicArray<T>&& other) noexcept {
        if (this != &other) {
            _capacity = other._capacity;
            _size = other._size;
            _items = std::move(other._items);
            other._capacity = 0;
            other._size = 0;
        }
        return *this;
    }

    size_t size() const {
        return _size;
    }

    bool isEmpty() const {
        return _size == 0;
    }

    const T& get(size_t index) const {
        if (index >= _size) throw IndexOutOfRange();
        return _items.getValue()[index];
    }

    void set(size_t index, T value) {
        if (index >= _size) throw IndexOutOfRange();
        _items.getValue()[index] = std::move(value);
    }

    void add(T value) {
        ensureCapacity(_size + 1);
        _items.getValue()[_size++] = std::move(value);
    }

    void prepend(T value) {
        ensureCapacity(_size + 1);
        std::move_backward(_items.getValue(), _items.getValue() + _size, _items.getValue() + _size + 1);
        _items.getValue()[0] = std::move(value);
        ++_size;
    }

    void insertAt(size_t index, T value) {
        if (index > _size) throw IndexOutOfRange();
        ensureCapacity(_size + 1);
        std::move_backward(_items.getValue() + index, _items.getValue() + _size, _items.getValue() + _size + 1);
        _items.getValue()[index] = std::move(value);
        ++_size;
    }

    void resize(size_t newCapacity) {
        if (newCapacity < _size) _size = newCapacity;
        UnqPtr<T[]> newItems(new T[newCapacity]);
        std::move(_items.getValue(), _items.getValue() + _size, newItems.getValue());
        _items = std::move(newItems);
        _capacity = newCapacity;
    }

    UnqPtr<DynamicArray<T>> getSubarray(size_t start, size_t end) const {
        if (start >= _size || end > _size || start > end) throw IndexOutOfRange();
        size_t newSize = end - start;
        auto subArray = UnqPtr<DynamicArray<T>>(new DynamicArray<T>(newSize));
        std::move(_items.getValue() + start, _items.getValue() + end, subArray->_items.getValue());
        subArray->_size = newSize;
        return subArray;
    }

    void swap(size_t index1, size_t index2) {
        if (index1 >= _size || index2 >= _size) throw IndexOutOfRange();
        std::swap(_items.getValue()[index1], _items.getValue()[index2]);
    }
};

#endif //LAB2_DYNAMICARRAY_H
