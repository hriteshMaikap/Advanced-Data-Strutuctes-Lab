#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100
#define INF INT_MAX

typedef struct Weighted_Vertex_Node {
    int vertex;
    int weight;
    struct Weighted_Vertex_Node* next;
} Node;

typedef struct {
    Node* list[MAX];
    int vertices;
} ListGraph;

typedef struct {
    int src;
    int dest;
    int weight;
} Edge;

typedef struct {
    int parent;
    int rank;
} Subset;

void initializeListGraph(ListGraph* graph, int vertices) {
    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        graph->list[i] = NULL;
    }
}

void addListEdge(ListGraph* graph, int src, int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->weight = weight;
    newNode->next = graph->list[src];
    graph->list[src] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->weight = weight;
    newNode->next = graph->list[dest];
    graph->list[dest] = newNode;
}

void printListGraph(ListGraph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        Node* temp = graph->list[i];
        printf("[%d] -> ", i);
        while (temp != NULL) {
            printf("%d(w=%d) ", temp->vertex, temp->weight);
            temp = temp->next;
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

void kruskalMST(ListGraph* graph) {
    int vertices = graph->vertices;
    Edge edges[vertices*vertices];
    int edgeCount = 0;

    // Convert adjacency list to edge list
    for (int i = 0; i < vertices; i++) {
        Node* temp = graph->list[i];
        while (temp != NULL) {
            if (i < temp->vertex) { // Ensure each edge is only considered once
                edges[edgeCount].src = i;
                edges[edgeCount].dest = temp->vertex;
                edges[edgeCount].weight = temp->weight;
                edgeCount++;
            }
            temp = temp->next;
        }
    }

    // Sort edges by weight
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
    ListGraph graph;
    int vertices, edges;
    int src, dest, weight;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    initializeListGraph(&graph, vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter the source, destination, and weight for edge %d: ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        addListEdge(&graph, src, dest, weight);
    }

    printf("Adjacency List:\n");
    printListGraph(&graph);

    printf("Minimum Spanning Tree using Kruskal's Algorithm:\n");
    kruskalMST(&graph);

    return 0;
}
