/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
FindComponent.c
Main program that determines and prints the strongest components of G to 
the output file in topologically sorted order
*/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char *argv[]) {
    // Check for correct number of command line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Open input and output files
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    
    if (in == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        return EXIT_FAILURE;
    }
    if (out == NULL) {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        return EXIT_FAILURE;
    }

    int n;
    fscanf(in, "%d", &n);
    Graph G = newGraph(n); 

    int u, v; 
    while (fscanf(in, "%d %d", &u, &v) == 2 && (u != 0 && v != 0)) {
        addArc(G, u, v); 
    }

    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);

    // Perform DFS on G to compute finishing times
    List L = newList();
    for (int i = 1; i <= n; i++) {
        append(L, i);
    }
    DFS(G, L);

    // Transpose the graph
    Graph T = transpose(G);

    // Perform DFS on the transpose graph in the order of decreasing finish times
    DFS(T, L);

    // Count the number of strongly connected components
    int sccCount = 0;
    List *elements = calloc(n, sizeof(List)); 
    
    moveFront(L);
    while (index(L) >= 0) {
        int vertex = get(L);
        if (getParent(T, vertex) == NIL) {
            List element = newList(); 
            elements[sccCount] = element; 
            sccCount++;
        }
        append(elements[sccCount - 1], vertex); 
        moveNext(L);
    }
    
    // Print the strongly connected components
    fprintf(out, "G contains %d strongly connected components:\n", sccCount);
    for (int i = sccCount - 1; i >= 0; i--) {
        fprintf(out, "Component %d: ", sccCount - i);
        printList(out, elements[i]); 
        fprintf(out, "\n"); 
    }

    // Free all allocated memory
    
    
    freeList(&L);
    for (int i = 0; i < sccCount; i++) {
        freeList(&elements[i]);
    }
    free(elements);
    freeGraph(&G);
    freeGraph(&T);
    
    // Close files
    fclose(in);
    fclose(out);

    return 0;
}