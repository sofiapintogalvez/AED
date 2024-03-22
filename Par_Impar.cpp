// Ordenar una lista de menor a mayor teniendo impares e impares, algoritmo insercion

#include <iostream>

using namespace std;

void orden(int* impar, int* par)
{
    int* tam = par + (par - impar);
    int* atras, aux;

    for (; par < tam; par++)
    {
        aux = *par;
        atras = par - 1;
        while (atras >= impar && *atras > aux)
        {
            *(atras + 1) = *atras;
            atras--;
        }
        *(atras + 1) = aux;
    }
}

void orden2(int* ini, int* mid)
{
    int* fin = mid + (mid - ini);

    while (ini < fin && mid < fin)
    {
        if (*mid < *ini)
        {
            for (int* M = ini; M < mid; M++)
                swap(*M, *mid);
            mid++;
        }
        else
            ini++;
    }
}

int main()
{
    int A[10] = { 1,3,5,7,9,2,4,6,8,10 };

    orden2(A, A + 5);
    for (int* p = A; p < A + 10; p++)
        cout << *p << " ";

    return 0;
}