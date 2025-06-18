// Uso de threads para imprimir cierta cantidad de caracteres en forma paralela

#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void F1(char c, int n)
{
    for(int i = 0; i < n; i++)
        cout << c;
}

int main()
{
    int nThreads = thread::hardware_concurrency();
    vector<thread> ths(nThreads);       // vector de threads

    cout << "Nucleos: " << nThreads << endl;

    for(int i = 0; i < nThreads; i++)
        ths[i] = thread(F1, char('a'+i), 100);  // parametros -> la funcion y luego los parametros de esa funcion

    for(int i = 0; i < nThreads; i++)
        ths[i].join();      // espera a que todos los threads terminen

    return 0;
}