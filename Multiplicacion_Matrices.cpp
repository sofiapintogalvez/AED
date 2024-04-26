// Hacer multiplicacion de dos matrices y guardarla en la ultima dimensión

#include <iostream>

using namespace std;

void multi(int(*A)[3][3])
{
    int* p = **A;
    int* q = **(A + 1);
    int* r = **(A + 2);
    int* ri = **(A + 2);

    while (p < **(A + 1))
    {
        *r += (*p) * (*q);
        q++;
        r++;

        if (r == ri + 3)
        {
            p++;
            r = ri;
        }

        if (q == **(A + 2))
        {
            q = **(A + 1);
            ri+=3;
            r = ri;
        }
    }
}

void multi2(int(*p)[3][3])
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
    int A[3][3][3] = { {{2,0,1},{3,0,0},{5,1,1}},{{1,0,1},{1,2,1},{1,1,0}},{{},{},{}} }; // 3 1 2, 3 0 3, 7 3 6

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
