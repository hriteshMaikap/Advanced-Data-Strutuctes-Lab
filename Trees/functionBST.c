#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct node{
    int data;
    struct node* left, *right;
};

typedef struct{
    int top;
    struct node* arr[MAX];
}Stack;

void initializeStack(Stack* stack){
    stack->top = -1;
}

void push(Stack* stack, struct node* root){
    if (stack->top==MAX-1){
        printf("Overflow...");
        return;
    }
    stack->arr[++stack->top] = root;
}

struct node* pop(Stack* stack){
    if (stack->top==-1){
        printf("Stack is emptyy...");
        return -1;
    }
    return stack->arr[stack->top--];
}

struct node* newNode(int item){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = item;
    temp->left = temp->right = NULL;
    return temp;
}

struct node* insert(struct node* root, int key){
    if (root==NULL) return newNode(key);

    if (key<root->data){
        root->left = insert(root->left, key);
    }
    else if (key>root->data){
        root->right = insert(root->right, key);
    }
    return root;
}

struct node* buildBST(){
    struct node* root = NULL;
    int data, val;
    printf("Enter the number of nodes: ");
    scanf("%d", &val);
    for(int i=0; i<val; i++){
        printf("Enter value: ");
        scanf("%d", &data);
        root = iterativeInsert(root, data);
    }
    return root;
}

int max(int a, int b){
    return a>b ? a : b;
}

int heighRecursive(struct node* root){
    if (root==NULL) return 0;
    int leftHeight = heighRecursive(root->left);
    int rightHeight = heighRecursive(root->right);

    return 1+max(leftHeight, rightHeight);
}

int height(struct node* root){
    if (root==NULL) return 0;

    Stack stack;
    initializeStack(&stack);
    push(&stack,root);
    int height = 0;
    while(1){
        int nodeCount = stack.top+1;
        if (nodeCount==0){
            return height;
        }
        height++;
        while(nodeCount>0){
            struct node* temp = pop(&stack);
            if (temp->left!=NULL){
                push(&stack, temp->left);
            }
            if (temp->right!=NULL){
                push(&stack, temp->right);
            }
            nodeCount--;
        }
    }

}   

int findMax(struct node* root){
    if (root==NULL) return -1;
    while(root!=NULL){
        root = root->right;
    }
    return root->data;
}

void displayLeaf(struct node* root){
    if (root==NULL) return;

    if (root->left==NULL && root->right==NULL){
        printf("%d ", root->data);
        return;
    }
    if (root->left!=NULL){
        displayLeaf(root->left);
    }
    if (root->right!=NULL){
        displayLeaf(root->right);
    }
}

void displayLeafIterative(struct node* root){
    if (root==NULL) return;
    Stack stack;
    initializeStack(&stack);
    push(&stack, root);

    while(stack.top!=-1){
        struct node* temp = pop(&stack);
        if (temp->left==NULL && temp->right==NULL){
            printf("%d ", temp->data);
        }
        if (temp->right!=NULL){
            push(&stack, temp->right);
        }
        if (temp->right!=NULL){
            push(&stack, temp->left);
        }
    }
}

void displayInternal(struct node* root){
    if (root==NULL) return;

    if (root->left!=NULL || root->right!=NULL){
        printf("%d ",root->data);
    }
    if (root->left!=NULL){
        displayInternal(root->left);
    }
    if (root->right!=NULL){
        displayInternal(root->right);
    }
}

void displayInternalIteravtive(struct node* root){
    if (root==NULL) return;
    Stack stack;
    initializeStack(&stack);
    push(&stack, root);

    while(stack.top!=-1){
        struct node* temp = pop(&stack);
        if (temp->left!=NULL || temp->right!=NULL){
            printf("%d ", temp->data);
        }
        if (temp->right!=NULL){
            push(&stack, temp->right);
        }
        if (temp->right!=NULL){
            push(&stack, temp->left);
        }
    }
}

struct node* search(struct node* root, int key){
    while (root!=NULL && root->data!=key){
        if (key<root->data){
            root = root->left;
        }
        else{
            root = root->right;
        }
    }
    return root; //if root==NULL data not found
}

struct node* searchRecursive(struct node* root, int key){
    if (root==NULL || root->data==key){
        return root;
    }
    if (key<root->data){
        return searchRecursive(root->left, key);
    }
    return searchRecursive(root->right, key);
}

int main(){
    struct node* root = buildBST();
    
}