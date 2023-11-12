#include "graph.h"
#include "path.h"
#include "stack.h"

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

Path *solve_tsp(const Graph *graph) {
    uint32_t num_vertices = graph_vertices(graph);

    uint32_t *vertices = (uint32_t *) malloc(num_vertices * sizeof(uint32_t));
    for (uint32_t i = 0; i < num_vertices; i++) {
        vertices[i] = i;
    }

    uint32_t best_weight = UINT32_MAX;
    Path *best_path = path_create(num_vertices);

    for (uint32_t i = 0; i < num_vertices; i++) {
        path_add(best_path, vertices[i], graph);
    }

    do {
        uint32_t current_weight = 0;

        for (uint32_t i = 0; i < num_vertices; i++) {
            current_weight
                += graph_get_weight(graph, vertices[i], vertices[(i + 1) % num_vertices]);
        }

        // Add the weight of the last edge.
        // current_weight += graph_get_weight(graph, vertices[num_vertices - 1], vertices[0]);

        // Debug print statements
        printf("Permutation: ");
        for (uint32_t i = 0; i < num_vertices; i++) {
            printf("%u ", vertices[i]);
        }
        printf("Weight: %u\n", current_weight);

        if (current_weight < best_weight) {
            best_weight = current_weight;

            while (path_vertices(best_path) > 0) {
                path_remove(best_path, graph);
            }

            for (uint32_t i = 0; i < num_vertices; i++) {
                path_add(best_path, vertices[i], graph);
            }
        }
    } while (next_permutation(vertices, num_vertices));

    free(vertices);

    return best_path;
}

int next_permutation(uint32_t *array, uint32_t length) {
    // Find the largest index k such that a[k] < a[k+1].
    int k = (int) (length - 2); // Cast to int to address signedness issue.
    while (k >= 0 && array[k] >= array[k + 1]) {
        k--;
    }

    if (k < 0) {
        return 0;
    }

    int l = (int) (length - 1);
    while (array[l] <= array[k]) {
        l--;
    }

    uint32_t temp = array[k];
    array[k] = array[l];
    array[l] = temp;

    int i = (int) (k + 1);
    int j = (int) (length - 1);
    while (i < j) {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        i++;
        j--;
    }

    return 1;
}
