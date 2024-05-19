#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* left, *right;
    int lthread, rthread;
};

struct node* newNode(int data){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = temp->right = NULL;
    temp->lthread = temp->rthread = 1;
    return temp;
}

struct node* insert(struct node* root, int key){
    if (root==NULL) return newNode(key);

    struct node* current = root;
    struct node* parent = NULL;

    while(current!=NULL){
        if (key==current->data){
            return root; //no duplicates
        }
        parent = current;
        if (key<current->data){
            if (current->lthread==0){
                current = current->left;
            }
            else{
                break;
            }
        }
        else if(key>current->data){
            if (current->rthread==0){
                current = current->right;
            }
            else{
                break;
            }
        }
    }

    struct node* new = newNode(key);
    if (key<parent->data){
        new->left = parent->left;
        new->right = parent;
        parent->lthread = 0;
        parent->left = new;
    }
    else if(key>parent->data){
        new->right = parent->right;
        new->left = parent;
        parent->rthread = 0;
        parent->right = new;
    }

    return root;
}

struct node* buildBST(){
    struct node* root = NULL;
    int val, data;
    printf("Enter the number of nodes: ");
    scanf("%d", &val);
    for (int i=0; i<val; i++){
        printf("Enter the value of the node: ");
        scanf("%d", &data);
        root = insert(root, data);
    }
    return root;
}

void inorder(struct node* root){
    struct node* current = root;
    while(current!=NULL && current->lthread==0){
        current = current->left;
    }
    while(current!=NULL){
        printf("%d ", current->data);
        if (current->rthread==1){
            current = current->right;
        }
        else{
            current = current->right;
            while(current!=NULL && current->lthread==0){
                current = current->left;
            }
        }
    }
}

void preorder(struct node* root){
    struct node* current = root;
    while (current!=NULL){
        printf("%d ", current->data);
        if (current->lthread==0){
            current = current->left;
        }
        else{
            while(current!=NULL && current->rthread==1){
                current = current->right;
            }
            if (current!=NULL){
                current = current->right;
            }
        }
    }
}

void postorder(struct node* root){
    if(root==NULL) return;

    struct node* current = root;
    struct node* previous = NULL;

    while(current!=NULL){
        if (previous==NULL || previous->left==current || previous->right==current){
            if(current->lthread==0){
                previous = current;
                current = current->left;
            }
            else if(current->rthread==0){
                previous = current;
                current = current->right;
            }
            else{
                printf("%d ", current->data);
                previous = current;
                current = current->right;
            }
        }
        else if(current->left == previous){
            if (current->rthread==0){
                previous = current;
                current = current->right;
            }
            else{
                printf("%d ", current->data);
                previous = current;
                current = current->right;
            }
        }
        else if(current->right == previous){
            printf("%d ", current->data);
            previous = current;
            current = current->right;
        }
    }
}


int main(){
    struct node* root = buildBST();
    printf("Inorder traversal: ");
    inorder(root);
}

//preorder explaination:
/*
        10
       /  \
      5    20
          /  \
        15    30

The threaded links are as follows:

5's right thread points to 10
15's right thread points to 20
30's left thread points to 20
Now, the preorder traversal of this tree would be: 10, 5, 20, 15, 30.

Here's how the preorder function traverses this tree:

Start at the root 10, print its value.
Move to the left child 5, print its value.
Return to the parent 10, move to the right child 20, print its value.
Move to the left child 15, print its value.
Return to the parent 20, move to the right child 30, print its value.
This traversal follows the preorder order: root, left, right.
*/