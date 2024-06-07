// Hacer la multiplicacion de matrices en memoria dinamica

#include <iostream>

using namespace std;

int** CrearM(int f, int c)
{
    int** A = new int* [f];

    for (int** p = A; p < A + f; p++)
        *p = new int[c];

    return A;
}

void LlenarM(int** A, int f, int c)
{
    int x = 0;
    for (int** p = A; p < A + f; p++)
    {
        for (int* q = *p; q < *p + c; q++)
        {
            x++;
            *q = x;
        }
    }
}

void Vacio(int** A, int f, int c)
{
    for (int** p = A; p < A + f; p++)
        for (int* q = *p; q < *p + c; q++)
            *q = 0;
}

void Multi(int** A1, int** A2, int** A3, int m, int i, int n)
{
    int** fA1 = A1;
    int* cA1 = *fA1;
    int** fA2 = A2;
    int** fA3 = A3;

    while (fA1 < A1 + m)
    {
        int* cA2 = *fA2;
        int* cA3 = *fA3;

        while (cA3 < *fA3 + n)
        {
            *cA3 += (*cA1) * (*cA2);
            cA2++;
            cA3++;
        }

        if (cA3 == *fA3 + n)
        {
            cA1++;
            fA2++;
        }

        if (cA1 == *fA1 + i)
        {
            fA1++;
            cA1 = *fA1;
            fA2 = A2;
            fA3++;
        }
    }
}

void print(int** A, int f, int c)
{
    for (int** p = A; p < A + f; p++)
    {
        for (int* q = *p; q < *p + c; q++)
            cout << *q << " ";
        cout << endl;
    }
    cout << endl;
}

void Liberar(int** A, int filas)
{
    for (int** p = A; p < A + filas; p++)
        delete[] * p;
    delete[] A;
}

int main()
{
    int m, i, n;

    cout << "M: "; cin >> m;
    cout << "I: "; cin >> i;
    cout << "N: "; cin >> n;

    cout << endl;

    int** A1 = CrearM(m, i);
    int** A2 = CrearM(i, n);
    int** A3 = CrearM(m, n);

    LlenarM(A1, m, i);
    LlenarM(A2, i, n);
    Vacio(A3, m, n);

    Multi(A1, A2, A3, m, i, n);

    print(A1, m, i);
    print(A2, i, n);
    print(A3, m, n);

    Liberar(A1, m);
    Liberar(A2, i);
    Liberar(A3, m);
}
