#include <stdio.h>
#include <stdlib.h>

// Structure to represent an employee
struct Employee {
    int empID;
    char name[50];
    struct Employee *left;
    struct Employee *right;
};

// Function to create a new employee node
struct Employee* createEmployee(int empID, const char *name) {
    struct Employee* newEmployee = (struct Employee*)malloc(sizeof(struct Employee));
    newEmployee->empID = empID;
    strcpy(newEmployee->name, name);
    newEmployee->left = NULL;
    newEmployee->right = NULL;
    return newEmployee;
}

// Function to insert an employee into the hierarchy
struct Employee* insertEmployee(struct Employee* root, int empID, const char *name) {
    if (root == NULL) {
        return createEmployee(empID, name);
    }

    if (empID < root->empID) {
        root->left = insertEmployee(root->left, empID, name);
    } else if (empID > root->empID) {
        root->right = insertEmployee(root->right, empID, name);
    }

    return root;
}

// Function to perform inorder traversal of the hierarchy
void inorderTraversal(struct Employee* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Employee ID: %d, Name: %s\n", root->empID, root->name);
        inorderTraversal(root->right);
    }
}

// Function to perform preorder traversal of the hierarchy
void preorderTraversal(struct Employee* root) {
    if (root != NULL) {
        printf("Employee ID: %d, Name: %s\n", root->empID, root->name);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Function to perform postorder traversal of the hierarchy
void postorderTraversal(struct Employee* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("Employee ID: %d, Name: %s\n", root->empID, root->name);
    }
}

int main() {
    struct Employee* root = NULL;

    int choice, empID;
    char name[50];

    do {
        printf("1. Add Employee\n");
        printf("2. Display Inorder\n");
        printf("3. Display Preorder\n");
        printf("4. Display Postorder\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &empID);
                printf("Enter Employee Name: ");
                scanf("%s", name);
                root = insertEmployee(root, empID, name);
                break;
            case 2:
                printf("Inorder Traversal:\n");
                inorderTraversal(root);
                break;
            case 3:
                printf("Preorder Traversal:\n");
                preorderTraversal(root);
                break;
            case 4:
                printf("Postorder Traversal:\n");
                postorderTraversal(root);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 5);

    // TODO: Free the allocated memory for the tree nodes before exiting

    return 0;
}
