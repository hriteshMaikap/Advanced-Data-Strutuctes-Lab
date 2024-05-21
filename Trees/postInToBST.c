#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* left, *right;
};

struct node* createNode(int item){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = item;
    temp->left=temp->right=NULL;
    return temp;
}

int find(int arr[], int value, int start, int end){
    for (int i=start; i<=end; i++){
        if (arr[i]==value){
            return i;
        }
    }
}

struct node* util(int inorder[], int postorder[], int inorderStart, int inorderEnd, int *postorderIndex ){
    if (inorderStart>inorderEnd) return NULL;

    struct node* node = createNode(postorder[*postorderIndex]);
    (*postorderIndex)--;

    if (inorderStart==inorderEnd){
        //single node condition
        return node;
    }
    int inorderIndex = find(inorder, node->data, inorderStart, inorderEnd);

    node->left = util(inorder, postorder, inorderStart, inorderIndex-1, postorderIndex);
    node->right = util(inorder, postorder, inorderIndex+1, inorderEnd, postorderIndex);

    return node;
}

struct node* buildTree(int inorder[], int postorder[], int length){
    int postorderIndex = length-1;
    return util(inorder, postorder, 0, length-1, &postorderIndex);
}

void inorderTraversal(struct node* root){
    if (root==NULL) return;
    inorderTraversal(root->left);
    printf("%d ",root->data);
    inorderTraversal(root->right);
}

int main(){
    int inorder[] = {9,3,15,20,7};
    int postorder[] = {3,9,20,15,7};
    int length = sizeof(inorder)/sizeof(inorder[0]);

    struct node* root = buildTree(inorder, postorder, length);
    printf("The inorder traversal of the tree is: ");
    inorderTraversal(root);
    return 0;
}