#include "hash.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 100

int main() {
    Hashtable *word_count = hash_create();
    if (word_count == NULL) {
        fprintf(stderr, "Failed to create hash table\n");
        return 1;
    }

    // Read input text and count total words
    char word[MAX_WORD_LEN];
    unsigned long num_words = 0;
    while (scanf("%99s", word) == 1) {
        num_words++; // Increment total words count

        // Increment count for this word
        int *count_ptr = hash_get(word_count, word);
        if (count_ptr != NULL) {
            (*count_ptr)++;
        } else {
            hash_put(word_count, word, 1);
        }
    }

    // Find number of repeated words
    unsigned long repeated_words = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *node = word_count->table[i]->head;
        while (node != NULL) {
            if (node->data.id > 1) {
                repeated_words++;
            }
            node = node->next;
        }
    }

    printf("%lu\n", num_words - repeated_words);

    // Cleanup
    hash_destroy(&word_count);
    return 0;
}
