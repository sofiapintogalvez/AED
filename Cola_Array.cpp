// Clase con array haciendo push y pop

#include <iostream>

using namespace std;

template <class T>
class Cola
{
    T elem[10];
    T* head = nullptr;
    T* tail = nullptr;

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
        head = tail = elem;
        *tail = valor;
        tail++;
    }
    else
    {
        if(tail == elem + 10)
        {
            tail = elem;
            *tail = valor;
            tail++;
        }
        else
        {
            *tail = valor;
            tail++;
        }
    }
}

template <class T>
bool Cola<T>::pop(T& valor)
{
    bool saque = false;
    if(head < elem + 10)
    {
        valor = *head;
        saque = true;
        head++;
    }
    else
    {
        head = elem;
        valor = *head;
        saque = true;
        head++;
    }

    if(head == tail)
        head = tail = nullptr;
    
    return saque;
}

template <class T>
void Cola<T>::print()
{
    if(!head)
        cout << "head->tail";
    else
    {
        if(tail > head)
        {
            cout << "head->";
            for(T* p = head; p < tail; p++)
                cout << *p << "->";
            cout << "tail" << endl;
        }
        else
        {
            cout << "head->";
            for(T* p = head; p < elem + 10; p++)
                cout << *p << "->";

            for(T* q = elem; q < tail; q++)
                cout << *q << "->";
            cout << "tail" << endl;
        }
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
    cout << x << endl;
    cl.print();

    cout << "POP" << endl;
    cl.pop(x);
    cout << x << endl;
    cl.print();
    
    cout << "PUSH" << endl;
    cl.push(11);
    cl.push(20);
    cl.print();

    return 0;
}
