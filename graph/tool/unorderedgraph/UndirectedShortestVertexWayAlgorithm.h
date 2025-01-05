#ifndef GISTOGRAMBAG_UNDIRECTEDSHORTESTVERTEXWAYALGORITHM_H
#define GISTOGRAMBAG_UNDIRECTEDSHORTESTVERTEXWAYALGORITHM_H


#include "../../domain/algorithm/Algorithm.h"
#include "../../presentation/logistic/data/Road.h"
#include "../../presentation/logistic/data/City.h"
#include "../../../gistogram/model/dictionary/HashMap.h"
#include "../../domain/model/UndirectedGraph.h"

template $graph
class UndirectedShortestVertexWayAlgorithm : public Algorithm {
public:
    UndirectedGraph* operator()(UndirectedGraph graph, City start, City end) {

        DynamicArray<Vertex*> vertices;
        DynamicArray<Vertex*> visited;
        std::unordered_map<Vertex*, Vertex*> prev;

        Vertex* endVertex = nullptr;
        Vertex* startVertex = nullptr;

        for (auto v : graph.vertices) {
            if (v->property == start) {
                startVertex = v;
            }
            if (v->property == end) {
                endVertex = v;
            }
        }

        vertices.add(startVertex);
        visited.add(startVertex);

        while (!vertices.isEmpty()) {
            Vertex* current = vertices[0];
            vertices.removeAt(0);

            if (current == endVertex) {
                break;
            }
            for (int j = 0;j<current->out.size();j++) {
                auto v = current->out[j]->end;
                bool isVisited = false;
                for (int i = 0; i < visited.size(); i++) {
                    if (visited[i] == v) {
                        isVisited = true;
                        break;
                    }
                }
                if (!isVisited) {
                    vertices.add(v);
                    visited.add(v);
                    prev[v] = current;
                }
            }
        }
        UndirectedGraph *result = new UndirectedGraph();
        if (prev[endVertex] != nullptr) {
            Vertex* next = nullptr;
            for (auto current = endVertex;current != nullptr;current = prev[current]) {
                if (next != nullptr) {
                    for (int i = 0;i<current->out.size();i++) {
                        if (current->out[i]->end == next) {
                            result->edge.add(current->out[i]);
                        }
                    }
                }
                next = current;
            }
        } else return nullptr;

        return result;
    }
};

#endif //GISTOGRAMBAG_UNDIRECTEDSHORTESTVERTEXWAYALGORITHM_H
