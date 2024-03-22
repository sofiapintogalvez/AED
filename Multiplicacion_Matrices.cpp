// Hacer multiplicacion de dos matrices y guardarla en la ultima dimensión

#include <iostream>

using namespace std;

void multi(int(*p)[3][3])
{
    int rpta = 0;

    int(*col)[3] = *(p + 1);
    int* c = *col;

    int(*z)[3] = *(p + 2);
    int* z1 = *z;

    int(*x)[3] = *p;

    while (x < *(p + 3))
    {
        while (x < *(p + 1) && c < *(col + 1))
        {
            for (int* x1 = *x, *y1 = c; x1 < *(x + 1) && y1 < *(col + 3); x1++, y1 += 3)
                rpta += *x1 * *y1;
            *z1 = rpta;
            rpta = 0;
            c++;
            z1++;
        }
        c = *col;
        x++;
    }
}

int main()
{
    int A[3][3][3] = { {{0,-7,3},{2,4,-1},{12,7,-6}},{{5,4,-3},{0,-6,10},{-2,8,11}},{{},{},{}} };

    multi(A);

    for (int(*p)[3][3] = A; p < A + 3; p++)
    {
        for (int(*q)[3] = *p; q < *(p + 1); q++)
        {
            for (int* r = *q; r < *(q + 1); r++)
                cout << *r << "\t";
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}