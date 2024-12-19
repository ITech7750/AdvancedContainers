#ifndef LAB2_ITERABLE_H
#define LAB2_ITERABLE_H

#include <iostream>

template<class T>
class Iterable {
public:
    virtual T get(size_t index) const = 0;

    T operator[](size_t index) const {
        return get(index);
    }

    virtual size_t size() const = 0;

    virtual bool isEmpty() = 0;

    friend std::ostream& operator << (std::ostream &os, const Iterable &thiz)
    {
        os << "[" << thiz.get(0);
        for (size_t i = 1; i<thiz.size(); i++) {
            os << ", " << thiz.get(i);
        }
        os << "]";
        return os;
    }

    virtual bool operator==(const Iterable<T>& other) const{
        if (other.size() != size()) return false;
        for (size_t i = 0;i<size();i++) {
            if (other[i] != get(i)) return false;
        }
        return true;
    }
};

#endif //LAB2_ITERABLE_H
