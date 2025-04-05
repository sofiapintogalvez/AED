// Clase con array haciendo push y pop

#include <iostream>

using namespace std;

template <class T>
class Cola
{
    T* top = nullptr;
    T elem[10];
    T* head = nullptr;
    T* tail = nullptr;
    T* fin = nullptr;

    public:
        void push(T valor);
        bool pop(T& valor);
        void print();
};

template <class T>
void Cola<T>::push(T valor)
{
    if(!head)
    {
        elem[0] = valor;
        head = tail = top = elem;
        fin = elem + 1;
    }
    else
    {
        if(tail == elem + 9)
        {
            *top = valor;
            tail = top;
            top++;
        }
        else
        {
            tail++;
            *tail = valor;
            fin++;
        }
    }
}

template <class T>
bool Cola<T>::pop(T& valor)
{
    bool saque = false;
    valor = *head;
    if (head)
    {
        cout << valor << endl;
        saque = true;
        head++;
    }
    return saque;
}

template <class T>
void Cola<T>::print()
{
    if(!head)
    {
        cout << "head->tail";
    }
    else
    {
        cout << "head->";
        for(T* p = head; p < fin; p++)
            cout << *p << "->";
    
        if(tail != elem + 9)
        {
            for(T* q = tail; q < top; q++)
                cout << *q << "->";
        }
        cout << "tail" << endl;
    }
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
    cl.push(9);
    cl.push(10);
    cl.print();

    cout << "POP" << endl;
    cl.pop(x);
    cl.print();
    cl.pop(x);
    cl.print();
    
    cout << "PUSH" << endl;
    cl.push(11);
    cl.print();
}
