#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100
#define WORD_LENGTH 50

typedef struct Node {
    char word[WORD_LENGTH];
    struct Node* next;
} Node;

Node* hashTable[TABLE_SIZE];

// Hash function
unsigned int hash(char* word) {
    unsigned int hashValue = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        hashValue += word[i];
    }
    return hashValue % TABLE_SIZE;
}

// Insert a word into the hash table
void insertWord(char* word) {
    unsigned int index = hash(word);
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->word, word);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// Delete a word from the hash table
void deleteWord(char* word) {
    unsigned int index = hash(word);
    Node* current = hashTable[index];
    Node* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            if (previous == NULL) {
                hashTable[index] = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Word '%s' deleted.\n", word);
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("Word '%s' not found.\n", word);
}

// Display the hash table
void displayHashTable() {
    printf("\nHash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        Node* current = hashTable[i];
        while (current != NULL) {
            printf("%s -> ", current->word);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

    while (1) {
        printf("\n1. Insert word\n");
        printf("2. Delete word\n");
        printf("3. Display hash table\n");
        printf("4. Exit\n");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char word[WORD_LENGTH];
                printf("Enter a word: ");
                scanf("%s", word);
                insertWord(word);
                break;
            }
            case 2: {
                char word[WORD_LENGTH];
                printf("Enter a word to delete: ");
                scanf("%s", word);
                deleteWord(word);
                break;
            }
            case 3:
                displayHashTable();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
