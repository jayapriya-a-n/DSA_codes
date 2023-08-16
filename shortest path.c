#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

struct Node {
    int data;
    struct Node* next;
};

struct Graph {
    int numNodes;
    struct Node* adjacencyList[MAX_NODES];
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;
}

void BFS(struct Graph* graph, int start, int end) {
    int visited[MAX_NODES] = {0}; // 0 represents unvisited, 1 represents visited
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    queue[rear++] = start;
    visited[start] = 1;

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        if (current == end) {
            printf("\nShortest path found.\n");
            return;
        }

        struct Node* temp = graph->adjacencyList[current];
        while (temp != NULL) {
            int neighbor = temp->data;
            if (visited[neighbor] == 0) {
                queue[rear++] = neighbor;
                visited[neighbor] = 1;
            }
            temp = temp->next;
        }
    }

    printf("\nNo path found.\n");
}

void deleteGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numNodes; ++i) {
        struct Node* current = graph->adjacencyList[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph);
}

int main() {
    int numNodes, numEdges;
    printf("Enter the number of nodes and edges: ");
    scanf("%d %d", &numNodes, &numEdges);

    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numNodes = numNodes;
    for (int i = 0; i < numNodes; ++i) {
        graph->adjacencyList[i] = NULL;
    }

    printf("Enter the edges (source and destination):\n");
    for (int i = 0; i < numEdges; ++i) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        insertEdge(graph, src, dest);
    }

    int start, end;
    printf("Enter the start and end nodes for shortest path: ");
    scanf("%d %d", &start, &end);

    printf("BFS traversal:\n");
    BFS(graph, start, end);

    deleteGraph(graph);

    return 0;
}
