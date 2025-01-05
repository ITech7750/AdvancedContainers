#ifndef LABA4_SHORTESTWAYALGORITHM_H
#define LABA4_SHORTESTWAYALGORITHM_H

#include "../../domain/algorithm/Algorithm.h"
#include "../../presentation/logistic/data/Road.h"
#include "../../presentation/logistic/data/City.h"
#include "../../../gistogram/model/dictionary/HashMap.h"

template $graph
class ShortestTimeWayAlgorithm : public Algorithm {
public:
    Graph* operator()(Graph graph, City start, City end, size_t startCargo) {
        std::unordered_map<Vertex*, size_t> timetable;
        std::unordered_map<Vertex*, Vertex*> prev;

        auto compare = [&](Vertex* left, Vertex* right) { return timetable[left] > timetable[right]; }; // Custom comparator for the priority queue
        DynamicArray<Vertex*> vertices;

        Vertex* endVertex = nullptr;
        Vertex* startVertex = nullptr;

        size_t cargo = startCargo;

        for (auto v : graph.vertices) {
            timetable[v] = 99999999;
            prev[v] = nullptr;
            if (v->property == start) {
                startVertex = v;
            }
            if (v->property == end) {
                endVertex = v;
            }
        }

        timetable[startVertex] = 0;
        vertices.add(startVertex);

        while (!vertices.isEmpty()) {
            Vertex* current = vertices[0];
            vertices.removeAt(0);

            if (current->property != end) {
                for (Edge *edge: current->out) {
                    Vertex *neighbor = edge->end;

                    size_t time =
                            timetable[current] + // время до текущего города
                            edge->property.duration(cargo) + // доп время из-за груза
                            (60 * edge->property.length / edge->property.maxSpeed) + // время проезда по дороге
                            neighbor->property.duration(timetable[current] + (edge->property.length / edge->property.maxSpeed)); // время пребывания в городе

                    if (time < timetable[neighbor]) {
                        timetable[neighbor] = time;
                        prev[neighbor] = current;
                        vertices.add(neighbor);
                    }
                }
            }
            if (endVertex == nullptr) {
                if (current->property == end) {
                    endVertex = current;
                }
            }
        }

        Graph *result = new Graph();
        if (endVertex != nullptr) {
            Vertex *previous = nullptr;
            for (Vertex* i = endVertex; i != nullptr; i = prev[i]) {
                if (previous != nullptr) {
                    for (int j = 0;j<i->out.size();j++) {
                        if (i->out[j]->start == i && i->out[j]->end == previous) {
                            result->edge.add(i->out[j]);
                            break;
                        }
                    }
                }
                previous = i;
            }
        } else return nullptr;
        return result;
    }
};

#endif //LABA4_SHORTESTWAYALGORITHM_H
