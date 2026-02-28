#include <iostream>
#include <string>
using namespace std;

class DNode {
public:
    string url;
    DNode* prev;
    DNode* next;

    explicit DNode(const string& u) : url(u), prev(nullptr), next(nullptr) {}
};

class BrowserHistory {
private:
    DNode* head;
    DNode* current;

public:
    explicit BrowserHistory(string homepage) : head(new DNode(homepage)), current(head) {}

    ~BrowserHistory() {
        DNode* node = head;
        while (node != nullptr) {
            DNode* nextNode = node->next;
            delete node;
            node = nextNode;
        }
    }

    void visit(string url) {
        DNode* forwardNode = current->next;
        while (forwardNode != nullptr) {
            DNode* nextNode = forwardNode->next;
            delete forwardNode;
            forwardNode = nextNode;
        }

        current->next = nullptr;

        DNode* newNode = new DNode(url);
        newNode->prev = current;
        current->next = newNode;
        current = newNode;
    }

    string back(int steps) {
        while (steps > 0 && current->prev != nullptr) {
            current = current->prev;
            --steps;
        }
        return current->url;
    }

    string forward(int steps) {
        while (steps > 0 && current->next != nullptr) {
            current = current->next;
            --steps;
        }
        return current->url;
    }

    void displayHistory() {
        DNode* node = head;
        while (node != nullptr) {
            if (node == current) {
                cout << "[" << node->url << "]";
            } else {
                cout << node->url;
            }
            if (node->next != nullptr) {
                cout << " <-> ";
            }
            node = node->next;
        }
        cout << endl;
    }
};

int main() {
    BrowserHistory browser("homepage.com");

    browser.visit("news.com");
    browser.visit("search.com");
    browser.visit("videos.com");

    cout << "History: ";
    browser.displayHistory();

    cout << "Back 1: " << browser.back(1) << endl;
    cout << "Back 1: " << browser.back(1) << endl;
    cout << "Forward 1: " << browser.forward(1) << endl;

    browser.visit("mail.com");

    cout << "After visiting new page: ";
    browser.displayHistory();

    return 0;
}
