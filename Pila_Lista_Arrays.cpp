// Hacer clase pila como lista enlazada de arrays (nodo contiene array)

#include <iostream>

using namespace std;

template <class T>
struct Nodo
{
	T ar[5];
	Nodo<T>* next;
	T* top = nullptr;

	Nodo(Nodo<T>* n = nullptr)
	{
		next = n;
	}
};

template <class T>
class Pila
{
    Nodo<T>* head = nullptr;

    public:
        void push(T valor);
        bool pop(T& valor);
        void print();

	~Pila()
        {
            Nodo<T>* tmp;
            while(head)
            {
                tmp = head;
                head = head->next;
                delete tmp;
            }
        }
};

template <class T>
void Pila<T>::push(T valor)
{
    if(!head)
    {
        head = new Nodo<T>(head);
        head->top = head->ar;
	*(head->top) = valor;
    }
    else
    {
        if(head->top == head->ar + 4)
        {
            Nodo<T>* tmp = new Nodo<T>(head);
            head = tmp;
            head->top = head->ar;
            *(head->top) = valor;
        }
        else
        {
            head->top++;
            *(head->top) = valor;
        }
    }
}

template <class T>
bool Pila<T>::pop(T& valor)
{
    bool saque = false;
    
    if(head->top >= head->ar)
    {
        valor = *(head->top);
        saque = true;
        head->top--;
    }
    else
    {
	Nodo<T>* tmp = head;
        head = head->next;
        delete tmp;
	    
        if (head == nullptr)
            return false;
        else
        {
            valor = *(head->top);
            saque = true;
            head->top--;
        }
    }
    return saque;
}

template <class T>
void Pila<T>::print()
{
    cout << "top" << endl;
    for(Nodo<T>* p = head; p; p = p->next)
    {
        for(T* q = p->top; q >= p->ar; q--)
            cout << *q << endl;
    }
    cout << "-------------------------------------------" << endl;
}

int main()
{
    Pila<int> pl;
    int x = 0;

    cout << "VACIO" << endl;
    pl.print();

    cout << "PUSH" << endl;
    pl.push(7);
    pl.push(3);
    pl.push(5);
    pl.push(1);
    pl.push(2);
    pl.push(4);
    pl.print();

    cout << "POP" << endl;
    pl.pop(x);
    cout << x << endl;
    pl.print();

    cout << "POP" << endl;
    pl.pop(x);
    cout << x << endl;
    pl.print();

    return 0;
}
