// #include <iostream>
// #include <algorithm>
// #include <queue>
// using namespace std;

// // Node structure for the binary tree
// struct Node {
//     int data;
//     Node* left;
//     Node* right;
// };

// // Function to create a new node
// Node* createNode(int value) {
//     Node* newNode = new Node();
//     newNode->data = value;
//     newNode->left = newNode->right = nullptr;
//     return newNode;
// }

// // Function to calculate the height of a tree
// int height(Node* root) {
//     if (root == nullptr)
//         return 0;
//     return max(height(root->left), height(root->right)) + 1;
// }

// // Function to calculate the balance factor of a node
// int balanceFactor(Node* root) {
//     if (root == nullptr)
//         return 0;
//     return height(root->left) - height(root->right);
// }

// // Function to insert a value into the binary tree
// Node* insertNode(Node* root, int value) {
//     if (root == nullptr)
//         return createNode(value);
    
//     if (value < root->data)
//         root->left = insertNode(root->left, value);
//     else if (value > root->data)
//         root->right = insertNode(root->right, value);
    
//     // Calculate balance factor after each insertion
//     cout << "Balance Factor after inserting " << value << ": " << balanceFactor(root) << endl;

//     return root;
// }

// // Function to perform left rotation
// Node* leftRotation(Node* root) {
//     Node* newRoot = root->right;
//     root->right = newRoot->left;
//     newRoot->left = root;
//     return newRoot;
// }

// // Function to perform right rotation
// Node* rightRotation(Node* root) {
//     Node* newRoot = root->left;
//     root->left = newRoot->right;
//     newRoot->right = root;
//     return newRoot;
// }

// // Function to identify rotation cases for AVL balancing
// Node* avlBalancing(Node* root) {
//     int bf = balanceFactor(root);

//     if (abs(bf) <= 1)
//         return root; // Tree is balanced

//     if (bf > 1) {
//         if (balanceFactor(root->left) < 0) {
//             // LR Rotation Case
//             root->left = leftRotation(root->left);
//         }
//         // LL Rotation Case
//         root = rightRotation(root);
//     } else {
//         if (balanceFactor(root->right) > 0) {
//             // RL Rotation Case
//             root->right = rightRotation(root->right);
//         }
//         // RR Rotation Case
//         root = leftRotation(root);
//     }
//     return root;
// }

// // Function to perform level order traversal (BFS) of the tree
// void levelOrderTraversal(Node* root) {
//     if (root == nullptr)
//         return;

//     queue<Node*> q;
//     q.push(root);

//     while (!q.empty()) {
//         Node* current = q.front();
//         q.pop();
//         cout << current->data << " ";

//         if (current->left != nullptr)
//             q.push(current->left);
//         if (current->right != nullptr)
//             q.push(current->right);
//     }
// }

// int main() {
//     Node* root = nullptr;
//     int n, value;

//     cout << "Enter the number of nodes in the binary tree: ";
//     cin >> n;

//     cout << "Enter the values of the nodes: ";
//     for (int i = 0; i < n; ++i) {
//         cin >> value;
//         root = insertNode(root, value);
//         // Rebalance the tree after each insertion
//         root = avlBalancing(root);
//     }

//     cout << "Tree (Level Order Traversal): ";
//     levelOrderTraversal(root);
//     cout << endl;

//     return 0;
// }
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

void printBalanceFactors(Node* root) {
    if (root != nullptr) {
        printBalanceFactors(root->left);
        cout << "Node " << root->data << " has balance factor " << balanceFactor(root) << endl;
        printBalanceFactors(root->right);
    }
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

void checkAVL(Node* root) {
    if (isBalanced(root)) {
        cout << "The tree is balanced and AVL.\n";
    } else {
        cout << "The tree is not AVL.\n";

        int bf = balanceFactor(root);

        if (bf > 1) {
            if (balanceFactor(root->left) > 0) {
                cout << "Left-Left rotation required.\n";
            } else {
                cout << "Left-Right rotation required.\n";
            }
        } else {
            if (balanceFactor(root->right) < 0) {
                cout << "Right-Right rotation required.\n";
            } else {
                cout << "Right-Left rotation required.\n";
            }
        }
    }
}

int main() {
    Node* root = nullptr;
    int choice, data;

    do {
        cout << "1. Insert node\n";
        cout << "2. Check if the tree is balanced and AVL\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter data to insert: ";
                cin >> data;
                root = insertNode(root, data);
                printBalanceFactors(root);
                break;
            case 2:
                checkAVL(root);
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}