// Hacer el ordenamiento por burbuja al derecho y al reves

#include <iostream>

using namespace std;

void cocktail(int* inicio, int* fin)
{
    while (inicio < fin)
    {
        for (int* m = inicio; m < fin; m++)
        {
            if (*m > *(m + 1))
                swap(*m, *(m + 1));
        }
        fin--;

        for (int* n = fin; n > inicio; n--)
        {
            if (*n < *(n - 1))
                swap(*n, *(n - 1));
        }
        inicio++;
    }
}

int main()
{
    int A[10] = { 10, 11, 15, 1, 8, 3, 9, 2, 7, 17 };

    cocktail(A, A + 9);
    for (int* p = A; p < A + 10; p++)
        cout << *p << " ";

    return 0;
}