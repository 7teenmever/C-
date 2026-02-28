#include <iostream>
#include <stack>
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

    void reverseIterative() {
        Node* prev = nullptr;
        Node* current = head;

        while (current != nullptr) {
            Node* nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }

        head = prev;
    }

    void reverseRecursive(Node* current, Node* prev) {
        if (current == nullptr) {
            head = prev;
            return;
        }

        Node* nextNode = current->next;
        current->next = prev;
        reverseRecursive(nextNode, current);
    }

    void reverseUsingStack() {
        if (head == nullptr || head->next == nullptr) {
            return;
        }

        stack<Node*> st;
        Node* current = head;

        while (current != nullptr) {
            st.push(current);
            current = current->next;
        }

        head = st.top();
        st.pop();
        current = head;

        while (!st.empty()) {
            current->next = st.top();
            st.pop();
            current = current->next;
        }

        current->next = nullptr;
    }

    Node* getHead() {
        return head;
    }
};

int main() {
    SinglyLinkedList list1;
    list1.insertAtTail(1);
    list1.insertAtTail(2);
    list1.insertAtTail(3);
    list1.insertAtTail(4);
    list1.insertAtTail(5);

    cout << "Original list: ";
    list1.display();

    list1.reverseIterative();
    cout << "Reversed (iterative): ";
    list1.display();

    SinglyLinkedList list2;
    list2.insertAtTail(1);
    list2.insertAtTail(2);
    list2.insertAtTail(3);
    list2.insertAtTail(4);
    list2.insertAtTail(5);

    list2.reverseRecursive(list2.getHead(), nullptr);
    cout << "Reversed (recursive): ";
    list2.display();

    SinglyLinkedList list3;
    list3.insertAtTail(1);
    list3.insertAtTail(2);
    list3.insertAtTail(3);
    list3.insertAtTail(4);
    list3.insertAtTail(5);

    list3.reverseUsingStack();
    cout << "Reversed (stack): ";
    list3.display();

    return 0;
}
