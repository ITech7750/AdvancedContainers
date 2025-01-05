#ifndef LABA4_UNDIRECTEDGRAPHTEST_H
#define LABA4_UNDIRECTEDGRAPHTEST_H

#include "../../graph/domain/model/UndirectedGraph.h"
#include "../../graph/presentation/logistic/data/Road.h"
#include "../../graph/presentation/logistic/data/City.h"

template $graph
void emptyGraphU() {
    std::cout << "Initialization test" << "\n";
    UndirectedGraph g = UndirectedGraph();
    std::cout << "  Expected: {}" << "\n";
    std::cout << "  Got: " << g << "\n";
}

template $graph
void addEdgeU() {
    std::cout << "Add edge test" << "\n";
    UndirectedGraph g = UndirectedGraph();
    Road road = Road("road", 200, 90, [](size_t cargo) { return 10; });
    Vertex *v1 = new Vertex(City("City1", 40, [](size_t time) { return time / 10; }), DynamicArray<Edge*>(), DynamicArray<Edge*>());
    Vertex *v2 = new Vertex(City("City2", 20, [](size_t time) { return time / 10; }), DynamicArray<Edge*>(), DynamicArray<Edge*>());
    g.addEdge(v1, v2, road);
    std::cout << "  Expected: {road|200|90;City1|40;City2|20}" << "\n";
    std::cout << "  Got: " << g << "\n";
}

template $graph
void addToU() {
    std::cout << "Add to test" << "\n";
    UndirectedGraph g = UndirectedGraph();
    Road road = Road("road", 200, 90, [](size_t cargo) { return 10; });
    g.addTo(City("City1", 40, [](size_t time) { return time / 10; }), City("City2", 40, [](size_t time) { return time / 10; }), Road("road", 200, 90, [](size_t cargo) { return 10; }));
    std::cout << "  Expected: {road|200|90;City1|40;City2|40}" << "\n";
    std::cout << "  Got: " << g << "\n";
}

template $graph
void addTo2U() {
    std::cout << "Add to 2 test" << "\n";
    UndirectedGraph g = UndirectedGraph();
    g.addTo(City("City1", 40, [](size_t time) { return time / 10; }), City("City2", 40, [](size_t time) { return time / 10; }), Road("road", 180, 90, [](size_t cargo) { return 10; }));
    g.addTo(City("City2", 40, [](size_t time) { return time / 10; }), City("City3", 40, [](size_t time) { return time / 10; }), Road("road", 210, 110, [](size_t cargo) { return 10; }));
    g.addTo(City("City3", 40, [](size_t time) { return time / 10; }), City("City1", 40, [](size_t time) { return time / 10; }), Road("road", 130, 90, [](size_t cargo) { return 10; }));
    std::cout << "  Expected: {road|180|90;City1|40;City2|40},{road|210|110;City2|40;City3|40},{road|130|90;City3|40;City1|40}" << "\n";
    std::cout << "  Got: " << g << "\n";
}

template $graph
void deleteVertexU() {
    std::cout << "Delete vertex test" << "\n";
    UndirectedGraph g = UndirectedGraph();
    g.addTo(City("City1", 40, [](size_t time) { return time / 10; }), City("City2", 40, [](size_t time) { return time / 10; }), Road("road", 450, 56, [](size_t cargo) { return 10; }));
    g.addTo(City("City2", 40, [](size_t time) { return time / 10; }), City("City3", 40, [](size_t time) { return time / 10; }), Road("road", 100, 60, [](size_t cargo) { return 10; }));
    g.addTo(City("City3", 40, [](size_t time) { return time / 10; }), City("City4", 40, [](size_t time) { return time / 10; }), Road("road", 200, 110, [](size_t cargo) { return 10; }));

    g.deleteVertex(City("City3", 40, [](size_t time) { return time / 10; }));
    std::cout << "  Expected: {road|450|56;City1|40;City2|40}" << "\n";
    std::cout << "  Got: " << g << "\n";
}

