// Implementar de cero la clase vector

#include <iostream>

using namespace std;

template <class T>
class CVector
{
    T* ar = nullptr;
    T* ptr;
    int tam;

    public:
        CVector(int n)
        {
            ar = new T[n];
            ptr = ar;
            tam = n;
        }

        ~CVector()
        {
            delete ar;
            ar = nullptr;
        }

        bool lleno();
        void push_back(T valor);
        void push_front(T valor);
        void pop_back();
        void pop_front();
        T& operator[](int indice);
        void print();
};

template <class T>
bool CVector<T>::lleno()
{
    return ptr == ar + tam;
}

template <class T>
void CVector<T>::push_back(T valor)
{
    if(lleno())
    {
        int x = 2*tam;
        T* ar2 = new T[x];
        
        T* j = ar2;
        for(T* i = ar; i < ar + tam; i++, j++)
            *j = *i;

        delete ar;
        ar = ar2;
        tam = x;
        ptr = j;
        *ptr = valor;
        ptr++;
    }
    else
    {
        *ptr = valor;
        ptr++;
    }
}

template <class T>
void CVector<T>::push_front(T valor)
{
    if(lleno())
    {
        int x = 2*tam;
        T* ar2 = new T[x];

        T* j = ar2 + 1;
        for(T* i = ar; i < ar + tam; i++, j++)
            *j = *i;

        delete ar;
        ar = ar2;
        tam = x;
        ptr = j;
        *ar = valor;
    }
    else
    {
        for(T* i = ptr - 1; i >= ar; i--)
            *(i+1) = *i;
        
        *ar = valor;
        ptr++;
    }
}

template <class T>
void CVector<T>::pop_back()
{
    if(ptr > ar)
        ptr--;
    else
        ptr = ar;
}

template <class T>
void CVector<T>::pop_front()
{
    if(ptr > ar)
    {
        for(T* i = ar + 1; i < ptr; i++)
            *(i-1) = *i;
        ptr--;
    }
    else
        ptr = ar;
}

template <class T>
T& CVector<T>::operator[](int indice)
{
    return ar[indice];  // return *(ar + indice);
}

template <class T>
void CVector<T>::print()
{
    cout << "v: ";
    for(T* p = ar; p < ptr; p++)
        cout << *p << " ";
    cout << endl;
}

int main()
{
    CVector<int> v(4);

    cout << "PUSH BACK" << endl;
    v.push_back(7);
    v.push_back(6);
    v.push_back(5);
    v.push_back(4);
    v.push_back(3);
    v.print();

    cout << "PUSH FRONT" << endl;
    v.push_front(8);
    v.push_front(9);
    v.print();

    cout << "POP BACK" << endl;
    v.pop_back();
    v.print();

    cout << "POP FRONT" << endl;
    v.pop_front();
    v.print();

    cout << "OPERATOR" << endl;
    v[1] = 0;
    v.print();

    return 0;
}
