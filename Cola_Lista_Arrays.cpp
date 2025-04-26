// Hacer clase cola como lista enlazada de arrays (nodo contiene array)

#include <iostream>

using namespace std;

template <class T>
struct Nodo
{
	T ar[5];
	Nodo<T>* next;
    	T* head = nullptr;
    	T* tail = nullptr;

	Nodo(Nodo<T>* n = nullptr)
	{
		next = n;
	}
};

template <class T>
class Cola
{
    Nodo<T>* list = nullptr;

    public:
        void fin(Nodo<T>*& pos);
        void push(T valor);
        bool pop(T& valor);
        void print();

        ~Cola()
        {
            Nodo<T>* tmp;
            while(list)
            {
                tmp = list;
                list = list->next;
                delete tmp;
            }
        }
};

template <class T>
void Cola<T>::fin(Nodo<T>*& pos)
{
    pos = nullptr;
    Nodo<T>* p = list;
    for(; p; pos = p, p = p->next);
}

template <class T>
void Cola<T>::push(T valor)
{
    if(!list)
    {
        list = new Nodo<T>(list);
        list->head = list->tail = list->ar;
	*(list->tail) = valor;
    }
    else
    {
        Nodo<T>* pos;
        fin(pos);

        if(pos->tail == pos->ar + 4)
        {
            pos->next = new Nodo<T>(pos->next);
            pos = pos->next;
            pos->head = pos->tail = pos->ar;
            *(pos->tail) = valor;
        }
        else
        {
            pos->tail++;
            *(pos->tail) = valor;
        }
    }
}

template <class T>
bool Cola<T>::pop(T& valor)
{
    bool saque = false;
    
    if(list->head < list->ar + 5)
    {
        valor = *(list->head);
        saque = true;
        list->head++;
    }
    else
    {
        Nodo<T>* tmp = list;
        list = list->next;
        delete tmp;

	if(list == nullptr)
            return false;
        else
        {
            valor = *(list->head);
            saque = true;
            list->head++;
        }
    }
    return saque;
}

template <class T>
void Cola<T>::print()
{
    cout << "head->";
    for(Nodo<T>* p = list; p; p = p->next)
    {
        for(T* q = p->head; q <= p->tail; q++)
            cout << *q << "->";
    }
    cout << "tail" << endl;
    cout << "----------------------------------------------------" << endl;
}

int main()
{
    Cola<int> cl;
    int x = 0;

    cout << "PUSH" << endl;
    cl.push(1);
    cl.push(2);
    cl.push(3);
    cl.push(4);
    cl.push(5);
    cl.push(6);
    cl.push(7);
    cl.push(8);
    cl.print();

    cout << "POP" << endl;
    cl.pop(x);
    cout << x << endl;
    cl.print();

    cout << "POP" << endl;
    cl.pop(x);
    cout << x << endl;
    cl.print();

    cout << "PUSH" << endl;
    cl.push(9);
    cl.print();

    return 0;
}
