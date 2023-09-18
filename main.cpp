#include "Heap.h"
#include "PQueue.h"
#include <chrono>
#include <thread>
#include <iostream>
using namespace std;
using namespace std::chrono;

int main() {
    int izbor, pom = 0;
    cout << "Dobrodosli! : )" << endl;
    while(1)
    {
        cout << "\n\n\tG L A V N I   M E N I\n\nunesite redni broj zeljene stavke:\n\t(1) rad sa heap-om\n\t(2) rad sa prioritetnim redom\n\n\t(0) kraj programa\n\n";
        cin >> izbor;
        switch(izbor)
        {
            case 1:
                switch1();
                break;

            case 2:
                switch2();
                break;

            case 0:
                cout << "Prijatan dan! : )" << endl;
                return 0;

            default:
                cout << "izabrali ste nepostojecu opaciju, pokusajte ponovo" << endl;
        }
    }
}

