#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the state structure
typedef struct State {
    char name[20];
    struct State *next;
    struct State *prev;
} State;

// Function to create a new state
State* createState(const char *name) {
    State *state = (State*)malloc(sizeof(State));
    strcpy(state->name, name);
    state->next = NULL;
    state->prev = NULL;
    return state;
}

// Function to insert a state after a given state
void insertAfter(State *prevState, State *newState) {
    newState->next = prevState->next;
    if (prevState->next != NULL) {
        prevState->next->prev = newState;
    }
    prevState->next = newState;
    newState->prev = prevState;
}

// Function to print all states in the linked list
void printStates(State *currentState) {
    printf("Current states: ");
    while (currentState != NULL) {
        printf("%s ", currentState->name);
        currentState = currentState->next;
    }
    printf("\n");
}

int main() {
    // Create initial states
    State *onlineState = createState("Online");
    State *offlineState = createState("Offline");
    State *awayState = createState("Away");

    // Set initial state
    State *currentState = onlineState;

    // Insert other states after the initial state
    insertAfter(onlineState, offlineState);
    insertAfter(offlineState, awayState);

    // Print initial states
    printStates(currentState);

    // Simulate state transitions based on user input
    char input[20];
    while (1) {
        printf("Enter command (online/offline/away/exit): ");
        scanf("%s", input);

        if (strcmp(input, "online") == 0) {
            currentState = onlineState;
        } else if (strcmp(input, "offline") == 0) {
            currentState = offlineState;
        } else if (strcmp(input, "away") == 0) {
            currentState = awayState;
        } else if (strcmp(input, "exit") == 0) {
            break;
        } else {
            printf("Invalid command\n");
        }

        printStates(currentState);
    }

    // Clean up memory
    free(onlineState);
    free(offlineState);
    free(awayState);

    return 0;
}
