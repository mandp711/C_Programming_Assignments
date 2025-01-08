README.md
    This file provides an overview of the project, including its purpose, setup instructions, and usage examples. It may also contain information about the structure of the codebase and how to run tests.

Makefile
    The Makefile contains rules and commands for compiling the project. It automates the build process for all the necessary source files and ensures that dependencies are managed correctly. Targets typically include building the executable, running tests, and cleaning up build artifacts.

List.h
    This header file defines the interface for the List Abstract Data Type (ADT). It declares the functions and data structures used to create and manipulate linked lists, including operations like creating a new list, inserting and deleting elements, and iterating through the list.

List.c
    This source file implements the functions declared in List.h. It contains the definitions for the operations of the List ADT, providing the functionality to manage linked lists in the project.

Graph.h
    This header file defines the interface for the Graph ADT. It declares the functions and data structures used to represent and manipulate directed graphs, including operations like adding vertices and edges, performing depth-first search, and transposing the graph.

Graph.c
    This source file implements the functions declared in Graph.h. It provides the functionality to create and manipulate graphs, including adding arcs, performing depth-first search, and other graph-related operations.

GraphTest.c
    This file contains test cases for the Graph ADT. It includes various tests to validate the functionality of the graph implementation, ensuring that the operations behave as expected and that the graph structure is correctly maintained.

FindComponents.c
    This source file implements the main program that reads a graph from an input file, computes its strongly connected components using depth-first search, and outputs the components to an output file. It uses the Graph and List ADTs to perform these tasks.