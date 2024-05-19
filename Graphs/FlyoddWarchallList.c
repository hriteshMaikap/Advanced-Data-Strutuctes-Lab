#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//LAST mein time bacha toh kar lena

#define INF INT_MAX
#define MAX 100

typedef struct node {
    int vertex;
    int weight;
    struct node* next;
} Node;

Node* newNode(int vertex, int weight) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->vertex = vertex;
    temp->weight = weight;
    temp->next = NULL;
    return temp;
}

void addEdge(Node* adjList[], int src, int dest, int weight) {
    Node* node = newNode(dest, weight);
    node->next = adjList[src];
    adjList[src] = node;
}

void printGraph(Node* adjList[], int vertices) {
    for (int i = 0; i < vertices; i++) {
        printf("Vertex %d ->", i);
        Node* temp = adjList[i];
        while (temp != NULL) {
            printf(" %d(w=%d)", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

void floydWarshall(int** adjMat, int vertices) {
    int dist[MAX][MAX];

    // Initialize distance matrix with adjacency matrix values
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            dist[i][j] = adjMat[i][j];
        }
    }

    // Floyd-Warshall algorithm
    for (int k = 0; k < vertices; k++) {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print the shortest path matrix
    printf("Shortest path matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (dist[i][j] == INF) {
                printf("INF ");
            } else {
                printf("%d ", dist[i][j]);
            }
        }
        printf("\n");
    }
}

int** convertListToMatrix(Node* adjList[], int vertices) {
    int** adjMat = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        adjMat[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            if (i == j) {
                adjMat[i][j] = 0;
            } else {
                adjMat[i][j] = INF;
            }
        }
        Node* temp = adjList[i];
        while (temp != NULL) {
            adjMat[i][temp->vertex] = temp->weight;
            temp = temp->next;
        }
    }
    return adjMat;
}

int main() {
    int vertices;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    Node* adjList[vertices];

    // Initialize the graph
    for (int i = 0; i < vertices; i++) {
        adjList[i] = NULL;
    }

    int edges;
    int src, dest, weight;
    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    for (int i = 0; i < edges; i++) {
        printf("Enter the source, destination, and weight for edge %d: ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(adjList, src, dest, weight);
    }

    printGraph(adjList, vertices);

    int** adjMat = convertListToMatrix(adjList, vertices);
    floydWarshall(adjMat, vertices);

    // Free allocated memory
    for (int i = 0; i < vertices; i++) {
        Node* temp = adjList[i];
        while (temp != NULL) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    for (int i = 0; i < vertices; i++) {
        free(adjMat[i]);
    }
    free(adjMat);

    return 0;
}
