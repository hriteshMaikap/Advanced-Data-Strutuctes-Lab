#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* left;
    struct node* right;
};

struct node* createNode(int data){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->right = temp->left = NULL;
    return temp;
}

int max(int val1, int val2){
    return (val1>val2) ? val1 : val2;
}

int height(struct node* root){
    if (root==NULL) return 0;
    return 1+ max(height(root->left), height(root->right));
}

int getBalance(struct node* root){
    if (root==NULL) return 0;
    return height(root->left)-height(root->right);
}

struct node* rightRotate(struct node* y){
    struct node* x = y->left;
    struct node* T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

struct node* leftRotate(struct node* x){
    struct node* y = x->right;
    struct node* T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

struct node* insert(struct node* root, int key){
    //insert data at the required position
    if (root==NULL) return createNode(key);

    if (key<root->data){
        root->left = insert(root->left, key);
    }
    else if (key>root->data){
        root->right = insert(root->right, key);
    }
    else{
        return root; //no duplicates
    }

    //check balance factor
    int balance = getBalance(root);

    //LL 
    if (balance>1 && key<root->left->data){
        return rightRotate(root);
    }

    //RR
    if (balance<-1 && key>root->right->data){
        return leftRotate(root);
    }

    //LR
    if (balance>1 && key>root->left->data){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    //RL
    if (balance<-1 && key<root->right->data){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct node* minVal(struct node* root){
    struct node* current = root;
    while(current && current->left!=NULL){
        current = current->left;
    }
    return current;
}

struct node* delete(struct node* root, int key){
    //Step 1. Standard delete
    if (root==NULL) return root;

    //1.1 find the position where we need to delete
    if (key<root->data){
        root->left = delete(root->left, key);
    }
    else if(key>root->data){
        root->right = delete(root->right, key);
    }
    //1.2 you find the position where you want to delete key==root->data
    else{
        //1.3 single child or no child
        if (root->left==NULL){
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right==NULL){
            struct node* temp = root->left;
            free(root);
            return temp;
        }
        else{
            //1.4 two child of the root
            struct node* temp = minVal(root->right);
            root->data = temp->data;
            root->right = delete(root->right, temp->data);
        }
    }
    
    if (root==NULL) return root;

    //Step 2 check for balance factors
    int balance = getBalance(root);

    //LL 
    if (balance>1 && getBalance(root->left)>=0){
        return rightRotate(root);
    }
    //LR
    if (balance>1 && getBalance(root->right)<0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    //RR
    if (balance<-1 && getBalance(root->right)<=0){
        return leftRotate(root);
    }
    //RL
    if (balance<-1 && getBalance(root->left)>0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void inorder (struct node* root){
    if (root==NULL) return;
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

int main(){
    struct node* root = NULL;
    int choice, key;

    do{
        printf("\n1. Insert Node\n2. Delete Node\n3. Inorder Traversal\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice){
        case 1:
            printf("Enter the node value to insert: ");
            scanf("%d", &key);
            root = insert(root, key);
            break;

        case 2:
            printf("Enter the value of the node to delete: ");
            scanf("%d", &key);
            root = delete(root, key);
            break;
        case 3:
            printf("Inorder traversal: ");
            inorder(root);
            printf("\n");
            break;
        case 4:
            printf("Exiting\n");
            break;
        default:
            break;
        }
    }while (choice!=4);
}
