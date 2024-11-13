#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

int fifoPageFaults(const std::vector<int>& pages, int frames) {
    std::unordered_set<int> s;
    std::queue<int> indexes;
    int pageFaults = 0;

    for (int page : pages) {
        // If page is not present in the set
        if (s.find(page) == s.end()) {
            // Check if we have reached frame limit
            if (s.size() == frames) {
                // Remove the page at the front of the queue
                int front = indexes.front();
                indexes.pop();
                s.erase(front);
            }
            // Insert the current page
            s.insert(page);
            indexes.push(page);
            pageFaults++;

            // Display the current state of frames
            std::cout << "Frames: ";
            std::queue<int> temp = indexes;
            while (!temp.empty()) {
                std::cout << temp.front() << " ";
                temp.pop();
            }
            std::cout << "(Page Fault)\n";
        } else {
            // Display the current state of frames without a page fault
            std::cout << "Frames: ";
            std::queue<int> temp = indexes;
            while (!temp.empty()) {
                std::cout << temp.front() << " ";
                temp.pop();
            }
            std::cout << "(No Page Fault)\n";
        }
    }
    return pageFaults;
}

int main() {
    int frames;
    std::cout << "Enter number of frames: ";
    std::cin >> frames;

    int n;
    std::cout << "Enter number of pages: ";
    std::cin >> n;

    std::vector<int> pages(n);
    std::cout << "Enter page reference string: ";
    for (int i = 0; i < n; i++) {
        std::cin >> pages[i];
    }

    std::cout << "FIFO Page Faults: " << fifoPageFaults(pages, frames) << std::endl;
    return 0;
}
/*
sample input
4
11
1 2 3 4 5 1 2 6 7 3 8
*/