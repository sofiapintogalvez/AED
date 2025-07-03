// Hash Table desde cero usando std::list y un adaptor para agregar o eliminar (funcion de dispersion)

#include <iostream>
#include <list>

using namespace std;

template <class T>
struct Fx
{
    T operator()(T x)
    {
        return x;
    }
};

template <class T>
struct xlist
{
    list<T> l;

    void add(T x)
    {
        l.push_back(x);
    }

    void del(T x)
    {
        l.remove(x);
    }

    void print()
    {
        for(T v : l)
            cout << v << " ";
        cout << endl;
    }
};

template <class T, class S, class F, int tam>
class HashTable
{
    S* ht;
    F fd;

    public:
        HashTable()
        {
            ht = new S[tam];        // array de listas enlazadas
        }

        void ins(T x);
        void rem(T x);
        void print();
};

template <class T, class S, class F, int tam>
void HashTable<T, S, F, tam>::ins(T x)
{
    int i = fd(x) % tam;
    ht[i].add(x);
}

template <class T, class S, class F, int tam>
void HashTable<T, S, F, tam>::rem(T x)
{
    int i = fd(x) % tam;
    ht[i].del(x);
}

template <class T, class S, class F, int tam>
void HashTable<T, S, F, tam>::print()
{
    for(int i = 0; i < tam; i++)
    {
        cout << i << " -> ";
        ht[i].print();
    }
    cout << endl;
}

int main()
{
    HashTable<int, xlist<int>, Fx<int>, 7> HT;

    HT.ins(7);
    HT.ins(8);
    HT.ins(2);
    HT.ins(3);
    HT.ins(4);
    HT.ins(5);
    HT.ins(6);
    HT.ins(1);

    HT.print();

    HT.rem(8);
    HT.print();

    return 0;
}
