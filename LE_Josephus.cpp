// Hacer el metodo JOSEPHUS para una lista DOBLEMENTE ENLAZADA

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
    nodo<T>* prev;
    nodo(T v, nodo<T>* n = NULL, nodo<T>* pr = NULL)
    {
        valor = v;
        next = n;
        prev = pr;
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
    void josephus(T valor);
    void printNext();
    void printPrev();
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
            nodo<T>* nuevo = new nodo<T>(valor, head, tail);
            if (!head)
            {
                head = tail = nuevo;
                head->next = head->prev = head;
            }
            else
            {
                head->prev = nuevo;
                tail->next = nuevo;
                head = nuevo;
            }
        }
        else
        {
            nodo<T>* nuevo = new nodo<T>(valor, pos->next, pos);
            pos->next = nuevo;
            if (nuevo->next)
                nuevo->next->prev = nuevo;

            if (pos == tail)
                tail = nuevo;

            tail->next = head;
            head->prev = tail;
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

            if (tmp->next)
            {
                tmp->next->prev = pos;
            }
        }
        else
        {
            tmp = head;
            if (head == tail)
            {
                head = tail = NULL;
            }
            else
            {
                head = head->next;
                head->prev = tail;
                tail->next = head;
            }
        }
        delete tmp;
    }
    else
        return false;

    return rpta;
}

template <class T, class O>
void LE<T, O>::josephus(T valor)
{
    nodo<T>* p = head, * tmp;
    int num{ 0 };

    do {
        p = p->next;
        num++;
    } while (p != head);

    for (; num > 0; num--)
    {
        for (int i = 1; i < valor; i++)
            p = p->next;

        cout << p->valor << endl;
        tmp = p->next;
        del(p->valor);
        p = tmp;
    }
}

template <class T, class O>
void LE<T, O>::printNext()
{
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
void LE<T, O>::printPrev()
{
    cout << "head->";
    for (nodo<T>* p = tail; p; p = p->prev)
    {
        cout << p->valor << "->";
        if (p->prev == tail)
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

    cout << "NEXT Circular\n";
    Lista_entera.add(30);
    Lista_entera.add(1);
    Lista_entera.add(7);
    Lista_entera.add(25);
    Lista_entera.add(2);
    Lista_entera.printNext();

    cout << endl;

    cout << "PREV Circular\n";
    Lista_entera.printPrev();

    cout << endl;

    cout << "Josephus\n";
    Lista_entera.josephus(3);
}