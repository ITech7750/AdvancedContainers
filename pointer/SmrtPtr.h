#ifndef LABA1_SMRTPTR_H
#define LABA1_SMRTPTR_H

#include <utility> // для std::move

template<class T>
class SmrtPtr {
private:
    size_t *referenceCount;
    T *value;

public:
    explicit SmrtPtr(T *value = nullptr) : value(value), referenceCount(new size_t(1)) {
        if (value == nullptr) {
            *referenceCount = 0;
        }
    }

    // Конструктор копирования
    SmrtPtr(const SmrtPtr &other) : value(other.value), referenceCount(other.referenceCount) {
        (*referenceCount)++;
    }

    template<class R>
    SmrtPtr(const SmrtPtr<R> &other) : value(other.value), referenceCount(other.getReferenceCount()) {
        (*referenceCount)++;
    }

    // Оператор присвоения копии
    SmrtPtr &operator=(const SmrtPtr &other) {
        if (this != &other) {
            clear();

            value = other.value;
            referenceCount = other.referenceCount;
            (*referenceCount)++;
        }
        return *this;
    }

    template<class R>
    SmrtPtr &operator=(const SmrtPtr<R> &other) {
        clear();

        value = other.value;
        referenceCount = other.getReferenceCount();
        (*referenceCount)++;
        return *this;
    }

    // Оператор присвоения перемещения
    SmrtPtr(SmrtPtr &&other) noexcept : value(other.value), referenceCount(other.referenceCount) {
        other.value = nullptr;
        other.referenceCount = new size_t(0);
    }

    SmrtPtr &operator=(SmrtPtr &&other) noexcept {
        if (this != &other) {
            clear();

            value = other.value;
            referenceCount = other.referenceCount;

            other.value = nullptr;
            other.referenceCount = new size_t(0);
        }
        return *this;
    }

    T *operator->() const {
        return value;
    }

    T &operator*() const {
        return *value;
    }

    size_t getCount() const {
        return *referenceCount;
    }

    size_t *getReferenceCount() const {
        return referenceCount;
    }

    ~SmrtPtr() {
        clear();
    }

private:
    void clear() {
        if (--(*referenceCount) == 0) {
            delete value;
            delete referenceCount;
        }
    }

};

#endif //LABA1_SMRTPTR_H
