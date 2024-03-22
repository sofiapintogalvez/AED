// Hacer 2 listas enlazadas ordenadas y sin repeticiones, método merge que une ambas en orden en la lista 1

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
    nodo<T>* p = h1;
    nodo<T>* q = h2;
    nodo<T>* r = NULL;

    while (p && q)
    {

        if (p->valor < q->valor)
        {

            if (p->valor != h1->valor)
                r->next = p;
            else
                r = p;

            r = p;
            p = p->next;
        }
        else
        {

            if (q->valor == h2->valor)
            {
                r = q;
                h1 = q;
                q = q->next;
            }
            else
            {
                r->next = q;
                r = q;
                q = q->next;
            }
        }
        if (!q)
            r->next = p;
        else
            r->next = q;
    }
    h2 = NULL;
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
    H1.print();
}