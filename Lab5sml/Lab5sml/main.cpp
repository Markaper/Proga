#include <iostream>
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib> 
#include <ctime>  
#include <set>

using namespace std;
using namespace sf;

const int MAX_TRIANGLES = 100; //макс кол-во треугольников

CircleShape* circleCreate(int numVertices, float radius) {
    CircleShape* circles = new CircleShape[numVertices];

    for (int i = 0; i < numVertices; i++) {
        float angle = 2 * M_PI * i / numVertices;
        float x = 480 + radius * cos(angle);
        float y = 430 + radius * sin(angle);

        circles[i].setRadius(30);
        circles[i].setFillColor(Color(255, 255, 255));
        circles[i].setOutlineColor(Color(0, 0, 0));
        circles[i].setOutlineThickness(3);
        circles[i].setPosition(x - 30, y - 30);
    }
    return circles;
}

Text* createNum(int numVertices, Font& font, CircleShape* circles) {
    Text* textNumbers = new Text[numVertices];
    for (int i = 0; i < numVertices; i++) {
        textNumbers[i].setFont(font);
        textNumbers[i].setString(to_string(i + 1));
        textNumbers[i].setCharacterSize(32);
        textNumbers[i].setFillColor(Color(0, 0, 0));
        textNumbers[i].setPosition(circles[i].getPosition().x + circles[i].getRadius() - textNumbers[i].getLocalBounds().width / 2,
            circles[i].getPosition().y + circles[i].getRadius() - textNumbers[i].getLocalBounds().height / 2);
    }
    return textNumbers;
}

class DirectedGraph {
public:
    DirectedGraph(int vertices) : numVertices(vertices), edgeCount(0) {
        edgesList = new int* [100]; // максимальное количество рёбер
        for (int i = 0; i < 100; i++) {
            edgesList[i] = new int[2];
        }

        adjacencyMatrix = new int* [numVertices];
        for (int i = 0; i < numVertices; i++) {
            adjacencyMatrix[i] = new int[numVertices]();
        }

        adjacencyList.resize(numVertices); // Используем вектор для списка смежностей
    }

    ~DirectedGraph() {
        for (int i = 0; i < 100; i++) {
            delete[] edgesList[i];
        }
        delete[] edgesList;

        for (int i = 0; i < numVertices; i++) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }

    void addEdge(int u, int v) {
        edgesList[edgeCount][0] = u;
        edgesList[edgeCount][1] = v;
        edgeCount++;

        adjacencyMatrix[u - 1][v - 1] = 1;

        adjacencyList[u - 1].push_back(v); // Используем push_back для добавления вектор
    }

    void printGraph() {
        std::cout << "Список рёбер:\n";
        for (int i = 0; i < edgeCount; i++) {
            std::cout << "{" << edgesList[i][0] << "," << edgesList[i][1] << "}";
        }
        std::cout << std::endl;

        std::cout << "\nМатрица смежности:\n";
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                std::cout << adjacencyMatrix[i][j] << " ";
            }
            std::cout << "\n";
        }

        std::cout << "\nСписок смежностей:\n";
        for (int i = 0; i < numVertices; i++) {
            std::cout << (i + 1) << ": ";
            for (const int& neighbor : adjacencyList[i]) {
                std::cout << neighbor << " ";
            }
            std::cout << "\n";
        }
    }

    int** getEdgesList() { return edgesList; }
    int getEdgeCount() { return edgeCount; }

private:
    int numVertices;
    int edgeCount;
    int** edgesList;
    int** adjacencyMatrix;
    std::vector<std::vector<int>> adjacencyList; // Теперь вектор векторов для списка смежностей
};

struct TriangleShape {
    VertexArray shape;

    TriangleShape(Vector2f point1, Vector2f point2, Vector2f point3, Color color) {
        shape.setPrimitiveType(Triangles);
        shape.append(Vertex(point1, color));
        shape.append(Vertex(point2, color));
        shape.append(Vertex(point3, color));
    }
    TriangleShape() {
        shape.setPrimitiveType(Triangles);
    }
};//структура для представления цвета (для удобства сравнения)
struct ColorRGB {
    unsigned char r, g, b;
    bool operator<(const ColorRGB& other) const {
        if (r != other.r) return r < other.r;
        if (g != other.g) return g < other.g;
        return b < other.b;
    }
};

//функция для генерации уникального случайного цвета
ColorRGB generateUniqueColor(set<ColorRGB>& usedColors) {
    ColorRGB newColor;
    do {
        newColor.r = rand() % 256;
        newColor.g = rand() % 256;
        newColor.b = rand() % 256;
    } while (usedColors.count(newColor)); //повторяем, пока не будет уникального цвета
    usedColors.insert(newColor);
    return newColor;
}

TriangleShape createTriangle(CircleShape& circle1, CircleShape& circle2, Color color,float radius) {
    Vector2f center1 = circle1.getPosition() + Vector2f(30, 30);
    Vector2f center2 = circle2.getPosition() + Vector2f(30, 30);

    Vector2f direction = center2 - center1;
    float angle = atan2(direction.y, direction.x);

    Vector2f point1(center1.x + radius * cos(angle - M_PI / 2), center1.y + radius * sin(angle - M_PI / 2));
    Vector2f point2(center1.x + radius * cos(angle + M_PI / 2), center1.y + radius * sin(angle + M_PI / 2));
    Vector2f point3(center2.x - radius * cos(angle), center2.y - radius * sin(angle));

    return TriangleShape(point1, point2, point3, color);
}




int main() {
    setlocale(LC_ALL, "RUS");
    srand(static_cast<unsigned int>(time(0)));
    int numVertices = 5;

    DirectedGraph graph(numVertices);


    graph.addEdge(1, 3);
    graph.addEdge(2, 5);
    graph.addEdge(3, 2);
    graph.addEdge(4, 3);
    graph.addEdge(4, 5);
    graph.addEdge(5, 1);


    graph.printGraph();



    RenderWindow window(VideoMode(1000, 800), "многоугольничек");

    float radius = 250;

    CircleShape* circles = circleCreate(numVertices, radius);

    Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        cerr << "Ошибка открытия файла";
    }

    Text* textNumbers = createNum(numVertices, font, circles);

    TriangleShape triangles[MAX_TRIANGLES];
    int triangleCount = 0;
    set<ColorRGB> usedColors; // множество для отслеживания использованных цветов

    for (int i = 0; i < graph.getEdgeCount(); i++) {
        if (triangleCount < MAX_TRIANGLES) {
            int u = graph.getEdgesList()[i][0] - 1;
            int v = graph.getEdgesList()[i][1] - 1;

            ColorRGB uniqueColor = generateUniqueColor(usedColors);
            triangles[triangleCount] = createTriangle(circles[u], circles[v], Color(uniqueColor.r, uniqueColor.g, uniqueColor.b), radius);
            triangleCount++;
        }
        else {
            cerr << "Достигнуто максимальное количество треугольников!" << endl;
            break;
        }
    }

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color(255, 255, 255));

        // Рисуем все треугольники
        for (int i = 0; i < triangleCount; i++) {
            window.draw(triangles[i].shape);
        }

        for (int i = 0; i < numVertices; i++) {
            window.draw(circles[i]);
            window.draw(textNumbers[i]);
        }



        window.display();
    }

    delete[] circles;
    delete[] textNumbers;

    return 0;
}