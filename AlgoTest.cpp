//
// Created by eden on 4/1/25.
// Email:Edenhassin@gmail.com

#include "doctest.h"
#include "Algorithms.h"
#include "Graph.h"
#include "structures.h"
#include <stdexcept>

using namespace graph;
using namespace std;

TEST_CASE("Test Bfs") {
    Graph g1(4);
    Graph emptyGraph(0);

    g1.addEdge(0, 1, 4);
    g1.addEdge(0, 2, 3);
    g1.addEdge(1, 3, 2);
    g1.addEdge(1, 2, 7);

    // Test BFS on a non-empty graph
    Graph bfsRes1 = Algorithms::bfs(g1, 0);

    // Assert that vertex 0 has neighbors 1 and 2
    CHECK(bfsRes1.getNeighbors(0) != nullptr);
    CHECK(bfsRes1.getNeighbors(0)->vertex == 1);
    CHECK(bfsRes1.getNeighbors(0)->next->vertex == 2);

    // Assert that vertex 1 has neighbors 3
    CHECK(bfsRes1.getNeighbors(1) != nullptr);
    CHECK(bfsRes1.getNeighbors(1)->vertex == 3);

    // Assert that vertex 2 has no neighbors
    CHECK(bfsRes1.getNeighbors(2) == nullptr);

    // Test BFS on an empty graph (should throw exception)
    CHECK_THROWS_AS(Algorithms::bfs(emptyGraph, 0), std::invalid_argument);

    // Test BFS with an invalid source vertex index
    CHECK_THROWS_AS(Algorithms::bfs(g1, -1), std::out_of_range);
    CHECK_THROWS_AS(Algorithms::bfs(g1, 100), std::out_of_range);
}

TEST_CASE("Test Dfs") {
    Graph g1(4);
    Graph emptyGraph(0);

    g1.addEdge(0, 1, 4);
    g1.addEdge(1, 2, 3);
    g1.addEdge(2, 3, 2);
    g1.addEdge(3, 0, 7);

    Graph dfsRes1 = Algorithms::dfs(g1, 0);
    // Vertex 0 should be connected to vertex 1
    CHECK(dfsRes1.getNeighbors(0) != nullptr);
    CHECK(dfsRes1.getNeighbors(0)->vertex == 3);

    // Vertex 1 should be connected to vertex 2
    CHECK(dfsRes1.getNeighbors(3) != nullptr);
    CHECK(dfsRes1.getNeighbors(3)->vertex == 2);

    // Vertex 2 should be connected to vertex 3
    CHECK(dfsRes1.getNeighbors(2) != nullptr);
    CHECK(dfsRes1.getNeighbors(2)->vertex == 1);

    // Vertex 3 should have no direct connection to vertex 0 in the DFS tree
    CHECK(dfsRes1.getNeighbors(1) == nullptr);

    CHECK_THROWS_AS(Algorithms::dfs(emptyGraph, 0), std::invalid_argument);
    CHECK_THROWS_AS(Algorithms::bfs(g1, -1), std::out_of_range);
    CHECK_THROWS_AS(Algorithms::bfs(g1, 100), std::out_of_range);
}

