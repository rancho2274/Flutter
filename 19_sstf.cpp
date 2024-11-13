#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include<climits>

using namespace std;

void SSTF_DiskScheduling(vector<int>& requests, int head) {
    int total_seek_time = 0;
    int current_position = head;
    vector<bool> visited(requests.size(), false);

    cout << setw(10) << "Request" << setw(15) << "Seek Time" << endl;
    cout << "------------------------------------" << endl;

    for (int i = 0; i < requests.size(); ++i) {
        int min_seek = INT_MAX;
        int closest_request_index = -1;

        for (int j = 0; j < requests.size(); ++j) {
            if (!visited[j]) {
                int seek_time = abs(requests[j] - current_position);
                if (seek_time < min_seek) {
                    min_seek = seek_time;
                    closest_request_index = j;
                }
            }
        }

        visited[closest_request_index] = true;
        total_seek_time += min_seek;
        cout << setw(10) << requests[closest_request_index] << setw(15) << min_seek << endl;
        current_position = requests[closest_request_index];
    }

    cout << "\nTotal Seek Time: " << total_seek_time << endl;
}

int main() {
    int num_requests, head;
    
    cout << "Enter the initial position of the disk head: ";
    cin >> head;

    cout << "Enter the number of disk requests: ";
    cin >> num_requests;
    
    vector<int> requests(num_requests);
    cout << "Enter the disk requests in sequence: ";
    for (int i = 0; i < num_requests; ++i) {
        cin >> requests[i];
    }

    cout << "\nSSTF Disk Scheduling\n";
    SSTF_DiskScheduling(requests, head);

    return 0;
}
/*Enter the initial position of the disk head: 60
Enter the number of disk requests: 8
Enter the disk requests in sequence: 87 160 40 140 36 72 66 15*/
