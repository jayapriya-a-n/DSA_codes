#include <stdio.h>
#include <stdlib.h>

#define MAX_ITEMS 100

typedef struct {
    int weight;
    int value;
} Item;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack(int W, Item items[], int n) {
    int i, w;
    int **K = (int **)malloc((n + 1) * sizeof(int *));
    for (i = 0; i <= n; i++) {
        K[i] = (int *)malloc((W + 1) * sizeof(int));
    }

    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                K[i][w] = 0;
            } else if (items[i - 1].weight <= w) {
                K[i][w] = max(items[i - 1].value + K[i - 1][w - items[i - 1].weight], K[i - 1][w]);
            } else {
                K[i][w] = K[i - 1][w];
            }
        }
    }

    int result = K[n][W];

    for (i = 0; i <= n; i++) {
        free(K[i]);
    }
    free(K);

    return result;
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Failed to open files.\n");
        return 1;
    }

    int W; // Knapsack capacity
    int n; // Number of items

    fscanf(inputFile, "%d %d", &W, &n);

    Item items[MAX_ITEMS];
    int i;

    for (i = 0; i < n; i++) {
        fscanf(inputFile, "%d %d", &items[i].weight, &items[i].value);
    }

    int max_value = knapsack(W, items, n);

    fprintf(outputFile, "Maximum value: %d\n", max_value);

    fclose(inputFile);
    fclose(outputFile);

    printf("Output saved to output.txt\n");

    return 0;
}
