#include "Heap.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <cmath>
using namespace std;

Heap::Heap(int m, int *arr, int n)
{
    int pom = 0;
    this->m = m;
    this->vel = 0;
    this->kap = (n > kap ? n : kap);
    this->h = new int [kap];
    for(int i = 0; i < n; i++)
        this->add(arr[i], pom);
}

void Heap::add(int elem, int &steps)
{
    int pom, par = (vel - 1) / m, tr = vel++;
    steps++;
    if(vel > kap)
        changeCapacity(*this);

    h[tr] = elem;
    while(h[par] >= elem and tr > 0)
    {
        steps++;
        pom = h[par];
        h[par] = h[tr];
        h[tr] = pom;
        tr = par;
        par = (par-1) / m;
    }
}

int Heap::deleteMin(int &steps)
{
    int first, pom, min, tr = 0;
    first = h[tr];
    h[tr] = h[--vel];

    while(1)
    {
        min = findMinChild(tr, *this);
        if(h[tr] > h[min])
        {
            steps++;
            pom = h[tr];
            h[tr] = h[min];
            h[min] = pom;
            tr = min;
        }
        else
            break;
    }

    return first;
}

Heap Heap::unionHeap(Heap heap, int &steps)
{
    Heap newHeap = Heap(m);
    for(int i = 0; i < this->vel; i++)
        newHeap.add(this->h[i], steps);
    for(int i = 0; i < heap.vel; i++)
        newHeap.add(heap.h[i], steps);
    return newHeap;
}

Heap Heap::convertTo(int newM)
{
    int pom = 0;
    Heap newHeap = Heap(newM);
    for(int i = 0; i < this->vel; i++)
        newHeap.add(this->h[i], pom);

    return newHeap;
}

Heap Heap::deleteKey(int key, int &steps)
{
    Heap newHeap(m);
    for(int i = 0; i < vel; i++)
        if(key != h[i]) newHeap.add(h[i], steps);

    return newHeap;
}

ostream &operator<<(ostream &os, const Heap &h) {
    int curr = 100, prev;
    if(!h.vel)
        return os << "hip je prazan!" << endl;
    queue <int> val;
    val.push(h.h[0]);
    queue <int> ind;
    ind.push(0);
    queue <char> ch;
    ch.push('('); ch.push(')');

    for(int i = 0; i <= 10; i++ )
    {
        prev = (curr ? curr : 1);
        curr = (curr - h.m) / h.m;

        for(int k = 0; k < curr; k++ )
            os << " ";

        for(int k = 0; k < pow(h.m, i); k++ )
        {
            int v = val.front();
            val.pop();

            int in = ind.front();
            ind.pop();

            char ch1 = ch.front();
            ch.pop();
            char ch2 = ch.front();
            ch.pop();

            for(int l = 0; l < h.m and in * h.m + 1 + l < h.vel; l++)
            {
                val.push(h.h[in * h.m + 1 + l]);
                ind.push(in * h.m + 1 + l);
                ch.push((l ? ' ' : '('));
                ch.push((l == h.m - 1 ? ')' : ' '));
            }

            os << ch1 << v << ch2;

            if(val.empty())
                return os << (ch2 == ')' ? ' ' : ')' );

            for(int l = 0; l < prev; l++)
                os << " ";
        }
        os <<  endl << endl;
    }
}

void Heap::kopiraj(const Heap &h) {
    this->vel = h.vel;
    this->kap = h.kap;
    this->m = h.m;
    this->h = new int [kap];
    for(int i = 0; i < kap; i++)
        this->h[i] = h.h[i];
}

void Heap::premesti(Heap &h) {
    this->h = h.h;
    this->vel = h.vel;
    this->kap = h.kap;
    this->m = h.m;
    h.h = nullptr;
    h.vel = 0;
}

void Heap::obrisi() {
    h = nullptr;
    delete [] this->h;
    vel = 0;
    kap = 150;
}

Heap::Heap(const Heap &h) {
    kopiraj(h);
}

Heap::Heap(Heap &&h) {
    premesti(h);
}

Heap &Heap::operator=(const Heap &h) {
    if(this != &h)
    {
        obrisi();
        kopiraj(h);
    }
    return *this;
}

Heap &Heap::operator=(Heap &&h) {
    if(this != &h)
    {
        obrisi();
        premesti(h);
    }
    return *this;
}

Heap::~Heap() {
    obrisi();
}

int findMinChild(int parent, const Heap &h)
{
    int min = h.h[parent], ind = parent;
    for(int i = parent * h.m + 1; i < h.vel and i <= parent * h.m + h.m; i++)
        if (min > h.h[i])
            min = h.h[ind = i];
    return ind;
}

void changeCapacity(Heap &h)
{
    h.kap *= 2;
    int *novi = new int [h.kap];
    for(int i = 0; i < h.kap; i++)
        novi[i] = (i < h.kap/2 ? h.h[i] : 0);
    delete [] h.h;
    h.h = novi;
}

