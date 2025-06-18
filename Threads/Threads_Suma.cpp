// Uso de threads para sumar un array por partes

#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void F1(int* ar, int n, int* s)     // n es la cantidad de elementos que proesara el thread
{
    for(int i = 0; i < n; i++)      // se suma en su respectiva "casilla" para cada thread
    {
        *s += ar[i];
    }
}

int main()
{
    int ar[16] = { 2, 6, 3, 1, 7, 8, 9, 6, 4, 3, 2, 8, 9, 11, 13, 1 };
    int xsum[4] = { 0, 0, 0, 0 };
    int sum = 0, nThreads = 4;
    vector<thread> ths(nThreads);

    for(int i = 0; i < nThreads; i++)
        ths[i] = thread(F1, &ar[i*4], 4, &xsum[i]);      // ar + (i*4) y xsum + i son equivalentes

    for(int i = 0; i < nThreads; i++)
        ths[i].join();

    for(int i = 0; i < nThreads; i++)
        sum += xsum[i];

    cout << "Suma: " << sum << endl;

    return 0;
}