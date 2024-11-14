#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

int getProcessIndex(const vector<string>& procs, const string& proc) {
    for (int i = 0; i < procs.size(); i++) {
        if (procs[i] == proc) {
            return i;
        }
    }
    return -1;
}

void solve(vector<string>& procs, vector<string>& rq, vector<int>& at, vector<int>& bt, vector<int>& ct) {
    int time = 0;
    int i = 0;
    int n = procs.size();
    vector<int> tat(n), wt(n);
    cout << "Time\tReady Queue\tRunning Process\tStatus" << endl;

    while (i < n || !rq.empty()) {
        // Check for processes that have arrived
        while (i < n && at[i] <= time) {
            // Add to ready queue if arrived
            int index = -1;
            for (int j = 0; j < rq.size(); j++) {
                if (at[i] < at[getProcessIndex(procs, rq[j])] || (at[i] == at[getProcessIndex(procs, rq[j])] && bt[i] < bt[getProcessIndex(procs, rq[j])])) {
                    index = j;
                    break;
                }
            }
            if (index == -1) {
                rq.push_back(procs[i]);
            } else {
                rq.insert(rq.begin() + index, procs[i]);
            }
            i++;
        }

        // Display ready queue and status
        cout << time << "\t";
        for (const auto& p : rq) cout << p << " ";
        cout << "\t\t";

        // Process the first process in the ready queue
        if (!rq.empty()) {
            string current_process = rq.front();
            int index = getProcessIndex(procs, current_process);
            cout << current_process << "\t\t";
            time += bt[index];
            ct[index] = time;
            tat[index] = ct[index] - at[index];
            wt[index] = tat[index] - bt[index];
            cout << current_process << " completed" << endl;
            rq.erase(rq.begin());  // Remove the completed process from ready queue
        } else {
            cout << "Idle" << "\t\tNo process completed" << endl;
            time++;
        }
    }

    // Print the final table of AT, BT, CT, TAT, WT
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (int j = 0; j < n; ++j) {
        cout << procs[j] << "\t" << at[j] << "\t" << bt[j] << "\t" << ct[j] << "\t" << tat[j] << "\t" << wt[j] << endl;
    }
}

int main() {
    vector<string> rq, procs;
    vector<int> at, bt, ct;
    int num;
    cout << "Enter the total number of processes: ";  // 3 or 4 
    cin >> num;
    cout << "Enter process names: ";  // P1 P2 P3 OR P1 P2 P3 P4
    for (int i = 0; i < num; i++) {
        string str;
        cin >> str;
        procs.push_back(str);
    }
    cout << "Enter arrival times: "; // arrival time
    for (int i = 0; i < num; i++) {
        int ele;
        cin >> ele;
        at.push_back(ele);
    }
    cout << "Enter burst times: "; // burst time
    for (int i = 0; i < num; i++) {
        int ele;
        cin >> ele;
        bt.push_back(ele);
    }
    ct.resize(num, 0); // Completion times initialized to zero
    solve(procs, rq, at, bt, ct);
    return 0;
}

/*
3
P1 P2 P3
0 1 2
20 2 2  
*/
