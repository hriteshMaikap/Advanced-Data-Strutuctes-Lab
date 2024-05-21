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
void delEdge(struct Graph *graph, int u, int v);

int main() {
    // Create a graph
    struct Graph graph;
    graph.numVertices = 0;
    graph.numEdges = 0;

    // Test the delEdge function
    delEdge(&graph, 1, 2); // Removing non-existing edge
    delEdge(&graph, 2, 3); // Removing non-existing edge

    return 0;
}

// Function to delete an edge from the graph
void delEdge(struct Graph *graph, int u, int v) {
    // Check if the edge (u, v) exists in the graph
    bool edgeExists = false;
    int index = -1;
    for (int i = 0; i < graph->numEdges; i++) {
        if ((graph->edges[i].u == u && graph->edges[i].v == v) ||
            (graph->edges[i].u == v && graph->edges[i].v == u)) {
            edgeExists = true;
            index = i;
            break;
        }
    }

    // If the edge does not exist, return
    if (!edgeExists) {
        printf("Edge between %d and %d does not exist. Cannot delete.\n", u, v);
        return;
    }

    // Move the last edge to the position of the deleted edge
    graph->edges[index] = graph->edges[graph->numEdges - 1];
    graph->numEdges--;

    printf("Deleted edge between %d and %d from the graph.\n", u, v);
}
