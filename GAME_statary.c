#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

// Structure to represent a node in the graph
struct Node {
    int data;
    struct Node* next;
};

// Function to insert an edge (connect nodes)
void insertEdge(struct Node* adjList[], int u, int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = v;
    newNode->next = adjList[u];
    adjList[u] = newNode;
}

// Function to perform DFS traversal on the graph
void DFS(struct Node* adjList[], int visited[], int current, int target) {
    visited[current] = 1;
    printf("%d ", current);

    struct Node* temp = adjList[current];
    while (temp != NULL) {
        int neighbor = temp->data;
        if (!visited[neighbor]) {
            if (neighbor == target) {
                printf("%d ", target);
                printf("\nPath Found!\n");
                exit(0);
            }
            DFS(adjList, visited, neighbor, target);
        }
        temp = temp->next;
    }
}

int main() {
    int numNodes, numEdges;
    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    struct Node* adjList[MAX_NODES];
    for (int i = 0; i < MAX_NODES; i++) {
        adjList[i] = NULL;
    }

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    printf("Enter the edges (u v):\n");
    for (int i = 0; i < numEdges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        insertEdge(adjList, u, v);
    }

    int startNode, targetNode;
    printf("Enter the starting node: ");
    scanf("%d", &startNode);
    printf("Enter the target node: ");
    scanf("%d", &targetNode);

    int visited[MAX_NODES] = {0};
    printf("DFS Path: ");
    DFS(adjList, visited, startNode, targetNode);

    printf("Path not found.\n");

    return 0;
}
