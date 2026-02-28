#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
private:
    void serializeHelper(TreeNode* root, ostringstream& out) {
        if (root == nullptr) {
            out << "null,";
            return;
        }
        out << root->val << ",";
        serializeHelper(root->left, out);
        serializeHelper(root->right, out);
    }

    TreeNode* deserializeHelper(vector<string>& tokens, int& index) {
        if (index >= static_cast<int>(tokens.size()) || tokens[index] == "null") {
            ++index;
            return nullptr;
        }

        TreeNode* node = new TreeNode(stoi(tokens[index++]));
        node->left = deserializeHelper(tokens, index);
        node->right = deserializeHelper(tokens, index);
        return node;
    }

public:
    string serialize(TreeNode* root) {
        ostringstream out;
        serializeHelper(root, out);
        return out.str();
    }

    TreeNode* deserialize(string data) {
        vector<string> tokens;
        string token;
        stringstream ss(data);

        while (getline(ss, token, ',')) {
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }

        int index = 0;
        return deserializeHelper(tokens, index);
    }
};

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
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    Codec codec;
    string encoded = codec.serialize(root);
    cout << "Serialized: " << encoded << endl;

    TreeNode* decoded = codec.deserialize(encoded);
    cout << "Serialized again after deserialization: " << codec.serialize(decoded) << endl;

    deleteTree(root);
    deleteTree(decoded);
    return 0;
}
