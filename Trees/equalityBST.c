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
    struct node* arr[MAX]; // Creating an array to store the nodes
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

// Iterative function to check if two BSTs are equal using a single stack
int areBSTsEqualIterative(struct node* root1, struct node* root2) {
    Stack stack;
    initializeStack(&stack);

    push(&stack, root1);
    push(&stack, root2);

    while (stack.top != -1) {
        struct node* current1 = pop(&stack);
        struct node* current2 = pop(&stack);

        if (current1 == NULL && current2 == NULL) {
            continue;
        }
        if (current1 == NULL || current2 == NULL || current1->data != current2->data) {
            return 0;
        }

        // Push the right children first so that the left children are processed first
        push(&stack, current1->right);
        push(&stack, current2->right);

        push(&stack, current1->left);
        push(&stack, current2->left);
    }

    return 1;
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

int main() {
    printf("Building first BST:\n");
    struct node* root1 = buildBST();
    
    printf("Building second BST:\n");
    struct node* root2 = buildBST();
    
    if (areBSTsEqualIterative(root1, root2)) {
        printf("The two BSTs are equal.\n");
    } else {
        printf("The two BSTs are not equal.\n");
    }
    
    return 0;
}
