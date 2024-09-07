#include <iostream>

using namespace std;

template<class T>
class nodo
{
public:
    T valor;
    nodo<T>* next;
    nodo(T v, nodo<T>* n = nullptr)
    {
        valor = v;
        next = n;
    }
};

template<class T>
class LE
{
    nodo<T>* head = nullptr;

public:
    void print();
    bool find(T v, nodo<T>*& pos);
    void add(T v);
    void del(T v);
    ~LE();
};

template<class T>
void LE<T>::print()
{
    cout << "Head->";
    for (nodo<T>* p = head; p; p = p->next)
        cout << p->valor << "->";
    cout << "NULL" << endl;
}

template<class T>
bool LE<T>::find(T v, nodo<T>*& pos)
{
    bool encontrado = false;
    pos = nullptr;
    for (nodo<T>* p = head; p && v >= p->valor; p = p->next)
    {
        if (v == p->valor)
        {
            encontrado = true;
            break;
        }
        pos = p;
    }
    return encontrado;
}

template<class T>
void LE<T>::add(T v)
{
    nodo<T>* pos_ant;
    if (!find(v, pos_ant))
    {
        if (pos_ant)
            pos_ant->next = new nodo<T>(v, pos_ant->next);
        else
            head = new nodo<T>(v, head);
    }

}

template<class T>
void LE<T>::del(T v)
{
    nodo<T>* pos_ant, * pos_del;
    if (find(v, pos_ant))
    {
        if (pos_ant)
        {
            pos_del = pos_ant->next;
            pos_ant->next = pos_del->next;
            delete pos_del;
        }
        else
        {
            pos_del = head;
            head = pos_del->next;
            delete pos_del;
        }
    }
}

template<class T>
LE<T>::~LE()
{
    while (head)
    {
        cout << "Adios mundo cruel, soy " << head->valor << " \n";
        del(head->valor);
    }
}

int main()
{
    LE<int> lista;

    lista.print();
    lista.add(3); //lista vacia
    lista.print();
    lista.add(5); // final
    lista.print();
    lista.add(1); //inicio
    lista.print();
    lista.add(4); //medio
    lista.print();

    cout << "\nBorrando numero 3\n";
    lista.del(3);
    lista.print();

    cout << "\nDestructor\n";
}