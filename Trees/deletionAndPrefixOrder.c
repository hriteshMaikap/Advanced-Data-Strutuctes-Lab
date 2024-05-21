#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the product structure
typedef struct Product {
    int code;
    char name[50];
    float price;
    int amount_in_stock;
    char date_received[11];
    char expiration_date[11];
} Product;

// Define the node for the BST
typedef struct Node {
    Product product;
    struct Node *left, *right;
} Node;

Node* createNode(Product product) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->product = product;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, Product product) {
    if (root == NULL) {
        return createNode(product);
    }
    if (product.code < root->product.code) {
        root->left = insert(root->left, product);
    } else if (product.code > root->product.code) {
        root->right = insert(root->right, product);
    }
    return root;
}

Node* find(Node* root, int code) {
    if (root == NULL || root->product.code == code) {
        return root;
    }
    if (code < root->product.code) {
        return find(root->left, code);
    } else {
        return find(root->right, code);
    }
}

// Function to list expired items in prefix order
void listExpiredItemsPrefixOrder(Node* root, const char* currentDate) {
    if (root == NULL) {
        return;
    }
    // Check if the current product is expired
    if (strcmp(root->product.expiration_date, currentDate) < 0) {
        printf("Code: %d, Name: %s, Price: %.2f, Stock: %d, Received: %s, Expiry: %s\n",
               root->product.code, root->product.name, root->product.price,
               root->product.amount_in_stock, root->product.date_received, root->product.expiration_date);
    }
    listExpiredItemsPrefixOrder(root->left, currentDate);
    listExpiredItemsPrefixOrder(root->right, currentDate);
}

Node* deleteAllExpiredItems(Node* root, const char* currentDate) {
    if (root == NULL) {
        return NULL;
    }

    root->left = deleteAllExpiredItems(root->left, currentDate);
    root->right = deleteAllExpiredItems(root->right, currentDate);

    if (strcmp(root->product.expiration_date, currentDate) < 0) {
        root = deleteNode(root, root->product.code);
    }

    return root;
}


Node* deleteNode(Node* root, int code) {
    if (root == NULL) return root;

    if (code < root->product.code) {
        root->left = deleteNode(root->left, code);
    } else if (code > root->product.code) {
        root->right = deleteNode(root->right, code);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->product = temp->product;
        root->right = deleteNode(root->right, temp->product.code);
    }
    return root;
}

// Function to update product by code with user confirmation
void updateProductByCode(Node* root, int code) {
    Node* node = find(root, code);
    if (node != NULL) {
        Product product = node->product;
        printf("Current product details:\n");
        printf("Code: %d, Name: %s, Price: %.2f, Stock: %d, Received: %s, Expiry: %s\n",
               product.code, product.name, product.price, product.amount_in_stock,
               product.date_received, product.expiration_date);
        printf("Do you want to update this product? (yes/no): ");
        char response[4];
        scanf("%s", response);
        if (strcmp(response, "yes") == 0) {
            printf("Enter updated product details:\n");
            printf("Code: ");
            scanf("%d", &product.code);
            printf("Name: ");
            scanf("%s", product.name);
            printf("Price: ");
            scanf("%f", &product.price);
            printf("Amount in Stock: ");
            scanf("%d", &product.amount_in_stock);
            printf("Date Received (YYYY-MM-DD): ");
            scanf("%s", product.date_received);
            printf("Expiration Date (YYYY-MM-DD): ");
            scanf("%s", product.expiration_date);
            node->product = product; // Update the product in the node
        }
    } else {
        printf("Product not found.\n");
    }
}

int main() {
    Node* root = NULL;
    int choice;
    Product product;
    int code;
    const char* currentDate = "2024-05-21"; // Current date

    while (1) {
        printf("\n1. Insert Product\n2. Find and Update Product\n3. List Expired Products\n4. Delete Product\n5. Delete All Expired Products\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter product details:\n");
                printf("Code: ");
                scanf("%d", &product.code);
                printf("Name: ");
                scanf("%s", product.name);
                printf("Price: ");
                scanf("%f", &product.price);
                printf("Amount in Stock: ");
                scanf("%d", &product.amount_in_stock);
                printf("Date Received (YYYY-MM-DD): ");
                scanf("%s", product.date_received);
                printf("Expiration Date (YYYY-MM-DD): ");
                scanf("%s", product.expiration_date);
                root = insert(root, product);
                break;
            case 2:
                printf("Enter product code to find: ");
                scanf("%d", &code);
                updateProductByCode(root, code);
                break;
            case 3:
                printf("Listing expired products in prefix order of their names:\n");
                listExpiredItemsPrefixOrder(root, currentDate);
                break;
            case 4:
                printf("Enter product code to delete: ");
                scanf("%d", &code);
                root = deleteNode(root, code);
                break;
            case 5:
                root = deleteAllExpiredItems(root, currentDate);
                printf("All expired products deleted.\n");
                break;
            case 6:
                exit(0);
        }
    }
    return 0;
}