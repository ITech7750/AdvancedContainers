#ifndef LAB2_DYNAMICARRAYUP_H
#define LAB2_DYNAMICARRAYUP_H

#include <stdexcept>
#include <utility>
#include <algorithm>
#include "../../pointer/UnqPtr.h"

template<class T>
class DynamicArrayUP {
private:
    UnqPtr<T[]> data;
    size_t capacity;
    size_t count;

    void ensureCapacity(size_t minCapacity) {
        if (minCapacity > capacity) {
            size_t newCapacity = std::max(minCapacity, capacity * 2);
            UnqPtr<T[]> newData(new T[newCapacity]);
            for (size_t i = 0; i < count; ++i) {
                newData[i] = std::move(data[i]);
            }
            data = std::move(newData);
            capacity = newCapacity;
        }
    }

public:
    DynamicArrayUP() : data(nullptr), capacity(0), count(0) {}

    explicit DynamicArrayUP(size_t initialCapacity)
        : data(new T[initialCapacity]()), capacity(initialCapacity), count(0) {}

    DynamicArrayUP(T* items, size_t size)
        : data(new T[size]), capacity(size), count(size) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = std::move(items[i]);
        }
    }

    DynamicArrayUP(const DynamicArrayUP<T>& other)
        : data(new T[other.capacity]), capacity(other.capacity), count(other.count) {
        for (size_t i = 0; i < other.count; ++i) {
            data[i] = other.data[i];
        }
    }

    DynamicArrayUP(DynamicArrayUP<T>&& other) noexcept
        : data(std::move(other.data)), capacity(other.capacity), count(other.count) {
        other.capacity = 0;
        other.count = 0;
    }

    DynamicArrayUP<T>& operator=(const DynamicArrayUP<T>& other) {
        if (this != &other) {
            data = UnqPtr<T[]>(new T[other.capacity]);
            capacity = other.capacity;
            count = other.count;
            for (size_t i = 0; i < other.count; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    DynamicArrayUP<T>& operator=(DynamicArrayUP<T>&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            capacity = other.capacity;
            count = other.count;
            other.capacity = 0;
            other.count = 0;
        }
        return *this;
    }

    size_t size() const {
        return count;
    }

    bool isEmpty() const {
        return count == 0;
    }

    T& get(size_t index) const {
        if (index >= count) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    void set(size_t index, T value) {
        if (index >= count) {
            throw std::out_of_range("Index out of range");
        }
        data[index] = std::move(value);
    }

    void append(T value) {
        ensureCapacity(count + 1);
        data[count++] = std::move(value);
    }

    void prepend(T value) {
        ensureCapacity(count + 1);
        for (size_t i = count; i > 0; --i) {
            data[i] = std::move(data[i - 1]);
        }
        data[0] = std::move(value);
        ++count;
    }

    void insertAt(size_t index, T value) {
        if (index > count) {
            throw std::out_of_range("Index out of range");
        }
        ensureCapacity(count + 1);
        for (size_t i = count; i > index; --i) {
            data[i] = std::move(data[i - 1]);
        }
        data[index] = std::move(value);
        ++count;
    }

    UnqPtr<DynamicArrayUP<T>> subarray(size_t start, size_t end) const {
        if (start >= count || end > count || start > end) {
            throw std::out_of_range("Invalid subarray range");
        }
        auto result = UnqPtr<DynamicArrayUP<T>>(new DynamicArrayUP<T>(end - start));
        for (size_t i = start; i < end; ++i) {
            result->append(data[i]);
        }
        return result;
    }

    T* getData() const {
        return data.get();
    }
};

#endif // LAB2_DYNAMICARRAYUP_H
