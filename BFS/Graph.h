/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
Graph.h 
Header file for Graph ADT that contains all functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

#define INF -1 
#define NIL 0 
#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct GraphObj* Graph;

/* Constructors - Destructors */
Graph newGraph(int n); 
void freeGraph(Graph* pG); 

/* Access functions */
int getOrder(Graph G);
int getSize(Graph G); 
int getSource(Graph G); 
int getParent(Graph G, int u); 
int getColor(Graph G, int u);
int getDist(Graph G, int u); 
void getPath(List L, Graph G, int u); 

/* Manipulation procedures */
void makeNull(Graph G); 
void addEdge(Graph G, int u, int v); 
void addArc(Graph G, int u, int v); 
void BFS(Graph G, int s); 

/* Other operations */
void printGraph(FILE* out, Graph G); 