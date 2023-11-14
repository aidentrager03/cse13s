#include "graph.h"
#include "path.h"
#include "stack.h"
#include <stdbool.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Path *solve_tsp(const Graph *graph);

int next_permutation(uint32_t *array, uint32_t length);

int main(int argc, char *argv[]) {
    int directed = 0;
    char *input_file = NULL;
    char *output_file = NULL;

    int opt;
    while ((opt = getopt(argc, argv, "dhi:o:")) != -1) {
        switch (opt) {
        case 'd': directed = 1; break;
        case 'i': input_file = optarg; break;
        case 'o': output_file = optarg; break;
        case 'h':
            printf("Usage: %s [options]\n", argv[0]);
            printf("Options:\n");
            printf("  -d                Specify the graph to be directed.\n");
            printf("  -i input_file     Specify the input file path containing the cities and "
                   "edges of a graph.\n");
            printf("  -o output_file    Specify the output file path to print to.\n");
            printf("  -h                Print out a help message describing the purpose of the "
                   "program and the command-line options it accepts, exiting the program "
                   "afterwards.\n");
            return 0;
        default:
            // read from stdin as a default
            fprintf(stderr, "Invalid option\n");
            return 1;
        }
    }
    FILE *input;
    if (input_file == NULL) {
        input = stdin;
    } else {
        input = fopen(input_file, "r");
    }
    if (input == NULL) {
        fprintf(stderr, "Failed to open the input file.\n");
        return 1;
    }

    uint32_t num_vertices;
    fscanf(input, "%" SCNu32 "\n", &num_vertices);
    Graph *graph = graph_create(num_vertices, directed);

    char vertex_name[100];
    for (uint32_t i = 0; i < num_vertices; i++) {
        // Use %[^\n] to read the entire line, including spaces.
        fscanf(input, " %[^\n]\n", vertex_name);
        graph_add_vertex(graph, vertex_name, i);
    }

    uint32_t num_edges;
    fscanf(input, "%" SCNu32, &num_edges);
    for (uint32_t i = 0; i < num_edges; i++) {
        uint32_t start, end, weight;
        fscanf(input, "%" SCNu32 " %" SCNu32 " %" SCNu32, &start, &end, &weight);
        graph_add_edge(graph, start, end, weight);
    }

    //made it here
    graph_print(graph);

    printf("here2\n\n\n\n\n\n");
    // Close the input file.
    fclose(input);

    // Solve the TSP problem using brute force.
    Path *tsp_path = solve_tsp(graph);

    // Print the TSP solution.
    if (output_file != NULL) {
        FILE *output = fopen(output_file, "w");
        if (output != NULL) {
            fprintf(output, "Alissa starts at:\n");
            path_print(tsp_path, output, graph);
            fprintf(output, "Total Distance: %u\n", path_distance(tsp_path));
            fclose(output);
        }
    } else {
        printf("Alissa starts at:\n");
        path_print(tsp_path, stdout, graph);
        printf("Total Distance: %u\n", path_distance(tsp_path));
    }

    // Free memory.
    path_free(&tsp_path);
    graph_free(&graph);

    return 0;
}




void dfs_tsp(const Graph *graph, Path *current_path, Path *best_path, uint32_t *visited) {
    uint32_t current_vertex = 0;

    // Find the first unvisited vertex
    while (current_vertex < graph_vertices(graph) && graph_visited(graph, current_vertex)) {
        current_vertex++;
        printf("hererer1\n");

    }

    graph_visit_vertex((Graph*)graph, current_vertex);

    bool all_visited = true;
    for (uint32_t i = 0; i < graph_vertices(graph); i++) {
        if (!graph_visited(graph, i)) {
            all_visited = false;
            break;
        }
    }

    if (all_visited) {
        if (path_distance(current_path) < path_distance(best_path)) {
            printf("hererer\n");
            path_print(current_path,stdout, graph);
            path_copy(best_path, current_path);
        }
        return;
    } else {
        for (uint32_t i = 0; i < graph_vertices(graph); i++) {
            if (!graph_visited(graph, i) && graph_get_weight(graph, current_vertex, i) > 0) {
                path_add(current_path, i, graph);
                dfs_tsp(graph, current_path, best_path, visited);
                path_remove(current_path, graph);
            }
        }
    }

    graph_unvisit_vertex((Graph*)graph, current_vertex);
}


Path *solve_tsp(const Graph *graph) {
    uint32_t num_vertices = graph_vertices(graph);

    uint32_t *visited = (uint32_t *)calloc(num_vertices, sizeof(uint32_t));
    Path *current_path = path_create(num_vertices);
    Path *best_path = path_create(num_vertices);

    // Start DFS from vertex 0
    path_add(current_path, 0, graph);
    dfs_tsp(graph, current_path, best_path, visited);

    // Free memory
    free(visited);
    path_free(&current_path);

    return best_path;
}


