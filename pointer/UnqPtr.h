#ifndef LABA1_UNQPTR_H
#define LABA1_UNQPTR_H

template<class T>
class UnqPtr {
private:
    T *value;

public:
    UnqPtr() : value(nullptr) {}

    UnqPtr(T *value) : value(value) {}

    UnqPtr(const T& value) : value(new T(value)) {}

    // Конструктор копирования
    UnqPtr(const UnqPtr<T>& other) = delete;

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

    UnqPtr<T>& operator=(UnqPtr<T>&& other) {
        delete value;
        value = other.value;
        other.value = nullptr;
        return *this;
    }

    UnqPtr<T>& operator=(T* val) {
        delete value;
        value = val;
        return *this;
    }

    void setValue(T value) {
        value = new T(value);
    }

    void clear() {
        delete value;
        value = nullptr;
    }
private:

};


#endif //LABA1_UNQPTR_H
