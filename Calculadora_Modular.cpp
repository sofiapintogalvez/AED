// Hacer una calculadora modular de suma, resta, multiplicacion e inverso

#include <iostream>

using namespace std;

void ModSuma(int n1, int n2, int mod)
{
    int rpta = (n1 + n2) % mod;

    if (rpta < 0)
    {
        rpta *= -1;
        rpta = mod - rpta;
    }

    cout << n1 << " mod " << mod << " + " << n2 << " mod " << mod << endl;
    cout << rpta << " mod " << mod;
}

void ModResta(int n1, int n2, int mod)
{
    int rpta = (n1 - n2) % mod;

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
    int rpta = (n1 * n2) % mod;

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
    do
    {
        int temp = y;
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

void Menu()
{
    int num1, num2, modulo;
    char opcion{ 'o' };

    do 
    {
        cout << "\tCALCULADORA MODULAR\n\n";
        cout << "Suma (s)\n";
        cout << "Resta (r)\n";
        cout << "Multiplicacion (m)\n";
        cout << "Inverso (i)\n";
        cout << "Salir (x)\n\n";

        cout << "Ingrese opcion: ";
        cin >> opcion;
        cout << endl;

        if (opcion == 's')
        {
            cout << "Primer numero: "; cin >> num1;
            cout << "Segundo numero: "; cin >> num2;
            cout << "Modulo: "; cin >> modulo;
            ModSuma(num1, num2, modulo);
            cout << "\n\n";
        }
        else if (opcion == 'r')
        {
            cout << "Primer numero: "; cin >> num1;
            cout << "Segundo numero: "; cin >> num2;
            cout << "Modulo: "; cin >> modulo;
            ModResta(num1, num2, modulo);
            cout << "\n\n";
        }
        else if (opcion == 'm')
        {
            cout << "Primer numero: "; cin >> num1;
            cout << "Segundo numero: "; cin >> num2;
            cout << "Modulo: "; cin >> modulo;
            ModMulti(num1, num2, modulo);
            cout << "\n\n";
        }
        else if (opcion == 'i')
        {
            ModInv();
            cout << "\n\n";
        }
        else
            return;
    } while (opcion != 'x');
}

int main()
{
    Menu();
}
