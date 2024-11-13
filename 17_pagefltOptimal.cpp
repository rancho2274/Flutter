#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

int optimalPageFaults(const std::vector<int>& pages, int frames) {
    std::unordered_set<int> s;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];

        // If page is not present in memory
        if (s.find(page) == s.end()) {
            // If there is a page fault and frames are full
            if (s.size() == frames) {
                int farthest = i, pageToRemove = -1;
                for (int p : s) {
                    int j;
                    for (j = i + 1; j < pages.size(); j++) {
                        if (pages[j] == p) break;
                    }
                    if (j > farthest) {
                        farthest = j;
                        pageToRemove = p;
                    }
                }
                // Remove the farthest page
                s.erase(pageToRemove);
            }
            // Insert the current page into memory
            s.insert(page);
            pageFaults++;

            // Display the current state of frames
            std::cout << "Frames: ";
            for (int p : s) {
                std::cout << p << " ";
            }
            std::cout << "(Page Fault)\n";
        } else {
            // Display the current state of frames without a page fault
            std::cout << "Frames: ";
            for (int p : s) {
                std::cout << p << " ";
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

    std::cout << "Optimal Page Faults: " << optimalPageFaults(pages, frames) << std::endl;
    return 0;
}
/*
3
7
7 0 1 2 0 3 0
*/