int* unosIzFajla(int n)
{
    int i = 0, *arr = new int[n];
    string name = "test_" + to_string(n) + ".txt";
    ifstream file (name);

    if(!file.is_open())
    {
        cout << "ne postoji fajl sa unetim imenom, pokusajte ponovo" << endl;
        return nullptr;
    }
    file >> arr[i++];
    while(!file.eof())
        file >> arr[i++];
    return arr;
}

int* unosPseudosluc(int n)
{
    srand((unsigned) time(nullptr));
    int *arr = new int [n];

    for(int i = 0; i < n; i++)
        arr[i] = 1 + rand() % 100;

    return arr;
}

void meni1()
{
    cout << "\n\n\tH E A P   M E N I\nunesite redni broj zeljene stavke:\n\t(1) stvaranje hipa\n\t(2) umetanje elementa u hip\n\t"
            "(3) dohvatanje najmanjeg elementa\n\t(4) brisanje najmanjeg elementa\n\t(5) menjanje reda hipa\n\t"
            "(6) unija dva hipa\n\t(7) ispis hipa\n\t(8) brisanje proizvoljnog kljuca\n\n\t(0) povratak na glavni meni\n\n";
}

void meni12()
{
    cout << "\nunesite redni broj zeljene stavke:\n\t(1) stvaranje hipa ucitavanjem iz datoteke\n\t(2) stvaranje hipa ucitavanjem sa komandne linije"
            "\n\t(3) stvaranje nasumicnog hipa\n";
}

Heap ucitajHeap()
{
    int m, n, izbor, *arr;
    Heap h;
    meni12();
    cin >> izbor;
    switch(izbor)
    {
        case 1:
            cout << "unesite red hipa:" << endl;
            cin >> m;
            cout << "unesite broj elemenata u datoteci" << endl;
            cin >> n;
            if(n != 10 and n != 100 and n != 1000 and n != 10000 and n != 100000)
            {
                cout << "ne postoji datoteka sa zadatim brojem elemenata, pokusajte ponovo" << endl;
                break;
            }
            arr = unosIzFajla(n);
            h = Heap(m, arr, n);
            cout << "hip reda " << m << " unesen iz datoteke je formiran!" << endl;
            break;

        case 2:
            cout << "unesite red hipa:" << endl;
            cin >> m;
            cout << "unesite broj elemenata koji unosite" << endl;
            cin >> n;
            arr = new int[n];
            cout << "unesite elemenate" << endl;
            for(int i = 0; i < n; i++)
                cin >> arr[i];
            h = Heap(m, arr, n);
            cout << "hip reda " << m << " unesen sa komandne linije je formiran!" << endl;
            break;

        case 3:
            cout << "unesite red hipa:" << endl;
            cin >> m;
            cout << "unesite broj elemenata koji unosite" << endl;
            cin >> n;
            arr = unosPseudosluc(n);
            h = Heap(m, arr, n);
            cout << "nasumican hip reda " << m << " je formiran!" << endl;
            break;

        default:
            cout << "izabrali ste nepostojecu opciju" << endl;
            break;
    }
    return h;
}

void switch1()
{
    int izbor, n, m, steps = 0;
    string name;
    Heap h(2), h2;
    while(true)
    {
        meni1();
        cin >> izbor;
        switch(izbor)
        {
            case 0:
                return;

            case 1:
                h = ucitajHeap();
                break;

            case 2:
                cout << "unesite element koji zelite da ubacite" << endl;
                cin >> n;
                steps = 0;
                h.add(n, steps);
                cout << "element je ubacen u hip u " << steps << " koraka!" << endl;
                break;

            case 3:
                if(h.getVel())
                    cout << "najmanji element u hipu je :  " << h.getMin() << endl;
                else
                    cout << "hip je prazan" << endl;
                break;

            case 4:
                if(h.getVel())
                {
                    h.deleteMin(steps);
                    cout << "obrisan je najmanji element u hipu!" << endl;
                }
                else
                    cout << "greska, hip je prazan" << endl;
                break;

            case 5:
                cout << "unesite zeljeni red hipa:" << endl;
                cin >> m;
                h = h.convertTo(m);
                cout << "promenjen je red hipa!" << endl;
                break;

            case 6:
                cout << "odaberite nacin unosa drugog hipa" << endl;
                h2 = ucitajHeap();
                h = h.unionHeap(h2, steps);
                break;

            case 7:
                cout << "izgled hipa:" << endl << h << endl << endl;
                break;

            case 8:
                cout << "hehe :)" << endl;
                cout << "unesite element koji zelite da izbacite" << endl;
                cin >> n;
                h = h.deleteKey(n, steps);
                cout << "element je uspesno obrisan!" << endl;
                break;

            default:
                cout << "izabrali ste nepostojecu opciju, pokusajte ponovo" << endl;
        }
    }
}