#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left, *right;
    int lthread, rthread;
};

struct node* createNode(int item){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = item;
    temp->left = temp->right = NULL;
    temp->lthread = temp->rthread = 1;
    return temp;
}

struct node* insert(struct node* root, int key){
    if (root==NULL) return createNode(key);

    struct node* current = root;
    struct node* parent = NULL;

    while(current!=NULL){
        if (current->data==key){
            return root;
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

    struct node* new = createNode(key);
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

struct node* inorderPredecessor(struct node* ptr){
    if (ptr->lthread==1){
        return ptr->left;
    }
    ptr = ptr->left;
    while(ptr->rthread==0){
        ptr = ptr->right;
    }
    return ptr;
}

struct node* inorderSuccessor(struct node* ptr){
    if (ptr->rthread==1){
        return ptr->right;
    }
    ptr = ptr->right;
    while(ptr->lthread==0){
        ptr = ptr->left;
    }
    return ptr;
}

struct node* delete(struct node* root, int key){
    struct node* current = root;
    struct node* parent = NULL;

    while(current!=NULL){
        if (current->data==key){
            break;
        }
        parent = current;
        if (key<current->data){
            if (current->lthread==0){
                current = current->left;
            }
            else{
                printf("\nNode not found!");
                return root;
            }
        }
        else if(key>current->data){
            if (current->rthread==0){
                current = current->right;
            }
            else{
                printf("\nNode not found!");
                return root;
            }
        }
    }

    if (parent==NULL){
        printf("\nNode not found!");
        return root;
    }

    //Case 1 no children or deletion of leaf node
    if (current->lthread==1 && current->rthread==1){
        if (parent==NULL){
            free(current);
            return NULL;
        }
        else if(parent->left==current){
            parent->left = current->left;
            parent->lthread=1;
        }
        else{
            parent->right= current->right;
            parent->rthread=1;
        }
        free(current);
    }
    //Case 2.1 One child on the left
    else if(current->lthread==0 && current->rthread==1){
        if (parent==NULL){
            root = current->left;
        }
        else if(parent->left==current){
            parent->left = current->left;
        }
        else{
            parent->right = current->left;
        }
        struct node* predecessor = inorderPredecessor(current);
        predecessor->right = current->right;
        free(current);
    }
    //Case 2.2 One child on the right
    else if(current->rthread==1 && current->rthread==0){
        if (parent==NULL){
            root = current->right;
        }
        else if (parent->left==current){
            parent->left = current->right;
        }
        else{
            parent->right = current->right;
        }
        struct node* successor = inorderSuccessor(current);
        successor->left = current->left;
        free(current);
    }
    //Case 3 two child nodes
    else{   
        struct node* successor = inorderSuccessor(current);
        int val = successor->data;
        delete(root, val);
        current->data = val;
    }
    return root;
}

void inorder(struct node* root){
    struct node* current = root;
    while(current!=NULL && current->lthread==0){
            current = current->left;
    }
    while(current!=NULL){
        printf("%d ",current->data);
        if (current->rthread==1){
            current = current->right;
        }
        else{
            current = current->right;
            while (current!=NULL && current->lthread==0){
                current = current->left;
            }
        }
    }
}

int main(){
    struct node* root = NULL;
    int choice, key;
    do{
        printf("\n1.Insert\n2.Delete\n3.Inorder\n4.Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                printf("Enter the node value to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Enter node value to delete: ");
                scanf("%d", &key);
                root = delete(root, key);
                break;
            case 3:
                printf("The inorder traversal is: ");
                inorder(root);
                break;
            case 4:
                printf("Exiting...");
                break;
            default:
                printf("Invalid choice!");
                break;
        }
    }while(choice!=4);
}