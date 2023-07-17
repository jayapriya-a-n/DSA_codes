#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

typedef struct {
    int* hashTable;
    int* flagTable;
} Hash;

// Function to initialize the hash table
void initHashTable(Hash* hash) {
    hash->hashTable = (int*)malloc(TABLE_SIZE * sizeof(int));
    hash->flagTable = (int*)malloc(TABLE_SIZE * sizeof(int));

    for (int i = 0; i < TABLE_SIZE; i++) {
        hash->hashTable[i] = -1;
        hash->flagTable[i] = 0;
    }
}

// Function to perform double hashing and insert an element into the hash table
void insert(Hash* hash, int key) {
    int hash1 = key % TABLE_SIZE;
    int hash2 = 7 - (key % 7); // Choose a prime number smaller than TABLE_SIZE

    int index = hash1;

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash->flagTable[index] == 0 || hash->flagTable[index] == -1) {
            hash->hashTable[index] = key;
            hash->flagTable[index] = 1;
            printf("Element %d inserted at index %d\n", key, index);
            return;
        }

        index = (hash1 + i * hash2) % TABLE_SIZE;
    }

    printf("Hash table is full. Element %d could not be inserted\n", key);
}

// Function to display the hash table
void displayHashTable(Hash* hash) {
    printf("Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%d: ", i);
        if (hash->flagTable[i] == 1) {
            printf("%d", hash->hashTable[i]);
        }
        printf("\n");
    }
}

int main() {
    FILE* inputFile = fopen("input.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Failed to open input.txt or output.txt\n");
        return 1;
    }

    Hash hash;
    initHashTable(&hash);

    int key;
    while (fscanf(inputFile, "%d", &key) == 1) {
        insert(&hash, key);
    }

    printf("Hash table has been generated.\n");
    displayHashTable(&hash);

    // Write the hash table to the output file
    fprintf(outputFile, "Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        fprintf(outputFile, "%d: ", i);
        if (hash.flagTable[i] == 1) {
            fprintf(outputFile, "%d", hash.hashTable[i]);
        }
        fprintf(outputFile, "\n");
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Hash table has been written to output.txt\n");

    free(hash.hashTable);
    free(hash.flagTable);

    return 0;
}
