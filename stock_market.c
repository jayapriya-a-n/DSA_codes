#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a stock
struct Stock {
    char symbol[10];
    float price;
    struct Stock *left;
    struct Stock *right;
    int height;
};

// Function to calculate the height of a node
int height(struct Stock *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to calculate the balance factor of a node
int balanceFactor(struct Stock *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to perform a right rotation
struct Stock *rightRotate(struct Stock *y) {
    struct Stock *x = y->left;
    struct Stock *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

// Function to perform a left rotation
struct Stock *leftRotate(struct Stock *x) {
    struct Stock *y = x->right;
    struct Stock *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

// Function to insert a stock into the AVL tree
struct Stock *insert(struct Stock *root, char symbol[], float price) {
    if (root == NULL) {
        struct Stock *newStock = (struct Stock *)malloc(sizeof(struct Stock));
        strcpy(newStock->symbol, symbol);
        newStock->price = price;
        newStock->left = NULL;
        newStock->right = NULL;
        newStock->height = 1;
        return newStock;
    }

    if (strcmp(symbol, root->symbol) < 0)
        root->left = insert(root->left, symbol, price);
    else if (strcmp(symbol, root->symbol) > 0)
        root->right = insert(root->right, symbol, price);
    else // Duplicate symbols not allowed
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = balanceFactor(root);

    // Left Left Case
    if (balance > 1 && strcmp(symbol, root->left->symbol) < 0)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && strcmp(symbol, root->right->symbol) > 0)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && strcmp(symbol, root->left->symbol) > 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && strcmp(symbol, root->right->symbol) < 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to find the node with the minimum value
struct Stock *minValueNode(struct Stock *node) {
    struct Stock *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a stock from the AVL tree
struct Stock *deleteNode(struct Stock *root, char symbol[]) {
    if (root == NULL)
        return root;

    if (strcmp(symbol, root->symbol) < 0)
        root->left = deleteNode(root->left, symbol);
    else if (strcmp(symbol, root->symbol) > 0)
        root->right = deleteNode(root->right, symbol);
    else {
        // Node with only one child or no child
        if (root->left == NULL || root->right == NULL) {
            struct Stock *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            struct Stock *temp = minValueNode(root->right);
            strcpy(root->symbol, temp->symbol);
            root->price = temp->price;
            root->right = deleteNode(root->right, temp->symbol);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = balanceFactor(root);

    // Left Left Case
    if (balance > 1 && balanceFactor(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && balanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && balanceFactor(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && balanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to perform inorder traversal and display stocks
void inorderTraversal(struct Stock *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Symbol: %s, Price: %.2f\n", root->symbol, root->price);
        inorderTraversal(root->right);
    }
}

// Function to calculate the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    struct Stock *root = NULL;
    int choice;
    char symbol[10];
    float price;

    do {
        printf("1. Insert Stock\n");
        printf("2. Delete Stock\n");
        printf("3. Display Inorder\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter stock symbol: ");
                scanf("%s", symbol);
                printf("Enter stock price: ");
                scanf("%f", &price);
                root = insert(root, symbol, price);
                break;
            case 2:
                printf("Enter stock symbol to delete: ");
                scanf("%s", symbol);
                root = deleteNode(root, symbol);
                break;
            case 3:
                printf("Stocks in ascending order of symbols:\n");
                inorderTraversal(root);
                printf("\n");
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    // TODO: Free memory allocated for the tree nodes before exiting

    return 0;
}
