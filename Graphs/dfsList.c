#include <stdio.h>
#include <stdlib.h>

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

void dfsRecursive(struct node* adjList[], int start, int visited[]){
    visited[start] = 1;
    printf("%d ", start);
    struct node* temp = adjList[start];
    while(temp!=NULL){
        int neighbour = temp->data;
        if (!visited[neighbour]){
            dfsRecursive(adjList, neighbour, visited);
        }
    }
}

void dfs(struct node* adjList[], int start, int visited[], Stack* stack){
    push(stack, start);
    while(!isEmpty(stack)){
        int current = pop(stack);
        if (!visited[current]){
            printf("%d ", current);
            visited[current] = 1;
        }
        struct node* temp = adjList[current];
        while(temp!=NULL){
            int neighbour = temp->data;
            if(!visited[neighbour]){
                push(stack, neighbour);
            }
            temp = temp->next;
        }
    }
}

int main(){
    int vertices;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    struct node* adjList[vertices];
    for (int i=0; i<vertices; i++){
        adjList[i] = NULL;
    }

    int edges, src, dest;
    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    for (int i=0; i<edges; i++){
        printf("Enter the source and destination for which edge exists: ");
        scanf("%d %d", &src, &dest);
        addEdge(adjList, src, dest);
    }
    printf("The graph you have entered is: \n");
    printGraph(adjList, vertices);

    int visited[vertices];
    for (int i=0; i<vertices; i++){
        visited[i] = 0;
    }
    // printf("Recursive depth first traversal: \n");
    // dfsRecursive(adjList, 0, visited);

    Stack* stack = intializeStack(vertices);
    printf("Iterative depth first traversal: \n");
    dfs(adjList, 0, visited, stack);
    return 0;

}