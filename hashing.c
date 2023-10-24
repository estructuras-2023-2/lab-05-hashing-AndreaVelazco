#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 10

typedef struct HashTable {
    int size;
    int* table;
    int (*hash_function)(int);
} HashTable;

int mi_Mod(int x, int n) {
    return x % n;
}

int randomFn(int x, int n) {
    return rand() % n;
}

void initHashTable(HashTable* ht, int (*hash_function)(int)) {
    ht->size = TABLE_SIZE;
    ht->table = (int*)malloc(TABLE_SIZE * sizeof(int));
    ht->hash_function = hash_function;

    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = -1;  
    }
}

void insert(HashTable* ht, int x) {
    int index = ht->hash_function(x) % ht->size;

    while (ht->table[index] != -1) {
        index = (index + 1) % ht->size; 
    }

    ht->table[index] = x;
}

bool find(HashTable* ht, int x) {
    int index = ht->hash_function(x) % ht->size;

    while (ht->table[index] != -1) {
        if (ht->table[index] == x) {
            return true;
        }

        index = (index + 1) % ht->size; 
    }

    return false;
}

int main() {
    srand(time(NULL));  
    HashTable ht;
    initHashTable(&ht, mi_Mod);

    int x = 1234567;
    int y = 76554334234;

    insert(&ht, x);

    printf("Find x: %d\n", find(&ht, x));  
    printf("Find y: %d\n", find(&ht, y)); 

    delete(&ht, x);

    printf("Find x after delete: %d\n", find(&ht, x));  
    return 0;
}

