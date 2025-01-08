/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
FindPath.c
Main program that reads in a graph and a list of a pair of vertices 
that finds the shortest path 
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

    // Read the number of vertices in the graph
    int numVertices;
    fscanf(in, "%d", &numVertices);

    // Create a new graph with the given number of vertices
    Graph G = newGraph(numVertices);

    // Read the edges and add them to the graph
    int u, v;
    while (fscanf(in, "%d %d", &u, &v) == 2) {
        if (u == 0 && v == 0) {
            break; 
        }
        addEdge(G, u, v);
    } 

    // Print the adjacency list representation of the graph to the output file
    printGraph(out, G);

    // Read the source-destination pairs and compute shortest paths
    while (fscanf(in, "%d %d", &u, &v) == 2) {
        if (u == 0 && v == 0) {
            break; 
        }
        BFS(G, u); // Perform BFS from source vertex u
        List L = newList();
        getPath(L, G, v);
        
        // Print the distance from u to v
        if (getDist(G, v) != INF) {
            // Find and print the shortest path  
            fprintf(out, "The distance from %d to %d is %d\n", u, v, getDist(G, v));
            fprintf(out, "A shortest %d-%d path is: ", u, v);
            printList(out, L);
            fprintf(out, "\n");
            
        } else {
            fprintf(out, "The distance from %d to %d is infinity\n", u, v);
            fprintf(out, "No %d-%d path exists\n", u, v);
        }
        freeList(&L);
    }

    // Free the graph and close the files
    freeGraph(&G);
    fclose(in);
    fclose(out);

    return 0;
}
