#include <iostream>

using namespace std;

int** CrearM(int f, int c) 
{
    int** A = new int* [f];
    for (int **p = A; p < A + f; p++) 
        *p = new int[c];
    
    return A;
}

void LlenarM(int** A, int f, int c) 
{
    /*int i = 0;
    for (int** p = A; p < A + f; p++, i++)
    {
        int j = 0;
        for (int* q = *p; q < *p + c; q++, j++) 
        {
            cout << "Valor " << i << "-" << j << ": ";
            cin >> *q;
        }
    }*/

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

int** multiplyMatrices(int** A1, int** A2, int rows1, int cols1, int cols2) 
{
    int** A3 = CrearM(rows1, cols2);

    for (int** p = A3; p < A3 + rows1; p++)
    {
        for (int* q = *p; q < *p + cols2; q++)
        {
            *q = 0;
        }
    }

    for (int i = 0; i < rows1; ++i) 
    {
        for (int j = 0; j < cols2; ++j) 
        {
            int* p = *(A3 + i) + j;
            for (int k = 0; k < cols1; ++k) 
            {
                int* p1 = *(A1 + i) + k;
                int* p2 = *(A2 + k) + j;
                *p += (*p1) * (*p2);
            }
        }
    }

    return A3;
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

void Liberar(int** A, int rows) 
{
    for (int** p = A; p < A + rows; p++)
        delete[] * p;
    delete[] A;
}

int main() 
{
    int m, i, n;

    cout << "M: "; cin >> m;
    cout << "I: "; cin >> i;
    cout << "N: "; cin >> n;

    int** A1 = CrearM(m, i);
    int** A2 = CrearM(i, n);

    cout << "\nPrimera matriz\n";
    LlenarM(A1, m, i);
    print(A1, m, i);

    cout << "\nSegunda matriz\n";
    LlenarM(A2, i, n);
    print(A2, i, n);

    int** A3 = multiplyMatrices(A1, A2, m, i, n);

    cout << "\nRespuesta\n";
    print(A3, m, n);

    Liberar(A1, m);
    Liberar(A2, i);
    Liberar(A3, n);
}