#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent an event
struct Event {
    char name[50];
    int date;
    struct Event* left;
    struct Event* right;
};

// Function to create a new event node
struct Event* createEvent(const char* name, int date) {
    struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));
    strcpy(newEvent->name, name);
    newEvent->date = date;
    newEvent->left = NULL;
    newEvent->right = NULL;
    return newEvent;
}

// Function to insert an event into the binary search tree
struct Event* insertEvent(struct Event* root, const char* name, int date) {
    if (root == NULL)
        return createEvent(name, date);

    if (date < root->date)
        root->left = insertEvent(root->left, name, date);
    else if (date > root->date)
        root->right = insertEvent(root->right, name, date);

    return root;
}

// Inorder traversal of the binary search tree
void inorderTraversal(struct Event* root) {
    if (root == NULL)
        return;

    inorderTraversal(root->left);
    printf("Event: %s, Date: %d\n", root->name, root->date);
    inorderTraversal(root->right);
}

// Preorder traversal of the binary search tree
void preorderTraversal(struct Event* root) {
    if (root == NULL)
        return;

    printf("Event: %s, Date: %d\n", root->name, root->date);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// Postorder traversal of the binary search tree
void postorderTraversal(struct Event* root) {
    if (root == NULL)
        return;

    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("Event: %s, Date: %d\n", root->name, root->date);
}

int main() {
    struct Event* root = NULL;
    int numEvents;

    printf("Enter the number of events: ");
    scanf("%d", &numEvents);

    for (int i = 0; i < numEvents; i++) {
        char eventName[50];
        int eventDate;

        printf("Enter event name: ");
        scanf("%s", eventName);

        printf("Enter event date: ");
        scanf("%d", &eventDate);

        root = insertEvent(root, eventName, eventDate);
    }

    printf("\nInorder Traversal:\n");
    inorderTraversal(root);

    printf("\nPreorder Traversal:\n");
    preorderTraversal(root);

    printf("\nPostorder Traversal:\n");
    postorderTraversal(root);

    return 0;
}
