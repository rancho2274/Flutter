#include <iostream>
#include <vector>
using namespace std;

void deadlockDetection(int processes, int resources, vector<vector<int>> allocation, vector<vector<int>> request, vector<int> available) {
    vector<bool> finish(processes, false);  // Initially, no process has finished
    vector<int> work = available;           // Initialize work with available resources
    vector<int> deadlockedProcesses;

    bool progress = true;
    while (progress) {
        progress = false;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool canProceed = true;
                for (int j = 0; j < resources; j++) {
                    if (request[i][j] > work[j]) { // Check if the request can be satisfied
                        canProceed = false;
                        break;
                    }
                }
                if (canProceed) {
                    for (int j = 0; j < resources; j++)
                        work[j] += allocation[i][j]; // Release resources
                    finish[i] = true;
                    progress = true;
                }
            }
        }
    }

    // Identify deadlocked processes
    for (int i = 0; i < processes; i++) {
        if (!finish[i]) {
            deadlockedProcesses.push_back(i);
        }
    }

    if (deadlockedProcesses.empty()) {
        cout << "No deadlock detected. The system is in a safe state." << endl;
    } else {
        cout << "Deadlock detected! Deadlocked processes: ";
        for (int pid : deadlockedProcesses) {
            cout << pid << " ";
        }
        cout << endl;
    }
}

int main() {
    int processes, resources;
    cout << "Enter number of processes: ";
    cin >> processes;
    cout << "Enter number of resources: ";
    cin >> resources;

    vector<vector<int>> allocation(processes, vector<int>(resources));
    vector<vector<int>> request(processes, vector<int>(resources));
    vector<int> available(resources);

    cout << "Enter Allocation Matrix:" << endl;
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            cin >> allocation[i][j];
        }
    }

    cout << "Enter Request Matrix:" << endl;
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            cin >> request[i][j];
        }
    }

    cout << "Enter Available Resources:" << endl;
    for (int j = 0; j < resources; j++) {
        cin >> available[j];
    }

    deadlockDetection(processes, resources, allocation, request, available);

    return 0;
}

/*
3 3


0 1 0
2 0 0
3 0 3

0 0 1
1 0 1
0 0 0

0 2 1
*/