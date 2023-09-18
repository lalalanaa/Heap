#ifndef DOM3_PQUEUE_H
#define DOM3_PQUEUE_H
#include "Heap.h"
#include <iostream>
using namespace std;

class PQueue{
public:
    PQueue(int m) : m(m), h(m) {};
    PQueue(int m, int *arr, int n) : m(m), h(m, arr, n) {};

    bool empty() const;
    int front() const;
    void changeM(int newM);
    void insert(int elem, int &steps);
    void deleteMin(int &steps);
    int deleteAndFront(int &steps);

private:
    int m;
    Heap h;
};

void meni2();

void meni22();

void switch2();

#endif
