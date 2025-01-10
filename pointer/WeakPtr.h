#ifndef LABA1_WEAKPTR_H
#define LABA1_WEAKPTR_H

#include <cstddef>

template<class T>
class ShrdPtr;

template<class T>
class WeakPtr {
private:
    T* value;
    size_t* referenceCount;
    size_t* weakReferenceCount;

public:
    WeakPtr() : value(nullptr), referenceCount(nullptr), weakReferenceCount(nullptr) {}

    WeakPtr(const ShrdPtr<T>& sharedPtr)
    : value(sharedPtr.value), referenceCount(sharedPtr.referenceCount), weakReferenceCount(sharedPtr.weakReferenceCount) {
        if (weakReferenceCount) {
            ++(*weakReferenceCount);
        }
    }


    WeakPtr(const WeakPtr<T>& other)
        : value(other.value), referenceCount(other.referenceCount), weakReferenceCount(other.weakReferenceCount) {
        if (weakReferenceCount) {
            ++(*weakReferenceCount);
        }
    }

    WeakPtr(WeakPtr<T>&& other) noexcept
        : value(other.value), referenceCount(other.referenceCount), weakReferenceCount(other.weakReferenceCount) {
        other.value = nullptr;
        other.referenceCount = nullptr;
        other.weakReferenceCount = nullptr;
    }

    WeakPtr<T>& operator=(const WeakPtr<T>& other) {
        if (this != &other) {
            clear();
            value = other.value;
            referenceCount = other.referenceCount;
            weakReferenceCount = other.weakReferenceCount;
            if (weakReferenceCount) {
                ++(*weakReferenceCount);
            }
        }
        return *this;
    }

    WeakPtr<T>& operator=(WeakPtr<T>&& other) noexcept {
        if (this != &other) {
            clear();
            value = other.value;
            referenceCount = other.referenceCount;
            weakReferenceCount = other.weakReferenceCount;
            other.value = nullptr;
            other.referenceCount = nullptr;
            other.weakReferenceCount = nullptr;
        }
        return *this;
    }

    ~WeakPtr() {
        clear();
    }
    ShrdPtr<T> lock() const {
        if (referenceCount && *referenceCount > 0) {
            return ShrdPtr<T>(*this);
        }
        return ShrdPtr<T>();
    }


    bool expired() const {
        return !referenceCount || *referenceCount == 0;
    }

    size_t use_count() const {
        return referenceCount ? *referenceCount : 0;
    }

private:
    void clear() {
        if (weakReferenceCount) {
            if (--(*weakReferenceCount) == 0) {
                delete weakReferenceCount;
                weakReferenceCount = nullptr;
            }
        }
        value = nullptr;
        referenceCount = nullptr;
    }



    friend class ShrdPtr<T>;
};

#endif // LABA1_WEAKPTR_H
