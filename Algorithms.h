//
// Created by edenh15 on 3/24/25.
//

#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include "Graph.h"
#include <iostream>


namespace graph {

    class Algorithms {
    public:
        static Graph bfs(Graph g,int srcVertex);
        static Graph dfs(Graph g,int srcVertex);
        static void recDfs(Graph& g,int srcVertex,Graph& dfsTree,bool* visited);
        static Graph dijkstra(Graph g,int srcVertex);
        //static Graph prim(Graph g);
        //static Graph kruskal(Graph g);

};

}

#endif //ALGORITHMS_H
