#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>

int lruPageFaults(const std::vector<int>& pages, int frames) {
    std::unordered_map<int, std::list<int>::iterator> pageTable;
    std::list<int> lruList;
    int pageFaults = 0;

    for (int page : pages) {
        bool isPageFault = false; // Variable to track if this access causes a page fault

        // If page is not present
        if (pageTable.find(page) == pageTable.end()) {
            isPageFault = true; // Mark as a page fault
            
            // Check if we need to remove an element due to full frames
            if (pageTable.size() == frames) {
                int lruPage = lruList.back();
                lruList.pop_back();
                pageTable.erase(lruPage);
            }
            pageFaults++;
        } else {
            // Remove page from its current position in the LRU list
            lruList.erase(pageTable[page]);
        }

        // Insert the page at the front of the list (most recently used position)
        lruList.push_front(page);
        pageTable[page] = lruList.begin();

        // Display the current state of frames
        std::cout << "Frames: ";
        for (int p : lruList) {
            std::cout << p << " ";
        }
        if (isPageFault)
            std::cout << "(Page Fault)\n";
        else
            std::cout << "(No Page Fault)\n";
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

    std::cout << "LRU Page Faults: " << lruPageFaults(pages, frames) << std::endl;
    return 0;
}
/*
4 
11
1 2 3 4 5 1 2 6 7 3 8
*/
