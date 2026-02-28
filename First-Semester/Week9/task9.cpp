#include <iostream>
#include <unordered_map>
using namespace std;

class RandomNode {
public:
    int val;
    RandomNode* next;
    RandomNode* random;

    explicit RandomNode(int x) : val(x), next(nullptr), random(nullptr) {}
};

RandomNode* copyRandomList(RandomNode* head) {
    if (head == nullptr) {
        return nullptr;
    }

    unordered_map<RandomNode*, RandomNode*> cloneMap;

    RandomNode* current = head;
    while (current != nullptr) {
        cloneMap[current] = new RandomNode(current->val);
        current = current->next;
    }

    current = head;
    while (current != nullptr) {
        cloneMap[current]->next = current->next ? cloneMap[current->next] : nullptr;
        cloneMap[current]->random = current->random ? cloneMap[current->random] : nullptr;
        current = current->next;
    }

    return cloneMap[head];
}

void freeRandomList(RandomNode* head) {
    while (head != nullptr) {
        RandomNode* nextNode = head->next;
        delete head;
        head = nextNode;
    }
}

void displayRandomList(RandomNode* head) {
    RandomNode* current = head;
    while (current != nullptr) {
        cout << "Node " << current->val << " random-> ";
        if (current->random != nullptr) {
            cout << current->random->val;
        } else {
            cout << "null";
        }
        cout << endl;
        current = current->next;
    }
}

class Node {
public:
    int data;
    Node* next;

    explicit Node(int val) : data(val), next(nullptr) {}
};

Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* current = head;

    while (current != nullptr) {
        Node* nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }

    return prev;
}

bool isPalindrome(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return true;
    }

    Node* slow = head;
    Node* fast = head;

    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* secondHalf = reverseList(slow->next);
    Node* copySecondHalf = secondHalf;

    Node* firstHalf = head;
    bool palindrome = true;

    while (secondHalf != nullptr) {
        if (firstHalf->data != secondHalf->data) {
            palindrome = false;
            break;
        }
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }

    slow->next = reverseList(copySecondHalf);
    return palindrome;
}

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

    void rotate(int k) {
        if (head == nullptr || head->next == nullptr || k == 0) {
            return;
        }

        int length = 1;
        Node* tail = head;
        while (tail->next != nullptr) {
            tail = tail->next;
            ++length;
        }

        k %= length;
        if (k == 0) {
            return;
        }

        tail->next = head;
        int stepsToNewTail = length - k - 1;
        Node* newTail = head;
        for (int i = 0; i < stepsToNewTail; ++i) {
            newTail = newTail->next;
        }

        head = newTail->next;
        newTail->next = nullptr;
    }

    Node* getHead() {
        return head;
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
    cout << "1) Deep copy random list:" << endl;
    RandomNode* a = new RandomNode(1);
    RandomNode* b = new RandomNode(2);
    RandomNode* c = new RandomNode(3);

    a->next = b;
    b->next = c;

    a->random = c;
    b->random = a;
    c->random = b;

    RandomNode* copied = copyRandomList(a);
    displayRandomList(copied);

    freeRandomList(a);
    freeRandomList(copied);

    cout << "\n2) Palindrome check:" << endl;
    SinglyLinkedList palList;
    palList.insertAtTail(1);
    palList.insertAtTail(2);
    palList.insertAtTail(3);
    palList.insertAtTail(2);
    palList.insertAtTail(1);

    palList.display();
    cout << "Is palindrome: " << (isPalindrome(palList.getHead()) ? "Yes" : "No") << endl;

    cout << "\n3) Rotate list by k positions:" << endl;
    SinglyLinkedList rotateList;
    rotateList.insertAtTail(1);
    rotateList.insertAtTail(2);
    rotateList.insertAtTail(3);
    rotateList.insertAtTail(4);
    rotateList.insertAtTail(5);

    cout << "Before rotate: ";
    rotateList.display();

    rotateList.rotate(2);
    cout << "After rotate by 2: ";
    rotateList.display();

    return 0;
}
