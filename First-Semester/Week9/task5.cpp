#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    explicit Node(int val) : data(val), next(nullptr) {}
};

class SinglyLinkedList {
private:
    Node* head;

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }

    void copyFrom(const SinglyLinkedList& other) {
        Node* current = other.head;
        while (current != nullptr) {
            insertAtTail(current->data);
            current = current->next;
        }
    }

public:
    SinglyLinkedList() : head(nullptr) {}

    ~SinglyLinkedList() {
        clear();
    }

    SinglyLinkedList(const SinglyLinkedList& other) : head(nullptr) {
        copyFrom(other);
    }

    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }

    SinglyLinkedList(SinglyLinkedList&& other) noexcept : head(other.head) {
        other.head = nullptr;
    }

    SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            other.head = nullptr;
        }
        return *this;
    }

    void insertAtTail(int val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    Node* getHead() const {
        return head;
    }

    void display() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << " -> ";
            }
            current = current->next;
        }
        cout << endl;
    }
};

SinglyLinkedList mergeSortedLists(SinglyLinkedList& list1, SinglyLinkedList& list2) {
    SinglyLinkedList merged;

    Node* p1 = list1.getHead();
    Node* p2 = list2.getHead();

    while (p1 != nullptr && p2 != nullptr) {
        if (p1->data <= p2->data) {
            merged.insertAtTail(p1->data);
            p1 = p1->next;
        } else {
            merged.insertAtTail(p2->data);
            p2 = p2->next;
        }
    }

    while (p1 != nullptr) {
        merged.insertAtTail(p1->data);
        p1 = p1->next;
    }

    while (p2 != nullptr) {
        merged.insertAtTail(p2->data);
        p2 = p2->next;
    }

    return merged;
}

int main() {
    SinglyLinkedList list1;
    list1.insertAtTail(1);
    list1.insertAtTail(3);
    list1.insertAtTail(5);

    SinglyLinkedList list2;
    list2.insertAtTail(2);
    list2.insertAtTail(4);
    list2.insertAtTail(6);
    list2.insertAtTail(8);

    cout << "List1: ";
    list1.display();

    cout << "List2: ";
    list2.display();

    SinglyLinkedList merged = mergeSortedLists(list1, list2);
    cout << "Merged: ";
    merged.display();

    return 0;
}
