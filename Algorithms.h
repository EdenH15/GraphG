//
//Created by edenh15 on 3/24/25.
//Email:Edenhassin@gmail.com
//

#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include "Graph.h"
#include "structures.h"
#include <iostream>


namespace graph {
    class Algorithms {
    public:
        static Graph bfs(const Graph &g, int srcVertex);

        static Graph dfs(Graph &g, int srcVertex);

        static void recDfs(Graph &g, int srcVertex, Graph &dfsTree, bool *visited);

        static Graph dijkstra(const Graph &g, int srcVertex);

        static void relax(int u, int vertex, int weight, int *d, minHeap &pq, int *parent);

        static Graph prim(const Graph &g);

        static Graph kruskal(Graph &g);
    };
}

#endif //ALGORITHMS_H
