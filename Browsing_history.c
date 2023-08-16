#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a browsing history node
struct HistoryNode {
    char url[100];
    struct HistoryNode *prev;
    struct HistoryNode *next;
};

// Function to create a new history node
struct HistoryNode *createNode(char url[]) {
    struct HistoryNode *node = (struct HistoryNode *)malloc(sizeof(struct HistoryNode));
    strcpy(node->url, url);
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// Function to add a new history item to the browsing history
void addHistory(struct HistoryNode **head, char url[]) {
    struct HistoryNode *newNode = createNode(url);
    if (*head == NULL) {
        *head = newNode;
    } else {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    }
}

// Function to display the browsing history
void displayHistory(struct HistoryNode *head) {
    printf("Browsing History:\n");
    struct HistoryNode *current = head;
    while (current != NULL) {
        printf("%s\n", current->url);
        current = current->next;
    }
}

int main() {
    struct HistoryNode *historyHead = NULL;
    int choice;
    char url[100];

    do {
        printf("\nMenu:\n");
        printf("1. Add URL to history\n");
        printf("2. Display history\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter URL: ");
                scanf("%s", url);
                addHistory(&historyHead, url);
                printf("URL added to history.\n");
                break;
            case 2:
                displayHistory(historyHead);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 3);

    // Free allocated memory
    struct HistoryNode *current = historyHead;
    while (current != NULL) {
        struct HistoryNode *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
