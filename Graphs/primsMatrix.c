#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100
#define INF INT_MAX

typedef struct {
    int vertices;
    int adjMat[MAX][MAX];
} Graph;

void initializeGraph(Graph* graph, int vertices) {
    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMat[i][j] = (i == j) ? 0 : INF;
        }
    }
}

void addEdgeUndirected(Graph* graph, int src, int dest, int weight) {
    graph->adjMat[src][dest] = weight;
    graph->adjMat[dest][src] = weight;
}

void printGraph(Graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            if (graph->adjMat[i][j] == INF) {
                printf("INF ");
            } else {
                printf("%d ", graph->adjMat[i][j]);
            }
        }
        printf("\n");
    }
}

void primMatrix(Graph* graph, int startVertex) {
    int vertices = graph->vertices;
    int parent[vertices];
    int key[vertices];
    int mstSet[vertices];

    for (int i = 0; i < vertices; i++) {
        key[i] = INF;
        mstSet[i] = 0;
    }

    key[startVertex] = 0;
    parent[startVertex] = -1;

    for (int count = 0; count < vertices - 1; count++) {
        int min = INF, minIndex;

        for (int v = 0; v < vertices; v++) {
            if (mstSet[v] == 0 && key[v] < min) {
                min = key[v];
                minIndex = v;
            }
        }

        int u = minIndex;
        mstSet[u] = 1;

        for (int v = 0; v < vertices; v++) {
            if (graph->adjMat[u][v] && mstSet[v] == 0 && graph->adjMat[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph->adjMat[u][v];
            }
        }
    }

    int minWeight = 0;
    printf("Edge \tWeight\n");
    for (int i = 1; i < vertices; i++) {
        printf("%d - %d \t%d \n", parent[i], i, key[i]);
        minWeight += key[i];
    }
    printf("Total weight of MST: %d\n", minWeight);
}

int main() {
    Graph graph;
    int vertices, edges;
    int src, dest, weight;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    initializeGraph(&graph, vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter the source, destination, and weight for edge %d: ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        addEdgeUndirected(&graph, src, dest, weight);
    }

    printf("Adjacency Matrix:\n");
    printGraph(&graph);

    int initialVertex;
    printf("Enter the root node to start the MST algorithm: ");
    scanf("%d", &initialVertex);

    printf("Minimum Spanning Tree using Adjacency Matrix:\n");
    primMatrix(&graph, initialVertex);

    return 0;
}

