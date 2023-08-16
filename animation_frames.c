#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent an animation frame
struct Frame {
    int frameNumber;
    char imagePath[100];
    struct Frame *next;
};

// Function to create a new animation frame node
struct Frame *createFrame(int frameNumber, const char *imagePath) {
    struct Frame *newFrame = (struct Frame *)malloc(sizeof(struct Frame));
    if (newFrame) {
        newFrame->frameNumber = frameNumber;
        strncpy(newFrame->imagePath, imagePath, sizeof(newFrame->imagePath));
        newFrame->next = NULL;
    }
    return newFrame;
}

// Function to insert a new frame at the end of the linked list
void insertFrame(struct Frame **head, int frameNumber, const char *imagePath) {
    struct Frame *newFrame = createFrame(frameNumber, imagePath);
    if (*head == NULL) {
        *head = newFrame;
    } else {
        struct Frame *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newFrame;
    }
}

// Function to display all animation frames in the linked list
void displayFrames(struct Frame *head) {
    printf("Animation Frames:\n");
    struct Frame *current = head;
    while (current != NULL) {
        printf("Frame %d: %s\n", current->frameNumber, current->imagePath);
        current = current->next;
    }
}

// Function to free memory occupied by the linked list
void freeFrames(struct Frame *head) {
    struct Frame *current = head;
    while (current != NULL) {
        struct Frame *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    struct Frame *framesList = NULL;
    int frameNumber;
    char imagePath[100];

    int numFrames;
    printf("Enter the number of animation frames: ");
    scanf("%d", &numFrames);

    for (int i = 0; i < numFrames; ++i) {
        printf("Enter details for frame %d:\n", i + 1);
        printf("Frame Number: ");
        scanf("%d", &frameNumber);
        printf("Image Path: ");
        scanf("%s", imagePath);
        insertFrame(&framesList, frameNumber, imagePath);
    }

    displayFrames(framesList);

    freeFrames(framesList);

    return 0;
}
