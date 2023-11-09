#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct graph {
    uint32_t vertices;
    bool directed;
    bool *visited;
    char **names;
    uint32_t **weights;
};

Graph *graph_create(uint32_t vertices, bool directed) {
    Graph *g = (Graph *) calloc(1, sizeof(Graph));
    g->vertices = vertices;
    g->directed = directed;
    g->visited = (bool *) calloc(vertices, sizeof(bool));
    g->names = (char **) calloc(vertices, sizeof(char *));
    g->weights = (uint32_t **) calloc(vertices, sizeof(uint32_t *));

    for (uint32_t i = 0; i < vertices; ++i) {
        g->weights[i] = (uint32_t *) calloc(vertices, sizeof(uint32_t));
    }

    return g;
}

void graph_free(Graph **gp) {
    if (gp != NULL && *gp != NULL) {
        for (uint32_t i = 0; i < (*gp)->vertices; ++i) {
            free((*gp)->names[i]);
            free((*gp)->weights[i]);
        }
        free((*gp)->names);
        free((*gp)->weights);
        free((*gp)->visited);
        free(*gp);
    }
    if (gp != NULL) {
        *gp = NULL;
    }
}

uint32_t graph_vertices(const Graph *g) {
    return g->vertices;
}

void graph_add_vertex(Graph *g, const char *name, uint32_t v) {
    if (g->names[v]) {
        free(g->names[v]);
    }
    g->names[v] = strdup(name);
}

const char *graph_get_vertex_name(const Graph *g, uint32_t v) {
    return g->names[v];
}

char **graph_get_names(const Graph *g) {
    return g->names;
}

void graph_add_edge(Graph *g, uint32_t start, uint32_t end, uint32_t weight) {
    g->weights[start][end] = weight;
    if (!g->directed) {
        g->weights[end][start] = weight;
    }
}

uint32_t graph_get_weight(const Graph *g, uint32_t start, uint32_t end) {
    return g->weights[start][end];
}

void graph_visit_vertex(Graph *g, uint32_t v) {
    g->visited[v] = true;
}

void graph_unvisit_vertex(Graph *g, uint32_t v) {
    g->visited[v] = false;
}

bool graph_visited(const Graph *g, uint32_t v) {
    return g->visited[v];
}

void graph_print(const Graph *g) {
    printf("Number of Vertices: %u\n", g->vertices);

    printf("Names of Vertices:\n");
    for (uint32_t i = 0; i < g->vertices; i++) {
        printf("%s\n", g->names[i]);
    }

    uint32_t num_edges = 0;

    printf("Edges:\n");
    for (uint32_t i = 0; i < g->vertices; i++) {
        for (uint32_t j = 0; j < g->vertices; j++) {
            uint32_t weight = g->weights[i][j];
            if (weight > 0) {
                printf("%u %u %u\n", i, j, weight);
                num_edges++;
            }
        }
    }
    printf("Number of Edges: %u\n", num_edges);
}
