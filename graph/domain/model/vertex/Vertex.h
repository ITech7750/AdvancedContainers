#ifndef LABA4_VERTEX_H
#define LABA4_VERTEX_H
#pragma once

#include "../../../../util/Definition.h"
#include "../../../../collectionunqptr/dinamicarray/DynamicArray.h"
#include "../../../core/define/template.h"

#define Edge s_Edge<Ep, Vp>
#define Vertex s_Vertex<Ep, Vp>

template $graph
class s_Vertex {
public:
    Vp property;
    DynamicArray<Edge *> in;
    DynamicArray<Edge *> out;

    s_Vertex(Vp _property,  DynamicArray<Edge *> _in, DynamicArray<Edge *> _out): property(_property), in(_in), out(_out) {}

    bool operator==(const Vertex &other) {
        if (in.size() != other.in.size() || out.size() != other.out.size()) return false;
        if (property != other.property) return false;
        for (int i = 0;i<in.size();i++) {
            if (*(in[i]) != *(other.in[i])) return false;
        }
        for (int i = 0;i<out.size();i++) {
            if (*(out[i]) != *(other.out[i])) return false;
        }
        return true;
    }

    bool operator!=(const Vertex &other) {
        return !(*this == other);
    }
};

template $graph
std::ostream &operator<<(std::ostream &os, const Vertex &thiz) {
    os << "{" << thiz.property << ";";
    for (int i = 0;i<thiz.in.size();i++) {
        os << thiz.in[i].property << " ";
    }
    os << ";";
    for (int i = 0;i<thiz.out.size();i++) {
        os << thiz.out[i].property << " ";
    }
    os << "}";
    return os;
}

#endif //LABA4_VERTEX_H
