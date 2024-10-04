// Hacer push-pop con top en una Pila

#include <iostream>

using namespace std;

template <class T>
struct nodo
{
    T valor;
    nodo<T>* next;
    nodo(T v, nodo<T>* n = NULL)
    {
        valor = v;
        next = n;
    }
};

template <class T>
class Pila
{
public:
    nodo<T>* top = NULL;
    void push(T valor);
    bool pop(T& valor);
    void print();
    ~Pila();
};

template <class T>
void Pila<T>::push(T valor)
{
    if (top == NULL)
        top = new nodo<T>(valor);         
    else
    {
        nodo<T>* temp = new nodo<T>(valor);
        temp->next = top;
        top = temp;
    }
}

template <class T>
bool Pila<T>::pop(T& valor)
{
    bool saque = false;
    valor = 0;
    if (top)
    {
        saque = true;
        nodo <T>* tmp = top;
        top = top->next;
        delete tmp;
    }
    return saque;
}

template <class T>
void Pila<T>::print()
{
    cout << "top->";
    for (nodo<T>* p = top; p; p = p->next)
        cout << p->valor << "->";
    cout << "null\n";
}

template <class T>
Pila<T>::~Pila()
{
    nodo<T>* tmp;
    while (top)
    {
        tmp = top;
        top = top->next;
        delete tmp;
    }
}

int main()
{
    Pila<int> PL;
    int popp = 0;

    cout << "VACIO\n";
    PL.print();

    cout << "PUSH\n";
    PL.push(5);
    PL.print();
    PL.push(3);
    PL.print();
    PL.push(8);
    PL.print();
 
    cout << "POP\n";
    PL.pop(popp);
    PL.print();
    PL.pop(popp);
    PL.print();
    PL.pop(popp);
    PL.print();
}