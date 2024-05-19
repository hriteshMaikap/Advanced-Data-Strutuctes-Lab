#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
    int lthread;
    int rthread;
};

struct node* newNode(int item) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = item;
    temp->left = NULL;
    temp->right = NULL;
    temp->lthread = 1;
    temp->rthread = 1;
    return temp;
}

void insert(struct node** root, int item) {
    struct node* parent = NULL;
    struct node* current = *root;

    while (current != NULL) {
        if (item == current->data) {
            return;
        }
        parent = current;
        if (item < current->data) {
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

    struct node* new_node = newNode(item);

    if (parent == NULL) {
        *root = new_node;
    } else if (item < parent->data) {
        new_node->left = parent->left;
        new_node->right = parent;
        parent->lthread = 0;
        parent->left = new_node;
    } else {
        new_node->right = parent->right;
        new_node->left = parent;
        parent->rthread = 0;
        parent->right = new_node;
    }
}

struct node* buildBST() {
    struct node* root = NULL;
    int val, data;
    printf("Enter the number of nodes: ");
    scanf("%d", &val);

    for (int i = 0; i < val; i++) {
        printf("Enter the data: ");
        scanf("%d", &data);
        insert(&root, data);
    }
    return root;
}

void inorder(struct node* root) {
    if (root == NULL) {
        return;
    }

    struct node* current = root;
    while (current->lthread == 0) {
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

void preorder(struct node* root) {
    if (root == NULL) {
        return;
    }

    struct node* current = root;
    while (current != NULL) {
        printf("%d ", current->data);

        if (current->lthread == 0) {
            current = current->left;
        } else {
            while (current != NULL && current->rthread == 1) {
                current = current->right;
            }
            if (current != NULL) {
                current = current->right;
            }
        }
    }
}

void postorder(struct node* root) {
    if (root == NULL) {
        return;
    }

    struct node* current = root;
    struct node* previous = NULL;

    while (current != NULL) {
        if (previous == NULL || previous->left == current || previous->right == current) {
            if (current->lthread == 0) {
                previous = current;
                current = current->left;
            } else if (current->rthread == 0) {
                previous = current;
                current = current->right;
            } else {
                printf("%d ", current->data);
                previous = current;
                current = current->right;
            }
        } else if (current->left == previous) {
            if (current->rthread == 0) {
                previous = current;
                current = current->right;
            } else {
                printf("%d ", current->data);
                previous = current;
                current = current->right;
            }
        } else if (current->right == previous) {
            printf("%d ", current->data);
            previous = current;
            current = current->right;
        }
    }
}

struct node* inorderSuccessor(struct node* ptr) {
    if (ptr->rthread == 1)
        return ptr->right;
    ptr = ptr->right;
    while (ptr->lthread == 0)
        ptr = ptr->left;
    return ptr;
}

struct node* deleteNode(struct node* root, int key) {
    struct node* parent = NULL;
    struct node* current = root;

    // Find the node to be deleted and its parent
    while (current != NULL) {
        if (key == current->data) {
            break;
        }
        parent = current;
        if (key < current->data) {
            if (current->lthread == 0) {
                current = current->left;
            } else {
                return root; // Node not found
            }
        } else {
            if (current->rthread == 0) {
                current = current->right;
            } else {
                return root; // Node not found
            }
        }
    }

    if (current == NULL) {
        printf("Node not found\n");
        return root; // Node not found
    }

    // Case 1: Node with no children (leaf node)
    if (current->lthread == 1 && current->rthread == 1) {
        if (parent == NULL) {
            free(current);
            return NULL; // Tree had only one node
        }

        if (parent->left == current) {
            parent->left = current->left;
            parent->lthread = 1;
        } else {
            parent->right = current->right;
            parent->rthread = 1;
        }
        free(current);
    }
    // Case 2: Node with one child
    else if (current->lthread == 0 && current->rthread == 1) {
        if (parent == NULL) {
            root = current->left;
        } else if (parent->left == current) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }

        struct node* predecessor = inorderSuccessor(current);
        predecessor->right = current->right;
        free(current);
    } else if (current->lthread == 1 && current->rthread == 0) {
        if (parent == NULL) {
            root = current->right;
        } else if (parent->left == current) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }

        struct node* successor = inorderSuccessor(current);
        successor->left = current->left;
        free(current);
    }
    // Case 3: Node with two children
    else {
        struct node* successor = inorderSuccessor(current);
        int val = successor->data;
        deleteNode(root, successor->data);
        current->data = val;
    }

    return root;
}

int main() {
    struct node* root = buildBST();
    printf("Inorder Traversal: ");
    inorder(root);
    printf("\nPreorder Traversal: ");
    preorder(root);
    printf("\nPostorder Traversal: ");
    postorder(root);
    printf("\n");

    int key;
    printf("Enter the key to delete: ");
    scanf("%d", &key);
    root = deleteNode(root, key);

    printf("Inorder Traversal after deletion: ");
    inorder(root);
    printf("\n");

    return 0;
}
