#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

typedef struct{
    int top;
    struct node* arr[MAX];   //creating a array to store the nodes
}Stack;

void initializeStack(Stack* stack){
    stack->top=-1;
}

void push(Stack* stack, struct node* element){
    if (stack->top==MAX-1){
        printf("Overflow");
        return;
    }
    stack->arr[++stack->top]=element;
}

struct node* pop(Stack* stack){
    if (stack->top==-1){
        printf("Underflow");
        return NULL;
    }
    struct node* val = stack->arr[stack->top--];
    return val;
}

struct node{
    int data;
    struct node* right;
    struct node* left;
};

struct node* newNode(int item){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = item;
    temp->right = NULL;
    temp->left = NULL;
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

void preorderIterative(struct node* root){
    if (root==NULL){
        return; 
    }
    Stack stack;
    initializeStack(&stack);
    push(&stack, root);
    while(stack.top!=-1){
        struct node* current = pop(&stack);
        printf("%d ", current->data);
        if(current->right!=NULL){
            push(&stack, current->right);
        } 
        if (current->left!=NULL){
            push(&stack, current->left);
        }
    }
}

void inorderIterative(struct node* root){
    if (root==NULL) return;
    Stack stack;
    initializeStack(&stack);
    struct node* current = root;

    while(stack.top!=-1 || current!=NULL){
        while (current!=NULL){
            push(&stack, current);
            current = current->left;
        }
        current = pop(&stack);
        printf("%d ", current->data);
        current = current->right;
    }
}

void postorderIterative(struct node* root){
    if (root==NULL) return;
    struct node* current = root;
    struct node* prev = NULL;
    Stack stack;
    initializeStack(&stack);

    while(stack.top!=-1||current!=NULL){
        if (current!=NULL){
            push(&stack, current);
            current = current->left;
        }
        else{
            struct node* temp = pop(&stack);
            if (temp->right==NULL || temp->right==prev){
                printf("%d ", temp->data);
                prev=temp;
            }
            else{
                push(&stack, temp);
                current = temp->right;
            }
        }
    }
}

int main(){
    struct node* root = NULL;
    root = buildBST();

    printf("Preorder traversal of the binary tree is: ");
    preorderIterative(root);
    printf("\nInorder traversal of the binary tree is: ");
    inorderIterative(root);
    printf("\nPostorder traversal of the binary tree is: ");
    postorderIterative(root);
}
