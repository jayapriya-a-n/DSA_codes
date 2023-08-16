#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for AVL tree node
struct Node {
    char name[50];
    double price;
    int height;
    struct Node *left;
    struct Node *right;
};

// Function to get the height of a node
int height(struct Node *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to calculate the balance factor of a node
int balanceFactor(struct Node *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to rotate a subtree to the right
struct Node *rotateRight(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + fmax(height(y->left), height(y->right));
    x->height = 1 + fmax(height(x->left), height(x->right));

    return x;
}

// Function to rotate a subtree to the left
struct Node *rotateLeft(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + fmax(height(x->left), height(x->right));
    y->height = 1 + fmax(height(y->left), height(y->right));

    return y;
}

// Function to insert a new node into the AVL tree
struct Node *insert(struct Node *node, char name[], double price) {
    if (node == NULL) {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        strcpy(newNode->name, name);
        newNode->price = price;
        newNode->height = 1;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (strcmp(name, node->name) < 0)
        node->left = insert(node->left, name, price);
    else if (strcmp(name, node->name) > 0)
        node->right = insert(node->right, name, price);
    else
        return node;

    node->height = 1 + fmax(height(node->left), height(node->right));

    int balance = balanceFactor(node);

    // Left Left Case
    if (balance > 1 && strcmp(name, node->left->name) < 0)
        return rotateRight(node);

    // Right Right Case
    if (balance < -1 && strcmp(name, node->right->name) > 0)
        return rotateLeft(node);

    // Left Right Case
    if (balance > 1 && strcmp(name, node->left->name) > 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && strcmp(name, node->right->name) < 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Function to find the node with the minimum value
struct Node *findMinNode(struct Node *node) {
    struct Node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node from the AVL tree
struct Node *deleteNode(struct Node *root, char name[]) {
    if (root == NULL)
        return root;

    if (strcmp(name, root->name) < 0)
        root->left = deleteNode(root->left, name);
    else if (strcmp(name, root->name) > 0)
        root->right = deleteNode(root->right, name);
    else {
        if (root->left == NULL || root->right == NULL) {
            struct Node *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            struct Node *temp = findMinNode(root->right);
            strcpy(root->name, temp->name);
            root->price = temp->price;
            root->right = deleteNode(root->right, temp->name);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + fmax(height(root->left), height(root->right));

    int balance = balanceFactor(root);

    // Left Left Case
    if (balance > 1 && balanceFactor(root->left) >= 0)
        return rotateRight(root);

    // Right Right Case
    if (balance < -1 && balanceFactor(root->right) <= 0)
        return rotateLeft(root);

    // Left Right Case
    if (balance > 1 && balanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Left Case
    if (balance < -1 && balanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Function to perform an inorder traversal of the AVL tree
void inorderTraversal(struct Node *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%s: %.2lf\n", root->name, root->price);
        inorderTraversal(root->right);
    }
}

int main() {
    struct Node *root = NULL;
    int choice;
    char name[50];
    double price;

    do {
        printf("\n1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display in ascending order\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter cryptocurrency name: ");
                scanf("%s", name);
                printf("Enter cryptocurrency price: ");
                scanf("%lf", &price);
                root = insert(root, name, price);
                break;
            case 2:
                printf("Enter cryptocurrency name to delete: ");
                scanf("%s", name);
                root = deleteNode(root, name);
                break;
            case 3:
                printf("Cryptocurrency prices in ascending order:\n");
                inorderTraversal(root);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 4);

    return 0;
}
