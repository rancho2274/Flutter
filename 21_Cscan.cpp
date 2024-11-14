#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to simulate C-SCAN disk scheduling
void cScanDiskScheduling(vector<int> requests, int head, int diskSize) {
    vector<int> left, right;
    int totalSeekTime = 0;

    // Requests on the left and right side of the head
    left.push_back(0); // Start boundary
    right.push_back(diskSize - 1); // End boundary

    for (int i = 0; i < requests.size(); i++) {
        if (requests[i] < head) {
            left.push_back(requests[i]);
        } else {
            right.push_back(requests[i]);
        }
    }

    // Sort the left and right vectors
    sort(left.begin(), left.end()); // Ascending for left
    sort(right.begin(), right.end()); // Ascending for right

    // Print the header for the detailed seek time
    cout << "\nC-SCAN Disk Scheduling\n";
    cout << "Request      Seek Time\n";
    cout << "------------------------------------\n";

    int currentPosition = head;

    // Process requests on the right side first
    for (int i = 0; i < right.size(); i++) {
        int seek = abs(currentPosition - right[i]);
        totalSeekTime += seek;
        if (i > 0 || right[i] != diskSize - 1) { // Avoid printing the boundary
            cout << right[i] << "\t\t" << seek << "\n";
        }
        currentPosition = right[i];
    }

    // Jump to the start of the disk
    currentPosition = 0;
    totalSeekTime += (diskSize - 1); // Add seek time for jumping to the start

    // Process requests on the left side
    for (int i = 1; i < left.size(); i++) { // Start from 1 to avoid the 0 boundary
        int seek = abs(currentPosition - left[i]);
        totalSeekTime += seek;
        cout << left[i] << "\t\t" << seek << "\n";
        currentPosition = left[i];
    }

    // Print total seek time
    cout << "\nTotal Seek Time: " << totalSeekTime << "\n";
}

int main() {
    int numRequests, head, diskSize;

    cout << "Enter the disk size: ";
    cin >> diskSize;

    cout << "Enter the number of requests: ";
    cin >> numRequests;

    vector<int> requests(numRequests);
    cout << "Enter the request queue: ";
    for (int i = 0; i < numRequests; i++) {
        cin >> requests[i];
    }

    cout << "Enter the initial head position: ";
    cin >> head;

    // Simulate C-SCAN disk scheduling
    cScanDiskScheduling(requests, head, diskSize);

    return 0;
}
/*Enter the disk size: 200
Enter the number of requests: 8
Enter the request queue: 87 160 40 140 36 72 66 15
Enter the initial head position: 60*/