#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

// Adjacency List Node
struct Node {
    int vertex;
    struct Node* next;
};

// Graph
struct Graph {
    struct Node* adjLists[MAX_NODES];
    int visited[MAX_NODES];
};

// Create a new node
struct Node* createNode(int vertex) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // For undirected graph, add an edge from dest to src as well
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Depth-First Search
void DFS(struct Graph* graph, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    struct Node* adjList = graph->adjLists[vertex];
    while (adjList != NULL) {
        int connectedVertex = adjList->vertex;
        if (!graph->visited[connectedVertex]) {
            DFS(graph, connectedVertex);
        }
        adjList = adjList->next;
    }
}

// Initialize graph
void initGraph(struct Graph* graph, int numNodes) {
    for (int i = 0; i < numNodes; ++i) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
}

int main() {
    int numNodes, numEdges;
    printf("Enter the number of nodes and edges: ");
    scanf("%d %d", &numNodes, &numEdges);

    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    initGraph(graph, numNodes);

    printf("Enter the edges (src dest):\n");
    for (int i = 0; i < numEdges; ++i) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    printf("DFS traversal starting from node 0:\n");
    DFS(graph, 0);
    printf("\n");

    free(graph);
    return 0;
}
