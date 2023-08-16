#include <stdio.h>
#include <stdlib.h>

#define MAX_CARS 20

struct Queue {
    int front, rear, size;
    int capacity;
    int* cars;
};

struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->cars = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isFull(struct Queue* queue) {
    return queue->size == queue->capacity;
}

int isEmpty(struct Queue* queue) {
    return queue->size == 0;
}

void enqueue(struct Queue* queue, int carNumber) {
    if (isFull(queue)) {
        printf("Queue is full. Car %d cannot be added.\n", carNumber);
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->cars[queue->rear] = carNumber;
    queue->size++;
    printf("Car %d has entered the drive-through.\n", carNumber);
}

int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return -1;
    }
    int carNumber = queue->cars[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return carNumber;
}

int main() {
    int numCars;
    printf("Enter the number of cars in the drive-through: ");
    scanf("%d", &numCars);

    if (numCars > MAX_CARS) {
        printf("Maximum number of cars allowed is %d.\n", MAX_CARS);
        return 1;
    }

    struct Queue* driveThrough = createQueue(numCars);

    for (int i = 1; i <= numCars; i++) {
        enqueue(driveThrough, i);
    }

    printf("\nProcessing drive-through orders:\n");

    while (!isEmpty(driveThrough)) {
        int carNumber = dequeue(driveThrough);
        if (carNumber != -1) {
            printf("Car %d has been served.\n", carNumber);
        }
    }

    free(driveThrough->cars);
    free(driveThrough);

    return 0;
}
