// Hacer la matriz transpuesta

#include <iostream>

using namespace std;

void transp(int(*p)[4])
{
    int* diag = *p;

    while (diag < *(p + 4))
    {
        for (int* f = diag, *c = diag; f < *(p + 4) && c < *(p + 4); f++, c += 4)
        {
            swap(*f, *c);
        }
        diag += 5;
    }
}

int main()
{
    int A[4][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16} };

    transp(A);

    for (int(*p)[4] = A; p < A + 4; p++)
    {
        for (int* q = *p; q < *(p + 1); q++)
        {
            cout << *q << "\t";
        }
        cout << endl;
    }

    return 0;
}