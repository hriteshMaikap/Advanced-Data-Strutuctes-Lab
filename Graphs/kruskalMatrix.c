#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

typedef struct {
    int vertices;
    int adjMat[MAX][MAX];
} Graph;

typedef struct {
    int src;
    int dest;
    int weight;
} Edge;

typedef struct {
    int parent;
    int rank;
} Subset;

void initializeGraph(Graph* graph, int vertices) {
    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMat[i][j] = 0;
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
            printf("%d ", graph->adjMat[i][j]);
        }
        printf("\n");
    }
}

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void Union(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank) {
        subsets[rootX].parent = rootY;
    } else if (subsets[rootX].rank > subsets[rootY].rank) {
        subsets[rootY].parent = rootX;
    } else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

void kruskalMST(Graph* graph) {
    int vertices = graph->vertices;
    Edge edges[MAX * MAX];
    int edgeCount = 0;

    for (int i = 0; i < vertices; i++) {
        for (int j = i; j < vertices; j++) {
            if (graph->adjMat[i][j] != 0) {
                edges[edgeCount].src = i;
                edges[edgeCount].dest = j;
                edges[edgeCount].weight = graph->adjMat[i][j];
                edgeCount++;
            }
        }
    }

    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    Subset* subsets = (Subset*) malloc(vertices * sizeof(Subset));
    for (int v = 0; v < vertices; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    int mstWeight = 0;
    printf("Edges in the MST:\n");
    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;

        int setU = find(subsets, u);
        int setV = find(subsets, v);

        if (setU != setV) {
            printf("%d - %d: %d\n", u, v, edges[i].weight);
            mstWeight += edges[i].weight;
            Union(subsets, setU, setV);
        }
    }

    printf("Total weight of MST: %d\n", mstWeight);
    free(subsets);
}

int main() {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    int vertices, edges;
    int src, dest, weight;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    initializeGraph(graph, vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter the source, destination, and weight for edge %d: ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        addEdgeUndirected(graph, src, dest, weight);
    }

    printGraph(graph);

    printf("Minimum Spanning Tree using Kruskal's Algorithm:\n");
    kruskalMST(graph);

    free(graph);
    return 0;
}
