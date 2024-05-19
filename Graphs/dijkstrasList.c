#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node{
    int vertex, weight;
    struct node* next;
};

struct node* newNode(int vertex, int weight){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->vertex = vertex;
    temp->weight = weight;
    temp->next = NULL;
    return temp;
}

void addEdge(struct node* adjList[], int src, int dest, int weight){
    struct node* node = newNode(dest, weight);
    node->next = adjList[src];
    adjList[src] = node;
}

void printGraph(struct node* adjList[], int vertices){
    for (int i=0; i<vertices; i++){
        printf("Vertex %d->", i);
        struct node* temp = adjList[i];
        while(temp!=NULL){
            printf("%d(%d)", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

int getMinVertex(int* distance, int* visited, int vertices){
    int minVertex = -1;
    for(int i=0; i<vertices; i++){
        if (!visited[i] && (minVertex==-1||distance[i]<distance[minVertex])){
            minVertex = i;
        }
    }
    return minVertex;
}

void printShortestPath(int* distance, int* parent, int vertices){
    for (int i=0; i<vertices; i++){
        if (distance[i]==INT_MAX){
            printf("Vertex %d is unreachable from source", i);
        }
        else{
            printf("Shortest path to vertex %d (distance %d)", i, distance[i]);
            int j=i;
            while(parent[j]!=j){
                printf("%d<-", j);
                j = parent[j];
            }
            printf("%d\n",j);
        }
    }
}

void dijkstra(struct node* adjList[], int vertices, int source){
    int distance[vertices];
    int visited[vertices];
    int parent[vertices];

    for (int i=0; i<vertices; i++){
        distance[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = i;
    }

    distance[source] = 0;
    for (int i=0; i<vertices-1; i++){
        int u = getMinVertex(distance, visited, vertices);
        visited[u] = 1;

        struct node* temp = adjList[u];
        while(temp!=NULL){
            int v = temp->vertex;
            int weight = temp->weight;
            if (!visited[v] && distance[u]!=INT_MAX && distance[u]+weight<distance[v]){
                distance[v] = distance[u]+weight;
                parent[v] = u; 
            }
            temp = temp->next;
        }
    }
    printShortestPath(distance, parent, vertices);
}

int main(){
    int vertices;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    struct node* adjList[vertices];
    for (int i = 0; i < vertices; i++){
        adjList[i]=NULL;    
    }

    int edges;
    int src, dest, weight;
    printf("Enter the number of edges: ");
    for (int i=0; i<edges; i++){
        print("Enter source, destination, weight: ");
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(adjList, src, dest, weight);
    }
    printGraph(adjList, vertices);

    int source;
    printf("Enter the source vertex: ");
    scanf("%d", &source);

    dijkstra(adjList, vertices, source);
    
}
