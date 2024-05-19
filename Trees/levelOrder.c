#include <stdio.h>
#include <stdlib.h>
#define MAX 100
struct node{
    int data;
    struct node* left;
    struct node* right;
};

typedef struct{
    int front;
    int rear;
    struct node* arr[MAX];
}Queue;

void initializeQueue(Queue* queue){
    queue->front = queue->rear = -1;
}

int isFull(Queue* queue){
    return (queue->rear==MAX-1);
}

int isEmpty(Queue* queue){
    return (queue->front==-1 || queue->front > queue->rear);
}

void enqueue(Queue* queue, struct node* item){
    if (isFull(queue)){
        printf("Queue is full\n");
        return;
    }
    if(isEmpty(queue)){
        queue->front = 0;
    }
    queue->arr[++queue->rear] = item;
}

struct node* dequeue(Queue* queue){
    if(isEmpty(queue)){
        printf("Queue is empty\n");
        return NULL;
    }
    struct node* val = queue->arr[queue->front++];
    if (queue->front>queue->rear){
        queue->front=queue->rear=-1;
    }
    return val;
}

struct node* newNode(int item){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = item;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct node* insert (struct node* root, int item){
    if (root==NULL){
        return newNode(item);
    }
    if (item<root->data){
        root->left = insert(root->left, item);
    }
    else if(item>root->data){
        root->right = insert(root->right, item);
    }
    return root;
}
struct node* buildBST(){
    struct node* root = NULL;
    int val, item;
    printf("Enter the number of nodes: ");
    scanf("%d", &val);

    for (int i=0; i<val; i++){
        printf("Enter the value: ");
        scanf("%d", &item);
        root = insert(root, item);
    }
    return root;
}

void levelOrderTraversal(struct node* root){
    if (root==NULL) return;
    Queue queue;
    initializeQueue(&queue);
    enqueue(&queue, root);

    while(!isEmpty(&queue)){
        int levelSize = queue.rear-queue.front+1;
        int *currentLevel = (int*)malloc(levelSize*sizeof(int));

        for (int i=0; i<levelSize; i++){
            struct node* node = dequeue(&queue);
            currentLevel[i]=node->data;
            if(node->left!=NULL){
                enqueue(&queue, node->left);
            }
            if(node->right!=NULL){
                enqueue(&queue, node->right);
            }
        }

        for (int i=0; i<levelSize; i++){
            printf("%d ", currentLevel[i]);
        }
        printf("\n");
    }
}

int main(){
    struct node* root = buildBST();
    printf("Level Order Traversal of the the code is:\n");
    levelOrderTraversal(root);
    return 0;
}
