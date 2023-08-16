#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// Stack structure
struct Stack {
    int top;
    char items[MAX_SIZE][50]; // Assuming function names have a maximum of 50 characters
};

// Function to initialize the stack
void initialize(struct Stack *stack) {
    stack->top = -1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

// Function to push an item onto the stack
void push(struct Stack *stack, const char *item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack Overflow!\n");
        return;
    }
    strcpy(stack->items[++stack->top], item);
}

// Function to pop an item from the stack
char* pop(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow!\n");
        return NULL;
    }
    return stack->items[stack->top--];
}

// Function to display the current stack contents
void display(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Function Call Stack:\n");
    for (int i = stack->top; i >= 0; i--) {
        printf("%s\n", stack->items[i]);
    }
}

int main() {
    struct Stack callStack;
    initialize(&callStack);

    int choice;
    char functionName[50];

    do {
        printf("\nFunction Call Management using Stacks\n");
        printf("1. Push Function Call\n");
        printf("2. Pop Function Call\n");
        printf("3. Display Function Call Stack\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter function name to push: ");
                scanf("%s", functionName);
                push(&callStack, functionName);
                break;
            case 2:
                if (!isEmpty(&callStack)) {
                    char *poppedFunction = pop(&callStack);
                    printf("Popped function: %s\n", poppedFunction);
                } else {
                    printf("Stack is empty. Cannot pop.\n");
                }
                break;
            case 3:
                display(&callStack);
                break;
            case 4:
                printf("Exiting.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
