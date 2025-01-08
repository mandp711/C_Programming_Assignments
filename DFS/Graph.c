/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
Graph.c 
Implementation file for Graph ADT with operations to alter the graph
*/
#include "Graph.h"
#include "List.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct GraphObj {
    List *adj;        // Array of adjacency lists
    int *color;       // Array for vertex colors
    int *parent;      // Array for parent vertices
    int *discover;    // Array for discover times
    int *dist;
    int *finish;      // Array for finish times
    int order;        // Number of vertices
    int size;         // Number of edges
    int source;       // Most recent source vertex used in BFS or DFS
} GraphObj;

Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj)); 
    G->adj = calloc(n+1, sizeof(List)); 
    G->color = calloc(n+1, sizeof(int)); 
    G->parent = calloc(n+1, sizeof(int)); 
    G->dist = calloc(n+1, sizeof(int)); 
    G->discover = calloc(n+1, sizeof(int));
    G->finish = calloc(n+1, sizeof(int)); 
    G->order = n;
    G->size = 0; 
    G->source = NIL; 

    for (int i = 1; i <= n; i++) {
        G->adj[i] = newList(); 
        G->color[i] = UNDEF;
        G->parent[i] = NIL;  
        G->discover[i] = UNDEF; 
        G->finish[i] = UNDEF; 
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
    free((*pG)->discover); 
    free((*pG)->finish); 
    free(*pG); 
    *pG = NULL; 
}

/* Access functions */
int getOrder(Graph G) {
    return G->order; 
}
int getSize(Graph G) {
    return G->size; 
}

int getSource(Graph G) {
    return G->source; 
}

int getParent(Graph G, int u) {
    return G->parent[u]; 
}

int getDiscover(Graph G, int u) {
    return G->discover[u]; 
}

int getFinish(Graph G, int u) {
    return G->finish[u]; 
}  
 /* Pre: 1<=u<=n=getOrder(G) */ // Manipulation procedures 
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
    List adjU = G->adj[u];
    moveFront(adjU);
    while (index(adjU) != -1) {
        if (get(adjU) == v) {
            return;  // Arc already exists, so don’t add it again
        }
        if (get(adjU) > v) {
            break;  // Stop if we’ve passed the insertion point
        }
        moveNext(adjU);
    }

    // Insert in sorted order to keep adjacency lists sorted
    if (index(adjU) == -1) {
        append(adjU, v);
    } else {
        insertBefore(adjU, v);
    }

    G->size++;  // Increment the size only for unique edges
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

void Visit(Graph G, int u, int *time, List S); 

void DFS(Graph G, List S) {
    for (int i = 1; i <= getOrder(G); i++) {
        G->parent[i] = NIL; 
        G->color[i] = WHITE; 
        G->discover[i] = UNDEF; // Reset discover times
        G->finish[i] = UNDEF;   // Reset finish times
    }
    int time = 0; 
    List copy = copyList(S); 
    clear(S); 
    moveFront(copy); 
    while (index(copy) >= 0) {
        int u = get(copy); 
        if (G->color[u] == WHITE) {
            Visit(G, u, &time, S); 
        }
        moveNext(copy); 
    }
    freeList(&copy); 
}


void Visit(Graph G, int u, int *time, List S) {
    G->color[u] = GRAY;
    G->discover[u] = ++(*time); 
    List ADJ = G->adj[u]; 
    moveFront(ADJ); 
    while(index(ADJ) != -1) {
        int v = get(ADJ); 
        if (G->color[v] == WHITE) {
            G->parent[v] = u; 
            Visit(G, v, time, S); 
        }
        moveNext(ADJ); 
    }
    G->color[u] = BLACK; 
    (*time)++; 
    G->finish[u] = *time; 
    prepend(S, u); 
}
 
 // Other Functions 
Graph transpose(Graph G) {
    Graph GT = newGraph(getOrder(G));
    for (int u = 1; u <= getOrder(G); u++) {
        List ADJ = G->adj[u]; 
        moveFront(ADJ); 
        while (index(ADJ) >= 0) {
            int v = get(ADJ); 
            addArc(GT, v, u); 
            moveNext(ADJ); 
        }
    }
    return GT; 
}
Graph copyGraph(Graph G) {
    Graph GC = newGraph(getOrder(G)); 
    for (int u = 1; u <= getOrder(G); u++) {
        List ADJ = G->adj[u]; 
        moveFront(ADJ); 
        while (index(ADJ) >= 0) {
            int v = get(ADJ); 
            addArc(GC, u, v); 
            moveNext(ADJ); 
        }
    }
    return GC; 
}

void printGraph(FILE* out , Graph G) {
    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }
}