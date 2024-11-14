
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class MemoryLoader {
private:
    std::vector<std::string> memory;  // Vector to store ALP instructions as lines of code

public:
    // Load the ALP from a file into the memory vector
    bool loadProgram(const std::string& filename) {
        std::ifstream inFile(filename);
        if (!inFile) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(inFile, line)) {  // Read each line as an instruction
            memory.push_back(line);           // Store each line into the memory vector
        }
        
        inFile.close();
        return true;
    }

    // Display the loaded program from memory
    void displayMemory() const {
        std::cout << "Loaded Program in Memory:" << std::endl;
        for (size_t i = 0; i < memory.size(); ++i) {
            std::cout << "Memory[" << i << "]: " << memory[i] << std::endl;
        }
    }
};

int main() {
    MemoryLoader loader;
    std::string filename;

    std::cout << "Enter the ALP program file name to load: ";
    std::cin >> filename;

    // Load the program and display memory if successful
    if (loader.loadProgram(filename)) {
        loader.displayMemory();
    } else {
        std::cerr << "Failed to load program into memory." << std::endl;
    }

    return 0;
}
