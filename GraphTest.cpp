//
// Created by eden on 4/6/25.
// Email:Edenhassin@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Graph.h"
#include <stdexcept>

using namespace graph;
using namespace std;

TEST_CASE("Create valid and invalid graphs") {
    CHECK_NOTHROW(Graph(0));
    CHECK_NOTHROW(Graph(5));
    CHECK_THROWS_AS(Graph(-2), std::invalid_argument);
}

TEST_CASE("Add/Remove edges") {
    //undirected graph
    Graph g1(3);
    // directed graph
    Graph g2(3);

    // Test adding an edge to an empty graph (should throw an error)
    Graph emptyGraph(0);
    CHECK_THROWS_AS(emptyGraph.addEdge(0, 1, 5), std::runtime_error);

    // Add edges
    CHECK_NOTHROW(g1.addEdge(0, 1, 10));
    CHECK_NOTHROW(g1.addEdge(0, 2, 5));
    CHECK_NOTHROW(g1.addEdge(2, 1, 2));

    CHECK_NOTHROW(g2.addNeighbor(0, 1, 10));
    CHECK_NOTHROW(g2.addNeighbor(0, 2, 5));
    CHECK_NOTHROW(g2.addNeighbor(1, 2, 2));

    // Check that the edges were successfully added
    CHECK(g1.edgeExists(0, 1));
    CHECK(g1.edgeExists(1, 0));
    CHECK(g1.edgeExists(0, 2));
    CHECK(g1.edgeExists(2, 0));
    CHECK(g1.edgeExists(1, 2));
    CHECK(g1.edgeExists(2, 1));

    CHECK(g2.edgeExists(0, 1));
    CHECK_FALSE(g2.edgeExists(1, 0));
    CHECK(g1.edgeExists(0, 2));
    CHECK_FALSE(g2.edgeExists(2, 0));
    CHECK(g2.edgeExists(1, 2));
    CHECK_FALSE(g2.edgeExists(2, 1));

    // Remove edges
    CHECK_NOTHROW(g1.removeEdge(0, 1));

    // Verify the edges were removed
    CHECK_FALSE(g1.edgeExists(0, 1));


    // Try to remove a non-existing edge (should throw an error)
    CHECK_THROWS_AS(g1.removeEdge(0, 1), std::runtime_error);

    // Trying to add an edge where source vertex is out of bounds
    CHECK_THROWS_AS(g1.addEdge(4, 1, 10), std::invalid_argument);
}
