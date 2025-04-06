//
// Created by edenh15 on 3/24/25.
// Email:Edenhassin@gmail.com

#include "Algorithms.h"
#include "Graph.h"
#include <iostream>
#include "structures.h"
#include <climits>
using namespace std;

namespace graph {
    Graph Algorithms::bfs(const Graph &g, int srcVertex) {
        const int numVertices = g.get_numV();
        if (numVertices == 0) {
            throw std::invalid_argument("Graph is empty.");
        }
        if (srcVertex < 0 || srcVertex >= numVertices) {
            throw std::out_of_range("Invalid source vertex: out of bounds.");
        }

        Graph bfsTree(numVertices);
        bool *visited = new bool[numVertices]();
        for (int i = 0; i < numVertices; i++) {
            visited[i] = false;
        }
        Queue q;
        q.enqueue(srcVertex);
        visited[srcVertex] = true;

        while (!q.isEmpty()) {
            int u = q.dequeue();
            Neighbor *neighbors = g.getNeighbors(u);
            while (neighbors) {
                int vertex = neighbors->vertex;
                if (!visited[vertex]) {
                    q.enqueue(vertex);
                    visited[vertex] = true;
                    bfsTree.addNeighbor(u, vertex, neighbors->weight);
                }
                neighbors = neighbors->next;
            }
        }

        delete[] visited;
        return bfsTree;
    }


    void Algorithms::recDfs(Graph &g, int srcVertex, Graph &dfsTree, bool *visited) {
        visited[srcVertex] = true;
        Neighbor *neighbors = g.getNeighbors(srcVertex);
        while (neighbors) {
            int vertex = neighbors->vertex;
            if (!visited[vertex]) {
                dfsTree.addNeighbor(srcVertex, vertex, neighbors->weight);
                recDfs(g, vertex, dfsTree, visited);
            }
            neighbors = neighbors->next;
        }
    }

    Graph Algorithms::dfs(Graph &g, int srcVertex) {
        const int numVertices = g.get_numV();
        if (numVertices == 0) {
            throw std::invalid_argument("Graph is empty.");
        }
        if (srcVertex < 0 || srcVertex >= numVertices) {
            throw std::out_of_range("Invalid source vertex: out of bounds.");
        }
        bool *visited = new bool[numVertices]();
        Graph dfsTree(numVertices);

        recDfs(g, srcVertex, dfsTree, visited);
        for (int i = 0; i < numVertices; i++) {
            if (!visited[i]) {
                recDfs(g, i, dfsTree, visited);
            }
        }
        delete[] visited;
        return dfsTree;
    }

    Graph Algorithms::dijkstra(const Graph &g, int srcVertex) {
        const int numV = g.get_numV();
        if (numV == 0) {
            throw std::invalid_argument("Graph is empty.");
        }
        if (srcVertex < 0 || srcVertex >= numV) {
            throw std::out_of_range("Invalid source vertex: out of bounds.");
        }
        const int INF = INT_MAX;
        Graph dijkstraTree(numV);

        int *d = new int[numV];
        bool *processed = new bool[numV];
        int *parent = new int[numV];

        for (int i = 0; i < numV; i++) {
            d[i] = INF;
            processed[i] = false;
            parent[i] = -1;
        }
        d[srcVertex] = 0;
        minHeap minHeap;
        minHeap.insert(srcVertex, srcVertex, 0);

        while (!minHeap.isEmpty()) {
            edge e = minHeap.extractMin();
            int u = e.dstV;
            if (processed[u]) {
                continue;
            }
            processed[u] = true;
            Neighbor *neighbors = g.getNeighbors(u);
            while (neighbors) {
                int vertex = neighbors->vertex;
                int weight = neighbors->weight;
                relax(u, vertex, weight, d, minHeap, parent);
                neighbors = neighbors->next;
                if (weight < 0) {
                    cout << "Negative weight detected!" << endl;
                    delete[] d;
                    delete[] processed;
                    delete[] parent;
                    throw std::runtime_error("Negative weight detected!");
                }
            }
        }
        for (int i = 0; i < numV; i++) {
            if (parent[i] != -1) {
                dijkstraTree.addNeighbor(parent[i], i, d[i] - d[parent[i]]);
            }
        }
        delete[] d;
        delete[] processed;
        delete[] parent;
        return dijkstraTree;
    }

    void Algorithms::relax(int u, int vertex, int weight, int *d, minHeap &pq, int *parent) {
        if (d[u] + weight < d[vertex]) {
            d[vertex] = d[u] + weight;
            pq.insert(u, vertex, weight);
            parent[vertex] = u;
        }
    }


    Graph Algorithms::prim(const Graph &g) {
        const int numV = g.get_numV();
        if (numV == 0) {
            throw std::invalid_argument("Graph is empty.");
        }

        bool *inTree = new bool[numV];

        for (int i = 0; i < numV; i++) {
            inTree[i] = false;
        }

        Graph mst(numV);
        minHeap minHeap;
        int srcV = 0;

        Neighbor *n = g.getNeighbors(srcV);
        while (n) {
            minHeap.insert(srcV, n->vertex, n->weight);
            n = n->next;
        }

        inTree[srcV] = true;
        while (!minHeap.isEmpty()) {
            edge e = minHeap.extractMin();

            if (!inTree[e.dstV]) {
                inTree[e.dstV] = true;
                mst.addEdge(e.srcV, e.dstV, e.weight);
            }
            Neighbor *neighbors = g.getNeighbors(e.dstV);
            while (neighbors) {
                if (!inTree[neighbors->vertex]) {
                    minHeap.insert(e.dstV, neighbors->vertex, neighbors->weight);
                }
                neighbors = neighbors->next;
            }
        }
        delete[] inTree;
        return mst;
    }

    Graph Algorithms::kruskal(Graph &g) {
        int numVertices = g.get_numV();
        if (numVertices == 0) {
            throw std::invalid_argument("Graph is empty.");
        }
        minHeap h;
        unionFind uf;
        Graph kruskalTree(numVertices);

        for (int u = 0; u < numVertices; u++) {
            Neighbor *neighbors = g.getNeighbors(u);
            while (neighbors) {
                int v = neighbors->vertex;
                int weight = neighbors->weight;

                if (u < v) {
                    h.insert(u, v, weight);
                }
                neighbors = neighbors->next;
            }
        }

        while (!h.isEmpty()) {
            edge e = h.extractMin();
            if (uf.find(e.srcV) != uf.find(e.dstV)) {
                kruskalTree.addEdge(e.srcV, e.dstV, e.weight);
                uf.unionSet(e.srcV, e.dstV);
            }
        }
        return kruskalTree;
    }
}
