#include <iostream>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

int treeHeightDFS(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = treeHeightDFS(root->left);
    int rightHeight = treeHeightDFS(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int treeHeightBFS(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }

    queue<TreeNode*> q;
    q.push(root);
    int height = 0;

    while (!q.empty()) {
        int levelSize = static_cast<int>(q.size());
        ++height;

        for (int i = 0; i < levelSize; ++i) {
            TreeNode* node = q.front();
            q.pop();

            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
    }

    return height;
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
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->left->left = new TreeNode(5);

    cout << "Height using DFS: " << treeHeightDFS(root) << endl;
    cout << "Height using BFS: " << treeHeightBFS(root) << endl;

    deleteTree(root);
    return 0;
}
