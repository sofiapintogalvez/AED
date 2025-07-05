// Max y min heap de un arbol usando vector

#include <iostream>
#include <vector>

using namespace std;

template <class T>
struct Greater
{
    bool operator()(T a, T b)
    {
        return a > b;
    }
};

template <class T>
struct Less
{
    bool operator()(T a, T b)
    {
        return a < b;
    }
};

template <class T, class P>
class Heap
{
    vector<T> v;
    P op;
    int nelem = 0;

    public:
        void push(T valor);
        void pop();
        T MaxMin();
        void print();
};

template <class T, class P>
void Heap<T, P>::push(T valor)
{
    v.push_back(valor);
    nelem++;
    int i = v.size() - 1;
    int padre = (i-1) / 2;

    while(padre >= 0 && op(v[i], v[padre]))
    {
        swap(v[padre], v[i]);
        i = padre;
        padre = (i-1) / 2;
    }
}

template <class T, class P>
void Heap<T, P>::pop()
{
    swap(v[0], v[nelem-1]);
    nelem--;
    v.pop_back();
    int j = 0;
    int h1 = (2*j) + 1;
    int h2 = (2*j) + 2;
    int m;

    while((h1 <= nelem || h2 <= nelem) && (op(v[h1], v[j]) || op(v[h2], v[j])))
    {
        if(op(v[h1], v[h2]))
            m = h1;
        else
            m = h2;

        swap(v[j], v[m]);
        j = m;
        h1 = (2*j) + 1;
        h2 = (2*j) + 2;
    }
}

template <class T, class P>
T Heap<T, P>::MaxMin()
{
    return v.front();
}

template <class T, class P>
void Heap<T, P>::print()
{
    for(int i = 0; i < nelem; i++)
        cout << v[i] << " ";
    cout << endl;
}

int main()
{
    Heap<int, Greater<int>> MaxHeap;
    //Heap<int, Less<int>> MinHeap;
    
    MaxHeap.push(42);
    MaxHeap.push(25);
    MaxHeap.push(38);
    MaxHeap.push(23);
    MaxHeap.push(22);
    MaxHeap.push(11);
    MaxHeap.push(32);
    MaxHeap.push(15);
    MaxHeap.push(21);
    MaxHeap.push(26);
    MaxHeap.print();

    cout << "Numero mayor: " << MaxHeap.MaxMin() << endl;

    MaxHeap.pop();
    MaxHeap.print();

    return 0;
}
