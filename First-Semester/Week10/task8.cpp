#include <climits>
#include <iostream>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

bool isValidBST(TreeNode* root) {
    stack<TreeNode*> st;
    TreeNode* current = root;
    long long prev = LLONG_MIN;

    while (current != nullptr || !st.empty()) {
        while (current != nullptr) {
            st.push(current);
            current = current->left;
        }

        current = st.top();
        st.pop();

        if (current->val <= prev) {
            return false;
        }
        prev = current->val;

        current = current->right;
    }

    return true;
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
    TreeNode* valid = new TreeNode(4);
    valid->left = new TreeNode(2);
    valid->right = new TreeNode(6);
    valid->left->left = new TreeNode(1);
    valid->left->right = new TreeNode(3);
    valid->right->left = new TreeNode(5);
    valid->right->right = new TreeNode(7);

    TreeNode* invalid = new TreeNode(5);
    invalid->left = new TreeNode(1);
    invalid->right = new TreeNode(4);
    invalid->right->left = new TreeNode(3);
    invalid->right->right = new TreeNode(6);

    cout << "Valid tree is BST: " << (isValidBST(valid) ? "Yes" : "No") << endl;
    cout << "Invalid tree is BST: " << (isValidBST(invalid) ? "Yes" : "No") << endl;

    deleteTree(valid);
    deleteTree(invalid);
    return 0;
}
