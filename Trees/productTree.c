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

// Function to count the number of nodes in the BST
int countNodes(Node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Function to store the codes of the nodes in an array using in-order traversal
void storeCodesInOrder(Node* root, int* res, int* index) {
    if (root == NULL) {
        return;
    }
    storeCodesInOrder(root->left, res, index);
    res[(*index)++] = root->product.code;
    storeCodesInOrder(root->right, res, index);
}

// Function to list products in lexicographical order by name using bubble sort
void listProductsInLexicographicalOrder(Node* root) {
    int nodeCount = countNodes(root);
    int* codes = (int*)malloc(nodeCount * sizeof(int));
    int index = 0;

    // Store the codes of the nodes in an array
    storeCodesInOrder(root, codes, &index);

    // Bubble sort the array of codes based on product names
    for (int i = 0; i < nodeCount - 1; i++) {
        for (int j = 0; j < nodeCount - i - 1; j++) {
            Node* nodeA = find(root, codes[j]);
            Node* nodeB = find(root, codes[j + 1]);
            if (strcmp(nodeA->product.name, nodeB->product.name) > 0) {
                // Swap the codes if names are out of order
                int temp = codes[j];
                codes[j] = codes[j + 1];
                codes[j + 1] = temp;
            }
        }
    }

    // Print the sorted products
    for (int i = 0; i < nodeCount; i++) {
        Node* node = find(root, codes[i]);
        Product p = node->product;
        printf("Code: %d, Name: %s, Price: %.2f, Stock: %d, Received: %s, Expiry: %s\n",
               p.code, p.name, p.price, p.amount_in_stock, p.date_received, p.expiration_date);
    }

    // Free the dynamic array
    free(codes);
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

    while (1) {
        printf("\n1. Insert Product\n2. Find and Update Product\n3. List Products\n4. Exit\n");
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
                printf("Listing products in lexicographic order of their names:\n");
                listProductsInLexicographicalOrder(root);
                break;
            case 4:
                exit(0);
        }
    }
    return 0;
}
