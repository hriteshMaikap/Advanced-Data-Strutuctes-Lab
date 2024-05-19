#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 100

typedef struct{
    int vertices;
    int adjMat[MAX][MAX];
}Graph;

void initializeGraph(Graph* graph, int vertices){
    graph->vertices = vertices;
    for (int i=0; i<vertices; i++){
        for (int j=0; j<vertices; j++){
            graph->adjMat[i][j] = (i==j) ? 0: INT_MAX; 
        }
    }
}

void addUndirectedEdge(Graph* graph, int src, int dest, int weight){
    graph->adjMat[src][dest] = weight;
    graph->adjMat[dest][src] = weight;
}

void printGraph(Graph* graph){
    for (int i=0; i<graph->vertices; i++){
        for (int j=0; j<graph->vertices; j++){
            if (graph->adjMat[i][j]==INT_MAX){
                printf("INF ");
            }
            else{
                printf("%d ", graph->adjMat[i][j]);
            }
        }
        printf("\n");
    }
}

void flyodWarshall(Graph* graph){
    int vertices = graph->vertices;
    int dist[vertices][vertices];

    //initialize
    for (int i=0; i<vertices; i++){
        for (int j=0; j<vertices; j++){
            dist[i][j] = graph->adjMat[i][j];
        }
    }

    //logic
    for (int k=0; k<vertices; k++){
        for (int i=0; i<vertices; i++){
            for (int j=0; j<vertices; j++){
                if (dist[i][k]!=INT_MAX && dist[k][j]!=INT_MAX && dist[i][k]+dist[k][j]<dist[i][j]){
                    dist[i][j] = dist[i][k]+dist[k][j];
                }
            }
        }
    }

    //print
    printf("Shortest path matrix:\n");
    for (int i=0; i<graph->vertices; i++){
        for (int j=0; j<graph->vertices; j++){
            if (dist[i][j]==INT_MAX){
                printf("INF ");
            }
            else{
                printf("%d ", dist[i][j]);
            }
        }
        printf("\n");
    }
}

int main(){
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    int vertices;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    initializeGraph(graph, vertices);

    int edges, src, dest, weight;
    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    for (int i = 0; i < edges; i++){
        printf("Enter the source and destination vertices and weight: ");
        scanf("%d %d %d", &src, &dest, &weight);
        addUndirectedEdge(graph, src, dest, weight);
    }
    printf("Graph you have entered is: \n");
    printGraph(graph);

    flyodWarshall(graph);
    return 0; 
}