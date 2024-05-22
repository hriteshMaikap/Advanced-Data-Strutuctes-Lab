#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// Structure for Hash Entry
typedef struct {
    int key;
    int value;
} HashEntry;

// Structure for Hash Table
typedef struct {
    HashEntry table[TABLE_SIZE];
    int chain[TABLE_SIZE]; // Array to store chain values
} HashTable;

// Initialize Hash Table
void initializeHashTable(HashTable* hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i].key = -1; // -1 indicates empty slot
        hashTable->table[i].value = -1;
        hashTable->chain[i] = -1; // -1 indicates no replacement
    }
}

// Hash Function
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Insert into Hash Table with Chaining and Replacement
void insert(HashTable* hashTable, int key, int value) {
    int index = hashFunction(key);
    if (hashTable->table[index].key == -1) { // If the slot is empty
        hashTable->table[index].key = key;
        hashTable->table[index].value = value;
    } else { // Slot is occupied, perform linear probing
        int originalIndex = index;
        int i = (index + 1) % TABLE_SIZE; // Start probing from next index

        // Look for an empty slot or the slot with a key that can be replaced
        while (i != index) {
            if (hashTable->table[i].key == -1) { // Found an empty slot
                hashTable->table[i].key = key;
                hashTable->table[i].value = value;
                
                // Update the chain of the original index
                while (hashTable->chain[originalIndex] != -1) {
                    originalIndex = hashTable->chain[originalIndex];
                }
                hashTable->chain[originalIndex] = i;
                return;
            }
            
            int existingKeyHash = hashFunction(hashTable->table[i].key);
            if (existingKeyHash != i && existingKeyHash == index) { // Found a key that can be replaced
                int displacedKey = hashTable->table[i].key;
                int displacedValue = hashTable->table[i].value;

                // Replace the current key-value pair
                hashTable->table[i].key = key;
                hashTable->table[i].value = value;

                // Insert the displaced key-value pair
                insert(hashTable, displacedKey, displacedValue);
                return;
            }
            i = (i + 1) % TABLE_SIZE; // Move to next index
        }
        // Table is full, cannot insert
        printf("Error: Hash table is full.\n");
    }
}

// Search in Hash Table
int search(HashTable* hashTable, int key) {
    int index = hashFunction(key);
    if (hashTable->table[index].key == key) { // Found at original index
        return index;
    } else { // Check chain for the key
        int chainIndex = hashTable->chain[index];
        while (chainIndex != -1) {
            if (hashTable->table[chainIndex].key == key) {
                return chainIndex;
            }
            chainIndex = hashTable->chain[chainIndex];
        }
    }
    // Key not found
    return -1;
}

// Display Hash Table
void displayHashTable(HashTable* hashTable) {
    printf("Hash Table:\n");
    printf("Index\tKey\tValue\tChain\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%d\t%d\t%d\t%d\n", i, hashTable->table[i].key, hashTable->table[i].value, hashTable->chain[i]);
    }
}

int main() {
    HashTable hashTable;
    initializeHashTable(&hashTable);

    // Inserting values
    insert(&hashTable, 94, 1); // Should go to index 4
    insert(&hashTable, 84, 2); // Should go to index 5 due to linear probing
    insert(&hashTable, 95, 3); // Should go to index 6 due to linear probing
    insert(&hashTable, 85, 4); // Should replace 84 and move it to index 7 due to replacement

    // Displaying Hash Table
    displayHashTable(&hashTable);

    // Searching for a key
    int keyToSearch = 85;
    int searchResult = search(&hashTable, keyToSearch);
    if (searchResult != -1) {
        printf("Key %d found at index %d\n", keyToSearch, searchResult);
    } else {
        printf("Key %d not found\n", keyToSearch);
    }

    return 0;
}
