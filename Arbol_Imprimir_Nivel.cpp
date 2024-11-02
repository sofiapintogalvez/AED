// Imprimir los valores de un arbol con el nivel al que pertenecen

#include <iostream>

using namespace std;

struct CBinNode
{
    CBinNode(int _v)
    { value = _v; nodes[0] = nodes[1] = 0; nivel = 0; }
    int value;
    CBinNode* nodes[2];
    int nivel;
};

class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    bool Insert(int x);
    bool Remove(int x);
    void Print();
    void asignar(CBinNode* n, int x);
    void print_con_nivel(CBinNode* n);
    CBinNode* dar();

private:
    bool Find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void InOrder(CBinNode* n);
    CBinNode* m_root;
    bool m_b;
};

CBinTree::CBinTree()
{   m_root = 0;
    m_b = 0;
}

CBinTree::~CBinTree()
{
    // ?
}

bool CBinTree::Find(int x, CBinNode**& p)
{
    for ( p = &m_root ;
         *p && (*p)->value != x ;
         p = &( (*p)->nodes[ (*p)->value < x ] ) );
    return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x)
{
    CBinNode** p;
    if ( Find(x,p) ) return 0;
    *p = new CBinNode(x);
    return 0;
}
bool CBinTree::Remove(int x)
{
    CBinNode** p;
    if ( !Find(x,p) ) return 0;
    if ( (*p)->nodes[0] && (*p)->nodes[1] )
    {
        CBinNode** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    CBinNode* t = *p;
    *p = (*p)->nodes[ (*p)->nodes[0] == 0 ];
    delete t;
    return 1;
}

CBinNode** CBinTree::Rep(CBinNode** q)
{
    m_b = !m_b;
    q = &((*q)->nodes[!m_b]);
    while( (*q)->nodes[m_b] )
        q = &((*q)->nodes[m_b]);
    return q;
}

void CBinTree::InOrder(CBinNode* n)
{
    if ( !n ) return;
    InOrder(n->nodes[0]);
    cout<<n->value<<" ";
    InOrder(n->nodes[1]);
}

void CBinTree::Print()
{
    InOrder(m_root);
    cout<<endl;
}

CBinNode* CBinTree::dar()
{
    return m_root;
}

void CBinTree::asignar(CBinNode* n, int x)
{
    if(!n) return;
    n->nivel = x;
    x++;
    asignar(n->nodes[0], x);
    asignar(n->nodes[1], x);
}

void CBinTree::print_con_nivel(CBinNode* n)
{
    if (!n) return;
    print_con_nivel(n->nodes[0]);
    cout<<n->value<<" "<<n->nivel<<endl;
    print_con_nivel(n->nodes[1]);
}

int main()
{
    CBinTree t;
    t.Insert(50);
    t.Insert(25);
    t.Insert(75);
    t.Insert(10);
    t.Insert(30);
    t.Insert(60);
    t.Insert(80);
    
    t.Print();
    t.asignar(t.dar(), 0);
    t.print_con_nivel(t.dar());
}
