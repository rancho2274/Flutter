// C++ program to read and display the contents of a file character by character and line by line
#include <iostream>
#include <fstream>
#include <string>

// Function to display file contents character by character
void displayFileCharacterByCharacter(const std::string& sourceFile) {
    std::ifstream src(sourceFile);

    if (!src.is_open()) {
        std::cerr << "Error: The file " << sourceFile << " was not found." << std::endl;
        return;
    }

    char ch;
    while (src.get(ch)) {  // Read one character at a time
        std::cout << ch;
    }

    std::cout << "\nFile displayed character by character successfully.\n" << std::endl;

    src.close();
}

// Function to display file contents line by line
void displayFileLineByLine(const std::string& sourceFile) {
    std::ifstream src(sourceFile);

    if (!src.is_open()) {
        std::cerr << "Error: The file " << sourceFile << " was not found." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(src, line)) {  // Read one line at a time
        std::cout << line << '\n';
    }

    std::cout << "\nFile displayed line by line successfully.\n" << std::endl;

    src.close();
}

int main() {
    std::string sourceFile = "sample1.txt";  // Replace with your source file

    // Displaying character by character
    displayFileCharacterByCharacter(sourceFile);

    // Displaying line by line
    displayFileLineByLine(sourceFile);

    return 0;
}
