// Busqueda y recorrido en un arbol binario balanceado

#include <iostream>
#include <queue>
#include <stack>

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
    void PreOrder(Node* n);
    void PosOrder(Node* n);
    void printProfundidad();
    void Level(Node* n);
    void printNiveles();
    void RecurStack(Node* n);
    void printStack();
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
    // CASO 2
    if((*p)->node[0] && (*p)->node[1])
    {
        Node** q = rep(p);
        (*p)->v = (*q)->v;
        p = q;
    }
    // CASO 0 y 1
    Node* t = *p;
    *p = (*p)->node[(*p)->node[1] != 0];
    delete t;
    return 1;
}

Node** BinTree::rep(Node** q)
{
    q = &((*q)->node[m_b]);     // primero al hijo izquierdo m_b = 0 = izq
    while((*q)->node[!m_b])
        q = &((*q)->node[!m_b]);    // se va al fondo derecha
    m_b = !m_b;     // se cambia al hijo derecho m_b = 1 = der y asi alternando
    return q;
}

void BinTree::InOrder(Node* n)
{
    if(!n) return;
    InOrder(n->node[0]);
    cout << n->v << " ";
    InOrder(n->node[1]);
}

void BinTree::PreOrder(Node* n)
{
    if(!n) return;
    cout << n->v << " ";
    PreOrder(n->node[0]);
    PreOrder(n->node[1]);
}

void BinTree::PosOrder(Node* n)
{
    if(!n) return;
    PosOrder(n->node[0]);
    PosOrder(n->node[1]);
    cout << n->v << " ";
}

void BinTree::printProfundidad()
{
    InOrder(root);
    cout << endl;
    PreOrder(root);
    cout << endl;
    PosOrder(root);
    cout << endl;
}

void BinTree::Level(Node* n)
{
    queue <Node*> q;
    q.push(n);
    while(!q.empty())
    {
        n = q.front();
        cout << n->v << " ";
        if(n->node[0] != nullptr)
            q.push(n->node[0]);
        if(n->node[1] != nullptr)
            q.push(n->node[1]);
        q.pop();
    }
}

void BinTree::printNiveles()
{
    Level(root);
    cout << endl;
}

void BinTree::RecurStack(Node* n)
{
    stack <pair<Node*, int>> s;
    s.push(make_pair(n, 0));
    while(!s.empty())
    {
        auto& x = s.top();
        switch(x.second)
        {
            case 0:
                if(x.first->node[0] != nullptr)
                    s.push(make_pair(x.first->node[0], 0));
                x.second = 1;
                break;
            
            case 1:
                cout << x.first->v << " ";
                x.second = 2;
                break;
            
            case 2:
                if(x.first->node[1] != nullptr)
                    s.push(make_pair(x.first->node[1], 0));
                x.second = 3;
                break;

            case 3:
                s.pop();
                break;

            default:
                break;
        }
    }
}

void BinTree::printStack()
{
    RecurStack(root);
    cout << endl;
}

int main()
{
    BinTree t;

    t.ins(52); t.ins(30); t.ins(72);
    t.ins(11); t.ins(41); t.ins(60);
    t.ins(80);

    cout << "POR PROFUNDIDAD" << endl;
    t.printProfundidad();

    cout << "\nPOR NIVELES QUEUE" << endl;
    t.printNiveles();

    cout << "\nRECURSIVO STACK" << endl;
    t.printStack();

    t.rem(52);
    t.print();

    return 0;
}
