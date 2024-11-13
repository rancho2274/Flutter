#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to simulate SCAN disk scheduling
void scanDiskScheduling(vector<int> requests, int head, int diskSize, string direction) {
    vector<int> left, right;
    int totalSeekTime = 0;

    // Requests on the left and right side of the head
    if (direction == "left") {
        left.push_back(0); // Start boundary
    } else {
        right.push_back(diskSize - 1); // End boundary
    }

    for (int i = 0; i < requests.size(); i++) {
        if (requests[i] < head) {
            left.push_back(requests[i]);
        } else {
            right.push_back(requests[i]);
        }
    }

    // Sort the left and right vectors
    sort(left.begin(), left.end(), greater<int>()); // Descending for left
    sort(right.begin(), right.end()); // Ascending for right

    // Print the header for the detailed seek time
    cout << "\nSCAN Disk Scheduling\n";
    cout << "Request      Seek Time\n";
    cout << "------------------------------------\n";

    int currentPosition = head;

    // Process requests based on the direction
    if (direction == "right") {
        // Process right side first
        for (int i = 0; i < right.size(); i++) {
            int seek = abs(currentPosition - right[i]);
            totalSeekTime += seek;
            if (i > 0 || right[i] != diskSize - 1) { // Avoid printing the boundary
                cout << right[i] << "\t\t" << seek << "\n";
            }
            currentPosition = right[i];
        }

        // Then process the left side
        for (int i = 0; i < left.size(); i++) {
            int seek = abs(currentPosition - left[i]);
            totalSeekTime += seek;
            if (i > 0 || left[i] != 0) { // Avoid printing the boundary
                cout << left[i] << "\t\t" << seek << "\n";
            }
            currentPosition = left[i];
        }
    } else if (direction == "left") {
        // Process left side first
        for (int i = 0; i < left.size(); i++) {
            int seek = abs(currentPosition - left[i]);
            totalSeekTime += seek;
            if (i > 0 || left[i] != 0) { // Avoid printing the boundary
                cout << left[i] << "\t\t" << seek << "\n";
            }
            currentPosition = left[i];
        }

        // Then process the right side
        for (int i = 0; i < right.size(); i++) {
            int seek = abs(currentPosition - right[i]);
            totalSeekTime += seek;
            if (i > 0 || right[i] != diskSize - 1) { // Avoid printing the boundary
                cout << right[i] << "\t\t" << seek << "\n";
            }
            currentPosition = right[i];
        }
    }

    // Print total seek time
    cout << "\nTotal Seek Time: " << totalSeekTime << "\n";
}

int main() {
    int numRequests, head, diskSize;
    string direction;

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

    cout << "Enter the direction (left/right): ";
    cin >> direction;

    // Simulate SCAN disk scheduling
    scanDiskScheduling(requests, head, diskSize, direction);

    return 0;
}
/*Enter the disk size: 200
Enter the number of requests: 8
Enter the request queue: 87 160 40 140 36 72 66 15
Enter the initial head position: 60
Enter the direction (left/right): right*/