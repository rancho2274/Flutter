#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

// Global variables
string IR;   // Instruction Register (Opcode)
int PI = 0;  // Program Interrupt flag

// MOS (Monitor) function to handle errors
void MOS() {
    if (PI == 1) {
        cout << "Error: Invalid Opcode!" << endl;
        // Additional error handling logic could go here
    }
}

// Function to check for opcode errors
void check_opcode_error(const string& instruction) {
    // Check if the operation code is valid
    if (!(   (instruction.substr(0, 2) == "GD") || 
            (instruction.substr(0, 2) == "PD") || 
            (instruction.substr(0, 2) == "HR") || 
            (instruction.substr(0, 2) == "LR") || 
            (instruction.substr(0, 2) == "SR") || 
            (instruction.substr(0, 2) == "CR") || 
            (instruction.substr(0, 2) == "BT"))) {
        PI = 1;  // Set the error code for invalid operation code
        cout << "Error: Invalid Opcode! Instruction: " << instruction << endl; // Output the invalid instruction
        MOS();    // Call the MOS function to handle the error
    } else {
        cout << "Valid Opcode: " << instruction << endl;
    }
}

// Function to process the job (job input with various instructions)
void process_job(const string& job) {
    stringstream ss(job);
    string line;
    bool skipDTA = false;  // Flag to skip lines between $DTA and $END

    // Read each line of the job
    while (getline(ss, line)) {
        // Skip empty lines or lines starting with $
        if (line.empty() || line[0] == '$') {
            // If $DTA is found, start skipping
            if (line.find("$DTA") != string::npos) {
                skipDTA = true;
            }
            // If $END is found, stop skipping
            if (line.find("$END") != string::npos) {
                skipDTA = false;
            }
            continue;  // Skip lines starting with $ or empty lines
        }

        // If within the $DTA and $END section, skip processing
        if (skipDTA) {
            continue;
        }

        // Split the line into individual instructions and validate each one
        stringstream line_ss(line);
        string instruction;
        while (line_ss >> instruction) {
            check_opcode_error(instruction);  // Validate the individual instruction
        }
    }
}

// Function to read job data from a file
string read_job_from_file(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(1);  // Exit with error if the file cannot be opened
    }

    stringstream buffer;
    buffer << file.rdbuf();  // Read the entire file into the buffer
    return buffer.str();     // Return the contents of the file as a string
}

int main() {
    string filename;
    cout << "Enter the job file name: ";
    cin >> filename;

    // Read the job from the file
    string job = read_job_from_file(filename);

    // Process the job
    process_job(job);

    return 0;
}

/*
$AMJ020100120003
GD20 Ly20 CR33 BT07
$DTA
hope for it
$END 0201
*/