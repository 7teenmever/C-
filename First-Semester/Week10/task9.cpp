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

vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (root == nullptr) {
        return result;
    }

    queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true;

    while (!q.empty()) {
        int levelSize = static_cast<int>(q.size());
        vector<int> level(levelSize);

        for (int i = 0; i < levelSize; ++i) {
            TreeNode* node = q.front();
            q.pop();

            int index = leftToRight ? i : (levelSize - 1 - i);
            level[index] = node->val;

            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }

        leftToRight = !leftToRight;
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
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    vector<vector<int>> levels = zigzagLevelOrder(root);
    printLevels(levels);

    deleteTree(root);
    return 0;
}
