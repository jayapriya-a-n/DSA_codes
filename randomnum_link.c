#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Node structure for linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to insert a new node at the end of the linked list
void insert(Node** head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to generate N random numbers between P and Q and store them in a linked list
void generateRandomNumbers(Node** head, int N, int P, int Q) {
    srand(time(NULL)); // Seed the random number generator

    for (int i = 0; i < N; i++) {
        int randomNum = (rand() % (Q - P + 1)) + P; // Generate a random number between P and Q
        insert(head, randomNum); // Insert the random number into the linked list
    }
}

// Function to write the linked list values to a file
void writeToFile(Node* head, const char* fileName) {
    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    Node* current = head;
    while (current != NULL) {
        fprintf(file, "%d\n", current->data); // Write the data to the file
        current = current->next;
    }

    fclose(file);
}

// Function to free the memory allocated for the linked list
void freeList(Node** head) {
    Node* current = *head;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

int main() {
    int N, P, Q;

    printf("Enter the number of random numbers to generate: ");
    scanf("%d", &N);

    printf("Enter the range (P and Q): ");
    scanf("%d %d", &P, &Q);

    Node* head = NULL;

    generateRandomNumbers(&head, N, P, Q); // Generate random numbers and store them in the linked list

    writeToFile(head, "Input.txt"); // Write the linked list values to a file

    freeList(&head); // Free the memory allocated for the linked list

    printf("Random numbers have been written to Input.txt\n");

    return 0;
}
