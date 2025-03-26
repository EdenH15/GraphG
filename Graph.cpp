//
// Created by edenh15 on 3/23/25.
//
using namespace std;
#include <cstdio>
#include "Graph.h"
#include <iostream>

namespace graph {

        Graph::Graph(int vertices) {
            this->numV = vertices;
            adjacencyList = new Neighbor*[vertices];
            for (int i = 0; i < vertices; i++) {
                adjacencyList[i] = nullptr;
            }
        }

        void Graph::addEdge(int src, int dst, int weight) {
            if (src<0 || dst<0 || src>=numV || dst>=numV) {
                printf("Error the vertex not found\n");
            }
            else if (edgeExists(src,dst) || edgeExists(dst,src)) {
                printf("Error the edge already exists\n");
            }
            else {
                addNeighbor(src,dst,weight);
                addNeighbor(dst,src,weight);
                printf("The edge added\n");
            }

        }
        bool Graph::edgeExists(int src, int dst) {
            Neighbor* current = adjacencyList[src];
            while (current) {
                if (current->vertex == dst) {
                    return true;
                }
                current = current->next;
            }
            return false;
        }

        void Graph::addNeighbor(int src, int dst, int weight) {
            Neighbor* newNeighbor = new Neighbor;
            newNeighbor->vertex = dst;
            newNeighbor->weight = weight;
            newNeighbor->next = nullptr;
            if (adjacencyList[src]==nullptr){
                adjacencyList[src] = newNeighbor;
            }
            else {
                newNeighbor->next = adjacencyList[src];
                adjacencyList[src] = newNeighbor;
            }


        }
        void Graph:: removeEdge(int src,int dst) {
            removeEdgeOneWay(src,dst);
            removeEdgeOneWay(dst,src);
        }
        void Graph::removeEdgeOneWay(int src, int dst) {
            if (!edgeExists(src,dst)) {
                printf("Error the edge not found\n");
                return;
            }
            Neighbor* current = adjacencyList[src];
            Neighbor* previous = nullptr;

            while (current) {
                if (current->vertex == dst) {
                    if (previous==nullptr) {
                        adjacencyList[src] = current->next;
                    }
                    else {
                        previous->next = current->next;
                    }
                    delete current;
                    return;
                }

                previous = current;
                current=current->next;

                }

            }
        void  Graph::print_graph() {
            for (int i = 0; i < numV; i++) {
                cout << "Vertex " << i << ": ";
                Neighbor* current = adjacencyList[i];
                if (current==nullptr) {
                    cout << "No neighbors";
                }
                while (current) {
                    cout << "<v:"<<current->vertex << ",w:" << current->weight << "> ";
                    current = current->next;
                }
                cout << endl;
            }

        }
        void Graph::releaseMemory() {
            for (int i = 0; i < numV; i++) {
                Neighbor* current = adjacencyList[i];

                while (current) {
                    Neighbor* temp = current;
                    current = current->next;
                    delete temp;
                }
                adjacencyList[i] = nullptr;
            }
            delete[] adjacencyList;
            adjacencyList = nullptr;
        }
        int Graph::get_numV() {
          return numV;
        }
        Neighbor* Graph::getNeighbors(int vertex) {
          return adjacencyList[vertex];
        }



        }






