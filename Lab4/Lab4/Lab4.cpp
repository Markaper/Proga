#include <iostream>
#include <string>
#include <stdexcept> // Для runtime_error

using namespace std;

// Структура узла для двусвязного списка
template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}

    // Деструктор для узла
    ~Node() {
        // Освобождаем память, если она была выделена
        next = nullptr;
        prev = nullptr;
    }
};

// Класс стека
template <typename T>
class Stack {
private:
    Node<T>* top;
    int size;

public:
    // Конструктор
    Stack() : top(nullptr), size(0) {}

    // Деструктор для освобождения памяти
    ~Stack() {
        Node<T>* current = top;
        while (current != nullptr) {
            Node<T>* nextNode = current->next; // Сохраняем следующий узел

            // Обнуляем ссылки на соседние узлы
            if (current->prev != nullptr) {
                current->prev->next = nullptr; // Убираем ссылку на текущий узел у предыдущего
            }
            if (current->next != nullptr) {
                current->next->prev = nullptr; // Убираем ссылку на текущий узел у следующего
            }

            delete current; // Освобождаем память текущего узла
            current = nextNode; // Переходим к следующему узлу
        }
        size = 0; // Сбрасываем размер
    }

    // Добавление элемента (в начало списка)
    void push(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        if (top == nullptr) {
            top = newNode;
        }
        else {
            newNode->next = top;
            top->prev = newNode;
            top = newNode;
        }
        size++;
    }

    // Просмотр и извлечение элемента (из начала)
    T pop() {
        if (top == nullptr) {
            throw runtime_error("Стек пуст!");
        }
        Node<T>* temp = top;
        T data = temp->data;
        top = top->next;
        if (top != nullptr) {
            top->prev = nullptr;
        }
        delete temp;
        size--;
        return data;
    }

    // Просмотр элемента (из начала)
    T peek() const {
        if (top == nullptr) {
            throw runtime_error("Стек пуст!");
        }
        return top->data;
    }

    // Поиск элемента а (вернуть T/F)
    bool find(const T& data) const {
        Node<T>* current = top;
        while (current != nullptr) {
            if (current->data == data) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Вычисление веса элемента а (номер в стек если есть либо -1)
    int weight(const T& data) const {
        int weight = 0;
        Node<T>* current = top;
        while (current != nullptr) {
            if (current->data == data) {
                return weight;
            }
            current = current->next;
            weight++;
        }
        return -1;
    }

    // Глубина стека (сколько всего элементов)
    int depth() const {
        return size;
    }

    // Переопределение операторов

    // + как добавление В поверх А
    Stack operator+(const Stack& other) const {
        Stack result = *this;
        Node<T>* current = other.top;
        while (current != nullptr) {
            result.push(current->data);
            current = current->next;
        }
        return result;
    }

    // * как перекрестное соединение стеков
    Stack operator*(const Stack& other) const {
        Stack result;
        Node<T>* current1 = top;
        Node<T>* current2 = other.top;

        while (current1 != nullptr || current2 != nullptr) {
            if (current1 != nullptr) {
                result.push(current1->data);
                current1 = current1->next;
            }
            if (current2 != nullptr) {
                result.push(current2->data);
                current2 = current2->next;
            }
        }

        return result; // Перевернем результат в обратном порядке 
    }

    // унарный оператор – как переворот стека
    Stack operator-() const {
        Stack result;
        Node<T>* current = top;
        while (current != nullptr) {
            result.push(current->data);
            current = current->next;
        }
        return result;
    }

    // Вариант 1: (м) Meshaem (a,B) встраивает стек В после а.
    void meshaem(const T& a, const Stack& other) {
        if (!find(a)) {
            throw runtime_error("Элемент a не найден в стеке!");
        }

        Node<T>* current = other.top;
        Node<T>* insertAfter = nullptr;
        Node<T>* currentThis = top;

        // Найдем узел, после которого нужно вставлять
        while (currentThis != nullptr) {
            if (currentThis->data == a) {
                insertAfter = currentThis;
                break;
            }
            currentThis = currentThis->next;
        }

        // Вставим элементы из other в наш стек
        while (current != nullptr) {
            Node<T>* newNode = new Node<T>(current->data);
            if (insertAfter == nullptr) {
                // Вставка в начало стека
                newNode->next = top;
                if (top != nullptr) {
                    top->prev = newNode;
                }
                top = newNode;
            }
            else {
                // Вставка после элемента a
                newNode->next = insertAfter->next;
                if (insertAfter->next != nullptr) {
                    insertAfter->next->prev = newNode;
                }
                insertAfter->next = newNode;
                newNode->prev = insertAfter;
            }
            current = current->next;
            size++;
        }
    }
};

int main() {
    setlocale(LC_ALL, "");
    Stack<string> stack1;
    stack1.push("A");
    stack1.push("B");
    stack1.push("C");

    Stack<string> stack2;
    stack2.push("D");
    stack2.push("E");

    // Тестирование методов
    cout << "Глубина стека 1: " << stack1.depth() << endl;
    cout << "Поиск элемента 'B': " << stack1.find("B") << endl;
    cout << "Вес элемента 'B': " << stack1.weight("B") << endl;
    cout << "Вершина стека 1: " << stack1.peek() << endl;

    // Тестирование операторов
    Stack<string> stack3 = stack1 + stack2;
    cout << "Стек 1 + Стек 2: ";
    for (int i = 0; i < stack3.depth(); i++) {
        cout << stack3.pop() << " ";
    }
    cout << endl;

    Stack<string> stack4 = stack1 * stack2;
    cout << "Стек 1 * Стек 2: ";
    for (int i = 0; i < stack4.depth(); i++) {
        cout << stack4.pop() << " ";
    }
    cout << endl;

    Stack<string> stack5 = -stack1;
    cout << "- Стек 1: ";
    for (int i = 0; i < stack5.depth(); i++) {
        cout << stack5.pop() << " ";
    }
    cout << endl;

    // Тестирование метода Meshaem
    stack1.meshaem("B", stack2);
    cout << "Meshaem (B, Стек 2): ";
    for (int i = 0; i < stack1.depth(); i++) {
        cout << stack1.pop() << " ";
    }
    cout << endl;

    return 0;
}
