#ifndef _HASH

#define _HASH

#include "badhash.h"
#include "ll.h"

#define TABLE_SIZE 1000

typedef struct Hashtable Hashtable;

struct Hashtable {
    // your datastructure here; this is just a placeholder
    LL *table[TABLE_SIZE];
    Node *head;
};

Hashtable *hash_create(void);

bool hash_put(Hashtable *, char *key, int val);

int *hash_get(Hashtable *, char *key);

void hash_destroy(Hashtable **);

#endif
