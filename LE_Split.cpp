// LE con functor de cumple, si es verdadero se queda en H1 y si es falso se va a H2

#include <iostream>

using namespace std;

template <class P>
struct CUM
{
    P operator()(P a)
    {
        return a % 3 == 0;
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

template <class T>
class LE
{
public:
    nodo<T>* head = NULL;
    bool find(T valor, nodo<T>*& pos);
    void add(T valor);
    void split(nodo<T>*& h1, nodo<T>*& h2, CUM<T> cumple);
    void print();
    ~LE();
};

template <class T>
bool LE<T>::find(T valor, nodo<T>*& pos)
{
    pos = NULL;
    nodo<T>* p = head;
    for (; p && p->valor; pos = p, p = p->next);
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
void LE<T>::split(nodo<T>*& h1, nodo<T>*& h2, CUM<T> cumple)
{
    nodo<T>* p = h1;
    nodo<T>* q = h1;
    nodo<T>* r = h1;

    if (!cumple(p->valor))
    {
        h2 = p;
        while (!cumple(p->valor))
        {
            r = p;
            p = p->next;
            if (p->next == NULL)
            {
                h2 = h1;
                h1 = NULL;
                return;
            }
        }
        h1 = p;
        q = p;
        p = p->next;
    }
    else
    {
        while (cumple(p->valor))
        {
            q = p;
            p = p->next;
            if (p->next == NULL)
                return;
        }
        h2 = p;
        r = p;
        p = p->next;
    }

    for (; p; p = p->next)
    {
        if (cumple(p->valor))
        {
            if (q != p)
            {
                q->next = p;
                q = p;
            }
        }
        else
        {
            r->next = p;
            r = p;
        }
    }
    r->next = NULL;
    q->next = NULL;
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
    CUM<int> c;

    H1.add(3);
    H1.add(6);
    H1.add(5);
    H1.add(4);
    H1.add(3);

    cout << "Lista\n";
    H1.print();
    cout << endl;

    H1.split(H1.head, H2.head, c);

    cout << "H1\n";
    H1.print();
    cout << endl;

    cout << "H2\n";
    H2.print();
}
