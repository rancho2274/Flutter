#include <stdio.h>
#include <string.h>

#define MAX_FRAMES 5    // Define the maximum number of frames
#define FRAME_SIZE 8    // Define the maximum size of each frame (without length prefix)
#define TOTAL_SIZE (FRAME_SIZE + 1) // Define the total size including the length prefix

// Function prototypes
void sender(char frames[MAX_FRAMES][TOTAL_SIZE], int *numFrames);
void receiver(char frames[MAX_FRAMES][TOTAL_SIZE], int numFrames);

int main() {
    char frames[MAX_FRAMES][TOTAL_SIZE];
    int numFrames = 0;

    sender(frames, &numFrames);

    receiver(frames, numFrames);

    return 0;
}

void sender(char frames[MAX_FRAMES][TOTAL_SIZE], int *numFrames) {
    printf("Sender\n-------------------------------------\n");
    printf("Enter the number of frames: ");
    scanf("%d", numFrames);

    if (*numFrames > MAX_FRAMES) {
        printf("Number of frames exceeds the maximum limit (%d).\n", MAX_FRAMES);
        *numFrames = MAX_FRAMES;
    }

    for (int j = 0; j < *numFrames; j++) {
        char data[FRAME_SIZE];
        printf("\nEnter data for frame %d: ", j + 1);
        scanf("%s", data);

        int len = strlen(data);
        frames[j][0] = len + '0'; // Store the length of the data as the first character

        for (int i = 0; i < len; i++) {
            frames[j][i + 1] = data[i];
        }

        frames[j][len + 1] = '\0'; // Null-terminate the frame

        printf("Data to send in frame %d: ", j + 1);
        for (int i = 0; i <= len; i++) {
            printf("%c", frames[j][i]);
        }
        printf("\n");
    }
}

void receiver(char frames[MAX_FRAMES][TOTAL_SIZE], int numFrames) {
    printf("\n\nReceiver\n-------------------------------------\n");

    for (int j = 0; j < numFrames; j++) {
        int lenofDataReceived = frames[j][0] - '0'; // Convert the first character back to the length

        printf("Original Data in frame %d: ", j + 1);
        for (int i = 1; i <= lenofDataReceived; i++) {
            printf("%c", frames[j][i]);
        }
        printf("\n");
    }

    // Print all frames together with spaces between them
    printf("\nAll frames together: ");
    for (int j = 0; j < numFrames; j++) {
        int lenofDataReceived = frames[j][0] - '0'; // Convert the first character back to the length
        for (int i = 1; i <= lenofDataReceived; i++) {
            printf("%c", frames[j][i]);
        }
        if (j < numFrames - 1) {
            printf(" "); // Add space between frames
        }
    }
    printf("\n");
}
