// Grafico de un arbol binario con GLUT

#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

void drawCircle(float x, float y, float radius)
{
    int segments = 100;  // Número de segmentos para aproximar el círculo
    float angleStep = 360.0f / segments;  // Ángulo entre cada segmento

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= segments; i++)
    {
        float angle = angleStep * i;
        float radian = angle * (3.14159265f / 180.0f);  // Convertir a radianes
        glVertex2f(x + cos(radian) * radius, y + sin(radian) * radius);
    }
    glEnd();
}

struct Node
{
    int v;
    Node* node[2];
    Node(int x)
    {
        v = x;
        node[0] = node[1] = nullptr;
    }
};

struct BinTree
{
    Node* root = nullptr;
    bool m_b = 0;
    bool find(int x, Node**& p);
    bool ins(int x);
    Node** rep(Node** q);
    bool rem(int x);
    void InOrder(Node* n);
    void print();
    void drawTree(Node* n, float x, float y, float offsetX, float offsetY);
};

bool BinTree::find(int x, Node**& p)
{
    p = &root;
    while (*p && (*p)->v != x) {
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

bool BinTree::rem(int x)
{
    Node** p;
    if (!find(x, p)) return 0;
    if ((*p)->node[0] && (*p)->node[1])
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
    while ((*q)->node[!m_b])
        q = &((*q)->node[!m_b]);
    m_b = !m_b;
    return q;
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

void BinTree::drawTree(Node* n, float x, float y, float offsetX, float offsetY)
{
    if (!n) return;

    // Dibujar el nodo actual como un círculo
    glColor3f(0.75f, 0.0f, 0.75f);  // Color del nodo
    drawCircle(x, y, 0.05f);      // Tamaño del círculo
    glColor3f(0.0f, 0.0f, 0.0f);  // Color del texto
    glRasterPos2f(x - 0.02f, y);
    string valueText = to_string(n->v);

    for (char c : valueText) 
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

    // Dibujar conexiones y llamar recursivamente a los hijos
    if (n->node[0])
    {
        glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x - offsetX, y - offsetY);
        glEnd();
        drawTree(n->node[0], x - offsetX, y - offsetY, offsetX * 0.5f, offsetY);
    }
    if (n->node[1])
    {
        glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x + offsetX, y - offsetY);
        glEnd();
        drawTree(n->node[1], x + offsetX, y - offsetY, offsetX * 0.5f, offsetY);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    extern BinTree t;
    t.drawTree(t.root, 0.0f, 0.8f, 0.4f, 0.2f);

    glFlush();
}

BinTree t;

int main(int argc, char** argv)
{
    t.ins(5);
    t.ins(2);
    t.ins(8);
    t.ins(1);
    t.ins(3);
    t.ins(9);
    t.ins(7);

    // Inicializar GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Árbol Binario en GLUT");

    // Configurar el color de fondo
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Blanco
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Proyección ortogonal

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
