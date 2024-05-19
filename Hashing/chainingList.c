#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10 
typedef struct {
    int id;
    char name[50];
    char dept[50];
} Faculty;

typedef struct Node {
    int key;
    Faculty faculty;
    struct Node* next;
} Node;

typedef struct {
    Node* table[SIZE];
} HashTable;

int hashFunction(int key) {
    return key % SIZE;
}

void initializeHashTable(HashTable *hashTable) {
    for (int i = 0; i < SIZE; i++) {
        hashTable->table[i] = NULL;
    }
}

Node* createNewNode(int key, Faculty faculty) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->faculty = faculty;
    newNode->next = NULL;
    return newNode;
}

void insertFaculty(HashTable *hashTable, int key, Faculty faculty) {
    int index = hashFunction(key);
    Node* newNode = createNewNode(key, faculty);

    if (hashTable->table[index] == NULL) {
        hashTable->table[index] = newNode;
    } else {
        Node* temp = hashTable->table[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void searchFaculty(HashTable *hashTable, int key) {
    int index = hashFunction(key);
    Node* temp = hashTable->table[index];
    while (temp != NULL && temp->key != key) {
        temp = temp->next;
    }
    if (temp != NULL && temp->key == key) {
        printf("Record found\n");
        printf("\nID: %d", temp->faculty.id);
        printf("\nName: %s", temp->faculty.name);
        printf("\nDepartment: %s\n", temp->faculty.dept);
    } else {
        printf("Record with ID %d not found!\n", key);
    }
}

int main() {
    HashTable hashTable;
    initializeHashTable(&hashTable);
    int key;
    Faculty faculty;
    int choice;
    do {
        printf("1. Insert\n2. Search\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter faculty id: ");
                scanf("%d", &key);
                faculty.id = key;
                printf("Enter faculty name: ");
                scanf("%s", faculty.name);
                printf("Enter faculty department: ");
                scanf("%s", faculty.dept);
                insertFaculty(&hashTable, key, faculty);
                break;
            case 2:
                printf("Enter the faculty id to search: ");
                scanf("%d", &key);
                searchFaculty(&hashTable, key);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    } while (choice != 3);
    return 0;
}
