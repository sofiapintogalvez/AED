// Clase pila con array haciendo push y pop

#include <iostream>

using namespace std;

template <class T>
class Pila
{
    T* top = nullptr;
    T elem[10];

    public:
        void push(T valor);
        bool pop(T& valor);
        void print();
};

template <class T>
void Pila<T>::push(T valor)
{
    if(!top)
    {
        elem[0] = valor;
        top = elem;
    }
    else
    {
        if(top == elem + 9)
            cout << "Pila llena" << endl;
        else
        {
            top++;
            *top = valor;
        }
    }
}

template <class T>
bool Pila<T>::pop(T& valor)
{
    bool saque = false;
    if(top >= elem)
    {
        valor = *top;
        cout << valor << endl;
        saque = true;
        top--;
    }
    return saque;
}

template <class T>
void Pila<T>::print()
{
    cout << "top" << endl;
    for(T* p = top; p >= elem; p--)
        cout << *p << endl;
    cout << "--------------------------------------------------" << endl;
}

int main()
{
    Pila<int> pl;
    int x = 0;

    cout << "VACIO" << endl;
    pl.print();

    cout << "PUSH" << endl;
    pl.push(5);
    pl.push(2);
    pl.push(8);
    pl.push(6);
    pl.push(3);
    pl.push(7);
    pl.push(4);
    pl.push(9);
    pl.push(1);
    pl.push(10);
    pl.print();

    cout << "POP" << endl;
    pl.pop(x);
    pl.print();
    pl.pop(x);
    pl.print();
}
