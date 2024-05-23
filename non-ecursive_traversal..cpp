#include <iostream>
#include <stack>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* createNode(int val) {
    return new Node(val);
}

void insert(Node*& root, int val) {
    if (root == nullptr) {
        root = createNode(val);
        return;
    }

    stack<Node*> s;
    s.push(root);

    while (!s.empty()) {
        Node* current = s.top();
        s.pop();

        if (val < current->data) {
            if (current->left == nullptr) {
                current->left = createNode(val);
                return;
            } else {
                s.push(current->left);
            }
        } else {
            if (current->right == nullptr) {
                current->right = createNode(val);
                return;
            } else {
                s.push(current->right);
            }
        }
    }
}

void inorder(Node* root) {
    if (root == nullptr) return;

    stack<Node*> s;
    Node* current = root;

    while (current != nullptr || !s.empty()) {
        while (current != nullptr) {
            s.push(current);
            current = current->left;
        }

        current = s.top();
        s.pop();
        cout << current->data << " ";
        current = current->right;
    }
}

void preorder(Node* root) {
    if (root == nullptr) return;

    stack<Node*> s;
    s.push(root);

    while (!s.empty()) {
        Node* current = s.top();
        s.pop();
        cout << current->data << " ";

        if (current->right) {
            s.push(current->right);
        }
        if (current->left) {
            s.push(current->left);
        }
    }
}

void postorder(Node* root) {
    if (root == nullptr) return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* current = s1.top();
        s1.pop();
        s2.push(current);

        if (current->left) {
            s1.push(current->left);
        }
        if (current->right) {
            s1.push(current->right);
        }
    }

    while (!s2.empty()) {
        Node* current = s2.top();
        s2.pop();
        cout << current->data << " ";
    }
}

int main() {
    Node* root = nullptr;
    int numNodes;
    cout << "Enter the number of nodes in the binary tree: ";
    cin >> numNodes;

    cout << "Enter the values of the nodes: ";
    for (int i = 0; i < numNodes; ++i) {
        int val;
        cin >> val;
        insert(root, val);
    }

    cout << "Inorder traversal of the binary tree: ";
    inorder(root);
    cout << endl;

    cout << "Preorder traversal of the binary tree: ";
    preorder(root);
    cout << endl;

    cout << "Postorder traversal of the binary tree: ";
    postorder(root);
    cout << endl;

    return 0;
}
