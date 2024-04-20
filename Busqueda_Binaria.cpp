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
    int* p, n, pp;

    cout << "Ingrese numero a buscar: ";
    cin >> n;

    if (BinarySearch(A, A + 8, p, n))
    {
        for (int* i = A; i <= p; i++)
            pp++;
        
        cout << "\nEl numero " << *p << " si esta en el array en la posicion " << pp << endl;
    }
        
    else
        cout << "\nEl numero no se encuentra en el array";
}
