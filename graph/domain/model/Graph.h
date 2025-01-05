#ifndef LABA4_GRAPH_H
#define LABA4_GRAPH_H

#include "../../core/define/template.h"
#include "vertex/Vertex.h"
#include "edge/Edge.h"
#include <iostream>

#define Graph s_Graph<Ep, Vp>

template $graph
class s_Graph {
public:
    DynamicArray<Vertex*> vertices;
    DynamicArray<Edge*> edge;

    void addTo(Vp p1, Vp p2, Ep edgeProperty) {
        add(p1, p2, edgeProperty, false);
    }

    void addBoth(Vp p1, Vp p2, Ep edgeProperty) {
        add(p1, p2, edgeProperty, true);
    }

    void addEdge(Vertex *v1, Vertex *v2, Ep edgeProperty) {
        Edge* e = new Edge(edgeProperty, v1, v2);
        edge.add(e);
        v1->out.add(e);
        v2->in.add(e);
    }

    void deleteEdge(Ep property) {
        for (int i = 0;i<edge.size();i++) {
            if (edge[i]->property == property) {
                Edge* e = edge[i];
                removeEdgeFromVertex(e);
                delete e;
                break;
            }
        }
    }

    void deleteVertex(Vp property) {
        for (int i = 0;i<vertices.size();i++) {
            if (vertices[i]->property == property) {
                Vertex *v = vertices[i];
                for (int j = 0;j<v->out.size();j++) {
                    removeEdgeFromVertex(v->out[j]);
                }
                for (int j = 0;j<v->in.size();j++) {
                    removeEdgeFromVertex(v->in[j]);
                }
                vertices.removeAt(i);
                delete v;
            }
        }
    }

    void editVertex(Vertex *vertex, Vp newProperty) {
        for (auto v: vertices) {
            if (v == vertex) {
                v->property = newProperty;
                break;
            }
        }
    }

    void editEdge(Edge *_edge, Ep newProperty) {
        for (auto e: edge) {
            if (e == _edge) {
                e->property = newProperty;
                break;
            }
        }
    }

private:

    void removeEdgeFromVertex(Edge* _edge) {
        Vertex *v1 = _edge->start;
        Vertex *v2 = _edge->end;
        for (int i = 0;i<v1->out.size();i++) {
            if (v1->out[i] == _edge) {
                v1->out.removeAt(i);
                break;
            }
        }
        for (int i = 0;i<v2->in.size();i++) {
            if (v2->in[i] == _edge) {
                v2->in.removeAt(i);
                break;
            }
        }
        for (int i = 0;i<edge.size();i++) {
            if (edge[i] == _edge) {
                edge.removeAt(i);
                i--;
            }
        }
    }

    void add(Vp p1, Vp p2, Ep edgeProperty, bool both) {
        Vertex *v1;
        Vertex *v2;
        Edge *newEdge;
        Edge *reverseEdge;

        bool edgeFound = false;
        bool reverseEdgeFound = false;
        bool v1Found = false;
        bool v2Found = false;

        for (auto v: vertices) {
            if ((*v).property == p1 && !v1Found) {
                v1 = v;
                v1Found = true;
            }
            if ((*v).property == p2 && !v2Found) {
                v2 = v;
                v2Found = true;
            }
            if (v1Found && v2Found) break;
        }

        if (!v1Found) {
            v1 = new Vertex(p1, DynamicArray<Edge*>(), DynamicArray<Edge*>());
            vertices.add(v1);
        }

        if (!v2Found) {
            v2 = new Vertex(p2, DynamicArray<Edge*>(), DynamicArray<Edge*>());
            vertices.add(v2);
        }

        for (auto e: edge) {
            if (e->property == edgeProperty && *(e->start) == *v1 && *(e->end) == *v2) {
                newEdge = e;
                edgeFound = true;
            }
            if (both && (e->property == edgeProperty && *(e->start) == *v2 && *(e->end) == *v1)) {
                reverseEdge = e;
                reverseEdgeFound = true;
            }
            if (reverseEdgeFound && edgeFound) break;
        }

        if (!edgeFound) {
            newEdge = new Edge(edgeProperty, v1, v2);
            v1->out.add(newEdge);
            v2->in.add(newEdge);
            edge.add(newEdge);
        }

        if (both && !reverseEdgeFound) {

        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Graph &thiz) {
        if (thiz.edge.size() == 0) {
            os << "{}";
        }
        for (int i = 0;i<thiz.edge.size();i++) {
            os << *thiz.edge[i];
            if (i != thiz.edge.size() - 1) {
                os << ",";
            }
        }
        return os;
    }
};



#endif //LABA4_GRAPH_H
