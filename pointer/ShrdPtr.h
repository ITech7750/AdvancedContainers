#ifndef LABA1_SHRDPTR_H
#define LABA1_SHRDPTR_H

#include <cstddef>
#include <stdexcept>

template<class T>
class WeakPtr;

template<class T>
class ShrdPtr {
private:
    T* value;
    size_t* referenceCount;
    size_t* weakReferenceCount;

public:
    ShrdPtr() : value(nullptr), referenceCount(nullptr), weakReferenceCount(nullptr) {}

    explicit ShrdPtr(T* ptr)
        : value(ptr), referenceCount(new size_t(1)), weakReferenceCount(new size_t(0)) {}

    ShrdPtr(const ShrdPtr<T>& other)
        : value(other.value), referenceCount(other.referenceCount), weakReferenceCount(other.weakReferenceCount) {
        if (referenceCount) {
            ++(*referenceCount);
        }
    }

    ShrdPtr(ShrdPtr<T>&& other) noexcept
        : value(other.value), referenceCount(other.referenceCount), weakReferenceCount(other.weakReferenceCount) {
        other.value = nullptr;
        other.referenceCount = nullptr;
        other.weakReferenceCount = nullptr;
    }

    explicit ShrdPtr(const WeakPtr<T>& weakPtr) {
        if (!weakPtr.expired()) {
            value = weakPtr.value;
            referenceCount = weakPtr.referenceCount;
            if (referenceCount) {
                ++(*referenceCount);
            }
        } else {
            value = nullptr;
            referenceCount = nullptr;
        }
    }
    ShrdPtr<T>& operator=(const ShrdPtr<T>& other) {
        if (this != &other) {
            clear();
            value = other.value;
            referenceCount = other.referenceCount;
            weakReferenceCount = other.weakReferenceCount;
            if (referenceCount) {
                ++(*referenceCount);
            }
        }
        return *this;
    }

    ShrdPtr<T>& operator=(ShrdPtr<T>&& other) noexcept {
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

    ~ShrdPtr() {
        clear();
    }

    T* operator->() const {
        return value;
    }

    T& operator*() const {
        if (!value) throw std::runtime_error("Dereferencing null ShrdPtr");
        return *value;
    }

    size_t use_count() const {
        return referenceCount ? *referenceCount : 0;
    }

    bool unique() const {
        return use_count() == 1;
    }

    void reset(T* ptr = nullptr) {
        clear();
        if (ptr) {
            value = ptr;
            referenceCount = new size_t(1);
            weakReferenceCount = new size_t(0);
        }
    }

    T* get() const {
        return value;
    }

    friend class WeakPtr<T>;

private:
    void clear() {
        if (referenceCount) {
            if (--(*referenceCount) == 0) {
                delete value;
                if (*weakReferenceCount == 0) {
                    delete weakReferenceCount;
                }
                delete referenceCount;
            }
        }
        value = nullptr;
        referenceCount = nullptr;
        weakReferenceCount = nullptr;
    }
};

#endif // LABA1_SHRDPTR_H
