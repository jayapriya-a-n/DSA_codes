#include <stdio.h>
#include <stdlib.h>

// Node structure for linked list
typedef struct Node
{
    int data;
    struct Node* next;
} Node;

// Function to insert a new node at the end of the linked list
void insert(Node** head, int value)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        Node* current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to read the numbers from the input file and store them in a linked list
void readFromFile(Node** head, const char* fileName)
{
    FILE* file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }

    int num;
    while (fscanf(file, "%d", &num) == 1)
    {
        insert(head, num); // Insert the number into the linked list
    }

    fclose(file);
}

// Function to sort the X numbers from the linked list
void sortList(Node** head, int X)
{
    int i, j, k, temp;
    Node* current;
    Node* next;

    for (i = 0, current = *head; i < X && current != NULL; i++, current = current->next)
    {
        for (j = i + 1, next = current->next; j < X && next != NULL; j++, next = next->next)
        {
            if (current->data > next->data)
            {
                temp = current->data;
                current->data = next->data;
                next->data = temp;
            }
        }
    }
}

// Function to write the linked list values to a file
void writeToFile(Node* head, const char* fileName)
{
    FILE* file = fopen(fileName, "w");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }

    Node* current = head;
    while (current != NULL)
    {
        fprintf(file, "%d\n", current->data); // Write the data to the file
        current = current->next;
    }

    fclose(file);
}

// Function to free the memory allocated for the linked list
void freeList(Node** head)
{
    Node* current = *head;
    Node* next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

int main()
{
    int X;
    printf("Enter the number of numbers to sort: ");
    scanf("%d", &X);
    Node* head = NULL;
    readFromFile(&head, "Input.txt"); // Read the numbers from the input file and store them in a linked list
    sortList(&head, X);               // Sort the X numbers from the linked list
    writeToFile(head, "Output.txt");  // Write the sorted numbers to a file
    freeList(&head);                  // Free the memory allocated for the linked list
    printf("Sorted numbers have been written to Output.txt\n");
    return 0;
}
