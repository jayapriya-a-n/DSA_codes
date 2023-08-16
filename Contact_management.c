#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a contact
struct Contact {
    char name[50];
    char phone[20];
    struct Contact *left;
    struct Contact *right;
};

// Function to create a new contact node
struct Contact *createContact(char *name, char *phone) {
    struct Contact *newContact = (struct Contact *)malloc(sizeof(struct Contact));
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    newContact->left = NULL;
    newContact->right = NULL;
    return newContact;
}

// Function to insert a contact into the BST
struct Contact *insertContact(struct Contact *root, char *name, char *phone) {
    if (root == NULL) {
        return createContact(name, phone);
    }

    if (strcmp(name, root->name) < 0) {
        root->left = insertContact(root->left, name, phone);
    } else if (strcmp(name, root->name) > 0) {
        root->right = insertContact(root->right, name, phone);
    }

    return root;
}

// Function to perform inorder traversal
void inorder(struct Contact *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("Name: %s, Phone: %s\n", root->name, root->phone);
        inorder(root->right);
    }
}

// Function to perform preorder traversal
void preorder(struct Contact *root) {
    if (root != NULL) {
        printf("Name: %s, Phone: %s\n", root->name, root->phone);
        preorder(root->left);
        preorder(root->right);
    }
}

// Function to perform postorder traversal
void postorder(struct Contact *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("Name: %s, Phone: %s\n", root->name, root->phone);
    }
}

int main() {
    struct Contact *root = NULL;
    int n;
    char name[50], phone[20];

    printf("Enter the number of contacts: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter name for contact %d: ", i + 1);
        scanf("%s", name);
        printf("Enter phone number for contact %d: ", i + 1);
        scanf("%s", phone);
        root = insertContact(root, name, phone);
    }

    printf("\nInorder Traversal:\n");
    inorder(root);

    printf("\nPreorder Traversal:\n");
    preorder(root);

    printf("\nPostorder Traversal:\n");
    postorder(root);

    return 0;
}
