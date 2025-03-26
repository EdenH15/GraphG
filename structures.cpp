//
// Created by edenh15 on 3/24/25.
//
// Created by edenh15 on 3/24/25.
#include "structures.h"
#include <cstdio>
#include <iostream>
using namespace std;

namespace graph {

Queue::Queue() : front(0), rear(0) {}

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

  Stack::Stack() : top(0) {}

  void Stack::push(int value) {
    if (top == MAX_SIZE) {
      cout << "Stack is full!" << endl;
      return;
    }
    data[top] = value;
    top = top + 1;
  }
  int Stack::pop() {
    if (top == 0) {
      cout << "Stack is empty!" << endl;
      return -1;
    }
    top = top-1;
    return data[top];
  }
  bool Stack::isEmpty() const {
    if (top == 0) {
      return true;
    }
    return false;
  }

  minHeap::minHeap() {
    size = 0;
  }

void minHeap::insert(int val) {
  if (size==MAX_SIZE) {
    cout << "Stack is full!" << endl;
  }
  data[size] = val;
  int curSize = size;
  size++;
  while (curSize>0 && data[curSize]>data[curSize-1]) {
    int tmp = data[curSize];
    data[curSize] = data[curSize-1];
    data[curSize-1] = tmp;
    curSize--;
  }

}
  int minHeap::extractMin() {
    if (size == 0) {
      cout << "Stack is empty!" << endl;
      return -1;
    }
    int minVal = data[size-1];
    size--;
    return minVal;

}
  bool minHeap::isEmpty() const {
  if (size == 0) {
    return true;
  }
  return false;
}

}
