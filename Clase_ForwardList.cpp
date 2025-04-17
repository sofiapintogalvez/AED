// Implementar de cero la clase forwardlist (solo tiene next)

#include <iostream>

using namespace std;

template <class T>
struct Nodo
{
	T valor;
	Nodo<T>* next;

	Nodo(T v, Nodo<T>* n = nullptr)
	{
		valor = v;
		next = n;
	}
};

template <class T>
class CForwardList
{
    Nodo<T>* head = nullptr;

	public:
		void fin(Nodo<T>*& pos);
		void push_back(T dato);
		void push_front(T dato);
		void pop_back();
		void pop_front();
        T& operator[](int indice);
		void print();

        ~CForwardList()
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
void CForwardList<T>::fin(Nodo<T>*& pos)
{
    pos = nullptr;
    Nodo<T>* p = head;
    for(; p; pos = p, p = p->next);
}

template <class T>
void CForwardList<T>::push_back(T data)
{
	if(!head)
        head = new Nodo<T>(data, head);
	else
	{
        Nodo<T>* pos;
        fin(pos);
        pos->next = new Nodo<T>(data, pos->next);
	}
}

template <class T>
void CForwardList<T>::push_front(T data)
{
	Nodo<T>* tmp = new Nodo<T>(data, head);
	head = tmp;
}

template <class T>
void CForwardList<T>::pop_back()
{
    if(!head)
        return;
    
    else if(!head->next)
    {
        delete head;
        head = nullptr;
    }
    else
    {
        Nodo<T>* tmp = head;
        while(tmp->next->next)  
            tmp = tmp->next;
    
        delete tmp->next;
        tmp->next = nullptr;
    }
}

template <class T>
void CForwardList<T>::pop_front()
{
    if(!head)
        return;
    else
    {
        Nodo<T>* tmp = head;
        head = head->next;
        delete tmp;
    }
}

template <class T>
T& CForwardList<T>::operator[](int indice)
{
    Nodo<T>* p = head;
    for(int i = 0; i < indice; i++)
        p = p->next;

    return p->valor;
}

template <class T>
void CForwardList<T>::print()
{
	cout << "head->";
	for(Nodo<T>* p = head; p; p = p->next)
		cout << p->valor << "->";
	cout << "null" << endl;
}

int main()
{
	CForwardList<int> fl;

	cout << "PUSH BACK" << endl;
	fl.push_back(5);
	fl.push_back(4);
	fl.push_back(3);
	fl.push_back(2);
	fl.print();

    cout << "PUSH FRONT" << endl;
	fl.push_front(6);
	fl.print();

    cout << "POP BACK" << endl;
    fl.pop_back();
	fl.print();

    cout << "POP FRONT" << endl;
    fl.pop_front();
	fl.print();

    cout << "OPERATOR" << endl;
    fl[1] = 0;
    fl.print();

    return 0;
}
