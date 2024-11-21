#include <iostream>
#include <string>

using namespace std;

// Структура узла двусвязного списка
struct Node {
    string data;
    Node* prev;
    Node* next;

    Node(string data) : data(data), prev(nullptr), next(nullptr) {}
};

// Класс Стек
class Stack {
private:
    Node* top;
    int size;

public:
    // Конструктор
    Stack() : top(nullptr), size(0) {}

    // Добавление элемента
    void push(string data) {
        Node* new_node = new Node(data);
        new_node->next = top;
        if (top) {
            top->prev = new_node;
        }
        top = new_node;
        size++;
    }

    // Извлечение элемента
    string pop() {
        if (top) {
            Node* temp = top;
            string data = top->data;
            top = top->next;
            if (top) {
                top->prev = nullptr;
            }
            delete temp;
            size--;
            return data;
        }
        else {
            return "";
        }
    }

    // Поиск элемента
    bool find(string data) {
        Node* current = top;
        while (current) {
            if (current->data == data) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Вес элемента
    int weight(string data) {
        Node* current = top;
        int weight = 0;
        while (current) {
            if (current->data == data) {
                return weight;
            }
            current = current->next;
            weight++;
        }
        return -1;
    }

    // Глубина стека
    int depth() {
        return size;
    }

    // Перегрузка оператора + (добавление стеков)
    Stack operator+(const Stack& other) const {
        Stack new_stack;
        Node* current = top;
        while (current) {
            new_stack.push(current->data);
            current = current->next;
        }
        current = other.top;
        while (current) {
            new_stack.push(current->data);
            current = current->next;
        }
        return new_stack;
    }

    // Перегрузка оператора * (перекрестное соединение)
    Stack operator*(const Stack& other) const {
        Stack result;

        // Перекрестное соединение
        Node* current1 = top;
        Node* current2 = other.top;

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

        // Перевернем результат, чтобы получить нужный порядок
        Stack finalResult;
        while (result.top != nullptr) {
            finalResult.push(result.pop());
        }

        return finalResult;
    }

    // Перегрузка унарного оператора - (переворот стека)
    Stack operator-() const {
        Stack new_stack;
        Node* current = top;
        while (current) {
            new_stack.push(current->data);
            current = current->next;
        }
        return new_stack;
    }

    // Метод Dzenga
    void dzenga(int i) {
        if (i < 0 || i >= size) {
            return;
        }
        Node* current = top;
        int count = 0;

        while (current) {
            // Если count == i, удаляем элемент из текущего стека
            if (count == i) {
                if (current->prev) {
                    current->prev->next = current->next;
                }
                if (current->next) {
                    current->next->prev = current->prev;
                }
                if (count == 0) {
                    top = current->next;
                }
                delete current;
                size--;
                return;
            }
            current = current->next;
            count++;
        }
    }

    // Вывод стека
    void print() {
        Node* current = top;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    Stack stack1, stack2;
    setlocale(LC_ALL, "");
    // Заполнение стеков
    stack1.push("A");
    stack1.push("B");
    stack1.push("C");

    stack2.push("D");
    stack2.push("E");

    // Демонстрация операций
    cout << "Стек 1: ";
    stack1.print();

    cout << "Стек 2: ";
    stack2.print();

    cout << "Стек 1 + Стек 2: ";
    (stack1 + stack2).print();

    cout << "Стек 1 * Стек 2: ";
    (stack1 * stack2).print();

    cout << "- Стек 1: ";
    (-stack1).print();

    cout << "Стек 1 после dzenga(1): ";
    stack1.dzenga(0);
    stack1.print();

    return 0;
}
