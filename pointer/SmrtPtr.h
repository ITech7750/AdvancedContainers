#ifndef LABA1_SMARTPTR_H
#define LABA1_SMARTPTR_H

#include <cstddef>
#include <type_traits>
#include <stdexcept>

template<class T>
class SmrtPtr {
private:
    size_t *referenceCount;
    T *value;
public:
    explicit SmrtPtr(T *value = nullptr)
            : value(value), referenceCount(value ? new size_t(1) : nullptr) {}

    SmrtPtr(const SmrtPtr &other)
            : value(other.value), referenceCount(other.referenceCount) {
        if (referenceCount) {
            (*referenceCount)++;
        }
    }

    template<class R, typename std::enable_if<std::is_convertible<R*, T*>::value, int>::type = 0>
    SmrtPtr(const SmrtPtr<R> &other)
            : value(other.value), referenceCount(other.getReferenceCount()) {
        if (referenceCount) {
            (*referenceCount)++;
        }
    }

    SmrtPtr &operator=(const SmrtPtr &other) {
        if (this != &other) {
            clear();
            value = other.value;
            referenceCount = other.referenceCount;
            if (referenceCount) {
                (*referenceCount)++;
            }
        }
        return *this;
    }

    template<class R, typename std::enable_if<std::is_convertible<R*, T*>::value, int>::type = 0>
    SmrtPtr &operator=(const SmrtPtr<R> &other) {
        clear();
        value = other.value;
        referenceCount = other.getReferenceCount();
        if (referenceCount) {
            (*referenceCount)++;
        }
        return *this;
    }

    SmrtPtr(SmrtPtr &&other) noexcept
            : value(other.value), referenceCount(other.referenceCount) {
        other.value = nullptr;
        other.referenceCount = nullptr;
    }

    SmrtPtr &operator=(SmrtPtr &&other) noexcept {
        if (this != &other) {
            clear();
            value = other.value;
            referenceCount = other.referenceCount;
            other.value = nullptr;
            other.referenceCount = nullptr;
        }
        return *this;
    }

    SmrtPtr &operator=(std::nullptr_t) {
        clear();
        return *this;
    }

    T *operator->() const {
        return value;
    }

    T &operator*() const {
        if (!value) throw std::runtime_error("Dereferencing null pointer");
        return *value;
    }

    size_t getCount() const {
        return referenceCount ? *referenceCount : 0;
    }

    size_t *getReferenceCount() const {
        return referenceCount;
    }

    ~SmrtPtr() {
        clear();
    }

    template<class R>
    SmrtPtr<R> dynamic_pointer_cast() const {
        R *castedValue = dynamic_cast<R *>(value);
        return SmrtPtr<R>(castedValue, referenceCount);
    }

    template<class R>
    SmrtPtr<R> static_pointer_cast() const {
        R *castedValue = static_cast<R *>(value);
        return SmrtPtr<R>(castedValue, referenceCount);
    }

    template<class R>
    SmrtPtr<R> const_pointer_cast() const {
        R *castedValue = const_cast<R *>(value);
        return SmrtPtr<R>(castedValue, referenceCount);
    }

    template<class R>
    SmrtPtr<R> reinterpret_pointer_cast() const {
        R *castedValue = reinterpret_cast<R *>(value);
        return SmrtPtr<R>(castedValue, referenceCount);
    }

private:
    void clear() {
        if (referenceCount) {
            if (--(*referenceCount) == 0) {
                delete value;
                delete referenceCount;
            }
        }
        value = nullptr;
        referenceCount = nullptr;
    }

    template<class R>
    SmrtPtr(R *value, size_t *referenceCount)
            : value(value), referenceCount(referenceCount) {
        if (referenceCount) {
            (*referenceCount)++;
        }
    }

    template<class R>
    friend class SmrtPtr;
};

#endif //LABA1_SMARTPTR_H
