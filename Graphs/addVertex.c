#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the maximum number of vertices in the graph
#define MAX_VERTICES 100

// Structure to represent a vertex
struct Vertex {
    int name;
};

// Structure to represent the graph
struct Graph {
    struct Vertex vertices[MAX_VERTICES];
    int numVertices;
};

// Function prototypes
void addVertex(struct Graph *graph, int n);

int main() {
    // Create a graph
    struct Graph graph;
    graph.numVertices = 0;

    // Test the addVertex function
    addVertex(&graph, 1);
    addVertex(&graph, 2);
    addVertex(&graph, 3);
    addVertex(&graph, 1); // Adding a vertex with an existing name

    return 0;
}

// Function to add a vertex to the graph
void addVertex(struct Graph *graph, int n) {
    // Check if the graph is full
    if (graph->numVertices == MAX_VERTICES) {
        printf("Error: Graph is full. Cannot add more vertices.\n");
        return;
    }

    // Check if a vertex with name n already exists
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->vertices[i].name == n) {
            printf("Vertex with name %d already exists. Not adding a new vertex.\n", n);
            return;
        }
    }

    // Add a new vertex with name n
    graph->vertices[graph->numVertices].name = n;
    graph->numVertices++;

    printf("Added vertex with name %d to the graph.\n", n);
}
