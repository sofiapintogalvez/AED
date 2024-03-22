// Hacer head-pop y tail-push

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
struct cola
{
    nodo<T>* head = NULL;
    nodo<T>* tail = NULL;
    void push(T valor);
    bool pop(T& valor);
    bool empty();
    void print();
    ~cola();
};

template <class T>
void cola<T>::push(T valor)
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
bool cola<T>::pop(T& valor)
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
bool cola<T>::empty()
{
    return tail;
}

template <class T>
void cola<T>::print()
{
    cout << "head->";
    for (nodo<T>* p = head; p; p = p->next)
        cout << p->valor << "->";
    cout << "tail\n";
}

template <class T>
cola<T>::~cola()
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
    cola<int> CL;

    for (int i = 1; i <= 15; i++)
        CL.push(i);

    CL.print();

    int popp = 20;
    CL.pop(popp);
    CL.print();
}