#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

struct Graph {
    int numNodes;
    int adjacencyMatrix[MAX_NODES][MAX_NODES];
};

struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

bool isFull(struct Queue* queue) {
    return (queue->size == queue->capacity);
}

bool isEmpty(struct Queue* queue) {
    return (queue->size == 0);
}

void enqueue(struct Queue* queue, int item) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size++;
}

int dequeue(struct Queue* queue) {
    if (isEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

struct Graph* createGraph(int numNodes) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numNodes = numNodes;
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            graph->adjacencyMatrix[i][j] = 0;
        }
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    graph->adjacencyMatrix[src][dest] = 1;
}

void deleteEdge(struct Graph* graph, int src, int dest) {
    graph->adjacencyMatrix[src][dest] = 0;
}

void displayGraph(struct Graph* graph) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->numNodes; i++) {
        for (int j = 0; j < graph->numNodes; j++) {
            printf("%d ", graph->adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

bool hasCycle(struct Graph* graph, int startNode, bool visited[], int parent[]) {
    struct Queue* queue = createQueue(MAX_NODES);
    visited[startNode] = true;
    enqueue(queue, startNode);

    while (!isEmpty(queue)) {
        int currentNode = dequeue(queue);
        for (int neighbor = 0; neighbor < graph->numNodes; neighbor++) {
            if (graph->adjacencyMatrix[currentNode][neighbor]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    enqueue(queue, neighbor);
                    parent[neighbor] = currentNode;
                } else if (parent[currentNode] != neighbor) {
                    // Found a cycle
                    free(queue);
                    return true;
                }
            }
        }
    }
    free(queue);
    return false;
}

bool containsCycle(struct Graph* graph) {
    bool visited[MAX_NODES] = { false };
    int parent[MAX_NODES];
    for (int i = 0; i < graph->numNodes; i++) {
        parent[i] = -1;
    }

    for (int i = 0; i < graph->numNodes; i++) {
        if (!visited[i] && hasCycle(graph, i, visited, parent)) {
            return true;
        }
    }
    return false;
}

int main() {
    int numNodes, numEdges;
    printf("Enter the number of nodes and edges: ");
    scanf("%d %d", &numNodes, &numEdges);

    struct Graph* graph = createGraph(numNodes);

    printf("Enter the edges (source destination):\n");
    for (int i = 0; i < numEdges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    displayGraph(graph);

    if (containsCycle(graph)) {
        printf("The graph contains cycles.\n");
    } else {
        printf("The graph does not contain cycles.\n");
    }

    return 0;
}
