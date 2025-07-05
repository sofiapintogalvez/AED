// Matriz esparta de vectores de punteros a listas enlazadas que no almacena ceros

#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int valor;
    int x, y;
    Node* down;
    Node* right;
    Node(int v, int x_, int y_)
    {
        valor = v;
        x = x_;
        y = y_;
        down = nullptr;
        right = nullptr;
    }
};

/*struct objK
{
    SMatrix* pm;
    int x, y;

    public:
        objK(int x_, int y_, SMatrix* t)
        {
            x = x_;
            y = y_;
            pm = t;
        }

        int operator =(int v)
        {
            pm->set(x, y, v);
            return v;
        }

        operator int()
        {
            return pm->get(x, y);
        }
};*/

class SMatrix
{
    vector<Node*> X;
    vector<Node*> Y;

    public:
        SMatrix(int x, int y);
        bool findx(int x, int y, Node**& p);
        bool findy(int x, int y, Node**& q);
        void set(int x, int y, int v);
        int get(int x, int y);
        void print();
        //objK operator()(int x, int y);
};

SMatrix::SMatrix(int x, int y)
{
    X.resize(x, nullptr);
    Y.resize(y, nullptr);
}

bool SMatrix::findx(int x, int y, Node**& p)
{
    p = &X[x];
    while(*p && (*p)->y < y)
        p = &((*p)->down);
    
    return *p && (*p)->y == y;
}

bool SMatrix::findy(int x, int y, Node**& q)
{
    q = &Y[y];
    while(*q && (*q)->x < x)
        q = &((*q)->right);

    return *q && (*q)->x == x;
}

void SMatrix::set(int x, int y, int v)
{
    Node** p;
    Node** q;

    bool fx = findx(x, y, p);
    bool fy = findy(x, y, q);

    if(fx)      // si ya existe un nodo en esa coordenada
    {
        if(v == 0)      // eliminar nodo
        {
            Node* tmp = *p;
            *p = tmp->down;
            *q = tmp->right;
            delete tmp;
        }
        else    // cambiar valor de ese nodo al nuevo
            (*p)->valor = v;
        
        return;
    }

    if(v == 0)
        return;     // no se insertan 0

    Node* nuevo = new Node(v, x, y);

    nuevo->down = *p;
    *p = nuevo;

    nuevo->right = *q;
    *q = nuevo;
}

int SMatrix::get(int x, int y)
{
    Node* n = Y[y];     // se puede con acceso a X (recorriendo con down) ó con Y (recorriendo con right)

    while(n)
    {
        if(n->x == x)
            return n->valor;
        n = n->right;
    }
    return 0;
}

void SMatrix::print()
{
    for(int y = 0; y < Y.size(); y++)
    {
        for(int x = 0; x < X.size(); x++)
        {
            if(Y[y] && X[x])
                cout << get(x, y) << " ";
            
            else
                cout << "0 ";
        }
        cout << endl;
    }
}

/*objK SMatrix::operator()(int x, int y)
{
    return objK(x, y, this);
}*/

int main()
{
    SMatrix m(4, 4);

    m.set(0, 1, 7);
    m.set(2, 1, 3);
    m.set(1, 2, 1);
    m.set(2, 3, 8);

    cout << "Coordenada 0,1: " << m.get(0, 1) << endl;
    cout << "Coordenada 2,1: " << m.get(2, 1) << endl;
    cout << "Coordenada 1,2: " << m.get(1, 2) << endl;
    cout << "Coordenada 2,3: " << m.get(2, 3) << endl;
    m.print();

    m.set(0, 1, 4);
    cout << "\nCoordenada 0,1: " << m.get(0, 1) << endl;
    m.print();

    m.set(0, 1, 0);
    cout << "\nCoordenada 0,1: " << m.get(0, 1) << endl;
    m.print();

    return 0;
}
