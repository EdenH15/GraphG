//
// Created by edenh15 on 3/23/25.
//Email:Edenhassin@gmail.com

using namespace std;
#include <cstdio>
#include "Graph.h"
#include <iostream>

namespace graph {
    Graph::Graph(int vertices) {
        if (vertices < 0) {
            throw std::invalid_argument("vertices must be greater than zero");
        }
        this->numV = vertices;
        adjacencyList = new Neighbor *[vertices]();
    }


    Graph::~Graph() {
        for (int i = 0; i < numV; i++) {
            Neighbor *current = adjacencyList[i];
            while (current) {
                Neighbor *temp = current;
                current = current->next;
                delete temp;
            }
            adjacencyList[i] = nullptr;
        }
        delete[] adjacencyList;
    }

    void Graph::addEdge(int src, int dst, int weight) {
        if (numV == 0) {
            throw std::runtime_error("Cannot add edge to empty graph.");
        }
        if (src < 0 || dst < 0 || src >= numV || dst >= numV) {
            throw std::invalid_argument("Invalid vertex index.");
        }
        if (edgeExists(src, dst) || edgeExists(dst, src)) {
            throw std::runtime_error("Error:Edge already exists");
        }
        addNeighbor(src, dst, weight);
        addNeighbor(dst, src, weight);
        printf("The edge added\n");
    }

    bool Graph::edgeExists(const int src, const int dst) const {
        const Neighbor *current = adjacencyList[src];
        while (current) {
            if (current->vertex == dst) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void Graph::addNeighbor(int src, int dst, int weight) {
        if (src < 0 || dst < 0 || src >= numV || dst >= numV) {
            throw std::invalid_argument("Invalid vertex index in addNeighbor");
        }
        if (edgeExists(src, dst)) {
            throw std::runtime_error("Error:edge already exists");
        }
        Neighbor *newNeighbor = new Neighbor{dst, weight, nullptr};
        newNeighbor->next = adjacencyList[src];
        adjacencyList[src] = newNeighbor;
    }

    void Graph::removeEdge(int src, int dst) {
        removeEdgeOneWay(src, dst);
        removeEdgeOneWay(dst, src);
    }

    void Graph::removeEdgeOneWay(int src, int dst) {
        if (!edgeExists(src, dst)) {
            throw std::runtime_error("Error:Edge not exists");
        }
        Neighbor *current = adjacencyList[src];
        Neighbor *previous = nullptr;

        while (current) {
            if (current->vertex == dst) {
                if (previous == nullptr) {
                    adjacencyList[src] = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                return;
            }

            previous = current;
            current = current->next;
        }
    }

    void Graph::print_graph() const {
        if (numV == 0 || adjacencyList == nullptr) {
            cout << "Empty graph." << endl;
            return;
        }

        for (int i = 0; i < numV; i++) {
            cout << "Vertex " << i << ": ";
            Neighbor *current = adjacencyList[i];
            if (current == nullptr) {
                cout << "No neighbors";
            }
            while (current) {
                cout << "<v:" << current->vertex << ",w:" << current->weight << "> ";
                current = current->next;
            }
            cout << endl;
        }
    }

    int Graph::get_numV() const {
        return numV;
    }

    Neighbor *Graph::getNeighbors(const int vertex) const {
        return adjacencyList[vertex];
    }
}
