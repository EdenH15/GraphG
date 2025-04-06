//
// Created by edenh15 on 3/24/25.
// Email:Edenhassin@gmail.com

#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>

namespace graph {
    struct Neighbor {
        int vertex;
        int weight;
        Neighbor *next;
    };

    class Graph {
    private:
        int numV;
        Neighbor **adjacencyList;

    public:
        explicit Graph(int vertices);

        ~Graph();

        int get_numV() const;

        Neighbor *getNeighbors(int vertex) const;

        void addNeighbor(int src, int dst, int weight = 1);

        void addEdge(int src, int dst, int weight = 1);

        bool edgeExists(int src, int dst) const;

        void removeEdge(int src, int dst);

        void removeEdgeOneWay(int src, int dst);

        void print_graph() const;

        // void releaseMemory();
    };
}

#endif
