#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a tree node
struct TreeNode {
    char word[50];
    char meaning[100];
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new node
struct TreeNode *createNode(const char *word, const char *meaning) {
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    strcpy(newNode->word, word);
    strcpy(newNode->meaning, meaning);
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a new node into the tree
struct TreeNode *insertNode(struct TreeNode *root, const char *word, const char *meaning) {
    if (root == NULL) {
        return createNode(word, meaning);
    }

    int cmpResult = strcmp(word, root->word);
    if (cmpResult < 0) {
        root->left = insertNode(root->left, word, meaning);
    } else if (cmpResult > 0) {
        root->right = insertNode(root->right, word, meaning);
    }

    return root;
}

// Function to perform inorder traversal
void inorderTraversal(struct TreeNode *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%s: %s\n", root->word, root->meaning);
        inorderTraversal(root->right);
    }
}

// Function to perform preorder traversal
void preorderTraversal(struct TreeNode *root) {
    if (root != NULL) {
        printf("%s: %s\n", root->word, root->meaning);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Function to perform postorder traversal
void postorderTraversal(struct TreeNode *root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%s: %s\n", root->word, root->meaning);
    }
}

int main() {
    struct TreeNode *root = NULL;
    int n;
    printf("Enter the number of words: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char word[50];
        char meaning[100];
        printf("Enter word %d: ", i + 1);
        scanf("%s", word);
        printf("Enter meaning for %s: ", word);
        scanf(" %[^\n]s", meaning);  // Read the meaning with spaces
        root = insertNode(root, word, meaning);
    }

    printf("\nInorder Traversal:\n");
    inorderTraversal(root);

    printf("\nPreorder Traversal:\n");
    preorderTraversal(root);

    printf("\nPostorder Traversal:\n");
    postorderTraversal(root);

    return 0;
}
