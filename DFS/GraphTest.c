/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
GraphTest.c
Test file for testing function of Graph.c 
*/
#include <stdio.h>
#include "Graph.h"
#include "List.h"

int main() {
    printf("Testing newGraph(): \n"); 

    Graph G = newGraph(5); 
    printf("Expected order: 5, Actual order: %d\n", getOrder(G));
    /* for (int i = 1; i <= 5; i++) {
        printf("Parent of %d: %d (Expected: NIL)\n", i, getParent(G, i));
        printf("Discover time of %d: %d (Expected: UNDEF)\n", i, getDiscover(G, i));
        printf("Finish time of %d: %d (Expected: UNDEF)\n", i, getFinish(G, i));
    }
    */ 

    printf("Testing addEdge() and addArc: \n");
    addEdge(G, 1, 2);
    addArc(G, 3, 4);

    printGraph(stdout, G); 
    
    printf("Testing DFS()...\n");
    addArc(G, 2, 3);
    addArc(G, 3, 4);
    addArc(G, 4, 5);

    List L = newList();
    for (int i = 1; i <= getOrder(G); i++) {
        append(L, i); 
    }

    DFS(G, L);

    for (int i = 1; i <= getOrder(G); i++) {
        printf("Vertex %d: discover time = %d, finish time = %d, parent = %d\n",
               i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
    }

    printf("\nTesting transpose(): \n");
    Graph GT = transpose(G);

    printf("Original Graph:\n");
    printGraph(stdout, G);

    printf("Transposed Graph: \n"); 
    printGraph(stdout, GT); 
    

}