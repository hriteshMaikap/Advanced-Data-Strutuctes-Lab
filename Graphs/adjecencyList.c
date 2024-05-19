#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* next;
};

struct node* newNode(int data){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void addEdge(struct node* adjList[], int src, int dest){
    struct node* node = newNode(dest);
    node->next = adjList[src];
    adjList[src] = node;
}

void printGraph(struct node* adjList[], int vertices){
    for (int i=0; i<vertices; i++){
        printf("Vertice %d->", i);
        struct node* temp = adjList[i];
        while(temp!=NULL){
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main(){
    int vertices;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    struct node* adjList[vertices];
    //initialize the graph
    for (int i=0; i<vertices; i++){
        adjList[i] = NULL;
    }

    int edges;
    int src, dest;
    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    for (int i=0; i<edges; i++){
        printf("Enter the source and destination between which edge exists: ");
        scanf("%d %d", &src, &dest);
        addEdge(adjList, src, dest);
    }

    printGraph(adjList, vertices);
    return 0;
}