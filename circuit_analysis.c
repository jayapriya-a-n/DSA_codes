#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 50

struct Graph {
    int vertices;
    int adjacencyMatrix[MAX_NODES][MAX_NODES];
};

int visited[MAX_NODES];

void initGraph(struct Graph *graph, int vertices) {
    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjacencyMatrix[i][j] = 0;
        }
    }
}

void insertEdge(struct Graph *graph, int source, int destination) {
    graph->adjacencyMatrix[source][destination] = 1;
    graph->adjacencyMatrix[destination][source] = 1;
}

void deleteEdge(struct Graph *graph, int source, int destination) {
    graph->adjacencyMatrix[source][destination] = 0;
    graph->adjacencyMatrix[destination][source] = 0;
}

void dfs(struct Graph *graph, int vertex) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjacencyMatrix[vertex][i] == 1 && visited[i] == 0) {
            dfs(graph, i);
        }
    }
}

int main() {
    struct Graph graph;
    int vertices, edges, source, destination;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    initGraph(&graph, vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter edge %d (source destination): ", i + 1);
        scanf("%d %d", &source, &destination);
        insertEdge(&graph, source, destination);
    }

    printf("DFS traversal starting from vertex 0: ");
    dfs(&graph, 0);
    printf("\n");

    return 0;
}
