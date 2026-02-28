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

TreeNode* lowestCommonAncestorRecursive(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr || p == nullptr || q == nullptr) {
        return nullptr;
    }

    if (p->val < root->val && q->val < root->val) {
        return lowestCommonAncestorRecursive(root->left, p, q);
    }
    if (p->val > root->val && q->val > root->val) {
        return lowestCommonAncestorRecursive(root->right, p, q);
    }
    return root;
}

TreeNode* lowestCommonAncestorIterative(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr || p == nullptr || q == nullptr) {
        return nullptr;
    }

    TreeNode* current = root;
    while (current != nullptr) {
        if (p->val < current->val && q->val < current->val) {
            current = current->left;
        } else if (p->val > current->val && q->val > current->val) {
            current = current->right;
        } else {
            return current;
        }
    }

    return nullptr;
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
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);
    root->left->right->left = new TreeNode(3);
    root->left->right->right = new TreeNode(5);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);

    TreeNode* p = findNode(root, 2);
    TreeNode* q = findNode(root, 8);

    TreeNode* lcaRec = lowestCommonAncestorRecursive(root, p, q);
    TreeNode* lcaItr = lowestCommonAncestorIterative(root, p, q);

    cout << "LCA recursive of 2 and 8: " << (lcaRec ? to_string(lcaRec->val) : "None") << endl;
    cout << "LCA iterative of 2 and 8: " << (lcaItr ? to_string(lcaItr->val) : "None") << endl;

    p = findNode(root, 2);
    q = findNode(root, 4);

    lcaRec = lowestCommonAncestorRecursive(root, p, q);
    lcaItr = lowestCommonAncestorIterative(root, p, q);

    cout << "LCA recursive of 2 and 4: " << (lcaRec ? to_string(lcaRec->val) : "None") << endl;
    cout << "LCA iterative of 2 and 4: " << (lcaItr ? to_string(lcaItr->val) : "None") << endl;

    deleteTree(root);
    return 0;
}
