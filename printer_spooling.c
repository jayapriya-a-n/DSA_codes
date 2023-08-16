#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

struct Stack {
    int items[MAX_SIZE];
    int top;
};

typedef struct Stack stack;

void initialize(stack *s) {
    s->top = -1;
}

int isFull(stack *s) {
    return s->top == MAX_SIZE - 1;
}

int isEmpty(stack *s) {
    return s->top == -1;
}

void push(stack *s, int value) {
    if (isFull(s)) {
        printf("Stack is full. Cannot push more items.\n");
    } else {
        s->items[++s->top] = value;
    }
}

int pop(stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty. Cannot pop any items.\n");
        return -1;
    } else {
        return s->items[s->top--];
    }
}

void printQueue(stack *s) {
    printf("Printing Queue: ");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->items[i]);
    }
    printf("\n");
}

int main() {
    stack printingQueue;
    initialize(&printingQueue);

    int choice, jobNumber;

    do {
        printf("\nPrinter Spooling Menu:\n");
        printf("1. Add Job\n");
        printf("2. Print Job\n");
        printf("3. Print Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (!isFull(&printingQueue)) {
                    printf("Enter job number: ");
                    scanf("%d", &jobNumber);
                    push(&printingQueue, jobNumber);
                    printf("Job %d added to the queue.\n", jobNumber);
                } else {
                    printf("Queue is full. Cannot add more jobs.\n");
                }
                break;

            case 2:
                if (!isEmpty(&printingQueue)) {
                    jobNumber = pop(&printingQueue);
                    printf("Printing job %d...\n", jobNumber);
                } else {
                    printf("Queue is empty. No jobs to print.\n");
                }
                break;

            case 3:
                printQueue(&printingQueue);
                break;

            case 4:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 4);

    return 0;
}
