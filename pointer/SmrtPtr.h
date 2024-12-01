#ifndef LABA1_SMARTPTR_H
#define LABA1_SMARTPTR_H


template<class T>
class SmrtPtr {
private:
    size_t *referenceCount;
    T *value;

public:
    explicit SmrtPtr(T *value = nullptr)
            : value(value), referenceCount(value ? new size_t(1) : nullptr) {}

    // Конструктор копирования
    SmrtPtr(const SmrtPtr &other)
            : value(other.value), referenceCount(other.referenceCount) {
        if (referenceCount) {
            (*referenceCount)++;
        }
    }

    template<class R>
    SmrtPtr(const SmrtPtr<R> &other)
            : value(other.value), referenceCount(other.getReferenceCount()) {
        if (referenceCount) {
            (*referenceCount)++;
        }
    }

    // Оператор присвоения копии
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

    template<class R>
    SmrtPtr &operator=(const SmrtPtr<R> &other) {
        clear();

        value = other.value;
        referenceCount = other.getReferenceCount();
        if (referenceCount) {
            (*referenceCount)++;
        }
        return *this;
    }

    // Оператор присвоения перемещения
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

    T *operator->() const {
        return value;
    }

    T &operator*() const {
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
};

#endif //LABA1_SMARTPTR_H
