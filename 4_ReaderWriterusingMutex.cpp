#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <unistd.h> // For sleep function

using namespace std;

 //sample input 
 // 3 
 // 2

pthread_mutex_t x, wsem; // Mutexes for synchronization
int readcount;  // Number of readers currently reading

void initialize() {
    pthread_mutex_init(&x, NULL);  // Initialize reader count mutex
    pthread_mutex_init(&wsem, NULL); // Initialize writer mutex
    readcount = 0;
}

void* reader(void* param) {
    int reader_id = *((int*)param);  // Get reader ID
    int waittime = rand() % 5;
    cout << "\nReader " << reader_id << " is trying to enter";

    pthread_mutex_lock(&x);  // Lock the reader count mutex
    readcount++;
    if (readcount == 1)
        pthread_mutex_lock(&wsem);  // First reader locks the resource for writers

    cout << "\nReader " << reader_id << " is inside";
    pthread_mutex_unlock(&x);  // Unlock reader count mutex

    sleep(waittime);  // Simulate reading

    pthread_mutex_lock(&x);  // Lock reader count mutex again to modify
    readcount--;
    if (readcount == 0)
        pthread_mutex_unlock(&wsem);  // Last reader unlocks the resource for writers

    pthread_mutex_unlock(&x);  // Unlock reader count mutex

    cout << "\nReader " << reader_id << " is Leaving";
    return NULL;
}

void* writer(void* param) {
    int writer_id = *((int*)param);  // Get writer ID
    int waittime = rand() % 3;
    cout << "\nWriter " << writer_id << " is trying to enter";

    pthread_mutex_lock(&wsem);  // Writer locks the resource

    cout << "\nWriter " << writer_id << " has entered";
    sleep(waittime);  // Simulate writing

    pthread_mutex_unlock(&wsem);  // Writer releases the lock

    cout << "\nWriter " << writer_id << " is leaving";
    return NULL;
}

int main() {
    int n1, n2;

    cout << "\nEnter the number of readers: ";
    cin >> n1;
    cout << "\nEnter the number of writers: ";
    cin >> n2;

    initialize();  // Initialize mutexes and reader count

    pthread_t readers[n1];  // Reader thread array
    int reader_ids[n1];  // Reader ID array
    for (int i = 0; i < n1; i++) {
        reader_ids[i] = i + 1;  // Assign unique ID to each reader
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);  // Create reader threads
    }

    pthread_t writers[n2];  // Writer thread array
    int writer_ids[n2];  // Writer ID array
    for (int i = 0; i < n2; i++) {
        writer_ids[i] = i + 1;  // Assign unique ID to each writer
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);  // Create writer threads
    }

    // Wait for all reader threads to finish
    for (int i = 0; i < n1; i++) {
        pthread_join(readers[i], NULL);
    }

    // Wait for all writer threads to finish
    for (int i = 0; i < n2; i++) {
        pthread_join(writers[i], NULL);
    }

    cout << "\nAll threads have completed.\n";
    return 0;
}
