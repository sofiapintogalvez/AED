// Armar un arbol desde una array con 2^n elementos (sumando de par en par para sacar los padres de esos nodos) con 4 threads

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

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

    Node* HijosPadres(const vector<int>& arr, int start, int end)
    {
        int length = end - start + 1;
        if (length == 1)
            return new Node(arr[start]);

        int mid = start + length / 2 - 1;
        Node* left = HijosPadres(arr, start, mid);
        Node* right = HijosPadres(arr, mid + 1, end);
        Node* parent = new Node(left->v + right->v);
        parent->node[0] = left;
        parent->node[1] = right;
        return parent;
    }

    void arbolThread(const vector<int>& arr)
    {
        int n = arr.size();
        if (n == 0) return;
        if ((n & (n - 1)) != 0)
        {
            cerr << "Tamaño invalido" << endl;
            return;
        }
        if (n < 4)
        {
            root = HijosPadres(arr, 0, n - 1);  // si hay menos de 4 elementos en el array no es necesario usar thread, de frente en secuencial
            return;
        }

        int partes = n / 4;

        Node* miniarboles[4] = { nullptr, nullptr, nullptr, nullptr };
        mutex mtx;

        auto th = [&](int idx)
        {
            int inicio = idx * partes;
            int fin = inicio + partes - 1;
            Node* nuevo = HijosPadres(arr, inicio, fin);
            lock_guard<mutex> lock(mtx);
            miniarboles[idx] = nuevo;
        };

        thread threads[4];
        for (int i = 0; i < 4; ++i)
            threads[i] = thread(th, i);

        for (int i = 0; i < 4; ++i)
            threads[i].join();

        Node* Pizq = new Node(miniarboles[0]->v + miniarboles[1]->v);
        Pizq->node[0] = miniarboles[0];
        Pizq->node[1] = miniarboles[1];

        Node* Pder = new Node(miniarboles[2]->v + miniarboles[3]->v);
        Pder->node[0] = miniarboles[2];
        Pder->node[1] = miniarboles[3];

        root = new Node(Pizq->v + Pder->v);
        root->node[0] = Pizq;
        root->node[1] = Pder;
    }

    void drawTree(Node* n, sf::RenderWindow& window, float x, float y, float offsetX, float offsetY, sf::Font& font)
    {
        if (!n) return;

        float radius = 20.f;

        sf::CircleShape circle(radius);
        circle.setFillColor(sf::Color(192, 0, 192));
        circle.setOutlineColor(sf::Color::Black);
        circle.setOutlineThickness(2);
        circle.setOrigin(radius, radius);
        circle.setPosition(x, y);
        window.draw(circle);

        sf::Text text;
        text.setFont(font);
        text.setString(to_string(n->v));
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::Black);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
        text.setPosition(x, y);
        window.draw(text);

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
};

int main()
{
    BinTree t;

    vector<int> arr = { 14, 41, 36, 18, 25, 72, 89, 100 };

    t.arbolThread(arr);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Árbol Binario SFML (4 Threads)");
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
        t.drawTree(t.root, window, 400.f, 50.f, 150.f, 80.f, font);
        window.display();
    }

    return 0;
}
