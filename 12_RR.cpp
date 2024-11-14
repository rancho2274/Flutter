#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void findWaitingTime(vector<int>& processes, int n, vector<int>& bt, vector<int>& at, vector<int>& wt, int quantum) {
    vector<int> rem_bt(n);
    for (int i = 0; i < n; i++)
        rem_bt[i] = bt[i];

    int t = 0;  // Track the current time

    while (1) {
        bool done = true;

        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0 && at[i] <= t) {  // Process must have arrived
                done = false;

                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    t += rem_bt[i];
                    wt[i] = t - bt[i] - at[i];  // Calculate waiting time considering arrival time
                    rem_bt[i] = 0;
                }
            }
        }

        if (done)
            break;

        // Move to the next time unit if no process has arrived
        for (int i = 0; i < n; i++) {
            if (at[i] > t) {
                t = at[i];
                break;
            }
        }
    }
}

void findTurnAroundTime(vector<int>& processes, int n, vector<int>& bt, vector<int>& wt, vector<int>& tat) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

void findAvgTime(vector<int>& processes, int n, vector<int>& bt, vector<int>& at, int quantum) {
    vector<int> wt(n), tat(n);
    int total_wt = 0, total_tat = 0;

    findWaitingTime(processes, n, bt, at, wt, quantum);
    findTurnAroundTime(processes, n, bt, wt, tat);

    cout << "PN\tAT\tBT\tWT\tTAT\n";

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << processes[i] << "\t" << at[i] << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i] << endl;
    }

    cout << "Average waiting time = " << (float)total_wt / n << endl;
    cout << "Average turn around time = " << (float)total_tat / n << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> processes(n);
    cout << "Enter process IDs: ";
    for (int i = 0; i < n; i++)
        cin >> processes[i];

    vector<int> burst_time(n);
    cout << "Enter burst times for each process: ";
    for (int i = 0; i < n; i++)
        cin >> burst_time[i];

    vector<int> arrival_time(n);
    cout << "Enter arrival times for each process: ";
    for (int i = 0; i < n; i++)
        cin >> arrival_time[i];

    int quantum;
    cout << "Enter time quantum: ";
    cin >> quantum;

    findAvgTime(processes, n, burst_time, arrival_time, quantum);
    return 0;
}
