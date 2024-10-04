// Hacer head-pop y tail-push en una Cola

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
struct Cola
{
    nodo<T>* head = NULL;
    nodo<T>* tail = NULL;
    void push(T valor);
    bool pop(T& valor);
    void print();
    ~Cola();
};

template <class T>
void Cola<T>::push(T valor)
{
    if (head == NULL && tail == NULL)
    {
        head = new nodo<T>(valor);
        tail = head;
    }
    else
    {
        tail->next = new nodo<T>(valor);
        tail = tail->next;
    }
}

template <class T>
bool Cola<T>::pop(T& valor)
{
    bool saque = false;
    valor = 0;
    if (head)
    {
        valor = head->valor;
        saque = true;
        nodo <T>* tmp = head;
        head = head->next;
        delete tmp;
    }
    return saque;
}

template <class T>
void Cola<T>::print()
{
    cout << "head->";
    for (nodo<T>* p = head; p; p = p->next)
        cout << p->valor << "->";
    cout << "tail\n";
}

template <class T>
Cola<T>::~Cola()
{
    nodo<T>* tmp;
    while (head)
    {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}

int main()
{
    Cola<int> CL;
    int popp = 0;

    CL.print();

    CL.push(5);
    CL.push(3);
    CL.push(8);
    CL.print();

    CL.pop(popp);
    CL.print();
    CL.pop(popp);
    CL.print();
    CL.pop(popp);
    CL.print();
}
