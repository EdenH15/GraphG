//
// Created by edenh15 on 3/24/25.
// Email:Edenhassin@gmail.com

#include "structures.h"
#include <cstdio>
#include <iostream>
using namespace std;

namespace graph {
    Queue::Queue() : front(0), rear(0) {
    }

    void Queue::enqueue(int value) {
        if ((rear + 1) % MAX_SIZE == front) {
            cout << "Queue is full!" << endl;
        } else {
            data[rear] = value;
            rear = (rear + 1) % MAX_SIZE;
        }
    }

    int Queue::dequeue() {
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


    minHeap::minHeap() {
        size = 0;
    }

    void minHeap::insert(int src, int dst, int weight) {
        if (size == MAX_SIZE) {
            cout << "Stack is full!" << endl;
        }
        data[size].dstV = dst;
        data[size].srcV = src;
        data[size].weight = weight;
        int curSize = size;
        size++;
        while (curSize > 0 && data[curSize].weight > data[curSize - 1].weight) {
            edge tmp = data[curSize];
            data[curSize] = data[curSize - 1];
            data[curSize - 1] = tmp;
            curSize--;
        }
    }

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

    unionFind::unionFind() {
        for (int i = 0; i < MAX_SIZE; i++) {
            parent[i] = i;
        }
    }

    int unionFind::find(int v) {
        while (parent[v] != v) {
            v = parent[v];
        }
        return v;
    }

    void unionFind::unionSet(int u, int v) {
        int root1 = find(u);
        int root2 = find(v);
        if (root1 != root2) {
            parent[root1] = root2;
        }
    }
}
