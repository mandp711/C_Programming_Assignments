/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
Graph.c 
Implementation file for Graph ADT with operations to alter the graph
*/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

typedef struct GraphObj {
    List *adj;  // adjacency list array 
    int *color; // represents the color 
    int *parent;   // parent array
    int *dist; // distance array
    int order; 
    int size; 
    int source; 
} GraphObj; 

Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj)); 
    G->adj = calloc(n+1, sizeof(List)); 
    G->color = calloc(n+1, sizeof(int)); 
    G->parent = calloc(n+1, sizeof(int)); 
    G->dist = calloc(n+1, sizeof(int)); 
    G->order = n;
    G->size = 0; 
    G->source = NIL; 

    for (int i = 1; i <= n; i++) {
        G->adj[i] = newList(); 
        G->color[i] = 0; // white
        G->parent[i] = NIL; 
        G->dist[i] = INF; 
    }
    return G; 
}

void freeGraph(Graph* pG) {
   if (pG != NULL && *pG != NULL) {
        for (int i = 1; i <= (*pG)->order; i++) {
            freeList(&((*pG)->adj[i])); 
        }
    }
    free((*pG)->adj);
    free((*pG)->color); 
    free((*pG)->parent); 
    free((*pG)->dist); 
    free(*pG); 
    *pG = NULL; 
}

int getOrder(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "List Error: calling getOrder() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return G->order; 
}

int getSize(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "List Error: calling getSize() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return G->size; 
}

int getSource(Graph G) { 
    if (G == NULL) {
        fprintf(stderr, "List Error: calling getSource() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return G->source; 
}

int getParent(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "List Error: calling getParent() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > G->order) {
        fprintf(stderr, "Graph Error: getParent() called with invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u]; 
}

int getDist(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "List Error: calling getDist() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > G->order) {
        fprintf(stderr, "Graph Error: getDist() called with invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->dist[u]; 
}

void getPath(List L, Graph G, int u) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling getPath() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (G == NULL) {
        fprintf(stderr, "List Error: calling getPath() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) == NIL) {
        fprintf(stderr, "Graph Error: calling getPath() before BFS()\n");
        exit(EXIT_FAILURE); 
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: getDist() called with invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    if (u == G->source) {
        append(L, G->source);
    }
    else if (G->parent[u] == NIL) {
        append(L, NIL); 
    }
    else {
        getPath(L, G, G->parent[u]);
        append(L, u); 
    }
}

int getColor(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "List Error: calling getColor() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > G->order) {
        fprintf(stderr, "Graph Error: calling getColor() with invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->color[u];
}

void makeNull(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "List Error: calling makeNull() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= G->order; i++) {
        clear(G->adj[i]); 
    }
    G->size = 0; 
}

void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "List Error: calling addEdge() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: addEdge() called with invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    if (v < 1 || v > getOrder(G)) {
        fprintf(stderr, "Graph Error: addEdge() called with invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    // insert v into adjacent list u
    List adjU = G->adj[u];  // vertex u has a List adjU that stores all neighboring vertices
    moveFront(adjU);        // move to the front of the list
    while ((index(adjU) != -1) && get(adjU) < v) {  // check to make sure cursor is valid and 
                                            // that element of adjU is less than v
        moveNext(adjU);
    }
    if (index(adjU) == -1) {
        append(adjU, v); 
    }
    else {
        insertBefore(adjU, v); 
    }
    // insert u into adjacency list v
    List adjV = G->adj[v];  // vertex u has a List A that stores all neighboring vertices
    moveFront(adjV);        // move to the front of the list
    while ((index(adjV) != -1) && get(adjV) < u) {  // check to make sure cursor is valid and 
                                            // that element of A is less than v
        moveNext(adjV);
    }
    if (index(adjV) == -1) {
        append(adjV, u); 
    }
    else {
        insertBefore(adjV, u); 
    }
    G->size++; 
} 

void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "List Error: calling addArc() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: addArc() called with invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    if (v < 1 || v > getOrder(G)) {
        fprintf(stderr, "Graph Error: addArc() called with invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    append(G->adj[u], v); // Add vertex v to the adjacency list of u
    G->size++; 
}

void BFS(Graph G, int s) {
    if (G == NULL) {
        fprintf(stderr, "List Error: calling BFS() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (s < 1 || s > getOrder(G)) {
        fprintf(stderr, "Graph Error: BFS() called with invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= G->order; i++) {
        G->color[i] = WHITE;  // mark vertices as unvisited 
        G->dist[i] = INF;      // mark all distances as infinity
        G->parent[i] = NIL;   // mark all parent vertices as 0 
    }
    G->color[s] = GRAY; 
    G->dist[s] = 0; 
    G->parent[s] = NIL; 
    G->source = s; 
    
    List q = newList(); 
    append(q, s); 
    while (length(q) > 0) {
        int node = front(q);   // Get the front element from the queue
        deleteFront(q);        // Dequeue the front element
        // printf("Processing node %d\n", node); // Debugging print

        // Process each neighbor of 'node'
        List neighbors = G->adj[node];  // Get adjacency list of current node
        moveFront(neighbors);           // Move to the first neighbor
        while (index(neighbors) != -1) { // Iterate through the neighbors
            int neighbor = get(neighbors);  // Get the current neighbor
            if (G->color[neighbor] == WHITE) {  // If neighbor is unvisited
                G->color[neighbor] = GRAY;  // Mark neighbor as discovered (GRAY)
                G->dist[neighbor] = G->dist[node] + 1;  // Update distance
                G->parent[neighbor] = node;  // Set parent of neighbor
                // printf("Setting parent of %d to %d\n", neighbor, node); // Debugging print
                append(q, neighbor);          // Enqueue the neighbor
            }
            moveNext(neighbors);  // Move to the next neighbor
        }
        G->color[node] = BLACK;   // Mark the node as fully processed (BLACK)
    }

    freeList(&q);  // Clean up the queue after BFS completes
}

void printGraph(FILE* out, Graph G) {
    if (G == NULL) {
        fprintf(stderr, "List Error: calling printGraph() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }
}