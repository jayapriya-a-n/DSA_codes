#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for a node in the linked list
struct Node {
    int data;
    struct Node* next;
};

// Structure for the linear queue
struct Queue {
    struct Node* front;
    struct Node* rear;
};

// Function to initialize an empty queue
void initializeQueue(struct Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return (queue->front == NULL);
}

// Function to enqueue an element into the queue
void enqueue(struct Queue* queue, int data) {
    // Create a new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    // If the queue is empty, set the new node as both front and rear
    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        // Otherwise, add the new node at the rear and update the rear
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Function to save the queue to a file
void saveQueueToFile(struct Queue* queue, char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!");
        return;
    }

    struct Node* current = queue->front;
    while (current != NULL) {
        fprintf(file, "%d\n", current->data);
        current = current->next;
    }

    fclose(file);
    printf("Queue saved to file successfully.\n");
}

int main() {
    struct Queue queue;
    initializeQueue(&queue);

    int min, max, numElements;

    printf("Enter the minimum value for the random numbers: ");
    scanf("%d", &min);

    printf("Enter the maximum value for the random numbers: ");
    scanf("%d", &max);

    printf("Enter the number of elements to generate: ");
    scanf("%d", &numElements);

    // Set the seed for random number generation
    srand(time(0));

    // Generate random numbers and enqueue them
    for (int i = 0; i < numElements; i++) {
        int randomNumber = min + (rand() % (max - min + 1));
        enqueue(&queue, randomNumber);
    }

    // Save the queue to a file
    saveQueueToFile(&queue, "l_queues.txt");

    return 0;
}
