#ifndef LABA1_A_H
#define LABA1_A_H
#include <iostream>
// Класс для тестирования использования указателей
class A {
protected:
    int _value;
public:
    explicit A(int value): _value(value) {}

    int getValue() const {
        return _value;
    }

    virtual int getValueModified(int modifier) const {
        return _value + modifier;
    }

    bool operator==(const A &other) const {
        return other._value == _value;
    }

    friend std::ostream &operator<<(std::ostream &os, const A &other) {
        return os << "A(value=" << other._value << ")" << std::endl;
    }
};

#endif //LABA1_A_H
