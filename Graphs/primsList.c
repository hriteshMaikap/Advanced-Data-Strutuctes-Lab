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

void initializeListGraph(ListGraph* graph, int vertices) {
    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        graph->list[i] = NULL;
    }
}

void addListEdge(ListGraph* graph, int src, int dest, int weight) { //for undirected graph
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

void primList(ListGraph* graph, int startVertex) {
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

        Node* temp = graph->list[u];
        while (temp != NULL) {
            int v = temp->vertex;
            if (mstSet[v] == 0 && temp->weight < key[v]) {
                parent[v] = u;
                key[v] = temp->weight;
            }
            temp = temp->next;
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

    int initialVertex;
    printf("Enter the root node to start the MST algorithm: ");
    scanf("%d", &initialVertex);

    printf("Minimum Spanning Tree using Adjacency List:\n");
    primList(&graph, initialVertex);

    return 0;
}
