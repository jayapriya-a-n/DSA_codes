#include <stdio.h>
#include <stdlib.h>

struct AVLNode {
    int data;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
};

typedef struct AVLNode AVLNode;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(AVLNode *node) {
    if (node == NULL)
        return -1;
    return node->height;
}

int getBalanceFactor(AVLNode *node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

AVLNode *rotateRight(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

AVLNode *rotateLeft(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

AVLNode *insert(AVLNode *root, int data) {
    if (root == NULL) {
        AVLNode *newNode = (AVLNode *)malloc(sizeof(AVLNode));
        newNode->data = data;
        newNode->height = 0;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    else
        return root;  // Duplicate data not allowed

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalanceFactor(root);

    if (balance > 1 && data < root->left->data)
        return rotateRight(root);

    if (balance < -1 && data > root->right->data)
        return rotateLeft(root);

    if (balance > 1 && data > root->left->data) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && data < root->right->data) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

AVLNode *getMinValueNode(AVLNode *node) {
    AVLNode *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

AVLNode *deleteNode(AVLNode *root, int data) {
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if (root->left == NULL || root->right == NULL) {
            AVLNode *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            AVLNode *temp = getMinValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalanceFactor(root);

    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rotateRight(root);

    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return rotateLeft(root);

    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void inorderTraversal(AVLNode *root) {
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

float findMedian(AVLNode *root, int count, int currentCount) {
    if (root == NULL)
        return 0;

    if (currentCount == count / 2) {
        if (count % 2 == 0) {
            AVLNode *pred = getMinValueNode(root->left);
            return (float)(pred->data + root->data) / 2;
        } else {
            return (float)root->data;
        }
    }

    if (currentCount < count / 2) {
        return findMedian(root->right, count, currentCount + 1);
    } else {
        return findMedian(root->left, count, currentCount - 1);
    }
}

int main() {
    AVLNode *root = NULL;
    int n, num;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        root = insert(root, num);
    }

    printf("Inorder traversal of the AVL tree: ");
    inorderTraversal(root);
    printf("\n");

    int count = n;
    float median = findMedian(root, count, 0);
    printf("Median of the numbers: %.2f\n", median);

    int numToDelete;
    printf("Enter a number to delete from the tree: ");
    scanf("%d", &numToDelete);
    root = deleteNode(root, numToDelete);

    printf("Inorder traversal of the AVL tree after deletion: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
