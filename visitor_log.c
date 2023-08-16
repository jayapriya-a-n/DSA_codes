#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for each visitor
struct Visitor {
    char name[50];
    struct Visitor* next;
};

// Function to add a new visitor to the linked list
struct Visitor* addVisitor(struct Visitor* head, const char* name) {
    struct Visitor* newVisitor = (struct Visitor*)malloc(sizeof(struct Visitor));
    if (newVisitor == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newVisitor->name, name);
    newVisitor->next = head;
    return newVisitor;
}

// Function to display the visitor log
void displayVisitorLog(struct Visitor* head) {
    printf("\nVisitor Log:\n");
    while (head != NULL) {
        printf("- %s\n", head->name);
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct Visitor* visitorLog = NULL;
    char name[50];

    int choice;
    do {
        printf("Menu:\n");
        printf("1. Add Visitor\n");
        printf("2. Display Visitor Log\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter visitor name: ");
                scanf("%s", name);
                visitorLog = addVisitor(visitorLog, name);
                printf("Visitor added successfully!\n");
                break;
            case 2:
                displayVisitorLog(visitorLog);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    } while (choice != 3);

    // Free allocated memory for the linked list
    while (visitorLog != NULL) {
        struct Visitor* temp = visitorLog;
        visitorLog = visitorLog->next;
        free(temp);
    }

    return 0;
}
