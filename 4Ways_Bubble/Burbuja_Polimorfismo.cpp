// Algoritmo burbuja con polimorfismo

#include <iostream>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

struct CP
{
    virtual bool cmp(int a, int b) = 0;
};

struct ASC : CP
{
    bool cmp(int a, int b)
    { 
        return a > b; 
    }
};

struct DESC : CP
{
    bool cmp(int a, int b)
    {
        return a < b;
    }
};

void bubble(int* ar, int n, CP* p)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            if(p->cmp(ar[i], ar[j]))
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
    const int n = 100000;
    int arr[n];
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 100000);
    for (int i = 0; i < n; i++)
        arr[i] = dist(gen);

    ASC asc;
    DESC desc;
    CP* p;

    p = &asc;
    auto start = high_resolution_clock::now();
    bubble(arr, n, p);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Tiempo de ejecución: " << duration.count() << " microsegundos" << endl;

    return 0;
}