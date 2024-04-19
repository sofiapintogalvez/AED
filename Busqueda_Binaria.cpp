// Hacer el algoritmo de busqueda binaria con punteros

#include <iostream>

using namespace std;

bool BinarySearch(int* ini, int* fin, int*& pos, int key)
{
    while (ini <= fin)
    {
        pos = ini + (fin - ini) / 2;

        if (key == *pos)
            return true;

        else if (key < *pos)
            fin = pos - 1;

        else if (key > *pos)
            ini = pos + 1;

        else
            return false;
    }
}

int main()
{
    int A[9] = { 1,2,3,5,7,20,23,25,35 };
    int* p;

    if (BinarySearch(A, A + 8, p, 23))
        cout << "El numero " << *p << " si esta en el array\n";
    else
        cout << "El numero no se encuentra en el array";
}