template $graph
void deleteEdgeU() {
    std::cout << "Delete edge test" << "\n";
    UndirectedGraph g = UndirectedGraph();
    g.addTo(City("City1", 40, [](size_t time) { return time / 10; }), City("City2", 40, [](size_t time) { return time / 10; }), Road("road", 450, 56, [](size_t cargo) { return 10; }));
    g.addTo(City("City2", 40, [](size_t time) { return time / 10; }), City("City3", 40, [](size_t time) { return time / 10; }), Road("road", 100, 60, [](size_t cargo) { return 10; }));
    g.addTo(City("City3", 40, [](size_t time) { return time / 10; }), City("City4", 40, [](size_t time) { return time / 10; }), Road("road", 200, 110, [](size_t cargo) { return 10; }));

    g.deleteEdge(Road("road", 450, 56, [](size_t cargo) { return 10; }));
    std::cout << "  Expected: {road|100|60;City2|40;City3|40},{road|200|110;City3|40;City4|40}" << "\n";
    std::cout << "  Got: " << g << "\n";
}

template $graph
void editEdgeU() {
    std::cout << "Edit edge test" << "\n";;
    UndirectedGraph g = UndirectedGraph();
    g.addTo(City("City1", 40, [](size_t time) { return time / 10; }), City("City2", 40, [](size_t time) { return time / 10; }), Road("road", 450, 56, [](size_t cargo) { return 10; }));
    g.addTo(City("City2", 40, [](size_t time) { return time / 10; }), City("City3", 40, [](size_t time) { return time / 10; }), Road("road", 100, 60, [](size_t cargo) { return 10; }));
    g.addTo(City("City3", 40, [](size_t time) { return time / 10; }), City("City4", 40, [](size_t time) { return time / 10; }), Road("road", 200, 110, [](size_t cargo) { return 10; }));

    g.editEdge(g.edge[0], Road("roadEdited", 100, 20, [](size_t cargo) { return 0; }));
    std::cout << "  Expected: {roadEdited|100|20;City1|40;City2|40},{road|100|60;City2|40;City3|40},{road|200|110;City3|40;City4|40}\n";
    std::cout << "  Got: " << g << "\n";
}

template $graph
void editVertexU() {
    std::cout << "Edit vertex test" << "\n";
    UndirectedGraph g = UndirectedGraph();
    g.addTo(City("City1", 40, [](size_t time) { return time / 10; }), City("City2", 40, [](size_t time) { return time / 10; }), Road("road", 450, 56, [](size_t cargo) { return 10; }));
    g.addTo(City("City2", 40, [](size_t time) { return time / 10; }), City("City3", 40, [](size_t time) { return time / 10; }), Road("road", 100, 60, [](size_t cargo) { return 10; }));
    g.addTo(City("City3", 40, [](size_t time) { return time / 10; }), City("City4", 40, [](size_t time) { return time / 10; }), Road("road", 200, 110, [](size_t cargo) { return 10; }));

    g.editVertex(g.vertices[0], City("CityEdited", 100, [](size_t time) { return time / 1; }));
    std::cout << "  Expected: {road|450|56;CityEdited|100;City2|40},{road|100|60;City2|40;City3|40},{road|200|110;City3|40;City4|40}" << "\n";
    std::cout << "  Got: " << g << "\n";
}

void runUndirectedGraphTests() {
    std::cout << "UndirectedGraph tests:"  << "\n";
    emptyGraphU<Road, City>();
    addEdgeU<Road, City>();
    addToU<Road, City>();
    addTo2U<Road, City>();
    deleteVertexU<Road, City>();
    deleteEdgeU<Road, City>();
    editEdgeU<Road, City>();
    editVertexU<Road, City>();
    std::cout << "-"  << "\n";
}

#endif //LABA4_UNDIRECTEDGRAPHTEST_H
