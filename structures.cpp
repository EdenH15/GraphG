//
// Created by edenh15 on 3/24/25.
// Email:Edenhassin@gmail.com

#include "structures.h"
#include <iostream>
using namespace std;

namespace graph {

    // Constructor for Queue: Initializes the front and rear pointers to 0
    Queue::Queue() : front(0), rear(0) {
    }

    void Queue::enqueue(int value) {
        // Check if the queue is full
        if ((rear + 1) % MAX_SIZE == front) {
            cout << "Queue is full!" << endl;
        } else {
            data[rear] = value;
            rear = (rear + 1) % MAX_SIZE;
        }
    }

    int Queue::dequeue() {
        // Check if the queue is empty
        if (front == rear) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        int val = data[front];
        front = (front + 1) % MAX_SIZE;
        return val;
    }

    bool Queue::isEmpty() const {
        if (front == rear) {
            return true;
        }
        return false;
    }

    // Constructor for minHeap: Initializes the size of the heap to 0
    minHeap::minHeap() {
        size = 0;
    }

    // Inserts a new edge into the min heap, ensuring that the heap property is maintained
    void minHeap::insert(int src, int dst, int weight) {
        if (size == MAX_SIZE) {
            cout << "Stack is full!" << endl;
        }
        data[size].dstV = dst;
        data[size].srcV = src;
        data[size].weight = weight;
        int curSize = size;
        size++;
        // Maintain the min heap property by moving the new element up the heap
        while (curSize > 0 && data[curSize].weight > data[curSize - 1].weight) {
            edge tmp = data[curSize];
            data[curSize] = data[curSize - 1];
            data[curSize - 1] = tmp;
            curSize--;
        }
    }

    // Extracts the minimum weight edge from the heap
    edge minHeap::extractMin() {
        if (size == 0) {
            cout << "Stack is empty!" << endl;
            return {-1, -1, -1};
        }
        edge minVal = data[size - 1];
        size--;
        return minVal;
    }

    bool minHeap::isEmpty() const {
        if (size == 0) {
            return true;
        }
        return false;
    }

    // Constructor for unionFind: Initializes each element to be its own parent (disjoint sets)
    unionFind::unionFind() {
        for (int i = 0; i < MAX_SIZE; i++) {
            parent[i] = i;
        }
    }

    // Finds the representative (root) of the set containing vertex v
    int unionFind::find(int v) {
        while (parent[v] != v) {
            v = parent[v];
        }
        return v;
    }

    // Unites the sets containing vertices u and v by linking the roots
    void unionFind::unionSet(int u, int v) {
        int root1 = find(u);
        int root2 = find(v);
        if (root1 != root2) {
            parent[root1] = root2;
        }
    }
}
