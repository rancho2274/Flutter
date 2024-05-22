#include <iostream>
using namespace std;


struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode* root;

    TreeNode* insertRecursive(TreeNode* node, int value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }

        if (value < node->data) {
            node->left = insertRecursive(node->left, value);
        } else if (value > node->data) {
            node->right = insertRecursive(node->right, value);
        }

        return node;
    }

    void inorderRecursive(TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        inorderRecursive(node->left);
        cout << node->data << " ";
        inorderRecursive(node->right);
    }

public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        destroyTree(root);
    }

    void insert(int value) {
        root = insertRecursive(root, value);
    }

    void inorderTraversal() {
        inorderRecursive(root);
        cout << endl;
    }

private:
    void destroyTree(TreeNode* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
};

int main() {
    BinaryTree tree;

    tree.insert(50);
    tree.insert(40);
    tree.insert(20);
    tree.insert(90);
    tree.insert(10);
    tree.insert(30);
    tree.insert(80);

    cout << "Inorder traversal: ";
    tree.inorderTraversal();

    return 0;
}
