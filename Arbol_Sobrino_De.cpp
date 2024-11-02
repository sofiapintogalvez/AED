#include <iostream>

using namespace std;

struct CBinNode
{
    CBinNode(int _v)
    { value = _v; nodes[0] = nodes[1] = 0; }
    int value;
    CBinNode* nodes[2];
};

class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    bool Insert(int x);
    bool Remove(int x);
    void Print();
    void sobrinos_de(int x);
    void sobrinos_2(int nivel, int niveloriginal, CBinNode* tmp, CBinNode* lista);
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

void CBinTree::sobrinos_2(int nivel, int niveloriginal, CBinNode* tmp, CBinNode* lista)
{
    if (!lista)
        return;

    if (nivel == niveloriginal && lista->value != tmp->nodes[0]->value && lista->value != tmp->nodes[1]->value)
    {
        cout << lista->value << " ";
        return;
    }
    niveloriginal++;
    sobrinos_2(nivel, niveloriginal, tmp, lista->nodes[0]);
    sobrinos_2(nivel, niveloriginal, tmp, lista->nodes[1]);
}

void CBinTree::sobrinos_de(int x)
{
    CBinNode** tmp = &m_root;
    int nivel = 0;
    while (*tmp && (*tmp)->value != x)
    {
        nivel++;
        tmp = &((*tmp)->nodes[(*tmp)->value < x]);
    }

    if (*tmp && (*tmp)->value == x)
        sobrinos_2(nivel + 1, 0, *tmp, m_root);
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
    t.sobrinos_de(25);
}