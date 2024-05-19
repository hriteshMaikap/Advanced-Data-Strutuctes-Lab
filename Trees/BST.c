#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

struct node{
    int data;
    struct node* left;
    struct node* right;
};

struct node* newNode(int item){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = item;
    temp->right= NULL;
    temp->left= NULL; 
}

struct node* insert(struct node* node, int item){
    if (node==NULL){
        return newNode(item);
    }
    if(item<node->data){
        node->left = insert(node->left, item);
    }
    else if(item>node->data){
        node->right = insert(node->right, item);
    }
    return node;
}

struct node* iterativeInsert(struct node* node, int item){
    struct node* current = node, *parent = NULL;
    //find the position where to insert
    while(current!=NULL){
        parent = current;
        if (item<current->data){
            current = current->left;
        }
        else if(item>current->data){
            current = current->right;
        }
        else{
            return node; //no duplicates
        }
    }

    //insert the node
    struct node* temp = newNode(item);
    if (parent==NULL){
        return temp;
    }
    if (temp->data<parent->data){
        parent->left = temp;
    }
    else if(temp->data>parent->data){
        parent->right = temp;
    }

    return node;
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

void inorder(struct node* root){
    if (root==NULL){
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(struct node* root){
    if (root==NULL){
        return;
    }
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct node* root){
    if (root==NULL){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int main(){
    struct node* root = buildBST();
    printf("\nInorder traversal of the tree is: ");
    inorder(root);

    printf("\nPreorder traversal of the tree is: ");
    preorder(root);

    printf("\nPostorder traversal of the tree is: ");
    postorder(root);
    return 0;
}
