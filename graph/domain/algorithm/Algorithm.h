#ifndef LABA4_ALGORITHM_H
#define LABA4_ALGORITHM_H

#include "../model/Graph.h"
#include "../../core/define/interface.h"

interface Algorithm {
public:
    template $graph
    Graph operator()(Graph graph) = delete;
};

#endif //LABA4_ALGORITHM_H
