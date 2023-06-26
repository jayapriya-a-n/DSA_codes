#include <stdio.h>
#include <stdlib.h>
#include<time.h>

// Structure for a binary tree node
struct Node
{
    struct Node* left;
    int data;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int item)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = item;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a new node into the binary search tree
struct Node* insert(struct Node* root, int data)
{
    if (root == NULL)
        return createNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

// Function to perform inorder traversal of the binary search tree and save the data to a file
void inorder(struct Node* root, FILE* file) {
    if (root != NULL)
    {
        inorder(root->left, file);
        fprintf(file, "%d ", root->data);
        inorder(root->right, file);
    }
}

// Function to perform preorder traversal of the binary search tree and save the data to a file
void preorder(struct Node* root, FILE* file) {
    if (root != NULL) {
        fprintf(file, "%d ", root->data);
        preorder(root->left, file);
        preorder(root->right, file);
    }
}

// Function to perform postorder traversal of the binary search tree and save the data to a file
void postorder(struct Node* root, FILE* file) {
    if (root != NULL) {
        postorder(root->left, file);
        postorder(root->right, file);
        fprintf(file, "%d ", root->data);
    }
}

int main() {
    // Generate random numbers and save them to input.txt
    int n, p, q;
    FILE *fp;

    printf("Enter the number of elements to generate: ");
    scanf("%d", &n);

    printf("Enter the range (P Q) to generate numbers in: ");
    scanf("%d %d", &p, &q);

    fp = fopen("Input.txt", "w");

    srand(time(0)); // seed for random number generator

    for (int i = 0; i < n; i++) {
        int num = rand() % (q - p + 1) + p; // generate random number in range [p, q]
        fprintf(fp, "%d ", num); // write number to file
    }

    fclose(fp);

    // Read the random numbers from input.txt and build the binary search tree
    FILE* inputFileRead = fopen("input.txt", "r");
    if (inputFileRead == NULL) {
        printf("Failed to open input.txt\n");
        return 1;
    }

    struct Node* root = NULL;
    int number;
    while (fscanf(inputFileRead, "%d", &number) == 1) {
        root = insert(root, number);
    }

    fclose(inputFileRead);

    // Perform inorder traversal and save the data to inorder.txt
    FILE* inorderFile = fopen("inorder.txt", "w");
    if (inorderFile == NULL) {
        printf("Failed to open inorder.txt\n");
        return 1;
    }
clock_t start, end;
     double cpu_time_used;

     start = clock();
    inorder(root, inorderFile);
    fclose(inorderFile);

    // Perform preorder traversal and save the data to preorder.txt
    FILE* preorderFile = fopen("preorder.txt", "w");
    if (preorderFile == NULL) {
        printf("Failed to open preorder.txt\n");
        return 1;
    }

    preorder(root, preorderFile);
    fclose(preorderFile);
    end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
     printf("%f",cpu_time_used);

    // Perform postorder traversal and save the data to postorder.txt
    FILE* postorderFile = fopen("postorder.txt", "w");
    if (postorderFile == NULL) {
        printf("Failed to open postorder.txt\n");
        return 1;
    }

    postorder(root, postorderFile);
    fclose(postorderFile);

    printf("Traversal and file operations completed successfully.\n");

    return 0;
}

