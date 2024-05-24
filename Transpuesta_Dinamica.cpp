#include <iostream>

using namespace std;

int** CrearM(int f, int c)
{
    int** A;
    A = new int* [f];

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

void Transpuesta(int** A, int** At, int f, int c)
{
    int** matriz = A;

    while (matriz < A + f)
    {
        int* fmatriz = *matriz;
        int** ftrans = At;

        while (fmatriz < *matriz + c)
        {
            *(*ftrans + (matriz - A)) = *fmatriz;
            fmatriz++;
            ftrans++;
        }
        matriz++;
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

void Liberar(int** A, int** At, int f, int c)
{
    for (int** p = A; p < A + f; p++)
        delete[] * p;
    delete[] A;

    for (int** p = At; p < At + c; p++)
        delete[] * p;
    delete[] At;
}

int main()
{
    int fil, col;

    cout << "Fila: "; cin >> fil;
    cout << "Columna : "; cin >> col;
    
    int** A = CrearM(fil, col);
    int** At = CrearM(col, fil);
    
    LlenarM(A, fil, col);
    Transpuesta(A, At, fil, col);
    
    print(A, fil, col);
    print(At, col, fil);
    
    Liberar(A, At, fil, col);
}
