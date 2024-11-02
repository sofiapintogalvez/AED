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
    Node* aux = NULL;
    bool m_b = 0;
    bool find(int x, Node**& p);
    bool ins(int x);
    Node** rep(Node** q);
    bool rem(int x);
    void InOrder(Node* n);
    void print();
    void toLEC(Node* n);
    void circular();
    void printcirculo();
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

void BinTree::toLEC(Node* n)
{
    if (!n) return;
    toLEC(n->node[0]);
    if (aux)
    {
        aux->node[1] = n;
        n->node[0] = aux;
    }
    aux = n;
    toLEC(n->node[1]);
}

void BinTree::circular()
{
    toLEC(root);
    Node* menor = root;
    Node* mayor = root;
    while (menor->node[0]) 
        menor = menor->node[0];
        
    while (mayor->node[1]) 
        mayor = mayor->node[1];
    
    menor->node[0] = mayor;  
    mayor->node[1] = menor;
}

void BinTree::printcirculo()
{
    Node* tmp = root;
    int i = 0;
    while (i < 10)
    {
        cout << tmp->v << "->";
        if (tmp == root)
        {
            i++;
        }
        tmp = tmp->node[1];
    }
}

int main()
{
    BinTree t;

    t.ins(8);
    t.ins(22);
    t.ins(26);
    t.ins(32);
    t.ins(52);
    t.ins(43);
    t.ins(61);
    t.print();

    t.circular();
    t.printcirculo();
}