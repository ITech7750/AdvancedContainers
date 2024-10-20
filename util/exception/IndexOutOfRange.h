#ifndef LAB2_INDEXOUTOFRANGE_H
#define LAB2_INDEXOUTOFRANGE_H


#include "Exception.h"

class IndexOutOfRange : public Exception {
public:
    IndexOutOfRange() : Exception("Exception IndexOutOfRange : index out of range") {}
};


#endif //LAB2_INDEXOUTOFRANGE_H
