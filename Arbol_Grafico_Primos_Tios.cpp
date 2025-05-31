// Hacer grafico de un arbol donde pinte los tios y sobrinos de un numero ingresado de diferente color

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>

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
    int obtenerNivel(Node* nodo, int valor, int nivel);
    Node* obtenerPadre(Node* nodo, int valor);
    void dibujarArbol(Node* nodo, sf::RenderWindow& window, float x, float y, float offsetX, float offsetY, int objetivo, int nivel, int nivelResaltado, int nivelPadre, Node* hermano, Node* padre, sf::Font& font);
    void dibujarArbolColoreado(sf::RenderWindow& window, sf::Font& font, int objetivo);
};

bool BinTree::find(int x, Node**& p)
{
    p = &root;
    while (*p && (*p)->v != x)
        p = &((*p)->node[x > (*p)->v]);
    return *p != nullptr;
}

bool BinTree::ins(int x)
{
    Node** p;
    if (find(x, p)) return false;
    *p = new Node(x);
    return true;
}

bool BinTree::rem(int x)
{
    Node** p;
    if (!find(x, p)) return false;
    if ((*p)->node[0] && (*p)->node[1])
    {
        Node** q = rep(p);
        (*p)->v = (*q)->v;
        p = q;
    }
    Node* t = *p;
    *p = (*p)->node[(*p)->node[1] != 0];
    delete t;
    return true;
}

Node** BinTree::rep(Node** q)
{
    q = &((*q)->node[m_b]);
    while ((*q)->node[!m_b])
        q = &((*q)->node[!m_b]);
    m_b = !m_b;
    return q;
}

int BinTree::obtenerNivel(Node* nodo, int valor, int nivel)
{
    if (!nodo)
        return -1;
    if (nodo->v == valor)
        return nivel;

    int izq = obtenerNivel(nodo->node[0], valor, nivel + 1);
    if (izq != -1)
        return izq;
    return obtenerNivel(nodo->node[1], valor, nivel + 1);
}

Node* BinTree::obtenerPadre(Node* nodo, int valor)
{
    if (!nodo || nodo->v == valor)
        return nullptr;
    if ((nodo->node[0] && nodo->node[0]->v == valor) || (nodo->node[1] && nodo->node[1]->v == valor))
        return nodo;

    Node* izq = obtenerPadre(nodo->node[0], valor);
    if (izq)
        return izq;
    return obtenerPadre(nodo->node[1], valor);
}

void BinTree::dibujarArbol(Node* nodo, sf::RenderWindow& window, float x, float y, float offsetX, float offsetY, int objetivo, int nivel, int nivelResaltado, int nivelPadre, Node* hermano, Node* padre, sf::Font& font) {
    if (!nodo) return;

    float radius = 20.f;
    bool esSobrino = (nivel == nivelResaltado && nodo != hermano && nodo->v != objetivo);
    bool esTio = (nivel == nivelPadre && nodo != padre);

    sf::Color color;
    if (esSobrino)
        color = sf::Color(255, 128, 0);       // Naranja
    else if (esTio)
        color = sf::Color(128, 0, 255);      // Púrpura
    else
        color = sf::Color(0, 200, 50);       // Verde

    sf::CircleShape circle(radius);
    circle.setFillColor(color);
    circle.setOutlineThickness(2);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOrigin(radius, radius);
    circle.setPosition(x, y);
    window.draw(circle);
    sf::Text text;
    text.setFont(font);
    text.setString(to_string(nodo->v));
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x - 10, y - 12);
    window.draw(text);

    if (nodo->node[0])
    {
        float newX = x - offsetX;
        float newY = y + offsetY;
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(x, y), sf::Color::Black),
            sf::Vertex(sf::Vector2f(newX, newY), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        dibujarArbol(nodo->node[0], window, newX, newY, offsetX * 0.5f, offsetY, objetivo, nivel + 1, nivelResaltado, nivelPadre, hermano, padre, font);
    }

    if (nodo->node[1])
    {
        float newX = x + offsetX;
        float newY = y + offsetY;
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y), sf::Color::Black),
            sf::Vertex(sf::Vector2f(newX, newY), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        dibujarArbol(nodo->node[1], window, newX, newY, offsetX * 0.5f, offsetY, objetivo, nivel + 1, nivelResaltado, nivelPadre, hermano, padre, font);
    }
}

void BinTree::dibujarArbolColoreado(sf::RenderWindow& window, sf::Font& font, int objetivo)
{
    int nivelObjetivo = obtenerNivel(root, objetivo, 0);
    if (nivelObjetivo == -1)
        return;

    Node* padre = obtenerPadre(root, objetivo);
    Node* hermano = (padre && padre->node[0] && padre->node[0]->v == objetivo) ? padre->node[1] : (padre && padre->node[1] && padre->node[1]->v == objetivo) ? padre->node[0] : nullptr;

    int nivelPadre = nivelObjetivo - 1;

    dibujarArbol(root, window, 400.0f, 50.0f, 160.0f, 80.0f, objetivo, 0, nivelObjetivo, nivelPadre, hermano, padre, font);
}

