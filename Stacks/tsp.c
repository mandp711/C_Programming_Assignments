#include "graph.h"
#include "path.h"
#include "stack.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_VERTEX 0

void dfs(Graph *graph, Path *recentPath, Path *bestPath, uint32_t currentVertex,
    uint32_t *shortestDistance) {

    // Mark the current vertex as visited
    graph_visit_vertex(graph, currentVertex);

    // Add the current vertex to the current path
    path_add(recentPath, currentVertex, graph);

    // Check if all vertices are visited
    if (path_vertices(recentPath) == graph_vertices(graph)) {
        uint32_t returnToStartWeight = graph_get_weight(graph, currentVertex, START_VERTEX);
        uint32_t currentTotalDistance = path_distance(recentPath) + returnToStartWeight;

        // If there's a path back to the start and the total distance is shorter, update the best path
        if (returnToStartWeight > 0 && currentTotalDistance < *shortestDistance) {
            path_copy(bestPath, recentPath);
            path_add(bestPath, START_VERTEX, graph);
            *shortestDistance = currentTotalDistance;
        }
    } else {
        // Recursively visit each unvisited adjacent vertex
        for (uint32_t nextVertex = 0; nextVertex < graph_vertices(graph); nextVertex++) {
            if (!graph_visited(graph, nextVertex)
                && graph_get_weight(graph, currentVertex, nextVertex) > 0) {
                dfs(graph, recentPath, bestPath, nextVertex, shortestDistance);
            }
        }
    }

    // Backtrack: remove the current vertex from the path and mark it as unvisited
    path_remove(recentPath, graph);
    graph_unvisit_vertex(graph, currentVertex);
}

void help_message(void) {
    printf("Usage: tsp [-i inputfile] [-o outputfile] [-d] [-h]\n");
    printf("Options:\n");
    printf("  -i inputfile   Specifies the input file containing the graph\n");
    printf("  -o outputfile  Specifies the output file for the results\n");
    printf("  -d             Specifies if the graph is directed\n");
    printf("  -h             Prints this help message\n");
}

int main(int argc, char **argv) {
    FILE *infile = stdin;
    FILE *outfile = stdout;
    bool directed = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            if (i + 1 < argc) {
                infile = fopen(argv[++i], "r");
                if (!infile) {
                    fprintf(stderr, "Error: Unable to open input file %s\n", argv[i]);
                    exit(EXIT_FAILURE);
                }
            } else {
                fprintf(stderr, "Error: -i option requires a filename argument\n");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                outfile = fopen(argv[++i], "w");
                if (!outfile) {
                    fprintf(stderr, "Error: Unable to open output file %s\n", argv[i]);
                    exit(EXIT_FAILURE);
                }
            } else {
                fprintf(stderr, "Error: -o option requires a filename argument\n");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[i], "-d") == 0) {
            directed = true;
        } else if (strcmp(argv[i], "-h") == 0) {
            help_message();
            exit(EXIT_SUCCESS);
        } else {
            fprintf(stderr, "Usage: tsp [-i inputfile] [-o outputfile] [-d] [-h]\n");
            exit(EXIT_FAILURE);
        }
    }

    // Read number of vertices
    uint32_t vertices;
    if (fscanf(infile, "%u\n", &vertices) != 1) {
        fprintf(stderr, "Error: Unable to read number of vertices\n");
        fclose(infile);
        fclose(outfile);
        exit(EXIT_FAILURE);
    }

    // Create graph
    Graph *g = graph_create(vertices, directed);
    if (!g) {
        fprintf(stderr, "Error: Unable to create graph\n");
        fclose(infile);
        fclose(outfile);
        exit(EXIT_FAILURE);
    }

    // Read vertex names
    char vertex_name[256];
    for (uint32_t i = 0; i < vertices; i++) {
        if (fgets(vertex_name, sizeof(vertex_name), infile) == NULL) {
            fprintf(stderr, "Error: Unable to read vertex name\n");
            graph_free(&g);
            fclose(infile);
            fclose(outfile);
            exit(EXIT_FAILURE);
        }
        vertex_name[strcspn(vertex_name, "\n")] = '\0'; // Remove newline character
        graph_add_vertex(g, vertex_name, i);
    }

    // Read number of edges
    uint32_t edges;
    if (fscanf(infile, "%u\n", &edges) != 1) {
        fprintf(stderr, "Error: Unable to read number of edges\n");
        graph_free(&g);
        fclose(infile);
        fclose(outfile);
        exit(EXIT_FAILURE);
    }

    // Read edges
    uint32_t start, end, weight;
    for (uint32_t i = 0; i < edges; i++) {
        if (fscanf(infile, "%u %u %u\n", &start, &end, &weight) != 3) {
            fprintf(stderr, "Error: Unable to read edge data\n");
            graph_free(&g);
            fclose(infile);
            fclose(outfile);
            exit(EXIT_FAILURE);
        }
        graph_add_edge(g, start, end, weight);
    }

    Path *current_path = path_create(vertices);
    Path *best_path = path_create(vertices);
    if (!current_path || !best_path) {
        fprintf(stderr, "Error: Unable to create paths\n");
        graph_free(&g);
        if (current_path)
            path_free(&current_path);
        if (best_path)
            path_free(&best_path);
        exit(EXIT_FAILURE);
    }

    uint32_t best_distance = UINT32_MAX;
    dfs(g, current_path, best_path, START_VERTEX, &best_distance);

    if (best_distance == UINT32_MAX) {
        fprintf(outfile, "No path found! Alissa is lost!\n");
    } else {
        fprintf(outfile, "Alissa starts at:\n");
        path_print(best_path, outfile, g);
        fprintf(outfile, "%s\n", graph_get_vertex_name(g, START_VERTEX));
        fprintf(outfile, "Total Distance: %u\n", best_distance);
    }

    graph_free(&g);
    path_free(&current_path);
    path_free(&best_path);

    if (infile != stdin)
        fclose(infile);
    if (outfile != stdout)
        fclose(outfile);

    return 0;
}
