#include <iostream>
#include <string>

using namespace std;

struct Node {
    string Data;
    Node* next;

    Node(const string& data) : Data(data), next(nullptr) {}
};

class Queue {
private:
    Node* head;

public:
    Queue() : head(nullptr) {}

    // ����������� �����������
    Queue(const Queue& other) {
        head = nullptr;
        Node* current = other.head;
        while (current != nullptr) {
            enqueue(current->Data);
            current = current->next;
        }
    }

    // 1) ���������� �������� (� ����� ������)
    void enqueue(const string& data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* last = head;
            while (last->next != nullptr) {
                last = last->next;
            }
            last->next = newNode;
        }
    }

    // 2) �������� � ���������� �������� (�� ������)
    string dequeue() {
        if (head == nullptr) {
            throw runtime_error("Queue is empty");
        }
        Node* temp = head;
        string data = head->Data;
        head = head->next;
        delete temp;
        return data;
    }

    // 3) ����� �������� � (������� T/F)
    bool search(const string& data) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->Data == data) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // 4) ���������� ���� �������� � (����� � ������� ���� ���� ���� -1)
    int weight(const string& data) const {
        Node* current = head;
        int weight = 0;
        while (current != nullptr) {
            if (current->Data == data) {
                return weight;
            }
            weight++;
            current = current->next;
        }
        return -1;
    }

    // ��������������� ��������:

    // 1) + ��� ���������������� ���������� ���� �������
    Queue operator+(const Queue& other) const {
        Queue result(*this);
        Node* current = other.head;
        while (current != nullptr) {
            result.enqueue(current->Data);
            current = current->next;
        }
        return result;
    }

    // 2) * ��� ������������ ���������� � ������������� �������
    Queue operator*(const Queue& other) const {
        Queue result;
        Node* current1 = head;
        Node* current2 = other.head;
        while (current1 != nullptr || current2 != nullptr) {
            if (current1 != nullptr) {
                result.enqueue(current1->Data);
                current1 = current1->next;
            }
            if (current2 != nullptr) {
                result.enqueue(current2->Data);
                current2 = current2->next;
            }
        }
        return result;
    }

    // 3) ������� �������� � ��� �������� �������
    Queue operator-() const {
        Queue result;
        Node* current = head;
        while (current != nullptr) {
            result.enqueueAtFront(current->Data);
            current = current->next;
        }
        return result;
    }

    // ������� 2) (�) DolgoZdat(a) ������� ������� ������� � �� ������ ����� ������� ���� �� ����.
    void DolgoZdat(const string& data) {
        if (head == nullptr) {
            return;
        }

        if (head->Data == data) {
            dequeue();
            return;
        }

        Node* current = head;
        Node* prev = nullptr;
        while (current != nullptr) {
            if (current->Data == data) {
                prev->next = current->next;
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void enqueueAtFront(const string& data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }

    // ����� ������� ��� ��������
    void print() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->Data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    setlocale(LC_ALL, "");
    Queue q1;
    q1.enqueue("a1");
    q1.enqueue("a2");
    q1.enqueue("a3");
    q1.enqueue("a4");

    cout << "Q1: ";
    q1.print();

    Queue q2;
    q2.enqueue("b1");
    q2.enqueue("b2");

    cout << "Q2: ";
    q2.print();

    // ������������ ��������

    Queue q3 = q1 + q2;
    cout << "Q1 + Q2: ";
    q3.print();

    Queue q4 = q1 * q2;
    cout << "Q1 * Q2: ";
    q4.print();

    Queue q5 = -q1;
    cout << "-Q1: ";
    q5.print(); // ����� q5 �����: a4 a3 a2 a1

    q1.DolgoZdat("a3");
    cout << "Q1 ����� DolgoZdat(a3): ";
    q1.print();

    return 0;
}
