/*1.	Write a C program to read  text lines  from the following interfaces
a.	User input (maximum 10 lines to be read)
Use user-defined functions and display the longest line read.
Do not use any inbuilt function. */

#include <stdio.h>

#define MAX_LINES 10  // Maximum number of lines to read
#define MAX_LENGTH 100  // Maximum length of each line

void readLines(char lines[MAX_LINES][MAX_LENGTH], int *numLines);
int findLongestLine(char lines[MAX_LINES][MAX_LENGTH], int numLines);

int main() {
    char lines[MAX_LINES][MAX_LENGTH];
    int numLines = 0;

    readLines(lines, &numLines);

    if (numLines > 0) {
        int longestLineIndex = findLongestLine(lines, numLines);
        printf("The longest line is:\n%s", lines[longestLineIndex]);
    } else {
        printf("No lines were entered.\n");
    }

    return 0;
}

// Reads up to MAX_LINES lines of text from user input
// Stores the lines in the lines array and updates numLines
void readLines(char lines[MAX_LINES][MAX_LENGTH], int *numLines) {
    printf("Enter up to %d lines of text:\n", MAX_LINES);
    for (int i = 0; i < MAX_LINES; i++) {
        if (gets(lines[i], MAX_LENGTH, stdin) == NULL)
        {
            break;  // Reached end of input
        }
        (*numLines)++;
    }
}

// Finds the index of the longest line in the lines array
int findLongestLine(char lines[MAX_LINES][MAX_LENGTH], int numLines) {
    int longestLineIndex = 0;
    int longestLineLength = 0;

    for (int i = 0; i < numLines; i++) {
        int lineLength = 0;
        while (lines[i][lineLength] != '\0' )
        {
            lineLength++;
        }
        if (lineLength > longestLineLength) {
            longestLineIndex = i;
            longestLineLength = lineLength;
        }
    }

    return longestLineIndex;
}

