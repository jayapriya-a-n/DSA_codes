#include <stdio.h>
#include <stdlib.h>

// Structure for AVL tree node
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

int max(int a, int b)
{
    if(a>b)
        return a;
    return b;
}
// Function to get the height of a node
int height(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to calculate the balance factor of a node
int balanceFactor(struct Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to rotate a node to the left
struct Node* rotateLeft(struct Node* y) {
    struct Node* x = y->right;
    struct Node* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

// Function to rotate a node to the right
struct Node* rotateRight(struct Node* x) {
    struct Node* y = x->left;
    struct Node* T2 = y->right;

    y->right = x;
    x->left = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

// Function to create a new AVL tree node
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Function to insert a key into the AVL tree
struct Node* insert(struct Node* node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;  // Duplicate keys are not allowed

    // Update height of the current node
    node->height = 1 + max(height(node->left), height(node->right));

    // Perform rotations to maintain balance
    int balance = balanceFactor(node);

    // Left Left case
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    // Right Right case
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    // Left Right case
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left case
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Function to find the node with the minimum key in a tree
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node with a given key from the AVL tree
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;  // Copy the contents of the non-empty child
            free(temp);
        } else {
            // Node with two children: Get the inorder successor (smallest
            // in the right subtree)
            struct Node* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // Update height of the current node
    root->height = 1 + max(height(root->left), height(root->right));

    // Perform rotations to maintain balance
    int balance = balanceFactor(root);

    // Left Left case
    if (balance > 1 && balanceFactor(root->left) >= 0)
        return rotateRight(root);

    // Left Right case
    if (balance > 1 && balanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Right case
    if (balance < -1 && balanceFactor(root->right) <= 0)
        return rotateLeft(root);

    // Right Left case
    if (balance < -1 && balanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Function to perform inorder traversal of the AVL tree
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, key;

    do {
        printf("\nArmy Missile Launching Analysis\n");
        printf("1. Insert Missile Data\n");
        printf("2. Delete Missile Data\n");
        printf("3. Display Inorder\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter missile key: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Enter missile key to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                break;
            case 3:
                printf("Inorder traversal: ");
                inorderTraversal(root);
                printf("\n");
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
