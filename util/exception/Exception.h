#ifndef LAB2_EXCEPTION_H
#define LAB2_EXCEPTION_H

#include <utility>

#include "../Definition.h"

class Exception : std::exception {
public:
    String _message;

    Exception(String message) {
        _message = std::move(message);
    }
};


#endif //LAB2_EXCEPTION_H
