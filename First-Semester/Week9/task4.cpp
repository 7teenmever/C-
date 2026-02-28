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

public:
    SinglyLinkedList() : head(nullptr) {}

    ~SinglyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
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

    Node* findMiddleTwoPass() {
        if (head == nullptr) {
            return nullptr;
        }

        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            ++count;
            current = current->next;
        }

        int midIndex = count / 2;
        current = head;
        for (int i = 0; i < midIndex; ++i) {
            current = current->next;
        }

        return current;
    }

    Node* findMiddleSinglePass() {
        if (head == nullptr) {
            return nullptr;
        }

        Node* slow = head;
        Node* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    void display() {
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

int main() {
    SinglyLinkedList list;
    for (int i = 1; i <= 7; ++i) {
        list.insertAtTail(i);
    }

    cout << "List: ";
    list.display();

    Node* mid1 = list.findMiddleTwoPass();
    Node* mid2 = list.findMiddleSinglePass();

    cout << "Middle (two-pass): " << (mid1 ? to_string(mid1->data) : "None") << endl;
    cout << "Middle (single-pass): " << (mid2 ? to_string(mid2->data) : "None") << endl;

    return 0;
}
