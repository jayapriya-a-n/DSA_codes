#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct {
    int vertices[MAX_VERTICES];
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Graph;

// Function to initialize the graph
void initGraph(Graph* graph, int numVertices) {
    graph->numVertices = numVertices;

    for (int i = 0; i < numVertices; i++) {
        graph->vertices[i] = 0;
        for (int j = 0; j < numVertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
}

// Recursive function to perform DFS traversal
void dfsTraversal(Graph* graph, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjMatrix[vertex][i] == 1 && visited[i] == 0) {
            dfsTraversal(graph, i, visited);
        }
    }
}

// Function to perform DFS traversal on the graph
void dfs(Graph* graph, int startVertex) {
    int visited[MAX_VERTICES] = { 0 };

    dfsTraversal(graph, startVertex, visited);
}

int main() {
    FILE* inputFile = fopen("input.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Failed to open input.txt or output.txt\n");
        return 1;
    }

    int numVertices;
    fscanf(inputFile, "%d", &numVertices);

    Graph graph;
    initGraph(&graph, numVertices);

    int src, dest;
    while (fscanf(inputFile, "%d %d", &src, &dest) == 2) {
        addEdge(&graph, src, dest);
    }

    int startVertex;
    fscanf(inputFile, "%d", &startVertex);

    fprintf(outputFile, "DFS Traversal: ");
    dfs(&graph, startVertex);
    fprintf(outputFile, "\n");

    fclose(inputFile);
    fclose(outputFile);

    printf("DFS traversal has been written to output.txt\n");

    return 0;
}
