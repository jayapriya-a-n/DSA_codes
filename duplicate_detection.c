#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HASH_SIZE 10

// Structure to hold elements in the linked list
struct Node {
    int data;
    struct Node* next;
};

// Hash table represented as an array of linked lists
struct Node* hashTable[HASH_SIZE] = { NULL };

// Hash function to calculate the index for a given data
int hashFunction(int data) {
    return data % HASH_SIZE;
}

// Insert an element into the hash table
void insert(int data) {
    int index = hashFunction(data);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// Check if an element exists in the hash table (duplicate detection)
bool contains(int data) {
    int index = hashFunction(data);
    struct Node* current = hashTable[index];
    while (current != NULL) {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Delete an element from the hash table
void delete(int data) {
    int index = hashFunction(data);
    struct Node* current = hashTable[index];
    struct Node* prev = NULL;

    while (current != NULL) {
        if (current->data == data) {
            if (prev == NULL) {
                hashTable[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Element %d deleted.\n", data);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Element %d not found.\n", data);
}

// Display the contents of the hash table
void display() {
    printf("Hash Table Contents:\n");
    for (int i = 0; i < HASH_SIZE; ++i) {
        printf("[%d]: ", i);
        struct Node* current = hashTable[i];
        while (current != NULL) {
            printf("%d -> ", current->data);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int choice, data;

    while (1) {
        printf("\nDuplicate Detection Using Hashing\n");
        printf("1. Insert\n2. Check Duplicate\n3. Delete\n4. Display\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter element to insert: ");
                scanf("%d", &data);
                insert(data);
                break;
            case 2:
                printf("Enter element to check for duplicate: ");
                scanf("%d", &data);
                if (contains(data)) {
                    printf("Element %d is a duplicate.\n", data);
                } else {
                    printf("Element %d is not a duplicate.\n", data);
                }
                break;
            case 3:
                printf("Enter element to delete: ");
                scanf("%d", &data);
                delete(data);
                break;
            case 4:
                display();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
