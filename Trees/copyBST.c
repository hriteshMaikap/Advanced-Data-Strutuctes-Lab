#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure for a node in the BST
struct node {
    int data;
    struct node* left;
    struct node* right;
};

// Structure for the stack
typedef struct {
    int top;
    struct node* arr[MAX];   // Creating an array to store the nodes
} Stack;

// Function to initialize the stack
void initializeStack(Stack* stack) {
    stack->top = -1;
}

// Function to push an element onto the stack
void push(Stack* stack, struct node* element) {
    if (stack->top == MAX - 1) {
        printf("Overflow\n");
        return;
    }
    stack->arr[++stack->top] = element;
}

// Function to pop an element from the stack
struct node* pop(Stack* stack) {
    if (stack->top == -1) {
        printf("Underflow\n");
        return NULL;
    }
    return stack->arr[stack->top--];
}

// Function to check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Function to create a new node
struct node* newNode(int item) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = item;
    temp->right = NULL;
    temp->left = NULL;
    return temp;
}

// Function to insert a node in the BST
struct node* insert(struct node* node, int item) {
    if (node == NULL) {
        return newNode(item);
    }
    if (item < node->data) {
        node->left = insert(node->left, item);
    } else if (item > node->data) {
        node->right = insert(node->right, item);
    }
    return node;
}

// Iterative function to copy the BST
struct node* copyBSTIterative(struct node* root) {
    if (root == NULL) {
        return NULL;
    }

    struct node* newRoot = newNode(root->data);
    Stack stack;
    initializeStack(&stack);

    struct node* currentOriginal = root;
    struct node* currentCopy = newRoot;
    push(&stack, root);
    push(&stack, newRoot);

    while (!isEmpty(&stack)) {
        currentCopy = pop(&stack);
        currentOriginal = pop(&stack);

        if (currentOriginal->right != NULL) {
            currentCopy->right = newNode(currentOriginal->right->data);
            push(&stack, currentOriginal->right);
            push(&stack, currentCopy->right);
        }
        if (currentOriginal->left != NULL) {
            currentCopy->left = newNode(currentOriginal->left->data);
            push(&stack, currentOriginal->left);
            push(&stack, currentCopy->left);
        }
    }

    return newRoot;
}

struct node* copyBSTRecursive(struct node* root) {
    if (root == NULL) {
        return NULL;
    }
    struct node* newRoot = newNode(root->data);
    newRoot->left = copyBSTRecursive(root->left);
    newRoot->right = copyBSTRecursive(root->right);
    return newRoot;
}

// Function to build a BST from user input
struct node* buildBST() {
    struct node* root = NULL;
    int data, val;
    printf("Enter the number of nodes: ");
    scanf("%d", &val);
    for (int i = 0; i < val; i++) {
        printf("Enter value: ");
        scanf("%d", &data);
        root = insert(root, data);
    }
    return root;
}

// Function to print the BST in order
void inorder(struct node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    struct node* root = buildBST();
    printf("Original BST (Inorder Traversal): ");
    inorder(root);
    printf("\n");

    struct node* copiedRoot = copyBSTIterative(root);
    printf("Copied BST (Inorder Traversal): ");
    inorder(copiedRoot);
    printf("\n");

    return 0;
}
