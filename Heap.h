#ifndef DOM3_HEAP_H
#define DOM3_HEAP_H
#include <iostream>

using namespace std;

class Heap {
public:
    Heap() = default;
    explicit Heap(int m) : m(m), vel(0), kap(150) {this->h = new int [kap];};
    explicit Heap(int m, int *arr, int n);

    Heap (const Heap &h);
    Heap (Heap &&h);
    Heap &operator=(const Heap &h);
    Heap &operator=(Heap &&h);
    ~Heap();

    int getVel() const {return vel;};
    int getMin() const {if(vel) return h[0]; return -1;};

    int deleteMin(int &steps);
    void add(int elem, int &steps);

    Heap deleteKey(int key, int &steps);
    Heap unionHeap(Heap h, int &steps);
    Heap convertTo(int newM);

    friend ostream& operator<<(ostream &os, const Heap &h);
    friend int findMinChild(int parent, const Heap &h);
    friend void changeCapacity(Heap &h);


private:
    void kopiraj(const Heap &h);
    void premesti(Heap &h);
    void obrisi();
    int kap = 150;
    int vel;
    int m;
    int *h;
};


int* unosIzFajla(int n);

int* unosPseudosluc(int n);

void meni1();

void meni12();

Heap ucitajHeap();

void switch1();


#endif