#ifndef LAB2_WRONGTYPE_H
#define LAB2_WRONGTYPE_H

#include <utility>

#include "Exception.h"
#include "../Definition.h"

class WrongType : public Exception {
public:
    WrongType() : Exception("wrong type") {}

    explicit WrongType(String message) : Exception(std::move(message)) {}
};

#endif //LAB2_WRONGTYPE_H
