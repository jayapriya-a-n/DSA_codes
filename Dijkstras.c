#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], int visited[], int vertices)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < vertices; v++)
    {
        if (visited[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the shortest path from source to destination
void printPath(int parent[], int j, FILE *outputFile)
{
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j], outputFile);
    fprintf(outputFile, "%d ", j);
}

// Function to print the final solution
void printSolution(int dist[], int parent[], int vertices, int source, FILE *outputFile)
{
    fprintf(outputFile, "VertexDistancePath\n");

    for (int i = 0; i < vertices; i++)
    {
        fprintf(outputFile, "%d -> %d\t\t%d\t\t%d ", source, i, dist[i], source);
        printPath(parent, i, outputFile);
        fprintf(outputFile, "\n");
    }
}

// Function to implement Dijkstra's algorithm
void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int vertices, int source, FILE *outputFile)
{
    int dist[MAX_VERTICES];     // Array to store the shortest distance from source to i
    int visited[MAX_VERTICES];  // Array to keep track of visited vertices
    int parent[MAX_VERTICES];   // Array to store the shortest path tree

    // Initialize all distances as INFINITY and visited[] as 0
    for (int i = 0; i < vertices; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    // Distance of source vertex from itself is always 0
    dist[source] = 0;

    // Parent of the source vertex is -1
    parent[source] = -1;

    // Find the shortest path for all vertices
    for (int count = 0; count < vertices - 1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not yet processed.
        int u = minDistance(dist, visited, vertices);

        // Mark the picked vertex as visited
        visited[u] = 1;

        // Update dist[v] only if it is not in visited[], there is an edge from u to v, and the total weight of path from source to v through u is smaller than current value of dist[v]
        for (int v = 0; v < vertices; v++)
        {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print the shortest path from source to all vertices
    printSolution(dist, parent, vertices, source, outputFile);
}

int main()
{
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL)
    {
        printf("Error opening files!\n");
        return 1;
    }

    int vertices;
    fscanf(inputFile, "%d", &vertices);

    int graph[MAX_VERTICES][MAX_VERTICES];

    // Read the adjacency matrix from the input file
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            fscanf(inputFile, "%d", &graph[i][j]);
        }
    }

    int source;
    printf("Enter the source vertex: ");
    scanf("%d", &source);

    // Run Dijkstra's algorithm
    dijkstra(graph, vertices, source, outputFile);

    printf("Shortest path computed and saved to output.txt\n");

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
