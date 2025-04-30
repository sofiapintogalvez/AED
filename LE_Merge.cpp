// Hacer 2 listas enlazadas ordenadas y sin repeticiones, método merge que une ambas en orden en la lista 2

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
class LE
{
public:
    nodo<T>* head = NULL;
    bool find(T valor, nodo<T>*& pos);
    void add(T valor);
    void merge(nodo<T>*& h1, nodo<T>*& h2);
    void print();
    ~LE();
};

template <class T>
bool LE<T>::find(T valor, nodo<T>*& pos)
{
    pos = NULL;
    nodo<T>* p = head;
    for (; p && p->valor < valor; pos = p, p = p->next);
    if (p && p->valor == valor)
        return true;
    else
        return false;
}

template <class T>
void LE<T>::add(T valor)
{
    nodo<T>* pos;
    if (!find(valor, pos))
        if (!pos)
            head = new nodo<T>(valor, head);
        else
            pos->next = new nodo<T>(valor, pos->next);
}

template <class T>
void LE<T>::merge(nodo<T>*& h1, nodo<T>*& h2)
{
    nodo<int>* p1 = h1;
    nodo<int>* p2 = h2;
    nodo<int>* ante;

    if (h1->valor < h2->valor)
    {
        h2 = h1;
        ante = p1;
        p1 = p1->next;
    }
    else
    {
        ante = p2;
        p2 = p2->next;
    }

    while (p1 && p2)
    {
        if (p1->valor < p2->valor)
        {
            ante->next = p1;
            p1 = p1->next;
            ante = ante->next;
        }
        else
        {
            ante->next = p2;
            p2 = p2->next;
            ante = ante->next;
        }
    }

    if (p1)
        ante->next = p1;
    else
        ante->next = p2;

    h1 = 0;
}

template <class T>
void LE<T>::print()
{
    cout << "head->";
    for (nodo<T>* p = head; p; p = p->next)
        cout << p->valor << "->";
    cout << "NULL\n";
}

template <class T>
LE<T>::~LE()
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
    LE<int> H1;
    LE<int> H2;

    for (int i = 200; i <= 800; i += 150)
        H1.add(i);

    cout << "Lista 1\n";
    H1.print();

    for (int i = 150; i <= 1000; i += 232)
        H2.add(i);

    cout << "Lista 2\n";
    H2.print();

    H1.merge(H1.head, H2.head);
    cout << "Merge\n";
    H2.print();
}
