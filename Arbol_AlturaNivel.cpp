// Recorrido en un arbol binario balanceado para saber la cantidad de niveles-altura que tiene

#include <iostream>

using namespace std;

struct Node
{
    int v;
    Node* node[2];
    Node(int x)
    {
        v = x;
        node[0] = node[1] = 0;
    }
};

struct BinTree
{
    Node* root = NULL;
    bool m_b = 0;
    bool find(int x, Node**& p);
    bool ins(int x);
    bool rem(int x);
    Node** rep(Node** q);
    void InOrder(Node* n);
    void print();
    void CantNiveles(Node* n, int l, int& L);
    void printCantNiveles();
    int Altura(Node* n);
    void printAltura(); 
    //~BinTree();
};

bool BinTree::find(int x, Node**& p)
{
    p = &root;
    while(*p && (*p)->v != x)
        p = &((*p)->node[x > (*p)->v]);
    
    return *p != nullptr;
}

bool BinTree::ins(int x)
{
    Node** p;
    if(find(x, p)) return 0;
    *p = new Node(x);
    return 1;
}

bool BinTree::rem(int x)
{
    Node** p;
    if(!find(x, p)) return 0;
    if((*p)->node[0] && (*p)->node[1])
    {
        Node** q = rep(p);
        (*p)->v = (*q)->v;
        p = q;
    }
    Node* t = *p;
    *p = (*p)->node[(*p)->node[1] != 0];
    delete t;
    return 1;
}

Node** BinTree::rep(Node** q)
{
    q = &((*q)->node[m_b]);
    while((*q)->node[!m_b])
        q = &((*q)->node[!m_b]);
    m_b = !m_b;
    return q;
}

void BinTree::InOrder(Node* n)
{
    if(!n) return;
    InOrder(n->node[0]);
    cout << n->v << " ";
    InOrder(n->node[1]);
}

void BinTree::print()
{
    InOrder(root);
    cout << endl;
}

void BinTree::CantNiveles(Node* n, int l, int& L)
{
    if(!n) 
    {
        if(l > L)
            L = l;
        return;
    }
    CantNiveles(n->node[0], l+1, L);
    CantNiveles(n->node[1], l+1, L);
}

void BinTree::printCantNiveles()
{
    int L = 0;
    CantNiveles(root, 0, L);
    cout << "Niveles del arbol: " << L << endl;
}

int BinTree::Altura(Node* n)
{
    if(!n) return 0;
    int izq = Altura(n->node[0]);
    int der = Altura(n->node[1]);
    return ((izq > der) ? izq : der) + 1;
}

void BinTree::printAltura()
{
    cout << "Altura del arbol: " << Altura(root) << endl;
}

int main()
{
    BinTree t;

    t.ins(52); t.ins(30); t.ins(72);
    t.ins(11); t.ins(41); t.ins(60);
    t.ins(80); t.ins(62);
    t.print();

    t.printAltura();
    t.printCantNiveles();

    return 0;
}
