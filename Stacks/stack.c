#include "stack.h"

#include <assert.h>
#include <stdlib.h>

Stack *stack_create(uint32_t capacity) {
    // Attempt to allocate memory for a stack
    // Cast it to a stack pointer too!
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->capacity = capacity;
    s->top = 0;
    // We need enough memory for <capacity> numbers
    s->items = calloc(s->capacity, sizeof(uint32_t));
    // We created our stack, return it!
    return s;
}

void stack_free(Stack **sp) {
    if (sp != NULL && *sp != NULL) {
        if ((*sp)->items) {
            free((*sp)->items);
            (*sp)->items = NULL;
        }
        // Free memory allocated for the stack
        free(*sp);
    }
    if (sp != NULL) {
        *sp = NULL;
    }
}

bool stack_push(Stack *s, uint32_t val) {
    if (stack_full(s)) {
        return false;
    }
    // Set val
    s->items[s->top] = val;
    // Move the top of the stack
    s->top++;
    return true;
}

bool stack_pop(Stack *s, uint32_t *val) {
    if (stack_empty(s)) {
        return false;
    }
    *val = s->items[s->top - 1];
    s->top--;
    return true;
}

bool stack_peek(const Stack *s, uint32_t *val) {

    if (stack_empty(s)) {
        return false;
    }
    *val = s->items[s->top - 1];
    return true;
}

bool stack_empty(const Stack *s) {
    return s->top == 0;
}

bool stack_full(const Stack *s) {
    return s->top == s->capacity;
}

uint32_t stack_size(const Stack *s) {
    return s->top;
}

void stack_copy(Stack *dst, const Stack *src) {
    assert(dst->capacity >= src->capacity);
    dst->top = src->top; // Copy the top index
    for (uint32_t i = 0; i < src->top; ++i) {
        dst->items[i]
            = src->items[i]; // Copy each item from the source stack to the destination stack
    }
}

void stack_print(const Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s\n", cities[s->items[i]]);
    }
}
