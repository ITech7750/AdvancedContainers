#ifndef LABA1_UNQPTR_H
#define LABA1_UNQPTR_H

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

#endif // LABA1_UNQPTR_H
