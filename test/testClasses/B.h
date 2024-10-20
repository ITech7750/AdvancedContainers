#ifndef LABA1_B_H
#define LABA1_B_H

#include "A.h"

// Класс-наследник A для тестирования использования указателей
class B : public A {
private:
    int _antiValue;
public:
    explicit B(int value) : A(value) {
        _value = value;
        _antiValue = value * -1;
    }

    int getAntiValue() const {
        return _antiValue;
    }

    int getValueModified(int modifier) const override {
        return _value + (_antiValue / modifier);
    }

    bool operator==(const B &other) const {
        return other._value == _value && other._antiValue == _antiValue;
    }

    friend std::ostream &operator<<(std::ostream &os, const B &other) {
        return os << "B(value=" << other._value << ", _antiValue=" << other._antiValue << ")" << std::endl;
    }

};

#endif //LABA1_B_H
