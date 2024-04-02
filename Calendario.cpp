// Imprimir la fecha ingresada en forma de calendario

#include <iostream>

using namespace std;

int Zeller(int mes, int anio, int dia)
{
    int x = (14 - mes) / 12;
    int y = anio - x;
    int z = mes + 12 * x - 2;

    int d = (dia + y + y / 4 - y / 100 + y / 400 + (31 * z) / 12) % 7;

    return d;
}

bool Bisiesto(int anio)
{
    if (anio % 4 != 0) 
        return false;
    else if (anio % 100 != 0) 
        return true;
    else if (anio % 400 != 0) 
        return false;
    return true;
}

int DiasMes(int mes, int anio)
{
    if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
        return 31;

    if (mes == 2)
    {
        if (Bisiesto(anio) == true)
            return 29;
        else
            return 28;
    }
    else
        return 30;
}

void Calendario(int mes, int anio)
{
    string meses[] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Noviembre", "Diciembre" };

    int primero = Zeller(mes, anio, 1);

    cout << meses[mes - 1] << " del " << anio << "\n\n";

    cout << "DOM LUN MAR MIE JUE VIE SAB\n";

    for (int i = 0; i < primero; i++)
        cout << "    ";

    int dias = DiasMes(mes, anio);

    for (int j = 1; j <= dias; j++)
    {
        if (j < 10)
            cout << j << "   ";
        else
            cout << j << "  ";
        primero++;
        
        if (primero % 7 == 0)
            cout << endl;
    }
}

int main()
{
    int m, a;

    cout << "Mes y anio:\n";
    cin >> m;
    cin >> a;

    cout << endl;

    Calendario(m, a);
}
