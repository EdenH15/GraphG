//
// Created by eden on 4/6/25.
// Email:Edenhassin@gmail.com

#include "doctest.h"
#include "Algorithms.h"
#include "Graph.h"
#include "structures.h"
#include <stdexcept>

using namespace graph;
using namespace std;

TEST_CASE("Queue test") {
    Queue q;
    CHECK(q.isEmpty());

    q.enqueue(2);
    CHECK(!q.isEmpty());

    int val = q.dequeue();
    CHECK(val == 2);
    CHECK(q.isEmpty());

    SUBCASE("Dequeue from empty queue returns -1") {
        Queue q1;
        CHECK(q1.dequeue() == -1);
    }
    SUBCASE("Enqueue to full queue does not change state") {
        Queue q2;
        // Fill queue to capacity
        for (int i = 0; i < MAX_SIZE - 1; ++i) {
            q2.enqueue(i);
        }
        // Try to enqueue when full (should not crash)
        q2.enqueue(102);
        // Next dequeue should not be 999 (was not added)
        CHECK(q2.dequeue() == 0);
    }
}

TEST_CASE("minHeap basic insert and extract") {
    minHeap h;
    h.insert(0, 1, 5);
    h.insert(1, 2, 3);
    h.insert(2, 3, 7);

    edge e = h.extractMin();
    CHECK(e.weight == 3);

    e = h.extractMin();
    CHECK(e.weight == 5);

    e = h.extractMin();
    CHECK(e.weight == 7);
}


TEST_CASE("minHeap test") {
    minHeap h;
    CHECK(h.isEmpty());
    edge e = h.extractMin();
    CHECK(e.dstV == -1);
    CHECK(e.srcV == -1);
    CHECK(e.weight == -1);

    h.insert(0, 1, 5);
    h.insert(1, 2, 3);
    h.insert(2, 3, 7);

    CHECK(!h.isEmpty());

    edge e1 = h.extractMin();
    CHECK(e1.weight == 3);

    e1 = h.extractMin();
    CHECK(e1.weight == 5);

    e1 = h.extractMin();
    CHECK(e1.weight == 7);
}

TEST_CASE("unionFind test") {
    unionFind uf;
    CHECK(uf.find(1) == 1);
    uf.unionSet(1, 2);
    CHECK(uf.find(1) == uf.find(2));
}
