#include <iostream>
#include <vector>

using namespace std;

void InsertA(vector<int>& A, int n) {
    int i = n;
    int temp = A[n];
    while (i > 0 && temp > A[(i - 1) / 2]) {
        A[i] = A[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    A[i] = temp;
}

void DeleteNode(vector<int>& A, int value) {
    int i;
    for (i = 0; i < A.size(); ++i) {
        if (A[i] == value) {
            break;
        }
    }
    if (i == A.size()) {
        cout << "Node with value " << value << " not found in the heap." << endl;
        return;
    }

    A[i] = A.back(); // Replace the node to delete with the last element
    A.pop_back(); // Remove the last element

    // Adjust the heap to maintain max heap property
    int n = A.size();
    while (i < n) {
        int leftChildIndex = 2 * i + 1;
        int rightChildIndex = 2 * i + 2;
        int maxIndex = i;

        if (leftChildIndex < n && A[leftChildIndex] > A[maxIndex]) {
            maxIndex = leftChildIndex;
        }
        if (rightChildIndex < n && A[rightChildIndex] > A[maxIndex]) {
            maxIndex = rightChildIndex;
        }

        if (maxIndex != i) {
            swap(A[i], A[maxIndex]);
            i = maxIndex;
        } else {
            break;
        }
    }
}

void Print(const vector<int>& vec) {
    cout << "Max Heap: [";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

int main() {
    vector<int> heap;

    int numElements;
    cout << "Enter the number of elements you want to insert into the heap: ";
    cin >> numElements;

    for (int i = 0; i < numElements; i++) {
        int newElement;
        cout << "Enter element " << i + 1 << ": ";
        cin >> newElement;

        heap.push_back(newElement);  // Add new element at the end
        InsertA(heap, heap.size() - 1);  // Adjust the heap to maintain max heap property

        Print(heap);  // Print the heap after each insertion
    }

    // Delete elements from the heap
    char choice;
    while (true) {
        cout << "Do you want to delete a node from the heap? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            int nodeToDelete;
            cout << "Enter the value of the node you want to delete: ";
            cin >> nodeToDelete;
            DeleteNode(heap, nodeToDelete);
            Print(heap);
        } else {
            break;
        }
    }

    return 0;
}
