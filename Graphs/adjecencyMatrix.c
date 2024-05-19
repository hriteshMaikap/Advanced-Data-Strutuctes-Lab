#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct{
    int vertices;
    int adjMat[MAX][MAX];
}Graph;

int initializeGraph(Graph* graph, int vertices){
    graph->vertices = vertices;
    for (int i=0; i<vertices; i++){
        for (int j=0; j<vertices; j++){
            graph->adjMat[i][j]=0;
        }
    }
}

void addEdgeDirected(Graph* graph, int src, int dest){
    graph->adjMat[src][dest] = 1;
}

void addEdgeUndirected(Graph* graph, int src, int dest){
    graph->adjMat[src][dest] = 1;
    graph->adjMat[dest][src] = 1;
}

void printGraph(Graph* graph){
    for (int i=0; i<graph->vertices; i++){
        for (int j = 0; j < graph->vertices; j++){
            printf("%d ", graph->adjMat[i][j]);
        }
        printf("\n");
    }
}

int main(){
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    int vertices, edges;
    int src, dest;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    initializeGraph(graph, vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i=0; i<edges; i++){
        printf("Enter the source and destination for which an edge exists: ");
        scanf("%d %d", &src, &dest);
        addEdgeUndirected(graph, src, dest);
    }

    printGraph(graph);
    return 0;
}