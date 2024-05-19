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

void addEdge(Graph* graph, int src, int dest, int weight){
    graph->adjMat[src][dest] = weight;
    graph->adjMat[dest][src] = weight;
}

int getMinVertex(int* distance, int* visited, int vertices){
    int minVertex = -1;
    for (int i=0; i<vertices; i++){
        if (!visited[i] && (minVertex==-1 || distance[i]<distance[minVertex])){
            minVertex = i;
        }
    }
    return minVertex;
}

printShortestPath(int* distance, int* parent, int vertices){
    for (int i=0; i<vertices; i++){
        if (distance[i]==INT_MAX){
            printf("Vertex %d is not reachable from the source!");
        }
        else{
            printf("Shortest path to vertex %d (distance %d): ", i, distance[i]);
            int j = i;
            while(parent[j]!=j){
                printf("%d<-", j);
                j = parent[j];
            }
            printf("%d\n", j);
        }
    }
}

void dijkstra(Graph* graph, int source){
    int vertices = graph->vertices;
    int distance[vertices];
    int visited[vertices];
    int parent[vertices];

    for (int i=0; i<vertices; i++){
        distance[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = i;
    }

    distance[source] = 0;
    for (int i=0; i<vertices; i++){
        int u = getMinVertex(distance, visited, vertices);
        visited[u]=1;
        for (int v=0; v<vertices; v++){
            if (graph->adjMat[u][v]!= INT_MAX && !visited[v]){
                int newDistance = distance[u]+graph->adjMat[u][v];
                if (newDistance<distance[v]){
                    distance[v] = newDistance;
                    parent[v] = u;
                }
            }
        }
    }
    printShortestPath(distance, parent, vertices);
}

int main(){
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    int vertices, edges;
    int src, dest, weight;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    initializeGraph(graph, vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    for (int i=0; i<edges; i++){
        printf("Enter source, destination and weight: ");
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }

    int source;
    printf("Enter the source vertex: ");
    scanf("%d", &source);

    dijkstra(graph, source);

    free(graph);
    return 0;
}