int main()
{
    BinTree t;
    t.ins(8); t.ins(4); t.ins(12);
    t.ins(2); t.ins(6); t.ins(10);
    t.ins(14); t.ins(1); t.ins(3);
    t.ins(5); t.ins(7); t.ins(9);
    t.ins(11); t.ins(13); t.ins(15);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Árbol Binario - Tíos y Sobrinos");
    window.setFramerateLimit(60);
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        cerr << "Error al cargar la fuente" << endl;
        return 1;
    }

    int objetivo;
    cout << "Ingrese numero: ";
    cin >> objetivo;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        t.dibujarArbolColoreado(window, font, objetivo);
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
    int segments = 100;
    float angleStep = 360.0f / segments;
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= segments; i++) {
        float angle = angleStep * i;
        float radian = angle * (3.14159265f / 180.0f);
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
    void dibujarArbol(Node* nodo, float x, float y, float offsetX, float offsetY, int objetivo, int nivel, int nivelResaltado, int nivelPadre, Node* hermano, Node* padre);
    int obtenerNivel(Node* nodo, int valor, int nivel);
    Node* obtenerPadre(Node* nodo, int valor);
    void dibujarArbolColoreado(int objetivo);
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
    if (!find(x, p)) return 0;
    // CASO 2
    if ((*p)->node[0] && (*p)->node[1])
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

int BinTree::obtenerNivel(Node* nodo, int valor, int nivel)
{
    if(!nodo) 
        return -1;
    if(nodo->v == valor) 
        return nivel;

    int nivelIzquierdo = obtenerNivel(nodo->node[0], valor, nivel + 1);
    if(nivelIzquierdo != -1) 
        return nivelIzquierdo;

    return obtenerNivel(nodo->node[1], valor, nivel + 1);
}

Node* BinTree::obtenerPadre(Node* nodo, int valor)
{
    if(!nodo || nodo->v == valor) 
        return nullptr;
    if((nodo->node[0] && nodo->node[0]->v == valor) || (nodo->node[1] && nodo->node[1]->v == valor))
        return nodo;

    Node* padreIzquierdo = obtenerPadre(nodo->node[0], valor);
    if(padreIzquierdo) 
        return padreIzquierdo;

    return obtenerPadre(nodo->node[1], valor);
}

void BinTree::dibujarArbol(Node* nodo, float x, float y, float offsetX, float offsetY, int objetivo, int nivel, int nivelResaltado, int nivelPadre, Node* hermano, Node* padre)
{
    if(!nodo) return;

    // Determinar color del nodo según su nivel
    bool resaltarActual = (nivel == nivelResaltado && nodo != hermano && nodo->v != objetivo);
    bool resaltarPrimos = (nivel == nivelPadre && nodo != padre);

    if (resaltarActual)
        glColor3f(1.0f, 0.5f, 0.0f);  // Naranja
    else if (resaltarPrimos)
        glColor3f(0.5f, 0.0f, 1.0f);  // Púrpura
    else
        glColor3f(0.0f, 0.8f, 0.2f);  // Verde

    drawCircle(x, y, 0.05f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(x - 0.02f, y);
    string textoValor = to_string(nodo->v);
    for(char c : textoValor) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

    // Dibujar líneas y recursión
    if(nodo->node[0])
    {
        glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x - offsetX, y - offsetY);
        glEnd();
        dibujarArbol(nodo->node[0], x - offsetX, y - offsetY, offsetX * 0.5f, offsetY, objetivo, nivel + 1, nivelResaltado, nivelPadre, hermano, padre);
    }
    if(nodo->node[1]) 
    {
        glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x + offsetX, y - offsetY);
        glEnd();
        dibujarArbol(nodo->node[1], x + offsetX, y - offsetY, offsetX * 0.5f, offsetY, objetivo, nivel + 1, nivelResaltado, nivelPadre, hermano, padre);
    }
}

void BinTree::dibujarArbolColoreado(int objetivo)
{
    int nivelObjetivo = obtenerNivel(root, objetivo, 0);
    if(nivelObjetivo == -1) 
        return;  // Objetivo no encontrado

    Node* padre = obtenerPadre(root, objetivo);
    Node* hermano = (padre && padre->node[0] && padre->node[0]->v == objetivo) ? padre->node[1] :
        (padre && padre->node[1] && padre->node[1]->v == objetivo) ? padre->node[0] : nullptr;

    int nivelPadre = nivelObjetivo - 1;
    dibujarArbol(root, 0.0f, 0.8f, 0.4f, 0.2f, objetivo, 0, nivelObjetivo, nivelPadre, hermano, padre);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    extern BinTree t;
    int objetivo;
    cout << "Ingrese numero: ";
    cin >> objetivo;
    t.dibujarArbolColoreado(objetivo);
    glFlush();
}

BinTree t;

int main(int argc, char** argv)
{
    t.ins(8); t.ins(4); t.ins(12);
    t.ins(2); t.ins(6); t.ins(10);
    t.ins(14); t.ins(1); t.ins(3);
    t.ins(5); t.ins(7); t.ins(9);
    t.ins(11); t.ins(13); t.ins(15);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Árbol Binario");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}*/
