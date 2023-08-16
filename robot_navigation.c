#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

typedef struct Graph {
    int numNodes;
    Node* adjacencyList[MAX_NODES];
} Graph;

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

void enqueue(Queue* queue, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return -1;
    }

    int data = queue->front->data;
    Node* temp = queue->front;
    queue->front = queue->front->next;
    free(temp);

    return data;
}

Graph* createGraph(int numNodes) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numNodes = numNodes;

    for (int i = 0; i < numNodes; ++i)
        graph->adjacencyList[i] = NULL;

    return graph;
}

void insertEdge(Graph* graph, int src, int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = dest;
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;
}

void bfs(Graph* graph, int startNode) {
    Queue* queue = createQueue();
    int visited[MAX_NODES] = {0};

    visited[startNode] = 1;
    enqueue(queue, startNode);

    printf("BFS traversal starting from node %d:\n", startNode);

    while (!isEmpty(queue)) {
        int currentNode = dequeue(queue);
        printf("%d ", currentNode);

        Node* neighbor = graph->adjacencyList[currentNode];
        while (neighbor) {
            int neighborNode = neighbor->data;
            if (!visited[neighborNode]) {
                visited[neighborNode] = 1;
                enqueue(queue, neighborNode);
            }
            neighbor = neighbor->next;
        }
    }

    printf("\n");
}

int main() {
    int numNodes, numEdges;
    printf("Enter the number of nodes and edges: ");
    scanf("%d %d", &numNodes, &numEdges);

    Graph* graph = createGraph(numNodes);

    printf("Enter the edges (src dest):\n");
    for (int i = 0; i < numEdges; ++i) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        insertEdge(graph, src, dest);
    }

    int startNode;
    printf("Enter the starting node for BFS: ");
    scanf("%d", &startNode);

    bfs(graph, startNode);

    return 0;
}
