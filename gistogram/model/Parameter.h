
#ifndef LABA3_PARAMETER_H
#define LABA3_PARAMETER_H
#include <functional>

#include "../../util/Definition.h"


template <class K, class V>
class Parameter {
public:
    K name;
    std::function<bool(V)> predicate;
};

#endif //LABA3_PARAMETER_H
