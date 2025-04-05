// Algoritmo burbuja con puntero a funcion

#include <iostream>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

bool ASC(int a, int b)
{
    return a > b;
}

bool DESC(int a, int b)
{
    return a < b;
}

void bubble(int* ar, int n, bool (*pf)(int, int))
{
    for(int i = 0; i < n; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            if(pf(ar[i], ar[j]))
            {
                swap(ar[i], ar[j]);
            }
        }
    }
}

void print(int* ar, int n)
{
    for(int* p = ar; p < ar + n; p++)
        cout << *p << " ";
    cout << endl;
}

int main()
{
    const int n = 10000;
    int arr[n];
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 10000);
    for (int i = 0; i < n; i++)
        arr[i] = dist(gen);

    auto start = high_resolution_clock::now();
    bubble(arr, n, ASC);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Tiempo de ejecución: " << duration.count() << " microsegundos" << endl;

    return 0;
}