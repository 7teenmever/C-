#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* findNode(TreeNode* root, int value) {
    while (root != nullptr) {
        if (value == root->val) {
            return root;
        }
        if (value < root->val) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return nullptr;
}

TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    if (root == nullptr || p == nullptr) {
        return nullptr;
    }

    if (p->right != nullptr) {
        TreeNode* current = p->right;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    TreeNode* successor = nullptr;
    TreeNode* current = root;

    while (current != nullptr) {
        if (p->val < current->val) {
            successor = current;
            current = current->left;
        } else if (p->val > current->val) {
            current = current->right;
        } else {
            break;
        }
    }

    return successor;
}

void deleteTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    TreeNode* root = new TreeNode(20);
    root->left = new TreeNode(10);
    root->right = new TreeNode(30);
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(15);
    root->right->left = new TreeNode(25);
    root->right->right = new TreeNode(35);

    TreeNode* p = findNode(root, 15);
    TreeNode* succ = inorderSuccessor(root, p);
    cout << "Successor of 15: " << (succ ? to_string(succ->val) : "None") << endl;

    p = findNode(root, 35);
    succ = inorderSuccessor(root, p);
    cout << "Successor of 35: " << (succ ? to_string(succ->val) : "None") << endl;

    deleteTree(root);
    return 0;
}
