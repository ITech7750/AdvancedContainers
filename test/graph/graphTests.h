#ifndef LABA4_GRAPHTESTS_H
#define LABA4_GRAPHTESTS_H

#include "../../graph/domain/model/Graph.h"
#include "../../graph/presentation/logistic/data/Road.h"
#include "../../graph/presentation/logistic/data/City.h"

template $graph
void emptyGraph() {
    std::cout << "Initialization test" << "\n";
    Graph g = Graph();
    std::cout << "  Expected: {}" << "\n";
    std::cout << "  Got: " << g << "\n";
}

template $graph
void addEdge() {
    std::cout << "Add edge test" << "\n";
    Graph g = Graph();
    Road road = Road("road", 200, 90, [](size_t cargo) { return 10; });
    Vertex *v1 = new Vertex(City("City1", 40, [](size_t time) { return time / 10; }), DynamicArray<Edge*>(), DynamicArray<Edge*>());
    Vertex *v2 = new Vertex(City("City2", 20, [](size_t time) { return time / 10; }), DynamicArray<Edge*>(), DynamicArray<Edge*>());
    g.addEdge(v1, v2, road);
    std::cout << "  Expected: {road|200|90;City1|40;City2|20}" << "\n";
    std::cout << "  Got: " << g << "\n";
}

template $graph
void addTo() {
    std::cout << "Add to test" << "\n";;
    Graph g = Graph();
    Road road = Road("road", 200, 90, [](size_t cargo) { return 10; });
    g.addTo(City("City1", 40, [](size_t time) { return time / 10; }), City("City2", 40, [](size_t time) { return time / 10; }), Road("road", 200, 90, [](size_t cargo) { return 10; }));
    std::cout << "  Expected: {road|200|90;City1|40;City2|40}" << "\n";;
    std::cout << "  Got: " << g << "\n";;
}

template $graph
void addBoth() {
    std::cout << "Add both test" << "\n";;
    Graph g = Graph();
    Road road = Road("road", 200, 90, [](size_t cargo) { return 10; });
    g.addBoth(City("City1", 40, [](size_t time) { return time / 10; }), City("City2", 40, [](size_t time) { return time / 10; }), Road("road", 200, 90, [](size_t cargo) { return 10; }));
    std::cout << "  Expected: {road|200|90;City1|40;City2|40}" << "\n";
    std::cout << "  Got: " << g << "\n";
}

template $graph
void addTo2() {
    std::cout << "Add to 2 test" << "\n";
    Graph g = Graph();
    g.addTo(City("City1", 40, [](size_t time) { return time / 10; }), City("City2", 40, [](size_t time) { return time / 10; }), Road("road", 180, 90, [](size_t cargo) { return 10; }));
    g.addTo(City("City2", 40, [](size_t time) { return time / 10; }), City("City3", 40, [](size_t time) { return time / 10; }), Road("road", 210, 110, [](size_t cargo) { return 10; }));
    g.addTo(City("City3", 40, [](size_t time) { return time / 10; }), City("City1", 40, [](size_t time) { return time / 10; }), Road("road", 130, 90, [](size_t cargo) { return 10; }));
    std::cout << "  Expected: {road|180|90;City1|40;City2|40},{road|210|110;City2|40;City3|40},{road|130|90;City3|40;City1|40}"  << "\n";;
    std::cout << "  Got: " << g << "\n";;
}

template $graph
void addBoth2() {
    std::cout << "Add both 2 test" << "\n";;
    Graph g = Graph();
    g.addBoth(City("City1", 40, [](size_t time) { return time / 10; }), City("City2", 40, [](size_t time) { return time / 10; }), Road("road", 450, 56, [](size_t cargo) { return 10; }));
    g.addBoth(City("City2", 40, [](size_t time) { return time / 10; }), City("City3", 40, [](size_t time) { return time / 10; }), Road("road", 100, 60, [](size_t cargo) { return 10; }));
    g.addBoth(City("City3", 40, [](size_t time) { return time / 10; }), City("City4", 40, [](size_t time) { return time / 10; }), Road("road", 200, 110, [](size_t cargo) { return 10; }));

    std::cout << "  Expected: {road|450|56;City1|40;City2|40},{road|100|60;City2|40;City3|40},{road|200|110;City3|40;City4|40}" << "\n";
    std::cout << "  Got: " << g << "\n";
}

