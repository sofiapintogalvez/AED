// Gaficar un arbol binario con SFML version 2.5.1 y GLUT

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

struct Node
{
    int v;
    Node* node[2];
    Node(int x) : v(x)
    {
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
    void drawTree(Node* n, sf::RenderWindow& window, float x, float y, float offsetX, float offsetY, sf::Font& font);
};

bool BinTree::find(int x, Node**& p)
{
    p = &root;
    while (*p && (*p)->v != x)
        p = &((*p)->node[x > (*p)->v]);
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

void BinTree::drawTree(Node* n, sf::RenderWindow& window, float x, float y, float offsetX, float offsetY, sf::Font& font)
{
    if (!n) return;

    float radius = 20.f;

    // Nodo como círculo
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color(192, 0, 192));  // Morado
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(2);
    circle.setOrigin(radius, radius);
    circle.setPosition(x, y);
    window.draw(circle);

    // Texto
    sf::Text text;
    text.setFont(font);
    text.setString(to_string(n->v));
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x - 10, y - 10);
    window.draw(text);

    // Hijo izquierdo
    if (n->node[0])
    {
        float newX = x - offsetX;
        float newY = y + offsetY;

        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(x, y), sf::Color::Black),
            sf::Vertex(sf::Vector2f(newX, newY), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(n->node[0], window, newX, newY, offsetX * 0.5f, offsetY, font);
    }

    // Hijo derecho
    if (n->node[1])
    {
        float newX = x + offsetX;
        float newY = y + offsetY;

        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(x, y), sf::Color::Black),
            sf::Vertex(sf::Vector2f(newX, newY), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(n->node[1], window, newX, newY, offsetX * 0.5f, offsetY, font);
    }
}

int main()
{
    BinTree t;

    t.ins(5); t.ins(2); t.ins(8);
    t.ins(1); t.ins(3); t.ins(9);
    t.ins(7);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Árbol Binario SFML");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        cerr << "No se pudo cargar la fuente" << endl;
        return 1;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        t.drawTree(t.root, window, 400.0f, 50.0f, 160.0f, 80.0f, font);
        window.display();
    }
    
    return 0;
}

/*#include <GL/glut.h>
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
    while (*p && (*p)->v != x)
        p = &((*p)->node[x > (*p)->v]);
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
    t.ins(5); t.ins(2); t.ins(8);
    t.ins(1); t.ins(3); t.ins(9);
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
}*/
