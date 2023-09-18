#include "Heap.h"
#include "PQueue.h"
#include <chrono>
#include <thread>
#include <iostream>
using namespace std;
using namespace std::chrono;

bool PQueue::empty() const
{
    return h.getVel() == 0;
}

int PQueue::front() const
{
    return h.getMin();
}

void PQueue::deleteMin(int &steps)
{
    h.deleteMin(steps);
}

int PQueue::deleteAndFront(int &steps)
{
    int pom = h.getMin();
    h.deleteMin(steps);
    return pom;
}

void PQueue::insert(int elem, int &steps)
{
    h.add(elem, steps);
}

void PQueue::changeM(int newM)
{
    m = newM;
    h.convertTo(newM);
}

void meni2()
{
    cout << "\n\n\tQ U E U E   M E N I\nunesite redni broj zeljene stavke:\n\t(1) stvaranje prioritetnog reda"
            "\n\t(2) ispitivanje da li je red prazan\n\t"
            "(3) dohvatanje najmanjeg elementa reda\n\t(4) brisanje sa dohvatanjem najmanjeg elementa\n\t"
            "(5) brisanje najmanjeg elementa\n\t(6) umetanje elementa u red\n\t(7) performanse\n\n\t(0) povratak na glavni meni\n\n";
}

void meni22()
{
    cout << "\nunesite redni broj zeljene stavke:\n\t(1) stvaranje prioritetnog reda ucitavanjem iz datoteke\n\t"
            "(2) stvaranje prioritetnog reda ucitavanjem sa komandne linije"
            "\n\t(3) stvaranje nasumicnog prioritetnog reda\n";
}

void switch2() {
    int izbor, *arr, n, steps = 0;
    string name;
    PQueue red(2);
    while (true) {
        meni2();
        cin >> izbor;
        switch (izbor) {
            case 0:
                return;

            case 1:
                meni22();
                cin >> izbor;
                switch(izbor)
                {
                    case 1:
                        cout << "unesite broj datoteke" << endl;
                        cin >> n;
                        if (n != 10 and n != 100 and n != 1000 and n != 10000 and n != 1000000) {
                            cout << "ne postoji datoteka sa zadatim brojem elemenata, pokusajte ponovo" << endl;
                            break;
                        }
                        arr = unosIzFajla(n);
                        red = PQueue(2, arr, n);
                        cout << "red unesen iz datoteke je formiran!" << endl;
                        break;

                    case 2:
                        cout << "unesite broj elemenata koji unosite" << endl;
                        cin >> n;
                        arr = new int[n];
                        for (int i = 0; i < n; i++)
                            cin >> arr[i];
                        red = PQueue(2, arr, n);
                        cout << "red unesen sa komandne linije je formiran!" << endl;
                        break;

                    case 3:
                        cout << "unesite broj elemenata koji unosite" << endl;
                        cin >> n;
                        arr = unosPseudosluc(n);
                        red = PQueue(2, arr, n);
                        cout << "nasumican red je formiran!" << endl;
                        break;
                    default:
                        cout << "izabrali ste nepostojecu opciju" << endl;
                        break;
                }
                break;

            case 2:
                cout << (red.empty() ? "red je prazan!" : "red nije prazan!") << endl;
                break;

            case 3:
                if (!red.empty())
                    cout << "najmanji element u redu je :  " << red.front() << endl;
                else
                    cout << "red je prazan" << endl;
                break;

            case 4:
                if (!red.empty())
                    cout << "obrisan je najmanji element u redu :  " << red.deleteAndFront(steps) << endl;
                else
                    cout << "greska, red je prazan" << endl;
                break;

            case 5:
                if (!red.empty()) {
                    red.deleteMin(steps);
                    cout << "obrisan je najmanji element u redu!" << endl;
                } else
                    cout << "greska, red je prazan" << endl;
                break;

            case 6:
                cout << "unesite element koji zelite da ubacite" << endl;
                cin >> n;
                red.insert(n, steps);
                cout << "element je ubacen u red! " << endl;
                break;

            case 7:
                cout << "velicina skupa i red hipa\tvreme umetanja\tbroj koraka-umetanje\tvreme izbacivanja\tbroj koraka-izbacivanje"<< endl;
                for (int i = 100; i <= 100000; i *= 10)
                {
                    arr = unosIzFajla(i);
                    for(int j = 2; j <= 8; j*=2)
                    {
                        steps = 0;
                        printf("%15d,%d\t", i, j);
                        red = PQueue(j);
                        auto start = high_resolution_clock::now();
                        for (int k = 0; k < i; k++)
                            red.insert(arr[k], steps);
                        auto end2 = high_resolution_clock::now();
                        duration<double, milli> time_elapsed_ms = end2 - start;
                        printf("%18lfms\t%15d\t", time_elapsed_ms.count(), steps);

                        steps = 0;
                        start = high_resolution_clock::now();
                        for (int k = 0; k < i; k++)
                            red.deleteMin(steps);
                        end2 = high_resolution_clock::now();
                        time_elapsed_ms = end2 - start;
                        printf("%18lfms\t%25d\n", time_elapsed_ms.count(), steps);
                    }
                }
                break;
            case 8:
                cout << "hehe :)" << endl;
                break;

            default:
                cout << "izabrali ste nepostojecu opciju, pokusajte ponovo" << endl;
        }
    }
}
