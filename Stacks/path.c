#include "path.h"

#include <stdlib.h>

Path *path_create(uint32_t capacity) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->total_weight = 0; // Initialize total weight to 0
    p->vertices = stack_create(capacity); // Create a stack with the given capacity for the vertices
    return p; // Return the created path
}

void path_free(Path **pp) {
    if ((pp != NULL) && (*pp != NULL)) {
        stack_free(&((*pp)->vertices));
        free(*pp);
        *pp = NULL;
    }
}

uint32_t path_vertices(const Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_distance(const Path *p) {
    return p->total_weight;
}

void path_add(Path *p, uint32_t val, const Graph *g) {
    if (stack_empty(p->vertices)) {
        stack_push(p->vertices, val);
    } else {
        uint32_t top_vertex;
        stack_peek(p->vertices, &top_vertex);
        p->total_weight += graph_get_weight(
            g, top_vertex, val); // Add the distance from the most recent vertex to the new one
        stack_push(p->vertices, val);
    }
}

uint32_t path_remove(Path *p, const Graph *g) {
    if (!stack_empty(p->vertices)) { // If the stack is not empty
        uint32_t removed_vertex, top_vertex;
        stack_pop(p->vertices, &removed_vertex); // Pop the most recent vertex
        if (!stack_empty(p->vertices)) { // If the stack is still not empty after popping
            stack_peek(p->vertices, &top_vertex); // Get the new top vertex
            p->total_weight -= graph_get_weight(
                g, top_vertex, removed_vertex); // Subtract the distance to the removed vertex
        } else {
            p->total_weight = 0; // If the stack is empty, set the total weight to 0
        }
        return removed_vertex; // Return the index of the removed vertex
    }
    return UINT32_MAX; // Return a maximum value if no vertex was removed (indicates an error)
}

void path_copy(Path *dst, const Path *src) {
    dst->total_weight = src->total_weight; // Copy the total weight
    stack_copy(dst->vertices, src->vertices);
}

void path_print(const Path *p, FILE *outfile, const Graph *g) {
    for (uint32_t i = 0; i < p->vertices->top; ++i) {
        fprintf(outfile, "%s\n", g->names[p->vertices->items[i]]);
    }
}
