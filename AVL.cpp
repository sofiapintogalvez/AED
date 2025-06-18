// Arbol AVL con stack

#include <iostream>
#include <stack>

using namespace std;

struct Node
{
    int v;
    int altura;
    Node* node[2];
    Node(int x)
    {
        v = x;
        node[0] = node[1] = 0;
        altura = 1;
    }
};

struct AVL
{
    Node* root = NULL;
    bool m_b = 0;
    bool find(int x, Node**& p, stack<Node**>& s);
    int getAltura(Node* n);
    int Diferencia(Node* n);
    Node* RR(Node* A);
    Node* LL(Node* C);
    Node* RL(Node* C);
    Node* LR(Node* A);
    bool ins(int x);
    bool rem(int x);
    Node** rep(Node** q);
    void InOrder(Node* n);
    void print();
    //~AVL();
};

bool AVL::find(int x, Node**& p, stack <Node**>& s)
{
    p = &root;
    while(*p && (*p)->v != x)
    {
        s.push(p);
        p = &((*p)->node[x > (*p)->v]);
    }
    
    return *p != nullptr;
}

int AVL::getAltura(Node* n) 
{
    return n ? n->altura : 0;   // si existe nodo retorna su altura sino 0
}

int AVL::Diferencia(Node* n) 
{
    return n ? getAltura(n->node[1]) - getAltura(n->node[0]) : 0;     // si existe nodo retorna der-izq sino 0 
}

Node* AVL::RR(Node* A) 
{
    Node* B = A->node[1];
    Node* bl = B->node[0];

    B->node[0] = A;
    A->node[1] = bl;

    A->altura = max(getAltura(A->node[0]), getAltura(A->node[1])) + 1;    // maximo entre izq y der + 1
    B->altura = max(getAltura(B->node[0]), getAltura(B->node[1])) + 1;

    return B;   // nuevo root
}

Node* AVL::LL(Node* C) 
{
    Node* B = C->node[0];
    Node* br = B->node[1];

    B->node[1] = C;
    C->node[0] = br;

    C->altura = max(getAltura(C->node[0]), getAltura(C->node[1])) + 1;
    B->altura = max(getAltura(B->node[0]), getAltura(B->node[1])) + 1;

    return B;
}

Node* AVL::RL(Node* C) 
{
    C->node[0] = RR(C->node[0]);    // nodo root A, convierte ese mini arbol en LL
    return LL(C);
}

Node* AVL::LR(Node* A) 
{
    A->node[1] = LL(A->node[1]);    // nodo root C, convierte ese mini arbol en RR
    return RR(A);
}

bool AVL::ins(int x)
{
    Node** p;
    stack <Node**> s;
    if(find(x, p, s)) return 0;
    *p = new Node(x);

    while(!s.empty())
    {
        Node** actual = s.top();
        s.pop();

        Node* n = *actual;
        n->altura = max(getAltura(n->node[0]), getAltura(n->node[1])) + 1;
        int dif = Diferencia(n);

        // se compara si es mayor o menor para saber las direcciones (grafico) de las flechas y saber cual es
        if(dif > 1 && x > n->node[1]->v)
            *actual = RR(n);
        
        else if(dif < -1 && x < n->node[0]->v)
            *actual = LL(n);
        
        else if(dif < -1 && x > n->node[0]->v)
            *actual = RL(n);

        else if(dif > 1 && x < n->node[1]->v) 
            *actual = LR(n);
    }
    return 1;
}

bool AVL::rem(int x)
{
    Node** p;
    stack<Node**> s;
    if(!find(x, p, s)) return 0;
    if((*p)->node[0] && (*p)->node[1])
    {
        Node** q = rep(p);
        (*p)->v = (*q)->v;
        p = q;
    }
    Node* t = *p;
    *p = (*p)->node[(*p)->node[1] != 0];
    delete t;

    while(!s.empty()) 
    {
        Node** actual = s.top();
        s.pop();

        Node* n = *actual;
        n->altura = max(getAltura(n->node[0]), getAltura(n->node[1])) + 1;
        int dif = Diferencia(n);

        if(dif > 1 && Diferencia(n->node[1]) >= 0)
            *actual = RR(n);

        else if(dif < -1 && Diferencia(n->node[0]) <= 0)
            *actual = LL(n);

        else if(dif < -1 && Diferencia(n->node[0]) > 0)
            *actual = RL(n);

        else if(dif > 1 && Diferencia(n->node[1]) < 0)
            *actual = LR(n);
    }
    return 1;
}

Node** AVL::rep(Node** q)
{
    q = &((*q)->node[m_b]);
    while((*q)->node[!m_b])
        q = &((*q)->node[!m_b]);
    m_b = !m_b;
    return q;
}

void AVL::InOrder(Node* n)
{
    if(!n) return;
    InOrder(n->node[0]);
    cout << n->v << " ";
    InOrder(n->node[1]);
}

void AVL::print()
{
    InOrder(root);
    cout << endl;
}

int main()
{
    AVL t;

    t.ins(51); t.ins(30); t.ins(20);
    t.ins(70); t.ins(90); t.ins(60);

    t.print();

    t.rem(20);
    t.print();

    return 0;
}
