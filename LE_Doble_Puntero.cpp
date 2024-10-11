// Lista enlazada con doble puntero

#include <iostream>

using namespace std;

struct Node
{
    int v;
    Node* next;
    Node (int x)
    {
        v = x;
        next = NULL;
    }
};

struct LE
{
    Node* head = NULL;
    bool find(int x, Node**& p);
    bool ins(int x);
    bool rem(int x);
    void print();
    ~LE();
};

bool LE::find(int x, Node**& p)
{
    p = &head;
    while (*p && (*p)->v < x)
        p = (&(*p)->next);

    return *p && (*p)->v == x;
}

bool LE::ins(int x)
{
    Node** p;
    if (find(x, p)) return 0;
    Node* t = new Node(x);
    t->next = *p;
    *p = t;
    return 1;
}

bool LE::rem(int x)
{
    Node** p;
    if (!find(x, p)) return 0;
    Node* t = *p;
    *p = t->next;
    delete t;
    return 1;
}

void LE::print()
{
    cout << "head->";
    for (Node* p = head; p; p = p->next)
        cout << p->v << "->";
    cout << "null\n";
}

LE::~LE()
{
    Node* tmp;
    while (head)
    {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}

int main()
{
    LE lista;

    lista.ins(7);
    lista.ins(4);
    lista.ins(14);
    lista.ins(11);

    lista.print();
}
