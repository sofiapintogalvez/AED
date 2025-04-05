// Algoritmo burbuja con functores

#include <iostream>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

struct ASC
{
    bool operator()(int a, int b)
    {
        return a > b;
    }
};

struct DESC
{
    bool operator()(int a, int b)
    {
        return a < b;
    }
};

template <class O>
void bubble(int* ar, int n)
{
    O op;
    for(int i = 0; i < n; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            if (op(ar[i], ar[j]))
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

    auto start = high_resolution_clock::now();
    bubble<ASC>(arr, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Tiempo de ejecución: " << duration.count() << " microsegundos" << endl;

    return 0;
}