#include "hash.h"

#include "item.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Creates a new hashtable
Hashtable *hash_create(void) {
    Hashtable *ht = (Hashtable *) malloc(sizeof(Hashtable));
    if (ht == NULL) {
        return NULL;
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = list_create(); // Create a new linked list for each index
        if (ht->table[i] == NULL) {
            for (int j = 0; j < i; j++) {
                list_destroy(&(ht->table[j]));
            }
            free(ht);
            return NULL;
        }
    }
    return ht;
}

// Simple hash function to hash keys to table indices
unsigned int hash_function(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash += *key++;
    }
    return hash % TABLE_SIZE;
}

// Inserts a key-value pair into the hashtable
bool hash_put(Hashtable *ht, char *key, int val) {
    if (key == NULL || ht == NULL) {
        return false;
    }
    unsigned int index = hash_function(key);

    // Create a new item
    item temp;
    strcpy(temp.key, key);
    temp.id = val;

    item *exists = list_find(ht->table[index], cmp, &temp);
    if (exists) {
        exists->id = val;
        return true;
    }
    // Add the new item to the linked list at the computed index
    list_add(ht->table[index], &temp);
    return true;
}

// Retrieves a value by key from the hashtable
int *hash_get(Hashtable *ht, char *key) {
    if (key == NULL || ht == NULL) {
        return NULL;
    }
    unsigned int index = hash_function(key);
    item temp;
    strncpy(temp.key, key, 254);
    temp.key[254] = '\0';

    // Find the item in the linked list at the computed index
    item *found_item = list_find(ht->table[index], cmp, &temp);
    if (found_item != NULL) {
        return &found_item->id;
    }
    return NULL;
}

// Destroys the hashtable and frees all associated memory
void hash_destroy(Hashtable **ht) {
    if (ht == NULL || *ht == NULL) {
        return;
    }
    // Free the memory for each linked list
    for (int i = 0; i < TABLE_SIZE; i++) {
        if ((*ht)->table[i] != NULL) {
            list_destroy(&((*ht)->table[i]));
        }
    }
    // Free the memory for the hash table itself
    free(*ht);
    *ht = NULL;
}
