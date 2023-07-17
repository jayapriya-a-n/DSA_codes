#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// Structure for a linked list node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Structure for a hash table
typedef struct {
    Node* head[TABLE_SIZE];
} HashTable;

// Function to initialize the hash table
void initHashTable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->head[i] = NULL;
    }
}

// Function to calculate the hash value for a given key
int getHash(int key) {
    return key % TABLE_SIZE;
}

// Function to insert a key into the hash table
void insert(HashTable* ht, int key) {
    int index = getHash(key);

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = key;
    newNode->next = NULL;

    if (ht->head[index] == NULL) {
        ht->head[index] = newNode;
    } else {
        Node* temp = ht->head[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to search for a key in the hash table
int search(HashTable* ht, int key) {
    int index = getHash(key);

    Node* temp = ht->head[index];
    while (temp != NULL) {
        if (temp->data == key) {
            return 1;  // Found
        }
        temp = temp->next;
    }

    return 0;  // Not found
}

int main() {
    FILE* inputFile = fopen("input.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Failed to open input.txt or output.txt\n");
        return 1;
    }

    HashTable hashTable;
    initHashTable(&hashTable);

    int key;
    while (fscanf(inputFile, "%d", &key) == 1) {
        insert(&hashTable, key);
    }

    fprintf(outputFile, "Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        fprintf(outputFile, "Index %d: ", i);
        Node* temp = hashTable.head[i];
        while (temp != NULL) {
            fprintf(outputFile, "%d ", temp->data);
            temp = temp->next;
        }
        fprintf(outputFile, "\n");
    }

    int searchKey;
    fscanf(inputFile, "%d", &searchKey);

    int isFound = search(&hashTable, searchKey);
    if (isFound) {
        fprintf(outputFile, "\n%d is found in the hash table.\n", searchKey);
    } else {
        fprintf(outputFile, "\n%d is not found in the hash table.\n", searchKey);
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Output has been written to output.txt\n");

    return 0;
}
