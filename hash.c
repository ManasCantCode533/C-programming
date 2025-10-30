#include <stdio.h>
#include <stdlib.h>

#define SIZE 10   // Hash table size

// -------------------------------
// OPEN HASHING (CHAINING)
// -------------------------------
struct Node {
    int data;
    struct Node* next;
};

struct Node* chain[SIZE];

// Initialize hash table
void initChain() {
    for (int i = 0; i < SIZE; i++)
        chain[i] = NULL;
}

// Hash function
int hashFunction(int key) {
    return key % SIZE;
}

// Insert using chaining
void insertChain(int key) {
    int index = hashFunction(key);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = key;
    newNode->next = chain[index];
    chain[index] = newNode;
}

// Delete using chaining
void deleteChain(int key) {
    int index = hashFunction(key);
    struct Node* temp = chain[index];
    struct Node* prev = NULL;

    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return; // not found

    if (prev == NULL)
        chain[index] = temp->next;
    else
        prev->next = temp->next;

    free(temp);
}

// Display open hashing table
void displayChain() {
    printf("\nOpen Hash Table (Chaining):\n");
    for (int i = 0; i < SIZE; i++) {
        printf("chain[%d]: ", i);
        struct Node* temp = chain[i];
        while (temp) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// -------------------------------
// CLOSED HASHING (LINEAR PROBING)
// -------------------------------
int hashTable[SIZE];
int status[SIZE]; // 0 = empty, 1 = occupied, -1 = deleted

void initTable() {
    for (int i = 0; i < SIZE; i++) {
        hashTable[i] = -1;
        status[i] = 0;
    }
}

// Insert using linear probing
void insertLinear(int key) {
    int index = hashFunction(key);
    int start = index;

    do {
        if (status[index] == 0 || status[index] == -1) {
            hashTable[index] = key;
            status[index] = 1;
            return;
        }
        index = (index + 1) % SIZE;
    } while (index != start);
}

// Delete using linear probing
void deleteLinear(int key) {
    int index = hashFunction(key);
    int start = index;

    do {
        if (status[index] == 0)
            return;
        if (status[index] == 1 && hashTable[index] == key) {
            status[index] = -1;
            return;
        }
        index = (index + 1) % SIZE;
    } while (index != start);
}

// Display closed hashing table
void displayLinear() {
    printf("\nClosed Hash Table (Linear Probing):\n");
    for (int i = 0; i < SIZE; i++) {
        if (status[i] == 1)
            printf("[%d] -> %d\n", i, hashTable[i]);
        else if (status[i] == -1)
            printf("[%d] -> (Deleted)\n", i);
        else
            printf("[%d] -> (Empty)\n", i);
    }
}

// -------------------------------
// MAIN PROGRAM — DIRECT INPUT
// -------------------------------
int main() {
    initChain();
    initTable();

    // Direct input elements
    int elements[] = {23, 43, 13, 27, 37, 33, 22, 72};
    int del_open[] = {43, 22};  // keys to delete from open hashing
    int del_closed[] = {13, 33}; // keys to delete from closed hashing
    int n = sizeof(elements) / sizeof(elements[0]);

    printf("Inserting elements into both hash tables...\n");
    for (int i = 0; i < n; i++) {
        insertChain(elements[i]);
        insertLinear(elements[i]);
    }

    printf("\nDeleting some elements...\n");
    for (int i = 0; i < 2; i++) {
        deleteChain(del_open[i]);
        deleteLinear(del_closed[i]);
    }

    // Display final hash tables
    displayChain();
    displayLinear();

    return 0;
}
