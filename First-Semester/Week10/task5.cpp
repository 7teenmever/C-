#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

bool hasPathSum(TreeNode* root, int targetSum) {
    if (root == nullptr) {
        return false;
    }

    if (root->left == nullptr && root->right == nullptr) {
        return targetSum == root->val;
    }

    int remaining = targetSum - root->val;
    return hasPathSum(root->left, remaining) || hasPathSum(root->right, remaining);
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
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(4);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(11);
    root->left->left->left = new TreeNode(7);
    root->left->left->right = new TreeNode(2);
    root->right->left = new TreeNode(13);
    root->right->right = new TreeNode(4);
    root->right->right->right = new TreeNode(1);

    cout << "Has path sum 22: " << (hasPathSum(root, 22) ? "Yes" : "No") << endl;
    cout << "Has path sum 26: " << (hasPathSum(root, 26) ? "Yes" : "No") << endl;
    cout << "Has path sum 18: " << (hasPathSum(root, 18) ? "Yes" : "No") << endl;

    deleteTree(root);
    return 0;
}
