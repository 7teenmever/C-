#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (root == nullptr) {
        return result;
    }

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = static_cast<int>(q.size());
        vector<int> level;

        for (int i = 0; i < levelSize; ++i) {
            TreeNode* node = q.front();
            q.pop();
            level.push_back(node->val);

            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }

        result.push_back(level);
    }

    return result;
}

void printLevels(const vector<vector<int>>& levels) {
    cout << "[";
    for (size_t i = 0; i < levels.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < levels[i].size(); ++j) {
            cout << levels[i][j];
            if (j + 1 < levels[i].size()) {
                cout << ",";
            }
        }
        cout << "]";
        if (i + 1 < levels.size()) {
            cout << ",";
        }
    }
    cout << "]" << endl;
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
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    vector<vector<int>> levels = levelOrder(root);
    printLevels(levels);  // Expected: [[3],[9,20],[15,7]]

    deleteTree(root);
    return 0;
}
