#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int front, rear, size;
    int* arr;
}Queue;

Queue* initializeQueue(int size){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = -1;
    queue->size = size;
    queue->arr = (int*)malloc(size*sizeof(int));
    
    return queue;
}

int isEmpty(Queue* queue){
    return queue->front == -1;
}   

int isFull(Queue* queue){
    return queue->rear+1 == queue->size;
}

void enqueue(Queue* queue, int data){
    if (isFull(queue)){
        printf("Queue is full\n");
        return;
    }
    if (isEmpty(queue)){
        queue->front = 0;
    }
    queue->arr[++queue->rear] = data;
}

int dequeue(Queue* queue){
    if (isEmpty(queue)){
        printf("Queue is empty");
        return -1;
    }
    int data = queue->arr[queue->front];
    if (queue->front==queue->rear){
        queue->front = queue->rear = -1;
    }
    else{
        queue->front++;
    }
    return data;
}

struct node{
    int data;
    struct node* next;
};

struct node* createNode(int data){
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->next = NULL;
    return node;
}

void addEdge(struct node* adjList[], int src, int dest){
    struct node* node = createNode(dest);
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

void bfs(struct node* adjList[], int start, int visited[], Queue* queue){
    visited[start] = 1;
    enqueue(queue, start);

    while(!isEmpty(queue)){
        int current = dequeue(queue);
        printf("%d ", current);

        struct node* temp = adjList[current];
        while(temp!=NULL){
            int neighbour = temp->data;
            if (!visited[neighbour]){
                visited[neighbour]=1;
                enqueue(queue, neighbour);
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

    //initialize the visted array
    int visited[vertices];
    for (int i=0; i<vertices; i++){
        visited[i] = 0;
    }
    //initialize the queue for bfs
    Queue* queue = initializeQueue(vertices);
    printf("The BFS of given graph is: \n");
    bfs(adjList, 0, visited, queue);
    return 0;
}