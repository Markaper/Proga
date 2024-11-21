//#include <iostream>
//#include <string>
//using namespace std;
//
//// Структура узла односвязного списка
//struct Node {
//    string Data;
//    Node* next;
//    Node(const string& data) : Data(data), next(nullptr) {}
//};
//
//class Queue {
//private:
//    Node* head;
//
//public:
//    // Конструктор по умолчанию
//    Queue() : head(nullptr) {}
//
//    // Конструктор копирования
//    Queue(const Queue& other) {
//        head = nullptr;
//        Node* current = other.head;
//        while (current != nullptr) {
//            enqueue(current->Data);
//            current = current->next;
//        }
//    }
//
//    // Деструктор
//    ~Queue() {
//        while (head != nullptr) {
//            Node* temp = head;
//            head = head->next;
//            delete temp;
//        }
//    }
//
//    // 1 Добавление элемента (в конец списка)
//    void enqueue(const string& data) {
//        Node* newNode = new Node(data);
//        if (head == nullptr) {
//            head = newNode;
//        }
//        else {
//            Node* current = head;
//            while (current->next != nullptr) {
//                current = current->next;
//            }
//            current->next = newNode;
//        }
//    }
//
//    // 2 Просмотр элемента (из начала)
//    string peek() const {
//        if (head == nullptr) {
//            return ""; // Возвращаем пустую строку, если очередь пуста
//        }
//        return head->Data;
//    }
//
//    // 3 Извлечение элемента (из начала)
//    string dequeue() {
//        if (head == nullptr) {
//            return ""; // Возвращаем пустую строку, если очередь пуста
//        }
//        Node* temp = head;
//        string data = head->Data;
//        head = head->next;
//        delete temp;
//        return data;
//    }
//
//    // 4 Поиск элемента (вернуть T/F)
//    bool search(const string& data) {
//        Node* current = head;
//        while (current != nullptr) {
//            if (current->Data == data) {
//                return true;
//            }
//            current = current->next;
//        }
//        return false;
//    }
//
//    // 5 Вычисление веса элемента (номер в очереди если есть либо -1)
//    int weight(const string& data) {
//        int count = 0;
//        Node* current = head;
//        while (current != nullptr) {
//            if (current->Data == data) {
//                return count;
//            }
//            current = current->next;
//            count++;
//        }
//        return -1;
//    }
//
//    // Перегрузка оператора + (последовательное соединение)
//    Queue operator+(const Queue& other) const {
//        Queue result(*this); // Используем конструктор копирования
//        Node* current = other.head;
//        while (current != nullptr) {
//            result.enqueue(current->Data);
//            current = current->next;
//        }
//        return result;
//    }
//
//    // Перегрузка оператора * (перекрестное соединение)
//    Queue operator*(const Queue& other) const {
//        Queue result;
//        Node* current1 = head;
//        Node* current2 = other.head;
//        while (current1 != nullptr || current2 != nullptr) {
//            if (current1 != nullptr) {
//                result.enqueue(current1->Data);
//                current1 = current1->next;
//            }
//            if (current2 != nullptr) {
//                result.enqueue(current2->Data);
//                current2 = current2->next;
//            }
//        }
//        return result;
//    }
//
//    // Перегрузка унарного оператора - (разворот)
//    Queue operator-() const {
//        Queue result;
//        Node* current = head;
//
//        // Разворот очереди - вставка в начало новой очереди
//        while (current != nullptr) {
//            result.enqueueAtFront(current->Data); // Вставка в начало
//            current = current->next;
//        }
//        return result;
//    }
//
//    // Метод для вставки элемента в начало очереди
//    void enqueueAtFront(const string& data) {
//        Node* newNode = new Node(data);
//        newNode->next = head;
//        head = newNode;
//    }
//
//    // Метод для вставки элемента после указанного
//    void YaZanimal(const string& after, const string& data) {
//        Node* current = head;
//        while (current != nullptr) {
//            if (current->Data == after) {
//                Node* newNode = new Node(data);
//                newNode->next = current->next;
//                current->next = newNode;
//                return;
//            }
//            current = current->next;
//        }
//    }
//
//    // Метод для печати очереди
//    void print() const {
//        Node* current = head;
//        while (current != nullptr) {
//            cout << current->Data << " ";
//            current = current->next;
//        }
//        cout << endl;
//    }
//};
//
//int main() {
//    setlocale(LC_ALL, "");
//    Queue queue1;
//    queue1.enqueue("a1");
//    queue1.enqueue("a2");
//    queue1.enqueue("a3");
//    queue1.enqueue("a4");
//    cout << "Очередь 1: ";
//    queue1.print(); // Вывод очереди 1
//
//    Queue queue2;
//    queue2.enqueue("b1");
//    queue2.enqueue("b2");
//    cout << "Очередь 2: ";
//    queue2.print(); // Вывод очереди 2
//
//    // Последовательное соединение (+):
//    Queue queue3 = queue1 + queue2;
//    cout << "Очередь 3 (queue1 + queue2): ";
//    queue3.print(); // Вывод очереди 3
//
//    // Перекрестное соединение (*):
//    Queue queue4 = queue1 * queue2;
//    cout << "Очередь 4 (queue1 * queue2): ";
//    queue4.print(); // Вывод очереди 4
//
//    // Разворот (-):
//    Queue queue5 = -queue1;
//    cout << "Очередь 5 (разворот queue1): ";
//    queue5.print(); // Вывод очереди 5
//
//    // YaZanimal
//    queue1.YaZanimal("a2", "b1");
//    cout << "Очередь 1 после YaZanimal: ";
//    queue1.print(); // Вывод очереди 1 после YaZanimal
//
//    return 0;
//}