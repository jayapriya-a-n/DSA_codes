#include <stdio.h>
#include <stdlib.h>

#define CACHE_SIZE 10

struct Node {
    int data;
    struct Node* next;
};

struct Node* hashTable[CACHE_SIZE] = {NULL};

// Hash function
int hash(int key) {
    return key % CACHE_SIZE;
}

// Insert a value into the cache
void insert(int value) {
    int index = hash(value);

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;

    printf("Inserted %d into the cache.\n", value);
}

// Delete a value from the cache
void delete(int value) {
    int index = hash(value);

    struct Node* prev = NULL;
    struct Node* current = hashTable[index];

    while (current != NULL && current->data != value) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("%d not found in the cache.\n", value);
        return;
    }

    if (prev == NULL) {
        hashTable[index] = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Deleted %d from the cache.\n", value);
}

// Display the contents of the cache
void display() {
    printf("Cache Contents:\n");
    for (int i = 0; i < CACHE_SIZE; i++) {
        printf("%d: ", i);
        struct Node* current = hashTable[i];
        while (current != NULL) {
            printf("%d -> ", current->data);
            current = current->next;
        }
        printf("NULL\n");
    }
    printf("\n");
}

int main() {
    while (1) {
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Exit\n");

        int choice, value;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                delete(value);
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
