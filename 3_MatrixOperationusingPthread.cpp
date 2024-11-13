#include <iostream>
#include <pthread.h>
#include <vector>

//sampleinput
// 3
// 1 2 3 4 5 6 7 8 9
// 9 8 7 6 5 4 3 2 1

int MAX_THREAD;
int MAX;  // Matrix dimension input by the user
std::vector<std::vector<int>> matA, matB, Add, Sub, Mul;
int stepAdd = 0, stepSub = 0, stepMul = 0;

pthread_mutex_t add_mutex, sub_mutex, mul_mutex;  // Mutexes to protect step variables

void* addition(void* arg) {
   // pthread_mutex_lock(&add_mutex);
    int core = stepAdd++;
   // pthread_mutex_unlock(&add_mutex);

    for (int i = core * MAX / MAX_THREAD; i < (core + 1) * MAX / MAX_THREAD; ++i) {
        for (int j = 0; j < MAX; ++j) {
            Add[i][j] = matA[i][j] + matB[i][j];
        }
    }
    return NULL;
}

void* subtraction(void* arg) {
   // pthread_mutex_lock(&sub_mutex);
    int core = stepSub++;
   // pthread_mutex_unlock(&sub_mutex);

    for (int i = core * MAX / MAX_THREAD; i < (core + 1) * MAX / MAX_THREAD; ++i) {
        for (int j = 0; j < MAX; ++j) {
            Sub[i][j] = matA[i][j] - matB[i][j];
        }
    }
    return NULL;
}

void* multiplication(void* arg) {
   // pthread_mutex_lock(&mul_mutex);
    int core = stepMul++;
   // pthread_mutex_unlock(&mul_mutex);

    for (int i = core * MAX / MAX_THREAD; i < (core + 1) * MAX / MAX_THREAD; ++i) {
        for (int j = 0; j < MAX; ++j) {
            Mul[i][j] = 0;
            for (int k = 0; k < MAX; ++k) {
                Mul[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
    return NULL;
}

void printMatrix(const std::vector<std::vector<int>>& mat) {
    for (const auto& row : mat) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "Enter the dimension of the matrices: ";
    std::cin >> MAX;

    MAX_THREAD = MAX+1;  // Adjusted to MAX instead of MAX + 1

    matA.resize(MAX, std::vector<int>(MAX));
    matB.resize(MAX, std::vector<int>(MAX));
    Add.resize(MAX, std::vector<int>(MAX));
    Sub.resize(MAX, std::vector<int>(MAX));
    Mul.resize(MAX, std::vector<int>(MAX));

    std::cout << "Enter elements of matrix A:\n";
    for (int i = 0; i < MAX; ++i)
        for (int j = 0; j < MAX; ++j)
            std::cin >> matA[i][j];

    std::cout << "Enter elements of matrix B:\n";
    for (int i = 0; i < MAX; ++i)
        for (int j = 0; j < MAX; ++j)
            std::cin >> matB[i][j];

    pthread_t threads[MAX_THREAD];

    // Initialize the mutexes
    // pthread_mutex_init(&add_mutex, NULL);
    // pthread_mutex_init(&sub_mutex, NULL);
    // pthread_mutex_init(&mul_mutex, NULL);

    // Addition
    for (int i = 0; i < MAX_THREAD; ++i) {
        pthread_create(&threads[i], NULL, addition, NULL);
    }
    for (int i = 0; i < MAX_THREAD; ++i) {
        pthread_join(threads[i], NULL);
    }

    std::cout << "Matrix Addition:\n";
    printMatrix(Add);

    // Subtraction
    stepSub = 0;
    for (int i = 0; i < MAX_THREAD; ++i) {
        pthread_create(&threads[i], NULL, subtraction, NULL);
    }
    for (int i = 0; i < MAX_THREAD; ++i) {
        pthread_join(threads[i], NULL);
    }

    std::cout << "Matrix Subtraction:\n";
    printMatrix(Sub);

    // Multiplication
    stepMul = 0;
    for (int i = 0; i < MAX_THREAD; ++i) {
        pthread_create(&threads[i], NULL, multiplication, NULL);
    }
    for (int i = 0; i < MAX_THREAD; ++i) {
        pthread_join(threads[i], NULL);
    }

    std::cout << "Matrix Multiplication:\n";
    printMatrix(Mul);

    // Destroy the mutexes
    // pthread_mutex_destroy(&add_mutex);
    // pthread_mutex_destroy(&sub_mutex);
    // pthread_mutex_destroy(&mul_mutex);

    return 0;
}