TEST_CASE("Test Dijkstra") {
    Graph g1(5);
    g1.addEdge(0, 1, 5);
    g1.addEdge(0, 4, 15);
    g1.addEdge(1, 2, 1);
    g1.addEdge(1, 4, 5);
    g1.addEdge(2, 3, 2);
    g1.addEdge(3, 4, 3);

    Graph emptyG(0);
    Graph negativeE(3);
    negativeE.addEdge(0, 1, 4);
    negativeE.addEdge(0, 2, 15);
    negativeE.addEdge(1, 2, -2);

    Graph disconnectedG(3);
    disconnectedG.addEdge(0, 1, 4);

    Graph dijkstraRes1 = Algorithms::dijkstra(g1, 0);
    Graph dijkstraRes2 = Algorithms::dijkstra(disconnectedG, 0);

    // Vertex 1 has two neighbors, Vertex 4 with weight 5 and Vertex 2 with weight 1
    CHECK(dijkstraRes1.getNeighbors(0) != nullptr);
    CHECK(dijkstraRes1.getNeighbors(0)->vertex == 1);
    CHECK(dijkstraRes1.getNeighbors(0)->weight == 5);

    // Vertex 1 has two neighbors, Vertex 4 with weight 5 and Vertex 2 with weight 1
    CHECK(dijkstraRes1.getNeighbors(1) != nullptr);
    CHECK(dijkstraRes1.getNeighbors(1)->vertex == 4);
    CHECK(dijkstraRes1.getNeighbors(1)->weight == 5);
    CHECK(dijkstraRes1.getNeighbors(1)->next != nullptr);
    CHECK(dijkstraRes1.getNeighbors(1)->next->vertex == 2);
    CHECK(dijkstraRes1.getNeighbors(1)->next->weight == 1);

    // Vertex 2 has one neighbor, Vertex 3 with weight 2
    CHECK(dijkstraRes1.getNeighbors(2) != nullptr);
    CHECK(dijkstraRes1.getNeighbors(2)->vertex == 3);
    CHECK(dijkstraRes1.getNeighbors(2)->weight == 2);

    // Vertex 3 has no neighbors
    CHECK(dijkstraRes1.getNeighbors(3) == nullptr);

    // Test Dijkstra on empty graph (should throw exception)
    CHECK_THROWS_AS(Algorithms::dijkstra(emptyG, 0), std::invalid_argument);

    CHECK_THROWS_AS(Algorithms::dijkstra(negativeE, 0), std::runtime_error);

    // Test Dijkstra with an invalid source vertex index
    CHECK_THROWS_AS(Algorithms::dijkstra(g1, -1), std::out_of_range);
    CHECK_THROWS_AS(Algorithms::dijkstra(g1, 100), std::out_of_range);

    // Ensure that 0, 1 are in the tree since they are reachable
    CHECK(dijkstraRes2.getNeighbors(0) != nullptr);
    CHECK(dijkstraRes2.getNeighbors(0)->vertex == 1);
    CHECK(dijkstraRes2.getNeighbors(0)->weight == 4);
    CHECK(dijkstraRes2.getNeighbors(0)->next == nullptr);
    CHECK(dijkstraRes2.getNeighbors(1) == nullptr);
    CHECK(dijkstraRes2.getNeighbors(2)==nullptr);
}

TEST_CASE("Test Prim") {
    Graph g1(4);
    g1.addEdge(0, 1, 1);
    g1.addEdge(0, 3, 2);
    g1.addEdge(1, 2, 2);
    g1.addEdge(1, 3, 1);
    g1.addEdge(2, 3, 1);
    Graph emptyG(0);
    Graph oneV(1);

    Graph primRes1 = Algorithms::prim(g1);
    Graph primRes2 = Algorithms::prim(oneV);

    CHECK(primRes1.getNeighbors(0)->vertex==1);
    CHECK(primRes1.getNeighbors(0)->weight == 1);
    CHECK(primRes1.getNeighbors(1)->vertex==3);
    CHECK(primRes1.getNeighbors(1)->weight == 1);
    CHECK(primRes1.getNeighbors(1)->next->vertex==0);
    CHECK(primRes1.getNeighbors(1)->next->weight == 1);
    CHECK(primRes1.getNeighbors(2)->vertex==3);
    CHECK(primRes1.getNeighbors(2)->weight == 1);

    int edgeC = 0;
    int totalW = 0;
    for (int i = 0; i < primRes1.get_numV(); ++i) {
        Neighbor *n = primRes1.getNeighbors(i);
        while (n) {
            totalW += n->weight;
            edgeC++;
            n = n->next;
        }
    }
    CHECK(edgeC == 6); // 3 edges * 2 directions
    CHECK(totalW == 6); // 1+1+1 doubled → 6

    // Test prim on one vertex graph
    CHECK(primRes2.getNeighbors(0)==nullptr);

    // Test prim on empty graph (should throw exception)
    CHECK_THROWS_AS(Algorithms::prim(emptyG), std::invalid_argument);
}

TEST_CASE("Test Kruskal") {
    Graph g1(4);
    g1.addEdge(0, 1, 1);
    g1.addEdge(0, 3, 2);
    g1.addEdge(1, 2, 2);
    g1.addEdge(1, 3, 1);
    g1.addEdge(2, 3, 1);
    Graph emptyG(0);

    Graph kruskalRes1 = Algorithms::kruskal(g1);

    int edgeC = 0;
    int totalW = 0;
    for (int i = 0; i < kruskalRes1.get_numV(); ++i) {
        Neighbor *n = kruskalRes1.getNeighbors(i);
        while (n) {
            totalW += n->weight;
            edgeC++;
            n = n->next;
        }
    }
    CHECK(edgeC == 6); // 3 edges * 2 directions
    CHECK(totalW == 6); // 1+1+1 doubled → 6

    // Test kruskal on empty graph (should throw exception)
    CHECK_THROWS_AS(Algorithms::kruskal(emptyG), std::invalid_argument);
}
