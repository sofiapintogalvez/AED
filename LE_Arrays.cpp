#include <iostream>

using namespace std;

template <class T>
struct Nodo
{
    T arr[5];
    T* top;
    Nodo* next;

    Nodo()
    {
        top = arr;
        next = nullptr;
    }

    bool lleno()
    {
        return top >= arr + 5;
    }

    void insertarEnOrden(T valor)
    {
        T* ptr = top - 1;

        while (ptr >= arr && *ptr > valor)
        {
            *(ptr + 1) = *ptr;
            ptr--;
        }
        *(ptr + 1) = valor;
        top++;
    }

    void eliminarEnOrden(T valor)
    {
        T* ptr = top + 1;

        while (ptr < arr + 5)
        {
            *(ptr - 1) = *ptr;
            top++;
            ptr++;
        }
    }

    T eliminarUltimo()
    {
        top--;
        return *top;
    }

    void imprimir()
    {
        for (T* ptr = arr; ptr < top; ++ptr)
        {
            cout << *ptr << " ";
        }
    }
};

template <class T>
class ListaDeArrays
{
private:
    Nodo<T>* head;

public:
    ListaDeArrays() : head(new Nodo<T>()) {}

    void insertar(T valor)
    {
        Nodo<T>* p = head;
        while (p)
        {
            if (!p->lleno())
            {
                p->insertarEnOrden(valor);
                return;
            }

            // Si el nodo está lleno, verificar si el valor debe estar en este nodo
            if (valor < *(p->top - 1))
            {
                T ultimo = p->eliminarUltimo();
                p->insertarEnOrden(valor);
                valor = ultimo;
            }

            if (!p->next)
            {
                p->next = new Nodo<T>();
            }
            p = p->next;
        }
    }

    void eliminar(T valor)
    {
        Nodo<T>* p = head;
        p->eliminarEnOrden(valor);
    }

    void imprimir()
    {
        Nodo<T>* p = head;
        cout << "head->";
        while (p)
        {
            cout << "[ ";
            p->imprimir();
            cout << "]->";
            p = p->next;
        }
        cout << "NULL\n";
    }
};

int main()
{
    ListaDeArrays<int> lista;

    lista.imprimir();

    lista.insertar(1);
    lista.insertar(2);
    lista.insertar(3);
    lista.insertar(4);
    lista.insertar(5);
    lista.imprimir();

    lista.insertar(6);
    lista.insertar(7);
    lista.insertar(8);
    lista.insertar(9);
    lista.imprimir();

    lista.eliminar(2);
    lista.imprimir();
}