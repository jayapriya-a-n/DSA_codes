#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10

// Structure to represent a caller
typedef struct {
    int id;
} Caller;

// Structure to represent a queue
typedef struct {
    Caller callers[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

// Initialize a queue
void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

// Check if the queue is empty
int isQueueEmpty(Queue *q) {
    return q->front == -1;
}

// Check if the queue is full
int isQueueFull(Queue *q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

// Enqueue a caller into the queue
void enqueue(Queue *q, Caller c) {
    if (isQueueFull(q)) {
        printf("Queue is full. Cannot add more callers.\n");
        return;
    }
    if (isQueueEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    }
    q->callers[q->rear] = c;
    printf("Caller %d is added to the queue.\n", c.id);
}

// Dequeue a caller from the queue
Caller dequeue(Queue *q) {
    Caller emptyCaller = {-1}; // Invalid caller ID
    if (isQueueEmpty(q)) {
        printf("Queue is empty. No callers to dequeue.\n");
        return emptyCaller;
    }
    Caller dequeuedCaller = q->callers[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1; // Reset queue
    } else {
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    }
    printf("Caller %d is being served.\n", dequeuedCaller.id);
    return dequeuedCaller;
}

int main() {
    Queue callCenterQueue;
    initQueue(&callCenterQueue);

    int choice;
    Caller newCaller;
    newCaller.id = 1; // Caller ID starts from 1

    do {
        printf("Call Center Menu:\n");
        printf("1. Enqueue Caller\n");
        printf("2. Dequeue Caller\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enqueue(&callCenterQueue, newCaller);
                newCaller.id++;
                break;
            case 2:
                dequeue(&callCenterQueue);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}
