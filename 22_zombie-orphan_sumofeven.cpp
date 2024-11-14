#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>

int calculateSumEven(const std::vector<int>& arr) {
    int sum = 0;
    for (int num : arr) {
        if (num % 2 == 0) sum += num;
    }
    return sum;
}

int calculateSumOdd(const std::vector<int>& arr) {
    int sum = 0;
    for (int num : arr) {
        if (num % 2 != 0) sum += num;
    }
    return sum;
}

int main() {
    int n;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;

    std::vector<int> numbers(n);
    std::cout << "Enter the elements:\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    // Fork a new process
    pid_t pid = fork();

    if (pid > 0) {
        // Parent process
        std::cout << "Parent Process ID: " << getpid() << std::endl;

        // Calculate sum of even numbers
        int evenSum = calculateSumEven(numbers);
        std::cout << "Sum of even numbers in parent process: " << evenSum << std::endl;

        // Delay the wait to create a zombie process for the child
        sleep(5);

        // Wait for the child to avoid zombie state in the end
        waitpid(pid, nullptr, 0);
        std::cout << "Parent process exiting after waiting for child.\n";

    } else if (pid == 0) {
        // Child process
        std::cout << "Child Process ID: " << getpid() << std::endl;
        std::cout << "Child Process Parent ID: " << getppid() << std::endl;

        // Calculate sum of odd numbers
        int oddSum = calculateSumOdd(numbers);
        std::cout << "Sum of odd numbers in child process: " << oddSum << std::endl;

        // Sleep to demonstrate orphan process if parent exits first
        sleep(10);
        std::cout << "Child process completed.\n";
    } else {
        // Fork failed
        std::cerr << "Fork failed!\n";
        return 1;
    }

    return 0;
}

// 6
// 1 2 3 4 5 6 