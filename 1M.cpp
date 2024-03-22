// Imprimir un numero ingresado por teclado en letras (como se lee) del 1 al 1M

#include <iostream>
#include <cmath>

using namespace std;

string dos_digitos(int n)
{
    string unidades[] = { "", "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve", "diez", "once", "doce", "trece", "catorce", "quince", "dieciseis", "diecisiete", "dieciocho", "diecinueve" };
    string decenas[] = { "", "", "veinte", "treinta", "cuarenta", "cincuenta", "sesenta", "setenta", "ochenta", "noventa" };

    if (n > 0 && n <= 19)
        return unidades[n];

    else if (n % 10 == 0)                           // cuando son decenas enteras 20,30,40...
        return decenas[n / 10];

    else
        return decenas[n / 10] + " y " + unidades[n % 10];
}

string centenas(int n)
{
    string centenas[] = { "", "ciento", "doscientos", "trescientos", "cuatrocientos", "quinientos", "seiscientos", "setecientos", "ochocientos", "novecientos" };
    string extra;

    extra = dos_digitos(n % 100);

    if (n == 100)
        return "cien";

    else if (n % 100 == 0)                          // cuando son centenas enteras 200,300,400...
        return centenas[n / 100];

    else
        return centenas[n / 100] + " " + extra;
}

string decenas_mil(int n)
{
    string res1, res2;
    int extra1, extra2;

    if (n == 1000)
        return "mil";

    else if (n % 1000 == 0)                         // cuando son miles enteros 2000,15000,7000...
        return dos_digitos(n / 1000) + " mil";

    extra1 = n / 1000;
    extra2 = n % 1000;

    if (extra1 == 1)
        return "mil " + centenas(extra2);

    res1 = dos_digitos(extra1) + " mil ";
    res2 = centenas(extra2);

    return res1 + res2;
}

string centenas_mil(int n)
{
    string res1, res2;
    int extra1, extra2;

    if (n == 100000)
        return centenas(100) + " mil";

    else if (n % 100000 == 0)
        return centenas(n / 1000) + " mil";           // cuando son centimiles enteros 200000,500000...

    extra1 = n / 1000;
    extra2 = n % 1000;

    res1 = centenas(extra1) + " mil ";
    res2 = centenas(extra2);

    return res1 + res2;
}

string conversion(int l, int n)
{
    if (l == 1 || l == 2)
        return dos_digitos(n);

    else if (l == 3)
        return centenas(n);

    else if (l == 4 || l == 5)
        return decenas_mil(n);

    else if (l == 6)
        return centenas_mil(n);

    else if (l == 7 && n == 1000000)
        return "un millon";

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

        if (num >= 0 && num <= 1000000)
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