#ifndef LABA1_UNQPTR_H
#define LABA1_UNQPTR_H

#include <cstddef>
#include <stdexcept>

template<class T>
class UnqPtr {
private:
    T* value;

public:
    UnqPtr() : value(nullptr) {}

    UnqPtr(T* value) : value(value) {}

    UnqPtr(const T& value) : value(new T(value)) {}

    // Конструктор копирования
    UnqPtr(const UnqPtr<T>& other) = delete;

    // Оператор присваивания копированием
    UnqPtr& operator=(const UnqPtr<T>& other) = delete;

    // Конструктор перемещения
    UnqPtr(UnqPtr<T>&& other) noexcept
            : value(other.value) {
        other.value = nullptr;
    }

    ~UnqPtr() {
        clear();
    }

    T* getValue() const {
        return value;
    }

    T* operator->() const {
        return value;
    }

    T& operator*() const {
        return *value;
    }

    UnqPtr<T>& operator=(UnqPtr<T>&& other) noexcept {
        if (this != &other) {
            delete value;
            value = other.value;
            other.value = nullptr;
        }
        return *this;
    }

    UnqPtr<T>& operator=(T* val) {
        if (value != val) {
            delete value;
            value = val;
        }
        return *this;
    }

    void setValue(const T& value) {
        clear();
        this->value = new T(value);
    }

    void reset(T* newValue = nullptr) {
        if (value != newValue) {
            delete value;
            value = newValue;
        }
    }

    T* release() {
        T* temp = value;
        value = nullptr;
        return temp;
    }

    void clear() {
        if (value != nullptr) {
            delete value;
            value = nullptr;
        }
    }
    operator bool() const {
        return value != nullptr;
    }
};

template<class T>
class UnqPtr<T[]> {
private:
    T* value;

public:
    UnqPtr() : value(nullptr) {}

    explicit UnqPtr(T* value) : value(value) {}

    explicit UnqPtr(size_t size) : value(size > 0 ? new T[size]() : nullptr) {}

    UnqPtr(const UnqPtr<T[]>& other) = delete;

    UnqPtr& operator=(const UnqPtr<T[]>& other) = delete;

    UnqPtr(UnqPtr<T[]>&& other) noexcept : value(other.value) {
        other.value = nullptr;
    }

    UnqPtr<T[]>& operator=(UnqPtr<T[]>&& other) noexcept {
        if (this != &other) {
            delete[] value;
            value = other.value;
            other.value = nullptr;
        }
        return *this;
    }

    ~UnqPtr() {
        clear();
    }

    T& operator[](size_t index) {
        if (!value) throw std::runtime_error("Dereferencing null UnqPtr");
        return value[index];
    }

    const T& operator[](size_t index) const {
        if (!value) throw std::runtime_error("Dereferencing null UnqPtr");
        return value[index];
    }

    void clear() {
        delete[] value;
        value = nullptr;
    }

    void reset(T* newValue = nullptr) {
        if (value != newValue) {
            delete[] value;
            value = newValue;
        }
    }

    T* release() {
        T* temp = value;
        value = nullptr;
        return temp;
    }

    operator bool() const {
        return value != nullptr;
    }

    T* getValue() const {
        return value;
    }
};


#endif // LABA1_UNQPTR_H
