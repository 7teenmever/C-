#include <iostream>
using namespace std;

class DNode {
public:
    int data;
    DNode* next;
    DNode* prev;

    explicit DNode(int val) : data(val), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private:
    DNode* head;
    DNode* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        DNode* current = head;
        while (current != nullptr) {
            DNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void insertAtHead(int val) {
        DNode* newNode = new DNode(val);
        if (head == nullptr) {
            head = tail = newNode;
            return;
        }

        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    void insertAtTail(int val) {
        DNode* newNode = new DNode(val);
        if (tail == nullptr) {
            head = tail = newNode;
            return;
        }

        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    void insertAtPosition(int val, int pos) {
        if (pos <= 1 || head == nullptr) {
            insertAtHead(val);
            return;
        }

        DNode* current = head;
        int index = 1;
        while (current->next != nullptr && index < pos - 1) {
            current = current->next;
            ++index;
        }

        if (current == tail) {
            insertAtTail(val);
            return;
        }

        DNode* newNode = new DNode(val);
        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;
    }

    void deleteNode(int val) {
        if (head == nullptr) {
            return;
        }

        DNode* current = head;
        while (current != nullptr && current->data != val) {
            current = current->next;
        }

        if (current == nullptr) {
            return;
        }

        if (current == head && current == tail) {
            head = tail = nullptr;
        } else if (current == head) {
            head = head->next;
            head->prev = nullptr;
        } else if (current == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        delete current;
    }

    void displayForward() {
        DNode* current = head;
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << " <-> ";
            }
            current = current->next;
        }
        cout << endl;
    }

    void displayBackward() {
        DNode* current = tail;
        while (current != nullptr) {
            cout << current->data;
            if (current->prev != nullptr) {
                cout << " <-> ";
            }
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    DoublyLinkedList dll;

    dll.insertAtHead(20);
    dll.insertAtHead(10);
    dll.insertAtTail(30);
    dll.insertAtTail(40);
    dll.insertAtPosition(25, 4);

    cout << "Forward: ";
    dll.displayForward();

    cout << "Backward: ";
    dll.displayBackward();

    dll.deleteNode(25);
    cout << "After deleting 25 (forward): ";
    dll.displayForward();

    return 0;
}
