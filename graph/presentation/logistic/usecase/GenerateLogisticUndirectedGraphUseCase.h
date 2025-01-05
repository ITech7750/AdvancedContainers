#ifndef LABA4_GENERATELOGISTICUNDIRECTEDGRAPHUSECASE_H
#define LABA4_GENERATELOGISTICUNDIRECTEDGRAPHUSECASE_H

#include "../../../../util/Definition.h"
#include "../../../domain/model/UndirectedGraph.h"
#include "../data/City.h"
#include "../data/Road.h"

template $graph
class GenerateLogisticUndirectedGraphUseCase {
public:
    UndirectedGraph operator()(size_t cityAmount, size_t roadAmount) {
        UndirectedGraph graph = UndirectedGraph();
        int cityCount = 0;
        int roadCount = 0;
        while (roadCount < roadAmount || cityCount < cityAmount) {
            if (cityCount == cityAmount) {
                auto v1 = graph.vertices[randomIntIn(0, cityAmount - 1)];
                Vertex* v2;
                bool isNotAbleToAdd = true;
                while (isNotAbleToAdd) {
                    v2 = graph.vertices[randomIntIn(0, cityAmount - 1)];
                    isNotAbleToAdd = false;
                    if (v1 == v2) {
                        isNotAbleToAdd = true;
                    }
                    for (auto ed: graph.edge) {
                        if (ed->start == v1 && ed->end == v2) {

                        }
                    }
                }
                graph.addEdge(v1, v2, randomRoad());
                roadCount++;
            } else {
                cityCount++;
                graph.vertices.add(new Vertex(randomCity(), DynamicArray<Edge*>(), DynamicArray<Edge*>()));
            }
        }
        return graph;
    }
};

#endif //LABA4_GENERATELOGISTICUNDIRECTEDGRAPHUSECASE_H
