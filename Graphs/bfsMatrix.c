#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int front, rear, size;
    int* arr;
} Queue;

Queue* initializeQueue(int vertices) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->size = vertices;
    queue->front = queue->rear = -1;
    queue->arr = (int*)malloc(vertices * sizeof(int));
    return queue;
}

int isEmpty(Queue* queue) {
    return queue->front == -1;
}

int isFull(Queue* queue) {
    return queue->rear == queue->size - 1;
}

void enqueue(Queue* queue, int data) {
    if (isFull(queue)) {
        printf("Queue is full\n");
        return;
    }
    if (isEmpty(queue)) {
        queue->front = 0;
    }
    queue->arr[++queue->rear] = data;
}

int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    int data = queue->arr[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }
    return data;
}

typedef struct {
    int vertices;
    int adjMat[MAX][MAX];
} Graph;

void initializeGraph(Graph* graph, int vertices) {
    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMat[i][j] = 0;
        }
    }
}

void addEdge(Graph* graph, int src, int dest) {
    graph->adjMat[src][dest] = 1;
    graph->adjMat[dest][src] = 1;
}

void printGraph(Graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            printf("%d ", graph->adjMat[i][j]);
        }
        printf("\n");
    }
}

void bfs(Graph* graph, int start, int visited[], Queue* queue) {
    visited[start] = 1;
    enqueue(queue, start);

    while (!isEmpty(queue)) {
        int current = dequeue(queue);
        printf("%d ", current);
        for (int i = 0; i < graph->vertices; i++) {
        //we dont use j because this is bfs and dfs to enter into every particular row and column
            if (graph->adjMat[current][i] && !visited[i]) {
                visited[i] = 1;
                enqueue(queue, i);
            }
        }
    }
}

int main() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    int vertices, edges, src, dest;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    initializeGraph(graph, vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    for (int i = 0; i < edges; i++) {
        printf("Enter the source and destination: ");
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    int visited[vertices];
    for (int i = 0; i < vertices; i++) {
        visited[i] = 0;
    }

    Queue* queue = initializeQueue(vertices);
    printf("The Breadth First Search of the given graph is:\n");
    bfs(graph, 0, visited, queue);

    free(queue->arr);
    free(queue);
    free(graph);

    return 0;
}
