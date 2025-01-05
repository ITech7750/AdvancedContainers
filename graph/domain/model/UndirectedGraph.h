#ifndef GISTOGRAMBAG_UNDIRECTEDGRAPH_H
#define GISTOGRAMBAG_UNDIRECTEDGRAPH_H

#include "../../core/define/template.h"
#include "vertex/Vertex.h"
#include "edge/Edge.h"
#include <iostream>

#define UndirectedGraph s_UndirectedGraph<Ep, Vp>

template $graph
class s_UndirectedGraph {
public:
    DynamicArray<Vertex*> vertices;
    DynamicArray<Edge*> edge;

    void addTo(Vp p1, Vp p2, Ep edgeProperty) {
        add(p1, p2, edgeProperty);
    }

    void addEdge(Vertex *v1, Vertex *v2, Ep edgeProperty) {
        Edge* e = new Edge(edgeProperty, v1, v2);
        edge.add(e);
        v1->out.add(e);
        v2->out.add(e);
    }


    void deleteEdge(Ep property) {
        for (int i = 0;i<edge.size();i++) {
            if (edge[i]->property == property) {
                Edge* e = edge[i];
                edge.removeAt(i);
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
                    Edge *e = v->out[j];
                    removeEdgeFromVertex(e);
                    j--;
                }
                vertices.removeAt(i);
                delete v;
                break;
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
            }
        }
        for (int i = 0;i<v2->out.size();i++) {
            if (v2->out[i] == _edge) {
                v2->out.removeAt(i);
            }
        }
        for (int i = 0;i<edge.size();i++) {
            if (edge[i]->property == _edge->property) {
                edge.removeAt(i);
                i--;
            }
        }
    }

    void add(Vp p1, Vp p2, Ep edgeProperty) {
        Vertex *v1;
        Vertex *v2;
        Edge *newEdge;

        bool edgeFound = false;
        bool v1Found = false;
        bool v2Found = false;

        for (int i = 0;i<vertices.size();i++) {
            auto v = vertices[i];
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

        for (size_t i = 0;i<edge.size();i++) {
            auto e = edge[i];
            if (e->property == edgeProperty && (e->start == v1 && e->end == v2 || e->start == v2 && e->end == v1)) {
                newEdge = e;
                edgeFound = true;
            }
        }

        if (!edgeFound) {
            newEdge = new Edge(edgeProperty, v1, v2);
            v2->out.add(newEdge);
            v1->out.add(newEdge);
            edge.add(newEdge);
        }

    }

    friend std::ostream &operator<<(std::ostream &os, const UndirectedGraph &thiz) {
        for (int i = 0;i<thiz.edge.size();i++) {
            os << *thiz.edge[i];
            if (i < thiz.edge.size() - 1) {
                os << ",";
            }

        }
        return os;
    }
};

#endif //GISTOGRAMBAG_UNDIRECTEDGRAPH_H