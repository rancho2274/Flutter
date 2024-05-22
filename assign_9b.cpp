#include <iostream>
#include <vector>
#define EMPTY -1
#define DELETED -2
using namespace std;

const int MAX = 100;

int hashFunction(int key, int size) {
    return key % size;
}

void insert(int table[], int size, int key) {
    int hashIndex = hashFunction(key, size);
    int originalIndex = hashIndex;

    while (table[hashIndex] != EMPTY && table[hashIndex] != DELETED) {
        hashIndex = (hashIndex + 1) % size;
        if (hashIndex == originalIndex) {
            cout << "Hash table is full, cannot insert key " << key << endl;
            return;
        }
    }
    table[hashIndex] = key;
    cout << "Inserted key " << key << " at index " << hashIndex << endl;
}

bool search(int table[], int size, int key) {
    int hashIndex = hashFunction(key, size);
    int originalIndex = hashIndex;

    while (table[hashIndex] != EMPTY) {
        if (table[hashIndex] == key) {
            return true;
        }
        hashIndex = (hashIndex + 1) % size;
        if (hashIndex == originalIndex) {
            return false;
        }
    }
    return false;
}

void remove(int table[], int size, int key) {
    int hashIndex = hashFunction(key, size);
    int originalIndex = hashIndex;

    while (table[hashIndex] != EMPTY) {
        if (table[hashIndex] == key) {
            table[hashIndex] = DELETED;
            cout << "Deleted key " << key << " from index " << hashIndex << endl;
            return;
        }
        hashIndex = (hashIndex + 1) % size;
        if (hashIndex == originalIndex) {
            cout << "Key " << key << " not found in the hash table" << endl;
            return;
        }
    }
    cout << "Key " << key << " not found in the hash table" << endl;
}

void display(int table[], int size) {
    cout << "Hash Table:" << endl;
    for (int i = 0; i < size; ++i) {
        if (table[i] == EMPTY) {
            cout << "Index " << i << ": EMPTY" << endl;
        } else if (table[i] == DELETED) {
            cout << "Index " << i << ": DELETED" << endl;
        } else {
            cout << "Index " << i << ": " << table[i] << endl;
        }
    }
}

int main() {
    int size, choice, key;
    cout << "Enter the size of the hash table: ";
    cin >> size;
    int table[MAX];
    for (int i = 0; i < size; ++i) {
        table[i] = EMPTY;
    }

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Delete\n";
        cout << "4. Display\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the key to insert: ";
                cin >> key;
                insert(table, size, key);
                break;
            case 2:
                cout << "Enter the key to search: ";
                cin >> key;
                if (search(table, size, key)) {
                    cout << "Key " << key << " found in the hash table" << endl;
                } else {
                    cout << "Key " << key << " not found in the hash table" << endl;
                }
                break;
            case 3:
                cout << "Enter the key to delete: ";
                cin >> key;
                remove(table, size, key);
                break;
            case 4:
                display(table, size);
                break;
            case 5:
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
