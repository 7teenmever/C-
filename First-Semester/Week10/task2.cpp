#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

class BST {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        Node(int val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    bool searchRecursive(Node* node, int value) {
        if (node == nullptr) {
            return false;
        }
        if (node->data == value) {
            return true;
        }
        if (value < node->data) {
            return searchRecursive(node->left, value);
        }
        return searchRecursive(node->right, value);
    }

    void inorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    Node* removeRecursive(Node* node, int value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (value < node->data) {
            node->left = removeRecursive(node->left, value);
        } else if (value > node->data) {
            node->right = removeRecursive(node->right, value);
        } else {
            if (node->left == nullptr) {
                Node* rightChild = node->right;
                delete node;
                return rightChild;
            }
            if (node->right == nullptr) {
                Node* leftChild = node->left;
                delete node;
                return leftChild;
            }

            Node* successor = node->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }
            node->data = successor->data;
            node->right = removeRecursive(node->right, successor->data);
        }

        return node;
    }

    void clear(Node* node) {
        if (node == nullptr) {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        clear(root);
    }

    void insert(int value) {
        Node* newNode = new Node(value);
        if (root == nullptr) {
            root = newNode;
            return;
        }

        Node* current = root;
        Node* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (value < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (value < parent->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }

    bool search(int value) {
        return searchRecursive(root, value);
    }

    void printInorder() {
        inorder(root);
        cout << endl;
    }

    void printPreorder() {
        preorder(root);
        cout << endl;
    }

    void printPostorder() {
        postorder(root);
        cout << endl;
    }

    void remove(int value) {
        root = removeRecursive(root, value);
    }
};

int main() {
    BST tree;

    srand(42);
    vector<int> inserted;
    for (int i = 0; i < 10; ++i) {
        int value = rand() % 100;
        inserted.push_back(value);
        tree.insert(value);
    }

    cout << "Inserted values: ";
    for (int v : inserted) {
        cout << v << " ";
    }
    cout << endl;

    cout << "Inorder (sorted): ";
    tree.printInorder();

    cout << "Preorder: ";
    tree.printPreorder();

    cout << "Postorder: ";
    tree.printPostorder();

    cout << "Search " << inserted[3] << ": " << (tree.search(inserted[3]) ? "Found" : "Not Found") << endl;
    cout << "Search 101: " << (tree.search(101) ? "Found" : "Not Found") << endl;

    tree.remove(inserted[0]);
    cout << "After deleting " << inserted[0] << " (inorder): ";
    tree.printInorder();

    return 0;
}
