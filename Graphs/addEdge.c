#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the maximum number of vertices in the graph
#define MAX_VERTICES 100

// Structure to represent a vertex
struct Vertex {
    int name;
};

// Structure to represent an edge
struct Edge {
    int u;
    int v;
};

// Structure to represent the graph
struct Graph {
    struct Vertex vertices[MAX_VERTICES];
    struct Edge edges[MAX_VERTICES * (MAX_VERTICES - 1)]; // Assuming no self-loops
    int numVertices;
    int numEdges;
};

// Function prototypes
void addEdge(struct Graph *graph, int u, int v);

int main() {
    // Create a graph
    struct Graph graph;
    graph.numVertices = 0;
    graph.numEdges = 0;

    // Test the addEdge function
    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 1, 2); // Adding an existing edge
    addEdge(&graph, 4, 5); // Adding edge with non-existing vertices

    return 0;
}

// Function to add an edge to the graph
void addEdge(struct Graph *graph, int u, int v) {
    // Check if the vertices u and v exist in the graph
    bool uExists = false, vExists = false;
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->vertices[i].name == u) {
            uExists = true;
        }
        if (graph->vertices[i].name == v) {
            vExists = true;
        }
    }

    // If either u or v does not exist, return
    if (!uExists || !vExists) {
        printf("Error: Vertex %d or %d does not exist. Cannot add edge.\n", u, v);
        return;
    }

    // Check if there is already an edge between u and v
    for (int i = 0; i < graph->numEdges; i++) {
        if ((graph->edges[i].u == u && graph->edges[i].v == v) ||
            (graph->edges[i].u == v && graph->edges[i].v == u)) {
            printf("Edge between %d and %d already exists. Not adding a new edge.\n", u, v);
            return;
        }
    }

    // Add a new edge between u and v
    graph->edges[graph->numEdges].u = u;
    graph->edges[graph->numEdges].v = v;
    graph->numEdges++;

    printf("Added edge between %d and %d to the graph.\n", u, v);
}
