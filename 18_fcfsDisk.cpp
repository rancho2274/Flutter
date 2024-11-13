#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void FCFS_DiskScheduling(const vector<int>& requests, int head) {
    int total_seek_time = 0;
    int current_position = head;
    
    cout << setw(10) << "Request" << setw(15) << "Seek Time" << endl;
    cout << "------------------------------------" << endl;

    for (int i = 0; i < requests.size(); ++i) {
        int seek_time = abs(requests[i] - current_position);
        total_seek_time += seek_time;
        cout << setw(10) << requests[i] << setw(15) << seek_time << endl;
        current_position = requests[i];
    }

    cout << "\nTotal Seek Time: " << total_seek_time << endl;
}

int main() {
    int num_requests;
    int head;
    
    cout << "Enter the initial position of the disk head: ";
    cin >> head;

    cout << "Enter the number of disk requests: ";
    cin >> num_requests;
    
    vector<int> requests(num_requests);
    cout << "Enter the disk requests in sequence: ";
    for (int i = 0; i < num_requests; ++i) {
        cin >> requests[i];
    }

    cout << "\nFCFS Disk Scheduling\n";
    FCFS_DiskScheduling(requests, head);
    return 0;
}
/*Enter the initial position of the disk head: 60
Enter the number of disk requests: 8
Enter the disk requests in sequence: 87 160 40 140 36 72 66 15*/