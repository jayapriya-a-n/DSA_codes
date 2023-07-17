#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// Function to perform quadratic probing and insert a key into the hash table
void insertKey(int hashTable[], int key) {
    int index = key % TABLE_SIZE;
    int i = 1;

    while (hashTable[index] != -1) {
        index = (index + i * i) % TABLE_SIZE;
        i++;
    }

    hashTable[index] = key;
}

// Function to display the contents of the hash table
void displayHashTable(int hashTable[]) {
    printf("Hash Table: ");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != -1) {
            printf("%d ", hashTable[i]);
        } else {
            printf("- ");
        }
    }
    printf("\n");
}

int main() {
    FILE* inputFile = fopen("input.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Failed to open input.txt or output.txt\n");
        return 1;
    }

    int hashTable[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = -1;
    }

    int key;
    while (fscanf(inputFile, "%d", &key) != EOF) {
        insertKey(hashTable, key);
    }

    fprintf(outputFile, "Hash Table: ");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != -1) {
            fprintf(outputFile, "%d ", hashTable[i]);
        } else {
            fprintf(outputFile, "- ");
        }
    }
    fprintf(outputFile, "\n");

    fclose(inputFile);
    fclose(outputFile);

    printf("Hash table has been written to output.txt\n");

    return 0;
}