template $graph
void deleteVertex() {
    std::cout << "Delete vertex test" << "\n";
    Graph g = Graph();
    g.addBoth(City("City1", 40, [](size_t time) { return time / 10; }), City("City2", 40, [](size_t time) { return time / 10; }), Road("road", 450, 56, [](size_t cargo) { return 10; }));
    g.addBoth(City("City2", 40, [](size_t time) { return time / 10; }), City("City3", 40, [](size_t time) { return time / 10; }), Road("road", 100, 60, [](size_t cargo) { return 10; }));
    g.addBoth(City("City3", 40, [](size_t time) { return time / 10; }), City("City4", 40, [](size_t time) { return time / 10; }), Road("road", 200, 110, [](size_t cargo) { return 10; }));

    g.deleteVertex(City("City3", 40, [](size_t time) { return time / 10; }));
    std::cout << "  Expected: {road|450|56;City1|40;City2|40}" << "\n";
    std::cout << "  Got: " << g << "\n";
}

template $graph
void deleteEdge() {
    std::cout << "Delete edge test" << "\n";;
    Graph g = Graph();
    g.addBoth(City("City1", 40, [](size_t time) { return time / 10; }), City("City2", 40, [](size_t time) { return time / 10; }), Road("road", 450, 56, [](size_t cargo) { return 10; }));
    g.addBoth(City("City2", 40, [](size_t time) { return time / 10; }), City("City3", 40, [](size_t time) { return time / 10; }), Road("road", 100, 60, [](size_t cargo) { return 10; }));
    g.addBoth(City("City3", 40, [](size_t time) { return time / 10; }), City("City4", 40, [](size_t time) { return time / 10; }), Road("road", 200, 110, [](size_t cargo) { return 10; }));

    g.deleteEdge(Road("road", 450, 56, [](size_t cargo) { return 10; }));
    std::cout << "  Expected: {road|100|60;City2|40;City3|40},{road|200|110;City3|40;City4|40}\n";
    std::cout << "  Got: " << g << "\n";
}

template $graph
void editEdge() {
    std::cout << "Edit edge test" << "\n";;
    Graph g = Graph();
    g.addBoth(City("City1", 40, [](size_t time) { return time / 10; }), City("City2", 40, [](size_t time) { return time / 10; }), Road("road", 450, 56, [](size_t cargo) { return 10; }));
    g.addBoth(City("City2", 40, [](size_t time) { return time / 10; }), City("City3", 40, [](size_t time) { return time / 10; }), Road("road", 100, 60, [](size_t cargo) { return 10; }));
    g.addBoth(City("City3", 40, [](size_t time) { return time / 10; }), City("City4", 40, [](size_t time) { return time / 10; }), Road("road", 200, 110, [](size_t cargo) { return 10; }));

    g.editEdge(g.edge[0], Road("roadEdited", 100, 20, [](size_t cargo) { return 0; }));
    std::cout << "  Expected: {roadEdited|100|20;City1|40;City2|40},{road|100|60;City2|40;City3|40},{road|200|110;City3|40;City4|40}\n";
    std::cout << "  Got: " << g << "\n";
}

template $graph
void editVertex() {
    std::cout << "Edit vertex test" << "\n";
    Graph g = Graph();
    g.addBoth(City("City1", 40, [](size_t time) { return time / 10; }), City("City2", 40, [](size_t time) { return time / 10; }), Road("road", 450, 56, [](size_t cargo) { return 10; }));
    g.addBoth(City("City2", 40, [](size_t time) { return time / 10; }), City("City3", 40, [](size_t time) { return time / 10; }), Road("road", 100, 60, [](size_t cargo) { return 10; }));
    g.addBoth(City("City3", 40, [](size_t time) { return time / 10; }), City("City4", 40, [](size_t time) { return time / 10; }), Road("road", 200, 110, [](size_t cargo) { return 10; }));

    g.editVertex(g.vertices[0], City("CityEdited", 100, [](size_t time) { return time / 1; }));
    std::cout << "  Expected: {road|450|56;CityEdited|100;City2|40},{road|100|60;City2|40;City3|40},{road|200|110;City3|40;City4|40}" << "\n";
    std::cout << "  Got: " << g << "\n";
}

void runGraphTests() {
    std::cout << "Graph tests:"  << "\n";
    emptyGraph<Road, City>();
    addEdge<Road, City>();
    addTo<Road, City>();
    addTo2<Road, City>();
    addBoth<Road, City>();
    addBoth2<Road, City>();
    deleteVertex<Road, City>();
    deleteEdge<Road, City>();
    editEdge<Road, City>();
    editVertex<Road, City>();
    std::cout  << "_\n";
}


#endif //LABA4_GRAPHTESTS_H
