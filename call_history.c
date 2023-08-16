#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HISTORY_SIZE 10
#define MAX_COMMAND_LENGTH 100

struct Stack {
    char commands[MAX_HISTORY_SIZE][MAX_COMMAND_LENGTH];
    int top;
};

void initializeStack(struct Stack* stack) {
    stack->top = -1;
}

int isStackEmpty(struct Stack* stack) {
    return stack->top == -1;
}

int isStackFull(struct Stack* stack) {
    return stack->top == MAX_HISTORY_SIZE - 1;
}

void push(struct Stack* stack, const char* command) {
    if (isStackFull(stack)) {
        printf("History is full. Some old commands will be discarded.\n");
        for (int i = 0; i < MAX_HISTORY_SIZE - 1; i++) {
            strcpy(stack->commands[i], stack->commands[i + 1]);
        }
        stack->top--;
    }
    strcpy(stack->commands[++stack->top], command);
}

void displayHistory(struct Stack* stack) {
    printf("Command History:\n");
    for (int i = 0; i <= stack->top; i++) {
        printf("%d: %s\n", i + 1, stack->commands[i]);
    }
}

int main() {
    struct Stack historyStack;
    initializeStack(&historyStack);

    char input[MAX_COMMAND_LENGTH];
    while (1) {
        printf("Enter a command: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove trailing newline

        if (strcmp(input, "exit") == 0) {
            printf("Exiting...\n");
            break;
        } else if (strcmp(input, "history") == 0) {
            displayHistory(&historyStack);
        } else {
            push(&historyStack, input);
            printf("Command '%s' has been saved.\n", input);
        }
    }

    return 0;
}
