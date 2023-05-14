/*1.	Write a C program to read  text lines  from the following interfaces
b. files
Use user-defined functions and display the longest line read.
Do not use any inbuilt function. */

#include <stdio.h>

#define MAXLEN 100  // Maximum length of each line

void readFile(char *filename, char str[][MAXLEN], int *n)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File could not be opened\n");
        return;
    }
    while (fgets(str[*n], MAXLEN, file) != NULL)
    {
        (*n)++;
    }
    fclose(file);
}

int Longest(char str[][MAXLEN], int n)
{
    int li = 0;
    int ll= 0;
    for (int i = 0; i < n; i++)
    {
        int Length = 0;
        while (str[i][Length] != '\0' )
        {
            Length++;
        }
        if (Length > ll)
        {
            li = i;
            ll = Length;
        }
    }
    return li;
}


int main()
{
    char str[100][MAXLEN];
    int n = 0;
    char *filename = "poems.txt";
    readFile(filename, str, &n);
    if (n > 0)
    {
        int l = Longest(str, n);//longestLine from file
        printf("The longest line is:\n%s", str[l]);
    }
    else
    {
        printf("No lines were found\n");
    }
    return 0;
}

