// Hacer una calculadora modular de suma, resta, multiplicacion e inverso

#include <iostream>

using namespace std;

char Menu()
{
    char opcion;

    cout << "\tCALCULADORA MODULAR\n\n";
    cout << "Suma (s)\n";
    cout << "Resta (r)\n";
    cout << "Multiplicacion (m)\n";
    cout << "Inverso (i)\n\n";

    cout << "Ingrese opcion: ";
    cin >> opcion;
    cout << endl;

    return opcion;
}

void ModSuma(int n1, int n2, int mod)
{
    int x, rpta;

    x = n1 + n2;
    rpta = x % mod;

    cout << n1 << " mod " << mod << " + " << n2 << " mod " << mod << endl;
    cout << rpta << " mod " << mod;
}

void ModResta(int n1, int n2, int mod)
{
    int x, rpta;

    x = n1 - n2;
    rpta = x % mod;

    if (rpta < 0)
    {
        rpta *= -1;
        rpta = mod - rpta;
    }

    cout << n1 << " mod " << mod << " - " << n2 << " mod " << mod << endl;
    cout << rpta << " mod " << mod;
}

void ModMulti(int n1, int n2, int mod)
{
    int x, rpta;

    x = n1 * n2;
    rpta = x % mod;

    if (rpta < 0)
    {
        rpta *= -1;
        rpta = mod - rpta;
    }

    cout << n1 << " mod " << mod << " * " << n2 << " mod " << mod << endl;
    cout << rpta << " mod " << mod;
}

int MCD(int x, int y)
{
    int temp;
    do
    {
        temp = y;
        y = x % y;
        x = temp;
    } while (y > 0);

    return x;
}

void ModInv()
{
    int n, mod;

    cout << "Numero: "; cin >> n;
    cout << "Modulo: "; cin >> mod;
    cout << endl;

    if (MCD(n, mod) != 1)
        cout << "No tiene inverso";

    else
        for (int i = 0; i < mod; i++)
        {
            if ((n * i - 1) % mod == 0)
                cout << i;
        }
}

int main()
{
    int num1, num2, modulo;
    char x;

    x = Menu();
    cout << endl;

    if (x == 's')
    {
        cout << "Primer numero: "; cin >> num1;
        cout << "Segundo numero: "; cin >> num2;
        cout << "Modulo: "; cin >> modulo;
        ModSuma(num1, num2, modulo);
    }
    else if (x == 'r')
    {
        cout << "Primer numero: "; cin >> num1;
        cout << "Segundo numero: "; cin >> num2;
        cout << "Modulo: "; cin >> modulo;
        ModResta(num1, num2, modulo);
    }
    else if (x == 'm')
    {
        cout << "Primer numero: "; cin >> num1;
        cout << "Segundo numero: "; cin >> num2;
        cout << "Modulo: "; cin >> modulo;
        ModMulti(num1, num2, modulo);
    }
    else if (x == 'i')
    {
        ModInv();
    }
    else
    {
        cout << "No existe";
    }
}