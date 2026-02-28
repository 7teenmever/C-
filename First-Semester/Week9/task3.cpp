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
        removeCycle();

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

    Node* getNodeAtPosition(int pos) {
        if (pos <= 0) {
            return nullptr;
        }

        Node* current = head;
        int index = 1;
        while (current != nullptr && index < pos) {
            current = current->next;
            ++index;
        }
        return current;
    }

    void createCycle(int fromPos, int toPos) {
        Node* fromNode = getNodeAtPosition(fromPos);
        Node* toNode = getNodeAtPosition(toPos);

        if (fromNode != nullptr && toNode != nullptr) {
            fromNode->next = toNode;
        }
    }

    bool hasCycle() {
        Node* slow = head;
        Node* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                return true;
            }
        }

        return false;
    }

    Node* detectCycleStart() {
        Node* slow = head;
        Node* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                Node* start = head;
                while (start != slow) {
                    start = start->next;
                    slow = slow->next;
                }
                return start;
            }
        }

        return nullptr;
    }

    void removeCycle() {
        Node* cycleStart = detectCycleStart();
        if (cycleStart == nullptr) {
            return;
        }

        Node* ptr = cycleStart;
        while (ptr->next != cycleStart) {
            ptr = ptr->next;
        }
        ptr->next = nullptr;
    }

    void displaySafe(int maxNodes = 20) {
        Node* current = head;
        int count = 0;
        while (current != nullptr && count < maxNodes) {
            cout << current->data;
            current = current->next;
            ++count;
            if (current != nullptr && count < maxNodes) {
                cout << " -> ";
            }
        }
        if (current != nullptr) {
            cout << " -> ...";
        }
        cout << endl;
    }
};

int main() {
    SinglyLinkedList list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);
    list.insertAtTail(4);

    list.createCycle(4, 2);  // node4->next = node2

    cout << "Has cycle: " << (list.hasCycle() ? "Yes" : "No") << endl;

    Node* start = list.detectCycleStart();
    if (start != nullptr) {
        cout << "Cycle starts at node with value: " << start->data << endl;
    }

    list.removeCycle();
    cout << "Cycle removed. Has cycle: " << (list.hasCycle() ? "Yes" : "No") << endl;

    cout << "List after cycle removal: ";
    list.displaySafe();

    return 0;
}
