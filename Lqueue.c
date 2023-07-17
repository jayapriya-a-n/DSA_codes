#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct {
    int front;
    int rear;
    int data[MAX_QUEUE_SIZE];
} Queue;

void initializeQueue(Queue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

int isQueueEmpty(Queue* queue) {
    return (queue->front == -1);
}

int isQueueFull(Queue* queue) {
    return ((queue->rear + 1) % MAX_QUEUE_SIZE == queue->front);
}

void enqueue(Queue* queue, int item) {
    if (isQueueFull(queue)) {
        printf("Queue is full. Cannot enqueue item.\n");
        return;
    }

    if (isQueueEmpty(queue)) {
        queue->front = 0;
    }

    queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
    queue->data[queue->rear] = item;
    printf("Enqueued: %d\n", item);
}

int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue item.\n");
        return -1;
    }

    int item = queue->data[queue->front];
    printf("Dequeued: %d\n", item);

    if (queue->front == queue->rear) {
        // Reset the queue when the last item is dequeued
        initializeQueue(queue);
    } else {
        queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
    }

    return item;
}

void displayQueue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue:\n");
    int i = queue->front;
    while (i != queue->rear) {
        printf("%d ", queue->data[i]);
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
    printf("%d\n", queue->data[i]);
}

int main() {
    Queue queue;
    initializeQueue(&queue);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    displayQueue(&queue);

    int dequeuedItem = dequeue(&queue);
    printf("Dequeued item: %d\n", dequeuedItem);

    displayQueue(&queue);

    return 0;
}
