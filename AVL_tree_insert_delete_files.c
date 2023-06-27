#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// AVL Tree node structure
struct AVLNode {
    int data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
};

// Function to get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to get the height of a node
int getHeight(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to create a new AVL tree node
struct AVLNode* createNode(int data) {
    struct AVLNode* newNode = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Function to right rotate a subtree rooted with y
struct AVLNode* rightRotate(struct AVLNode* y) {
    struct AVLNode* x = y->left;
    struct AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // Return new root
    return x;
}

// Function to left rotate a subtree rooted with x
struct AVLNode* leftRotate(struct AVLNode* x) {
    struct AVLNode* y = x->right;
    struct AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    // Return new root
    return y;
}

// Function to get the balance factor of a node
int getBalance(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to insert a node into an AVL tree
struct AVLNode* insertNode(struct AVLNode* node, int data) {
    // Perform the normal BST insertion
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    else // Duplicate keys are not allowed
        return node;

    // Update the height of the current node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Get the balance factor of the current node
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the unchanged node pointer
    return node;
}

// Function to write inorder traversal to a file
void writeInorderToFile(struct AVLNode* node, FILE* file) {
    if (node != NULL) {
        writeInorderToFile(node->left, file);
        fprintf(file, "%d ", node->data);
        writeInorderToFile(node->right, file);
    }
}

// Function to write preorder traversal to a file
void writePreorderToFile(struct AVLNode* node, FILE* file) {
    if (node != NULL) {
        fprintf(file, "%d ", node->data);
        writePreorderToFile(node->left, file);
        writePreorderToFile(node->right, file);
    }
}

// Function to write postorder traversal to a file
void writePostorderToFile(struct AVLNode* node, FILE* file) {
    if (node != NULL) {
        writePostorderToFile(node->left, file);
        writePostorderToFile(node->right, file);
        fprintf(file, "%d ", node->data);
    }
}

// Function to display the tree inorder
void displayInorder(struct AVLNode* node) {
    if (node != NULL) {
        displayInorder(node->left);
        printf("%d ", node->data);
        displayInorder(node->right);
    }
}

// Function to display the tree preorder
void displayPreorder(struct AVLNode* node) {
    if (node != NULL) {
        printf("%d ", node->data);
        displayPreorder(node->left);
        displayPreorder(node->right);
    }
}

// Function to display the tree postorder
void displayPostorder(struct AVLNode* node) {
    if (node != NULL) {
        displayPostorder(node->left);
        displayPostorder(node->right);
        printf("%d ", node->data);
    }
}

int main() {
    struct AVLNode* root = NULL;
    int choice, data;

    // Generate random number based on user input and store it in input.txt
    FILE* file = fopen("input.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    printf("Enter the number of random values to generate: ");
    scanf("%d", &choice);

    srand(time(NULL));

    for (int i = 0; i < choice; i++) {
        data = rand() % 100; // Generating random number between 0 and 99
        fprintf(file, "%d ", data);
    }

    fclose(file);
    printf("Random numbers generated and stored in input.txt.\n");

    // Perform operations on AVL tree based on user's choice
    do {
        printf("\n1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Display Preorder\n");
        printf("4. Display Postorder\n");
        printf("5. Display Inorder\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to be inserted: ");
                scanf("%d", &data);
                root = insertNode(root, data);
                break;
            case 2:
                // TODO: Implement deletion function
                printf("Deletion function not implemented yet.\n");
                break;
            case 3:
                printf("Preorder Traversal: ");
                displayPreorder(root);
                break;
            case 4:
                printf("Postorder Traversal: ");
                displayPostorder(root);
                break;
            case 5:
                printf("Inorder Traversal: ");
                displayInorder(root);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid choice.\n");
        }
    } while (choice != 6);

    // Write tree traversal orders to files
    FILE* inorderFile = fopen("inorder.txt", "w");
    FILE* preorderFile = fopen("preorder.txt", "w");
    FILE* postorderFile = fopen("postorder.txt", "w");

    if (inorderFile == NULL || preorderFile == NULL || postorderFile == NULL) {
        printf("Error opening files!\n");
        return 0;
    }

    writeInorderToFile(root, inorderFile);
    writePreorderToFile(root, preorderFile);
    writePostorderToFile(root, postorderFile);

    fclose(inorderFile);
    fclose(preorderFile);
    fclose(postorderFile);

    return 0;
}
