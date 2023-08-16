#include <stdio.h>

#define N 8 // Change N for different board sizes

int board[N][N];
int stack[N];
int top = -1;

int isSafe(int row, int col) {
    int i;
    for (i = 0; i < row; i++) {
        if (board[i][col] == 1 ||
            (col - (row - i) >= 0 && board[i][col - (row - i)] == 1) ||
            (col + (row - i) < N && board[i][col + (row - i)] == 1)) {
            return 0;
        }
    }
    return 1;
}

void printSolution() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void solveNQueens() {
    int row = 0, col = 0;

    while (row < N) {
        if (col >= N) {
            if (top == -1) {
                break;
            }

            row--;
            col = stack[top];
            board[row][col] = 0;
            top--;
            col++;
        }

        if (isSafe(row, col)) {
            board[row][col] = 1;
            stack[++top] = col;
            col = 0;
            row++;
        } else {
            col++;
        }
    }

    if (row == N) {
        printSolution();
    } else {
        printf("No solution found.\n");
    }
}

int main() {
    solveNQueens();
    return 0;
}
