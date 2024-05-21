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
void delVertex(struct Graph *graph, int u);

int main() {
    // Create a graph
    struct Graph graph;
    graph.numVertices = 0;
    graph.numEdges = 0;

    // Test the delVertex function
    delVertex(&graph, 1); // Removing from an empty graph
    delVertex(&graph, 2); // Removing non-existing vertex

    return 0;
}

// Function to delete a vertex from the graph
void delVertex(struct Graph *graph, int u) {
    // Check if the vertex u exists in the graph
    bool vertexExists = false;
    int vertexIndex = -1;
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->vertices[i].name == u) {
            vertexExists = true;
            vertexIndex = i;
            break;
        }
    }

    // If the vertex does not exist, return
    if (!vertexExists) {
        printf("Vertex %d does not exist. Cannot delete.\n", u);
        return;
    }

    // Remove all edges incident to vertex u
    for (int i = 0; i < graph->numEdges; i++) {
        if (graph->edges[i].u == u || graph->edges[i].v == u) {
            // Move the last edge to the position of the deleted edge
            graph->edges[i] = graph->edges[graph->numEdges - 1];
            graph->numEdges--;
            i--; // Decrement i to re-check the current position
        }
    }

    // Remove the vertex by overwriting it with the last vertex in the array
    graph->vertices[vertexIndex] = graph->vertices[graph->numVertices - 1];
    graph->numVertices--;

    printf("Deleted vertex %d and its incident edges from the graph.\n", u);
}
