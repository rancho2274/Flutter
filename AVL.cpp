#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int data) {
    Node* newNode = new Node();
    if (!newNode) {
        cout << "Memory error\n";
        return nullptr;
    }
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

Node* insertNode(Node* root, int data) {
    if (root == nullptr) {
        root = createNode(data);
        return root;
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }
    return root;
}

int height(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return max(height(node->left), height(node->right)) + 1;
}

int balanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

Node* leftRotation(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

Node* rightRotation(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

Node* leftRightRotation(Node* z) {
    z->left = leftRotation(z->left);
    return rightRotation(z);
}

Node* rightLeftRotation(Node* z) {
    z->right = rightRotation(z->right);
    return leftRotation(z);
}

Node* balanceTree(Node* root) {
    if (root == nullptr) {
        return root;
    }

    int bf = balanceFactor(root);

    if (bf > 1) {
        if (balanceFactor(root->left) > 0) {
            root = rightRotation(root);
        } else {
            root = leftRightRotation(root);
        }
    } else if (bf < -1) {
        if (balanceFactor(root->right) < 0) {
            root = leftRotation(root);
        } else {
            root = rightLeftRotation(root);
        }
    }

    return root;
}

bool isBalanced(Node* root) {
    if (root == nullptr) {
        return true;
    }

    int bf = balanceFactor(root);

    if (bf > 1 || bf < -1) {
        return false;
    }

    return isBalanced(root->left) && isBalanced(root->right);
}

void printInorder(Node* root) {
    if (root != nullptr) {
        printInorder(root->left);
        cout << root->data << " ";
        printInorder(root->right);
    }
}

int main() {
    Node* root = nullptr;
    int choice, data;

    do {
        cout << "1. Insert node\n";
        cout << "2. Balance the tree\n";
        cout << "3. Check if the tree is balanced and AVL\n";
        cout << "4. Print balanced tree (Inorder traversal)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter data to insert: ";
                cin >> data;
                root = insertNode(root, data);
                break;
            case 2:
                root = balanceTree(root);
                cout << "Tree balanced successfully.\n";
                break;
            case 3:
                if (isBalanced(root)) {
                    cout << "The tree is balanced and AVL.\n";
                } else {
                    cout << "The tree is not AVL.\n";
                }
                break;
            case 4:
                cout << "Balanced tree (Inorder traversal): ";
                printInorder(root);
                cout << endl;
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
