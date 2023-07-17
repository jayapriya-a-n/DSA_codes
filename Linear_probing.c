#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct {
    int key;
    int value;
} HashEntry;

typedef struct {
    HashEntry entries[SIZE];
} HashTable;

// Function to initialize the hash table
void initHashTable(HashTable* hashTable) {
    for (int i = 0; i < SIZE; i++) {
        hashTable->entries[i].key = -1;
        hashTable->entries[i].value = -1;
    }
}

// Function to compute the hash value
int computeHash(int key) {
    return key % SIZE;
}

// Function to insert an entry into the hash table using linear probing
void insert(HashTable* hashTable, int key, int value) {
    int hashIndex = computeHash(key);
    int probeCount = 0;

    while (hashTable->entries[hashIndex].key != -1 && probeCount < SIZE) {
        hashIndex = (hashIndex + 1) % SIZE;
        probeCount++;
    }

    if (probeCount == SIZE) {
        printf("Hash table is full, unable to insert key: %d\n", key);
        return;
    }

    hashTable->entries[hashIndex].key = key;
    hashTable->entries[hashIndex].value = value;
}

// Function to search for a key in the hash table
int search(HashTable* hashTable, int key) {
    int hashIndex = computeHash(key);
    int probeCount = 0;

    while (hashTable->entries[hashIndex].key != key && hashTable->entries[hashIndex].key != -1 && probeCount < SIZE) {
        hashIndex = (hashIndex + 1) % SIZE;
        probeCount++;
    }

    if (probeCount == SIZE || hashTable->entries[hashIndex].key == -1) {
        return -1; // Key not found
    }

    return hashTable->entries[hashIndex].value;
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

    int key, value;
    while (fscanf(inputFile, "%d %d", &key, &value) == 2) {
        insert(&hashTable, key, value);
    }

    int searchKey;
    fscanf(inputFile, "%d", &searchKey);

    int searchResult = search(&hashTable, searchKey);

    if (searchResult == -1) {
        fprintf(outputFile, "Key %d not found in the hash table\n", searchKey);
    } else {
        fprintf(outputFile, "Value for key %d: %d\n", searchKey, searchResult);
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Linear probing operations have been written to output.txt\n");

    return 0;
}
