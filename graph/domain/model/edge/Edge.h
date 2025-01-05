#ifndef LABA4_EDGE_H
#define LABA4_EDGE_H

#include <iostream>
#include "../../../core/define/template.h"

#define Edge s_Edge<Ep, Vp>
#define Vertex s_Vertex<Ep, Vp>

template $graph
class s_Edge {
public:
    Ep property;
    Vertex *start;
    Vertex *end;

    s_Edge(Ep _property, Vertex *_start, Vertex *_end): property(_property), start(_start), end(_end) {}

    bool operator==(const Edge &other) {
        if (property != other.property) return false;
        if (*start != *other.start) return false;
        if (*end != *other.end) return false;
        return true;
    }

    bool operator!=(const Edge &other) {
        return !(*this == other);
    }
};

template $graph
std::ostream &operator<<(std::ostream &os, const Edge &thiz) {
    os << "{" << thiz.property << ";";
    os << thiz.start->property << ";";
    os << thiz.end->property;
    os << "}";
    return os;
}

#endif //LABA4_EDGE_H
