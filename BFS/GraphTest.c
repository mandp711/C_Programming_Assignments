/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
GraphTest.c
Test file for testing function of Graph.c 
*/
#include <stdio.h>
#include "Graph.h"

void printPath(List path) {
    if (path == NULL || length(path) == 0) {
        printf("No path found\n");
        return;
    }
    moveFront(path);
    while (index(path) >= 0) {
        printf("%d ", get(path));
        moveNext(path);
    }
    printf("\n");
}

int main() {
    Graph G = newGraph(5);

    printf("Initial Order (Expected 5): %d\n", getOrder(G)); 
    printf("Initial size (expected 0): %d\n", getSize(G));
    printf("Initial source (expected NIL): %d\n", getSource(G)); 

    
    addEdge(G, 1, 2);  // Add edge between vertex 1 and 2
    addEdge(G, 1, 3);  // Add edge between vertex 1 and 3
    addArc(G, 1, 2); 
    addEdge(G, 2, 4);  // Add edge between vertex 2 and 4
    addEdge(G, 3, 5);  // Add edge between vertex 3 and 5

    // Test after adding edges
    printf("Graph size after adding edges (expected 4): %d\n", getSize(G));
    printGraph(stdout, G); 

    BFS(G, 1); // start BFS from vertex 1
    printf("Testing BFS on graph\n"); 
    
    printf("Source after BFS from vertex 1 (expected 1): %d\n", getSource(G));

    for (int i = 1; i <= 5; i++) {
            printf("Vertex %d: distance = %d, parent = %d, color = %d\n", i, getDist(G, i), getParent(G, i), getColor(G, i));
    }

    printf("\nTesting getPath from source (1) to each vertex:\n");
    for (int i = 1; i <= 5; i++) {
        printf("Path from 1 to %d: ", i);
        List path = newList(); 
        getPath(path, G, i);  // Get the path from vertex 1 to vertex i
        printPath(path);            // Print the path
        freeList(&path);            // Free the path list
    }
    

    makeNull(G); 
    printf("Empty Graph\n"); 
    printGraph(stdout, G); 

    freeGraph(&G); 
    return 0; 

}