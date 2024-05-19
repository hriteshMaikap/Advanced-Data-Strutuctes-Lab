#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node{
    int data;
    struct node* left;
    struct node* right;
};

struct node* newNode(int item){
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->data = item;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct node* insert(struct node* root, int item){
    if (root==NULL) return newNode(item);
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
    int val, data;
    printf("Enter the number of nodes: ");
    scanf("%d", &val);

    for (int i=0; i<val; i++){
        printf("Enter the data: ");
        scanf("%d", &data);
        root = insert(root, data);
    }
    return root;
}

void inorder(struct node* root){
    if (root==NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

//finding the inorder successor (leftmost value for a given right subtree)
struct node* minVal(struct node* node){
    struct node* current = node;
    while(current && current->left!=NULL){
        current = current->left;
    }
    return current;
}

struct node* deleteNode(struct node* root, int item){
    if (root==NULL) return root;
    //search for the node to be deleted
    if (item<root->data){
        root->left = deleteNode(root->left, item);
    }
    else if(item>root->data){
        root->right = deleteNode(root->right, item);
    }

    //node to be deleted is found
    else{
        //node with single or no child
        if (root->left==NULL){
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right==NULL){
            struct node* temp = root->left;
            free(root);
            return temp;
        }
        else{
            //node with two children
            struct node* temp = minVal(root->right); //minimum value of right subtree
            root->data = temp->data; //replace the value at the root without affecting the connections
            //delete leaf node of the right subtree after switching the vale of root node
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}   

int main(){
    struct node* root = buildBST();
    printf("Inorder traversal:\n");
    inorder(root);
    int del;
    printf("\nEnter the node to delete:");
    scanf("%d", &del);
    root = deleteNode(root, del);
    printf("Inorder traversal after deletion is: \n");
    inorder(root);
    return 0;
}