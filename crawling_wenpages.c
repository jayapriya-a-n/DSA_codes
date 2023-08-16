#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAGES 50
#define MAX_URL_LENGTH 100

typedef struct Node {
    char url[MAX_URL_LENGTH];
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

typedef struct Graph {
    int numVertices;
    Node** adjacencyList;
} Graph;

Node* createNode(const char* url) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->url, url);
    newNode->next = NULL;
    return newNode;
}

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, const char* url) {
    Node* newNode = createNode(url);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

Node* dequeue(Queue* queue) {
    if (queue->front == NULL) {
        return NULL;
    }
    Node* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    return temp;
}

Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->adjacencyList = (Node**)malloc(numVertices * sizeof(Node*));
    for (int i = 0; i < numVertices; ++i) {
        graph->adjacencyList[i] = NULL;
    }
    return graph;
}

void insertEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(graph->adjacencyList[dest]->url);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;
}

void displayGraph(Graph* graph) {
    printf("Graph:\n");
    for (int i = 0; i < graph->numVertices; ++i) {
        printf("[%d] -> ", i);
        Node* curr = graph->adjacencyList[i];
        while (curr != NULL) {
            printf("%s -> ", curr->url);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

void crawlWebPages(Graph* graph, const char* startUrl) {
    Queue* queue = createQueue();
    int visited[MAX_PAGES] = {0};

    int vertex = 0;
    while (vertex < graph->numVertices && graph->adjacencyList[vertex] != NULL) {
        ++vertex;
    }
    if (vertex == graph->numVertices) {
        printf("Graph is full. Cannot add more pages.\n");
        return;
    }

    enqueue(queue, startUrl);
    visited[vertex] = 1;

    printf("Crawled Pages:\n");
    while (queue->front != NULL) {
        Node* currentUrlNode = dequeue(queue);
        printf("%s\n", currentUrlNode->url);
        for (int i = 0; i < graph->numVertices; ++i) {
            if (!visited[i] && graph->adjacencyList[i] == NULL) {
                graph->adjacencyList[i] = createNode(currentUrlNode->url);
                visited[i] = 1;
                enqueue(queue, currentUrlNode->url);
                break;
            }
        }
    }
}

int main() {
    int numPages;
    printf("Enter the number of web pages (max %d): ", MAX_PAGES);
    scanf("%d", &numPages);

    Graph* graph = createGraph(numPages);

    char startUrl[MAX_URL_LENGTH];
    printf("Enter the starting URL: ");
    scanf("%s", startUrl);

    crawlWebPages(graph, startUrl);
    displayGraph(graph);

    return 0;
}
