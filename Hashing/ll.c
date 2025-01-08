#include "ll.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

LL *list_create(void) {
    LL *l = (LL *) malloc(sizeof(LL));
    if (l == NULL) {
        return NULL;
    }
    l->head = NULL;
    return l;
}

// make it so that the function runs to the very end of the linked list and adds an item instead of making a while loop
bool list_add(LL *l, item *i) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n == NULL) {
        return false;
    }
    n->data = *i;
    n->next = NULL;
    if (l->head == NULL) {
        l->head = n;
        l->tail = n; // Both head and tail point to the new node
    } else {
        l->tail->next = n; // Link the new node at the end of the list
        l->tail = n; // Update the tail to point to the new node
    }
    return true;
}

item *list_find(LL *l, bool (*cmpfn)(item *, item *), item *i) {
    Node *n = l->head;
    while (n != NULL) {
        if (cmpfn(&n->data, i)) {
            return &n->data;
        }
        n = n->next;
    }
    return NULL;
}

void list_destroy(LL **ll) {
    if (ll == NULL || *ll == NULL) {
        return;
    }
    Node *n = ((*ll)->head);

    while (n != NULL) {
        Node *next = n;
        n = n->next;
        free(next);
    }
    free(*ll);
    *ll = NULL;
}
void list_remove(LL *ll, bool (*cmpfn)(item *, item *), item *iptr) {
    if (ll == NULL || ll->head == NULL) {
        return;
    }

    Node *n = ll->head;
    Node *prev = NULL;
    // Node *tail = NULL; // Pointer to track the tail node
    while (n != NULL) {
        if (cmpfn(&n->data, iptr)) {
            if (prev == NULL) {
                ll->head = n->next;
            } else {
                prev->next = n->next;
            }

            if (n == ll->tail) { // Check if the node to remove is the tail
                ll->tail = prev; // Update tail to point to the previous node
            }
            free(n);
            return;
        }
        prev = n;
        n = n->next;
    }
}
