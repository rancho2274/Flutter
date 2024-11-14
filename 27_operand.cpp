#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// Global variable
int PI = 0;  // Program Interrupt flag

// MOS (Monitor) function to handle errors
void MOS() {
    if (PI == 2) {
        cout << "Error: Operand Error!" << endl;
    }
}

// Function to check for operand errors
void check_operand_error(const string& instruction) {
    // Check if the instruction has at least 4 characters (for third and fourth bits)
    if (instruction.length() >= 4) {
        char operand1 = instruction[2];
        char operand2 = instruction[3];

        // Check if both operand1 and operand2 are digits between 0-9
        if (!(isdigit(operand1) && isdigit(operand2))) {
            PI = 2;  // Set the error code for operand error
            MOS();    // Call the MOS function to handle the error
        } else {
            cout << "Valid Operand: " << instruction << endl;
        }
    } else {
        PI = 2;  // Operand error if instruction length is less than 4
        MOS();    // Call the MOS function to handle the error
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
            check_operand_error(instruction);  // Validate the operand in the instruction
        }
    }
}

int main() {
    string job;
    string line;

    cout << "Enter the job input line by line (type '$END' as the last line):" << endl;

    // Keep reading lines until we encounter "$END"
    while (getline(cin, line)) {
        job += line + "\n";  // Add the line to the job string with a newline
        if (line.find("$END") != string::npos) {
            break;  // Stop reading if "$END" is found
        }
    }

    // Process the job
    process_job(job);

    return 0;
}

/*
"$AMJ020100120003\n"
"GD20 LR20 CR33 BT07\n"
"$DTA\n"
"hope for it\n"
"$END 0201"
*/
