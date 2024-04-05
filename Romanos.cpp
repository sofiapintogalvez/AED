// Imprimir un numero ingresado por teclado en numeros romanos del 1 al 9999

#include <iostream>
#include <cmath>

using namespace std;

string dos_digitos(int n)
{
    string unidades[] = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

    string decenas[] = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };

    if (n < 10)
        return unidades[n];

    else if (n % 10 == 0)
        return decenas[n / 10];

    else
        return decenas[n / 10] + unidades[n % 10];
}

string centenas(int n)
{
    string centenas[] = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
    string extra;

    extra = dos_digitos(n % 100);

    if (n % 100 == 0)
        return centenas[n / 100];

    else
        return centenas[n / 100] + extra;
}

string decenas_mil(int n)
{
    string especiales[] = { "", "M", "MM", "MMM" };

    string res1, res2;
    int extra1, extra2;

    extra1 = n / 1000;
    extra2 = n % 1000;

    if (n % 1000 == 0 && n < 4000)
        return especiales[n / 1000];

    else if (n < 4000)
        return especiales[n / 1000] + centenas(extra2);

    res1 = dos_digitos(extra1);
    res2 = centenas(extra2);

    return "|" + res1 + "|" + res2;
}

string conversion(int l, int n)
{
    if (l == 1 || l == 2)
        return dos_digitos(n);

    else if (l == 3)
        return centenas(n);

    else if (l == 4)
        return decenas_mil(n);

    else
        return "";
}

int main()
{
    int num;
    do
    {
        cout << "\nIngrese numero: ";
        cin >> num;

        if (num >= 0 && num <= 9999)
        {
            int longitud = log10(num) + 1;
            cout << conversion(longitud, num);
        }
        else
        {
            cout << "\nNumero no valido, vuelva a ingresar\n";
            continue;
        }
    } while (num != 0);

    return 0;
}