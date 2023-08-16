#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10

typedef struct {
    int front, rear, size;
    int items[MAX_QUEUE_SIZE];
} Queue;

void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
    q->size = 0;
}

int isQueueEmpty(Queue *q) {
    return (q->size == 0);
}

int isQueueFull(Queue *q) {
    return (q->size == MAX_QUEUE_SIZE);
}

void enqueue(Queue *q, int item) {
    if (isQueueFull(q)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }

    if (q->front == -1)
        q->front = 0;
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->items[q->rear] = item;
    q->size++;
}

int dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }

    int item = q->items[q->front];
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    q->size--;
    return item;
}

int main() {
    Queue roadA, roadB;
    initializeQueue(&roadA);
    initializeQueue(&roadB);

    while (1) {
        printf("Enter 1 for vehicle arrival at Road A, 2 for vehicle arrival at Road B, 0 to exit: ");
        int choice;
        scanf("%d", &choice);

        if (choice == 0)
            break;

        switch (choice) {
            case 1:
                if (!isQueueFull(&roadA)) {
                    enqueue(&roadA, 1);
                    printf("Vehicle added to Road A.\n");
                } else {
                    printf("Road A queue is full.\n");
                }
                break;

            case 2:
                if (!isQueueFull(&roadB)) {
                    enqueue(&roadB, 1);
                    printf("Vehicle added to Road B.\n");
                } else {
                    printf("Road B queue is full.\n");
                }
                break;

            default:
                printf("Invalid choice.\n");
                break;
        }
    }

    printf("Simulation Ended.\n");

    return 0;
}
