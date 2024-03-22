// Hacer functores para ordenar una lista enlazada CIRCULAR de forma ASC ó DESC

#include <iostream>

using namespace std;

template <class P>
struct ASC
{
    P operator()(P a, P b)
    {
        return a < b;
    }
};

template <class P>
struct DESC
{
    P operator()(P a, P b)
    {
        return a > b;
    }
};

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

template <class T, class O>
class LE
{
public:
    nodo<T>* head = NULL;
    nodo<T>* tail = NULL;
    bool find(T valor, nodo<T>*& pos);
    void add(T valor);
    bool del(T valor);
    void print();
    ~LE();
};

template <class T, class O>
bool LE<T, O>::find(T valor, nodo<T>*& pos)
{
    O op;
    pos = NULL;
    nodo<T>* p = head;

    if (!head)
        return false;

    do {
        if (op(p->valor, valor)) 
        {
            pos = p;
            p = p->next;
        }
        else 
            break;
    } while (p != head);

    return (p && p->valor == valor);
}

template <class T, class O>
void LE<T, O>::add(T valor)
{
    nodo<T>* pos;
    if (!find(valor, pos))
    {
        if (!pos)
        {
            head = new nodo<T>(valor, (head == NULL) ? NULL : head);
            if (!tail)
            {
                tail = head;
                tail->next = head;
            }
            else
                tail->next = head;
        }
        else
        {
            pos->next = new nodo<T>(valor, pos->next);
            if (pos == tail)
            {
                tail = pos->next;
                tail->next = head;
            }
        }
    }
}

template <class T, class O>
bool LE<T, O>::del(T valor)
{
    nodo<T>* pos, * tmp;
    bool rpta;
    rpta = find(valor, pos);

    if (rpta)
    {
        if (pos)
        {
            tmp = pos->next;
            pos->next = tmp->next;
            if (tmp == tail)
                tail = pos;
        }
        else
        {
            tmp = head;
            head = tmp->next;
            if (tmp == tail)
                tail = head;
        }
        delete tmp;
    }
    return rpta;
}

template <class T, class O>
void LE<T, O>::print()
{
    cout << "head->";
    for (nodo<T>* p = head; p ; p = p->next)
    {
        cout << p->valor << "->";
        if (p->next == head)
            break;
    }

    cout << "head->";
    for (nodo<T>* p = head; p; p = p->next)
    {
        cout << p->valor << "->";
        if (p->next == head)
            break;
    }
    cout << "head\n";
}

template <class T, class O>
LE<T, O>::~LE()
{
    nodo<T>* actual = head;
    nodo<T>* tmp;
    
    do {
        tmp = actual->next;
        delete actual;
        actual = tmp;
    } while (actual != head);

    head = NULL;
    tail = NULL;
}

int main()
{
    LE<int, ASC<int>> Lista_entera;

    cout << "Add Circular\n";
    Lista_entera.add(80);
    Lista_entera.add(21);
    Lista_entera.add(102);
    Lista_entera.add(1);
    Lista_entera.add(5);
    Lista_entera.print();

    cout << endl;

    cout << "Del Circular\n";
    Lista_entera.del(3);
    Lista_entera.print();
}