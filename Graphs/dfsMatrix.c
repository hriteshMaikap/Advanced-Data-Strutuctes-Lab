#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct{
    int top, size;
    int* arr;
}Stack;

Stack* intializeStack(int size){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->size = size;
    stack->top = -1;
    stack->arr = (int*)malloc(size*sizeof(int));
}

int isEmpty(Stack* stack){
    return stack->top==-1;
}

int isFull(Stack* stack){
    return stack->top == stack->size-1;
}

void push(Stack* stack, int data){
    if (isFull(stack)){
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = data;
}

int pop(Stack* stack){
    if (isEmpty(stack)){
        printf("Stack underflow");
        return -1;
    }
    return stack->arr[stack->top--];
}

typedef struct {
    int vertices;
    int adjMat[MAX][MAX];
} Graph;

void initializeGraph(Graph* graph, int vertices) {
    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMat[i][j] = 0;
        }
    }
}

void addEdge(Graph* graph, int src, int dest) {
    graph->adjMat[src][dest] = 1;
    graph->adjMat[dest][src] = 1;
}

void printGraph(Graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            printf("%d ", graph->adjMat[i][j]);
        }
        printf("\n");
    }
}

void dfsRecursive(Graph* graph, int start, int visited[]){
    visited[start] = 1;
    printf("%d ", start);

    for (int i=0; i<graph->vertices; i++){
        if (!visited[i] && graph->adjMat[start][i]){
            dfsRecursive(graph, i, visited);
        }
    }
}

void dfs(Graph* graph, int start, int visited[], Stack* stack){
    push(stack, start);
    while(!isEmpty(stack)){
        int current = pop(stack);
        if (!visited[current]){
            printf("%d ", current);
            visited[current] = 1;
        }
        for (int i=0; i<graph->vertices; i++){
            if (graph->adjMat[current][i] && !visited[i]){
                push(stack, i);
            }
        }
    }
}

int main(){
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    int vertices, edges, src, dest;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    initializeGraph(graph, vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    for (int i = 0; i < edges; i++) {
        printf("Enter the source and destination: ");
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    int visited[vertices];
    for (int i = 0; i < vertices; i++) {
        visited[i] = 0;
    }

    Stack* stack = intializeStack(vertices);
    printf("The depth first search of the given graph:\n");
    dfsRecursive(graph, 0, visited);
    dfs(graph, 0, visited, stack);

    free(stack->arr);
    free(stack);
    free(graph);
}

