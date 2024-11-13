#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    int finishTime;
    int turnaroundTime;
    int waitingTime;
};

void displayResults(const vector<Process>& processes) {
    cout << "\nProcess ID | Finish Time | Turnaround Time | Waiting Time\n";
    for (const auto& p : processes) {
        cout << "    " << p.id << "       |      " << p.finishTime << "       |       " 
             << p.turnaroundTime << "       |     " << p.waitingTime << "\n";
    }
}

// Non-Preemptive Priority
void priorityNonPreemptive(vector<Process> processes) {
    vector<Process> result;
    int currentTime = 0;

    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    while (!processes.empty()) {
        vector<Process> readyQueue;
        for (const auto& p : processes) {
            if (p.arrivalTime <= currentTime) {
                readyQueue.push_back(p);
            }
        }

        if (readyQueue.empty()) {
            currentTime++;
            continue;
        }

        auto it = min_element(readyQueue.begin(), readyQueue.end(), [](const Process& a, const Process& b) {
            return a.priority < b.priority;
        });
        
        Process currentProcess = *it;
        currentProcess.finishTime = currentTime + currentProcess.burstTime;
        currentProcess.turnaroundTime = currentProcess.finishTime - currentProcess.arrivalTime;
        currentProcess.waitingTime = currentProcess.turnaroundTime - currentProcess.burstTime;
        
        currentTime = currentProcess.finishTime;
        
        result.push_back(currentProcess);

        processes.erase(remove_if(processes.begin(), processes.end(), [&](const Process& p) {
            return p.id == currentProcess.id;
        }), processes.end());
    }
    
    cout << "\nPriority (Non-Preemptive):";
    displayResults(result);
}

// Preemptive Priority
void priorityPreemptive(vector<Process> processes) {
    vector<Process> result;
    int currentTime = 0, completed = 0;
    int n = processes.size();
    vector<int> remainingBurstTime(n);
    for (int i = 0; i < n; i++) remainingBurstTime[i] = processes[i].burstTime;

    while (completed != n) {
        int idx = -1, highestPriority = 1e9;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && remainingBurstTime[i] > 0 && processes[i].priority < highestPriority) {
                highestPriority = processes[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            remainingBurstTime[idx]--;
            currentTime++;
            if (remainingBurstTime[idx] == 0) {
                completed++;
                processes[idx].finishTime = currentTime;
                processes[idx].turnaroundTime = currentTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
                result.push_back(processes[idx]);
            }
        } else {
            currentTime++;
        }
    }
    cout << "\nPriority Scheduling (Preemptive):";
    displayResults(result);
}

int main() {
    int n, quantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        cout << "\nEnter arrival time, burst time, and priority for process " << i + 1 << ": ";
        processes[i].id = i + 1;
        cin >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
    }

    priorityNonPreemptive(processes);
    priorityPreemptive(processes);

    return 0;
}
