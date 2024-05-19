#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

typedef struct{
    int id;
    char name[50];
    char dept[50];
}Faculty;

typedef struct{
    int key;
    Faculty faculty;
}HashEntry;

typedef struct{
    HashEntry table[SIZE];
}HashTable;

void initializeHashTable(HashTable* hashTable){
    for (int i=0; i<SIZE; i++){
        hashTable->table[i].key = -1;
    }
}

int hashFuntion(int key){
    return key%SIZE;
}

void insert(HashTable* hashTable, int key, Faculty faculty){
    int index = hashFuntion(key);
    while(hashTable->table[index].key!=-1){
        index = (index+1)%SIZE;
    }
    hashTable->table[index].key = key;
    hashTable->table[index].faculty = faculty;
}

void search(HashTable* hashTable, int key){
    int index = hashFuntion(key);
    int original = index;
    while (hashTable->table[index].key!=key && hashTable->table[index].key!=-1){
        index = (index+1)%SIZE;
        if (index==original){
            printf("Record with id %d not found", key);
        }
    }
    if (hashTable->table[index].key==key){
        printf("Record found!\n");
        printf("Faculty ID: %d\n", hashTable->table[index].faculty.id);
        printf("Faculty Name: %s\n", hashTable->table[index].faculty.name);
        printf("Faculty Department: %s\n", hashTable->table[index].faculty.dept);
    }
    else{
        printf("Record with id %d not found", key);
    }
}

int main(){
    HashTable hashTable;
    initializeHashTable(&hashTable);
    int choice;
    Faculty faculty;
    int key;
    do{
        printf("1. Insert\n2. Search\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter faculty id: ");
            scanf("%d", &key);
            faculty.id = key;
            printf("Enter faculty name: ");
            scanf("%s", faculty.name);
            printf("Enter faculty department: ");
            scanf("%s", faculty.dept);
            insert(&hashTable, key, faculty);
            break;
        
        case 2:
            printf("Enter the faculty id to search: ");
            scanf("%d", &key);
            search(&hashTable, key);
            break;
        case 3:
            printf("Exiting...\n");
            break;
        default:
            break;
        }
    }while (choice!=3);
    return 0;
}