#include <stdio.h>
#include <stdlib.h>

#define HASH_TABLE_SIZE 10

typedef struct {
    int key;
    int value;
} Node;

Node* createNode(int key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    return newNode;
}

int hashFunction(int key) {
    return key % HASH_TABLE_SIZE;
}

void insert(Node* hashTable[], int key, int value) {
    int index = hashFunction(key);

    Node* newNode = createNode(key, value);

    // Linear probing to handle collisions
    while (hashTable[index] != NULL) {
        index = (index + 1) % HASH_TABLE_SIZE;
    }

    hashTable[index] = newNode;
}

Node* search(Node* hashTable[], int key) {
    int index = hashFunction(key);

    // Linear probing to handle collisions
    while (hashTable[index] != NULL) {
        if (hashTable[index]->key == key) {
            return hashTable[index];
        }
        index = (index + 1) % HASH_TABLE_SIZE;
    }

    return NULL; // Key not found
}

int main() {
    FILE* inputFile = fopen("input.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Failed to open input.txt or output.txt\n");
        return 1;
    }

    Node* hashTable[HASH_TABLE_SIZE] = { NULL };

    int key, value;
    while (fscanf(inputFile, "%d %d", &key, &value) == 2) {
        insert(hashTable, key, value);
    }

    fprintf(outputFile, "Hash Table:\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (hashTable[i] != NULL) {
            fprintf(outputFile, "Index %d: Key = %d, Value = %d\n", i, hashTable[i]->key, hashTable[i]->value);
        }
    }

    int searchKey;
    printf("Enter the key to search: ");
    scanf("%d", &searchKey);

    Node* result = search(hashTable, searchKey);
    if (result != NULL) {
        fprintf(outputFile, "Key %d found, Value = %d\n", searchKey, result->value);
    } else {
        fprintf(outputFile, "Key %d not found\n", searchKey);
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Hash table and search result have been written to output.txt\n");

    return 0;
}
