#ifndef LABA4_LOGISTIC_H
#define LABA4_LOGISTIC_H

#include <fstream>
#include "../../domain/model/Graph.h"
#include "usecase/GenerateLogisticGraphUseCase.h"
#include "usecase/GenerateLogisticUndirectedGraphUseCase.h"
#include "../../tool/graph/ShortestTimeWayAlgorithm.h"
#include "../../tool/graph/ShortestVertexWayAlgorithm.h"
#include "../../tool/unorderedgraph/UndirectedShortestTimeWayAlgorithm.h"
#include "../../tool/unorderedgraph/UndirectedShortestVertexWayAlgorithm.h"
#include "usecase/BuildLogisticGraphFromFileUseCase.h"
#include "usecase/BuildLogisticUndirectedGraphFromFileUseCase.h"

template $graph
class Logisitc {
private:
    GenerateLogisticGraphUseCase<Ep, Vp> generateLogisticGraphUseCase;
    GenerateLogisticUndirectedGraphUseCase<Ep, Vp> generateLogisticUndirectedGraphUseCase;

    BuildLogisticGraphFromFileUseCase buildLogisticGraphFromFileUseCase;
    BuildLogisticUndirectedGraphFromFileUseCase buildLogisticUndirectedGraphFromFileUseCase;

    ShortestTimeWayAlgorithm<Ep, Vp> shortestTimeWayAlgorithm;
    ShortestVertexWayAlgorithm<Ep, Vp> shortestVertexWayAlgorithm;

    UndirectedShortestTimeWayAlgorithm<Ep, Vp> undirectedShortestTimeWayAlgorithm;
    UndirectedShortestVertexWayAlgorithm<Ep, Vp> undirectedShortestVertexWayAlgorithm;

    template<class G>
    void writeResults(String resultFilePath, G *graph, G *result) {
        std::ofstream file;
        file.open(resultFilePath);

        file << *graph << "\n";
        if (result != nullptr) {
            file << *result;
        } else {
            file << "noway!";
        }
        file.close();
    }

public:
    void buildLogistic(
            String resultFilePath,
            int cityAmount,
            int roadAmount,
            int cargo
    ) {
        Graph graph = generateLogisticGraphUseCase(cityAmount, roadAmount);
        Graph *result = shortestTimeWayAlgorithm(graph, graph.vertices[randomIn(1, graph.vertices.size() - 1)]->property, graph.vertices[0]->property, cargo);

        writeResults(resultFilePath, &graph, result);
    }

    void buildLogisticUndirected(
            String resultFilePath,
            int cityAmount,
            int roadAmount,
            int cargo
    ) {
        UndirectedGraph graph = generateLogisticUndirectedGraphUseCase(cityAmount, roadAmount);
        UndirectedGraph *result = undirectedShortestTimeWayAlgorithm(graph, graph.vertices[randomIn(1, graph.vertices.size() - 1)]->property, graph.vertices[0]->property, cargo);

        writeResults(resultFilePath, &graph, result);
    }

    void buildLogisticFromFile(
            String startCity,
            String endCity,
            String resultFilePath,
            String dataFilePath,
            int cargo
    ) {
        Graph graph = buildLogisticGraphFromFileUseCase(dataFilePath);
        Graph *result = shortestTimeWayAlgorithm(graph, getCityFromString(startCity), getCityFromString(endCity), cargo);

        writeResults(resultFilePath, &graph, result);
    }

    void buildLogisticFromFileUndirected(
            String startCity,
            String endCity,
            String resultFilePath,
            String dataFilePath,
            int cargo
    ) {
        UndirectedGraph graph = buildLogisticUndirectedGraphFromFileUseCase(dataFilePath);
        UndirectedGraph *result = undirectedShortestTimeWayAlgorithm(graph, getCityFromString(startCity), getCityFromString(endCity), cargo);

        writeResults(resultFilePath, &graph, result);
    }

    void buildLogisticShortestVertex(
            String resultFilePath,
            int cityAmount,
            int roadAmount
    ) {
        Graph graph = generateLogisticGraphUseCase(cityAmount, roadAmount);
        Graph *result = shortestVertexWayAlgorithm(graph, graph.vertices[randomIn(1, graph.vertices.size() - 1)]->property, graph.vertices[0]->property);

        writeResults(resultFilePath, &graph, result);
    }

    void buildLogisticFromFileShortestVertex(
            String startCity,
            String endCity,
            String resultFilePath,
            String dataFilePath
    ) {
        Graph graph = buildLogisticGraphFromFileUseCase(dataFilePath);
        Graph *result = shortestVertexWayAlgorithm(graph, getCityFromString(startCity), getCityFromString(endCity));

        writeResults(resultFilePath, &graph, result);
    }

    void buildLogisticShortestVertexUndirected(
            String resultFilePath,
            int cityAmount,
            int roadAmount
    ) {
        UndirectedGraph graph = generateLogisticUndirectedGraphUseCase(cityAmount, roadAmount);
        UndirectedGraph *result = undirectedShortestVertexWayAlgorithm(graph, graph.vertices[randomIn(1, graph.vertices.size() - 1)]->property, graph.vertices[0]->property);

        writeResults(resultFilePath, &graph, result);
    }

    void buildLogisticFromFileShortestVertexUndirected(
            String startCity,
            String endCity,
            String resultFilePath,
            String dataFilePath
    ) {
        UndirectedGraph graph = buildLogisticUndirectedGraphFromFileUseCase(dataFilePath);
        UndirectedGraph *result = undirectedShortestVertexWayAlgorithm(graph, getCityFromString(startCity), getCityFromString(endCity));

        writeResults(resultFilePath, &graph, result);
    }
};

#endif //LABA4_LOGISTIC_H
