// Busqueda en un arbol binario balanceado

#include <iostream>

using namespace std;

struct Node
{
    int v;
    Node* node[2];
    Node (int x)
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
    Node** rep(Node** q);
    bool rem(int x);
    void InOrder(Node* n);
    void print();
    //~BinTree();
};

bool BinTree::find(int x, Node**& p)
{
    p = &root;
    while (*p && (*p)->v != x)
    {
        p = &((*p)->node[(*p)->v < x]);
    }
    return *p;
}

bool BinTree::ins(int x)
{
    Node** p;
    if (find(x, p)) return 0;
    *p = new Node(x);
    return 1;
}

Node** BinTree::rep(Node** q)
{
    m_b = !m_b;
    q = &((*q)->node[!m_b]);
    while ((*q)->node[m_b])
        q = &((*q)->node[m_b]);
    return q;
}

bool BinTree::rem(int x)
{
    Node** p;
    if (!find(x, p)) return 0;
    // CASO 2
    if ((*p)->node[0] && (*p)->node[1])
    {
        Node** q = rep(p);
        (*p)->v = (*q)->v;
        p = q;
    }
    Node* t = *p;
    // CASO 0 y 1
    *p = (*p)->node[(*p)->node[1] != 0];
    delete t;
    return 1;
}

void BinTree::InOrder(Node* n)
{
    if (!n) return;
    InOrder(n->node[0]);
    cout << n->v << " ";
    InOrder(n->node[1]);
}

void BinTree::print()
{
    InOrder(root);
    cout << endl;
}

int main()
{
    BinTree t;

    t.ins(50); t.ins(30); t.ins(60);
    t.ins(80); t.ins(55); t.ins(11);
    t.ins(35); t.ins(5);  t.ins(14);
    t.ins(32); t.ins(48);
    
    t.print();
}