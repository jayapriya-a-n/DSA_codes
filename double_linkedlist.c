#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }
}

void deleteNode(Node** head, int data) {
    if (*head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return;
    }

    Node* current = *head;

    while (current != NULL) {
        if (current->data == data) {
            if (current == *head) {
                *head = current->next;
                if (*head != NULL) {
                    (*head)->prev = NULL;
                }
            } else {
                Node* prevNode = current->prev;
                Node* nextNode = current->next;

                if (prevNode != NULL) {
                    prevNode->next = nextNode;
                }
                if (nextNode != NULL) {
                    nextNode->prev = prevNode;
                }
            }
            free(current);
            printf("Node with value %d deleted.\n", data);
            return;
        }
        current = current->next;
    }

    printf("Node with value %d not found in the list.\n", data);
}

void displayList(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node* current = head;
    printf("List: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void clearList(Node** head) {
    Node* current = *head;

    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    *head = NULL;
    printf("List cleared.\n");
}

int main() {
    Node* head = NULL;
    int option = 0;

    while (option != 4) {
        printf("Doubly Linked List Menu:\n");
        printf("1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Display List\n");
        printf("4. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &option);

        switch (option) {
            case 1: {
                int data;
                printf("Enter value to insert: ");
                scanf("%d", &data);
                insertAtEnd(&head, data);
                break;
            }
            case 2: {
                int data;
                printf("Enter value to delete: ");
                scanf("%d", &data);
                deleteNode(&head, data);
                break;
            }
            case 3:
                displayList(head);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }

    clearList(&head);

    return 0;
}
