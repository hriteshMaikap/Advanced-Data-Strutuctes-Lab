#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* left, *right;
    int lthread, rthread;
};

// Function to create a new node
struct node* newNode(int data){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = temp->right = NULL;
    temp->lthread = temp->rthread = 1;
    return temp;
}

// Function to perform left rotation
struct node* leftRotate(struct node* x){
    struct node* y = x->right;
    struct node* T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

// Function to perform right rotation
struct node* rightRotate(struct node* y){
    struct node* x = y->left;
    struct node* T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

// Function to get the height of a node
int height(struct node* root){
    if (root == NULL) return 0;
    return 1 + max(height(root->left), height(root->right));
}

// Function to get the balance factor of a node
int getBalance(struct node* root){
    if (root == NULL) return 0;
    return height(root->left) - height(root->right);
}

// Function to balance the AVL tree
struct node* balanceAVL(struct node* root, int key){
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && key < root->left->data)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && key > root->right->data)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && key > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && key < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to insert a node into AVL tree
struct node* insert(struct node* root, int key){
    if (root == NULL) return newNode(key);

    struct node* current = root;
    struct node* parent = NULL;

    while (current != NULL) {
        if (key == current->data) {
            return root; // no duplicates
        }
        parent = current;
        if (key < current->data) {
            if (current->lthread == 0) {
                current = current->left;
            } else {
                break;
            }
        } else {
            if (current->rthread == 0) {
                current = current->right;
            } else {
                break;
            }
        }
    }

    struct node* new = newNode(key);
    if (key < parent->data) {
        new->left = parent->left;
        new->right = parent;
        parent->lthread = 0;
        parent->left = new;
    } else {
        new->right = parent->right;
        new->left = parent;
        parent->rthread = 0;
        parent->right = new;
    }

    // Update balance factors and perform rotations
    root = balanceAVL(root, key);

    // Re-threading after balancing
    if (new->left == NULL) {
        new->lthread = 1;
        new->left = parent;
    }
    if (new->right == NULL) {
        new->rthread = 1;
        new->right = parent->right;
        parent->rthread = 0;
    }

    return root;
}

// Function to perform inorder traversal of the threaded AVL tree
void inorder(struct node* root){
    struct node* current = root;
    while (current != NULL && current->lthread == 0) {
        current = current->left;
    }
    while (current != NULL) {
        printf("%d ", current->data);
        if (current->rthread == 1) {
            current = current->right;
        } else {
            current = current->right;
            while (current != NULL && current->lthread == 0) {
                current = current->left;
            }
        }
    }
}

// Main function
int main(){
    struct node* root = NULL;
    int val, data;
    printf("Enter the number of nodes: ");
    scanf("%d", &val);
    for (int i = 0; i < val; i++){
        printf("Enter the value of the node: ");
        scanf("%d", &data);
        root = insert(root, data);
    }
    printf("Inorder traversal: ");
    inorder(root);
    return 0;
}