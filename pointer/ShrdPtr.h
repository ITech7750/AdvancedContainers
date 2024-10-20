#ifndef LABA1_SHRDPTR_H
#define LABA1_SHRDPTR_H

#include "UnqPtr.h"

template<class T>
class ShrdPtr {
private:
    const UnqPtr<T> *unqPtr;

public:
    ShrdPtr() : unqPtr() {}

    explicit ShrdPtr(const UnqPtr<T>* ptr) : unqPtr(ptr) {}

    // Конструктор копирования
    ShrdPtr(const ShrdPtr<T>& other): unqPtr(other.unqPtr) {}

    const T* getValue() const {
        return unqPtr->getValue();
    }

    // Оператор присвоения копии
    ShrdPtr<T>& operator=(const ShrdPtr<T>& other) {
        unqPtr = other.unqPtr;
        return *this;
    };

    T* operator->() const {
        if (unqPtr != nullptr) return unqPtr->operator->();
        return nullptr;
    }

    T& operator*() const {
        return unqPtr->operator*();
    }

    const UnqPtr<T>* getOrigin() {
        return unqPtr;
    }

    void clearOrigin() {
        const_cast<UnqPtr<T>*>(unqPtr)->clear();
    }
};

#endif //LABA1_SHRDPTR_H