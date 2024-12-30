#ifndef LABA1_SHRDPTR_H
#define LABA1_SHRDPTR_H

#include "UnqPtr.h"

template<class T>
class ShrdPtr {
private:
    const UnqPtr<T> *unqPtr;

public:
    ShrdPtr() : unqPtr(nullptr) {}

    explicit ShrdPtr(const UnqPtr<T>* ptr) : unqPtr(ptr) {}

    // Конструктор копирования
    ShrdPtr(const ShrdPtr<T>& other) : unqPtr(other.unqPtr) {}

    const T* getValue() const {
        return unqPtr ? unqPtr->getValue() : nullptr;
    }

    // Оператор присвоения копии
    ShrdPtr<T>& operator=(const ShrdPtr<T>& other) {
        unqPtr = other.unqPtr;
        return *this;
    }

    T* operator->() const {
        return unqPtr ? unqPtr->getValue() : nullptr;
    }

    T& operator*() const {
        return *(unqPtr->getValue());
    }

    const UnqPtr<T>* getOrigin() const {
        return unqPtr;
    }

    void clearOrigin() {
        if (unqPtr) {
            const_cast<UnqPtr<T>*>(unqPtr)->clear();
        }
    }
};

#endif //LABA1_SHRDPTR_H