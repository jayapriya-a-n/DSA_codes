#include <stdio.h>
#include <stdlib.h>

// Define a structure for a doubly linked list node
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the linked list
void insertEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
}

// Function to double the intensity of pixels in the linked list
void doubleIntensity(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        current->data *= 2;
        current = current->next;
    }
}

// Function to display the linked list
void display(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    int numPixels;

    printf("Enter the number of pixels: ");
    scanf("%d", &numPixels);

    printf("Enter the pixel values:\n");
    for (int i = 0; i < numPixels; ++i) {
        int pixelValue;
        scanf("%d", &pixelValue);
        insertEnd(&head, pixelValue);
    }

    printf("Original pixel values: ");
    display(head);

    doubleIntensity(head);

    printf("Pixel values after doubling intensity: ");
    display(head);

    // Free the allocated memory
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
