#include <stdio.h>
#include <stdlib.h>

// Define the structure for a queue node
struct Node {
    int data;
    struct Node* next;
};

// Define the structure for the queue
struct Queue {
    struct Node* front;
    struct Node* rear;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create an empty queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to enqueue an item to the rear of the queue
void enqueue(struct Queue* queue, int data) {
    struct Node* newNode = createNode(data);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

// Function to dequeue an item from the front of the queue
int dequeue(struct Queue* queue) {
    if (queue->front == NULL)
        return -1; // Queue is empty
    struct Node* temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;
    free(temp);
    if (queue->front == NULL)
        queue->rear = NULL;
    return data;
}

// Function to display the items in the queue
void displayQueue(struct Queue* queue) {
    struct Node* current = queue->front;
    printf("Items in the queue: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct Queue* checkoutQueue = createQueue();

    while (1) {
        printf("1. Add item to queue\n");
        printf("2. Remove item from queue\n");
        printf("3. Display queue\n");
        printf("4. Exit\n");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int item;
                printf("Enter item: ");
                scanf("%d", &item);
                enqueue(checkoutQueue, item);
                printf("Item %d added to the queue.\n", item);
                break;
            }
            case 2: {
                int item = dequeue(checkoutQueue);
                if (item == -1)
                    printf("Queue is empty.\n");
                else
                    printf("Item %d removed from the queue.\n", item);
                break;
            }
            case 3: {
                displayQueue(checkoutQueue);
                break;
            }
            case 4: {
                exit(0);
            }
            default: {
                printf("Invalid choice. Please try again.\n");
                break;
            }
        }
    }

    return 0;
}
