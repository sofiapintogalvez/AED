// Implementar de cero la clase list (tiene next y prev)

#include <iostream>

using namespace std;

template <class T>
struct Nodo
{
	T valor;
	Nodo<T>* next;
    Nodo<T>* prev;

	Nodo(T v, Nodo<T>* n = nullptr, Nodo<T>* p = nullptr)
	{
		valor = v;
		next = n;
        prev = p;
	}
};

template <class T>
class CList
{
    Nodo<T>* head = nullptr;
    Nodo<T>* tail = nullptr;

	public:
		void push_back(T dato);
		void push_front(T dato);
		void pop_back();
        void pop_front();
        T& operator[](int indice);
		void print();

        ~CList()
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
void CList<T>::push_back(T data)
{
	if(!head)
    {
        head = new Nodo<T>(data);
        tail = head;
    }
	else
	{
        tail->next = new Nodo<T>(data, tail->next, tail);
        tail = tail->next;
	}
}

template <class T>
void CList<T>::push_front(T data)
{
	if(!head)
    {
        head = new Nodo<T>(data);
        tail = head;
    }
	else
	{
		Nodo<T>* tmp = new Nodo<T>(data, head);
        head->prev = tmp;
		head = tmp;
	}
}

template <class T>
void CList<T>::pop_back()
{
    if(!head)
        return;
    else
    {
        Nodo<T>* tmp = tail;
        tail = tail->prev;
        delete tmp;
        tail->next = nullptr;
    }
}

template <class T>
void CList<T>::pop_front()
{
    if(!head)
        return;
    else
    {
        Nodo<T>* tmp = head;
        head = head->next;
        delete tmp;
        head->prev = nullptr;
    }
}

template <class T>
T& CList<T>::operator[](int indice)
{
    Nodo<T>* p = head;
    for(int i = 0; i < indice; i++)
        p = p->next;

    return p->valor;
}

template <class T>
void CList<T>::print()
{
	cout << "head->";
	for(Nodo<T>* p = head; p; p = p->next)
		cout << p->valor << "->";
	cout << "null" << endl;
}

int main()
{
	CList<int> l;

    cout << "PUSH BACK" << endl;
	l.push_back(5);
	l.push_back(4);
	l.push_back(3);
	l.push_back(2);
	l.print();

    cout << "PUSH FRONT" << endl;
	l.push_front(6);
	l.print();

    cout << "POP BACK" << endl;
    l.pop_back();
	l.print();

    cout << "POP FRONT" << endl;
    l.pop_front();
	l.print();

    cout << "OPERATOR" << endl;
    l[1] = 0;
    l.print();

    return 0;
}
