#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a node in the maze graph
typedef struct Node {
    int row, col;
    struct Node* next;
} Node;

// Function to insert a node at the end of the linked list
void insertNode(Node** head, int row, int col) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->row = row;
    newNode->col = col;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

// Function to delete the first node in the linked list
void deleteNode(Node** head) {
    if (*head == NULL) {
        return;
    }
    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

// Function to display the maze
void displayMaze(char maze[][10], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
}

// Function to solve the maze using BFS
bool solveMaze(char maze[][10], int rows, int cols, int startRow, int startCol, int endRow, int endCol) {
    bool visited[rows][cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            visited[i][j] = false;
        }
    }

    Node* queue = NULL;
    insertNode(&queue, startRow, startCol);
    visited[startRow][startCol] = true;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (queue != NULL) {
        int currentRow = queue->row;
        int currentCol = queue->col;
        deleteNode(&queue);

        for (int i = 0; i < 4; i++) {
            int newRow = currentRow + dx[i];
            int newCol = currentCol + dy[i];

            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                maze[newRow][newCol] != '#' && !visited[newRow][newCol]) {
                insertNode(&queue, newRow, newCol);
                visited[newRow][newCol] = true;
                maze[newRow][newCol] = '*';

                if (newRow == endRow && newCol == endCol) {
                    return true;
                }
            }
        }
    }

    return false;
}

int main() {
    int rows, cols;
    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    char maze[10][10];

    printf("Enter the maze:\n");
    for (int i = 0; i < rows; i++) {
        scanf("%s", maze[i]);
    }

    int startRow, startCol, endRow, endCol;
    printf("Enter the starting row and column: ");
    scanf("%d %d", &startRow, &startCol);
    printf("Enter the ending row and column: ");
    scanf("%d %d", &endRow, &endCol);

    printf("\nMaze before solving:\n");
    displayMaze(maze, rows, cols);

    if (solveMaze(maze, rows, cols, startRow, startCol, endRow, endCol)) {
        printf("\nMaze after solving:\n");
        displayMaze(maze, rows, cols);
        printf("\nPath from start to end:\n");
        printf("(%d, %d) ", startRow, startCol);

        Node* solutionPath = NULL;
        insertNode(&solutionPath, endRow, endCol);

        while (solutionPath != NULL) {
            printf("-> (%d, %d) ", solutionPath->row, solutionPath->col);
            solutionPath = solutionPath->next;
        }
    } else {
        printf("\nNo path found to the destination.\n");
    }

    return 0;
}
