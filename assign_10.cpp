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

void Print(vector<int>& vec) {
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

    return 0;
}
