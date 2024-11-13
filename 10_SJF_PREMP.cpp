#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Process {
    string name;
    int at; // Arrival time
    int bt; // Burst time
    int ct; // Completion time
    int tat; // Turnaround time
    int wt; // Waiting time
    int remaining_bt; // Remaining burst time
};

bool compareArrival(Process p1, Process p2) {
    return p1.at < p2.at;
}

void printStatus(int currentTime, const vector<string>& rq, const string& currentProcess, const string& status) {
    cout << currentTime << "\t";
    for (const auto& p : rq) cout << p << " ";
    cout << "\t\t" << currentProcess << "\t\t" << status << endl;
}

void sjf_preemptive(vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0, completed = 0;
    vector<bool> done(n, false);
    vector<string> rq;

    cout << "Time\tReady Queue\tRunning Process\tStatus" << endl;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (!done[i] && processes[i].at <= currentTime && find(rq.begin(), rq.end(), processes[i].name) == rq.end()) {
                rq.push_back(processes[i].name);
            }
        }

        if (!rq.empty()) {
            auto it = min_element(rq.begin(), rq.end(), [&](const string& a, const string& b) {
                return processes[find_if(processes.begin(), processes.end(), [&](Process p) { return p.name == a; }) - processes.begin()].remaining_bt <
                       processes[find_if(processes.begin(), processes.end(), [&](Process p) { return p.name == b; }) - processes.begin()].remaining_bt;
            });

            int idx = find_if(processes.begin(), processes.end(), [&](Process p) { return p.name == *it; }) - processes.begin();

            processes[idx].remaining_bt--;

            if (processes[idx].remaining_bt == 0) {
                rq.erase(it);
                processes[idx].ct = currentTime + 1;
                processes[idx].tat = processes[idx].ct - processes[idx].at;
                processes[idx].wt = processes[idx].tat - processes[idx].bt;
                done[idx] = true;
                completed++;
                printStatus(currentTime + 1, rq, processes[idx].name, "Completed");
            } else {
                printStatus(currentTime, rq, processes[idx].name, "Executing");
            }

            currentTime++;
        } else {
            printStatus(currentTime, rq, "Idle", "No process completed");
            currentTime++;
        }
    }

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].name << "\t" << processes[i].at << "\t" << processes[i].bt << "\t" << processes[i].ct << "\t" << processes[i].tat << "\t" << processes[i].wt << endl;
    }
}

int main() {
    int num;
    cout << "Enter the total number of processes: ";
    cin >> num;
    vector<Process> processes(num);

    cout << "Enter process names, arrival times, and burst times: \n";
    for (int i = 0; i < num; i++) {
        cin >> processes[i].name >> processes[i].at >> processes[i].bt;
        processes[i].remaining_bt = processes[i].bt;
    }

    sort(processes.begin(), processes.end(), compareArrival);
    sjf_preemptive(processes);

    return 0;
}

