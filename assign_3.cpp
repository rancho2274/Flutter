#include <iostream>
#include <queue>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* createNode(int val) {
    TreeNode* newNode = new TreeNode;
    newNode->data = val;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

TreeNode* insert(TreeNode* root, int val) {
    if (root == nullptr) {
        return createNode(val);
    }
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

int height(TreeNode* root) {
    if (root == nullptr) {
        return -1;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return max(leftHeight, rightHeight) + 1;
}

int countNodes(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    return countNodes(root->left) + countNodes(root->right) + 1;
}

int countLeafNodes(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    if (root->left == nullptr && root->right == nullptr) {
        return 1;
    }
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

int findMin(TreeNode* root) {
    if (root == nullptr) {
        cout << "Error: Tree is empty\n";
        return -1; 
    }
    while (root->left != nullptr) {
        root = root->left;
    }
    return root->data;
}

int findMax(TreeNode* root) {
    if (root == nullptr) {
        cout << "Error: Tree is empty\n";
        return -1; 
    }
    while (root->right != nullptr) {
        root = root->right;
    }
    return root->data;
}

void printLeafNodes(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    if (root->left == nullptr && root->right == nullptr) {
        cout << root->data << " ";
    }
    printLeafNodes(root->left);
    printLeafNodes(root->right);
}

void deleteTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void mirror(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    // Swap the left and right subtrees
    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    // Recursively apply mirror to left and right subtrees
    mirror(root->left);
    mirror(root->right);
}

int main() {
    TreeNode* root = nullptr;

    int n;
    cout << "Enter the number of elements to insert: ";
    cin >> n;
    cout << "Enter the elements:\n";
    for (int i = 0; i < n; i++) {
        int element;
        cin >> element;
        root = insert(root, element);
    }
    
    int h = height(root);
    cout << "Height of the BST: " << h << endl;

    int numNodes = countNodes(root);
    cout << "Number of nodes in the BST: " << numNodes << endl;

    int numLeafNodes = countLeafNodes(root);
    cout << "Number of leaf nodes in the BST: " << numLeafNodes << endl;

    int minNode = findMin(root);
    int maxNode = findMax(root);
    cout << "Minimum node value: " << minNode << endl;
    cout << "Maximum node value: " << maxNode << endl;

    cout << "Leaf nodes of the BST: ";
    printLeafNodes(root);
    cout << endl;

    cout << "Nodes of the BST level-wise: ";
    // Assuming printLevelWise function is defined elsewhere
    // printLevelWise(root);
    // cout << endl;

    // Mirror the tree and print its properties again
    mirror(root);
    cout << "Mirror image of the BST created." << endl;

    h = height(root);
    cout << "Height of the mirrored BST: " << h << endl;

    numNodes = countNodes(root);
    cout << "Number of nodes in the mirrored BST: " << numNodes << endl;

    numLeafNodes = countLeafNodes(root);
    cout << "Number of leaf nodes in the mirrored BST: " << numLeafNodes << endl;

    minNode = findMin(root);
    maxNode = findMax(root);
    cout << "Minimum node value in mirrored BST: " << minNode << endl;
    cout << "Maximum node value in mirrored BST: " << maxNode << endl;

    cout << "Leaf nodes of the mirrored BST: ";
    printLeafNodes(root);
    cout << endl;

    deleteTree(root);

    return 0;
}
