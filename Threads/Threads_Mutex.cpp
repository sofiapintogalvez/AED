// Uso de threads con mutex para imprimir numeros

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

mutex m;
long sum = 0;

void F1(int x, int n)
{
    for(int i = 0; i < n; i++)
    {
        m.lock();       // convierte a secuencial un proceso paralelo de threads
        sum += x;
        m.unlock();
    }
}

int main()
{
    int nThreads = thread::hardware_concurrency();
    vector<thread> ths(nThreads);

    cout << "Nucleos: " << nThreads << endl;

    for(int i = 0; i < nThreads; i++)
        ths[i] = thread(F1, i, 1000);

    for(int i = 0; i < nThreads; i++)
        ths[i].join();

    cout << "Suma: " << sum << endl;

    return 0;
}