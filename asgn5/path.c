#include "path.h"

#include "graph.h"
#include "stack.h"

#include <stdlib.h>

typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

Path *path_create(uint32_t capacity) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->total_weight = 0;
    p->vertices = stack_create(capacity);
    return p;
}

void path_free(Path **pp) {
    if (pp != NULL && *pp != NULL) {
        stack_free(&((*pp)->vertices));
        free(*pp);
        *pp = NULL;
    }
}

uint32_t path_vertices(const Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_distance(const Path *p) {
    return p->total_weight;
}

void path_add(Path *p, uint32_t val, const Graph *g) {
    uint32_t last_vertex;
    if (stack_pop(p->vertices, &last_vertex)) {
        p->total_weight += graph_get_weight(g, last_vertex, val);
    }
    stack_push(p->vertices, val);
}

uint32_t path_remove(Path *p, const Graph *g) {
    uint32_t removed_vertex;
    if (stack_pop(p->vertices, &removed_vertex)) {
        uint32_t peeked;
        if (stack_peek(p->vertices, &peeked)) {
            p->total_weight -= graph_get_weight(g, peeked, removed_vertex);
        } else {
            p->total_weight = 0;
        }
    }
    return removed_vertex;
}

void path_copy(Path *dst, const Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->total_weight = src->total_weight;
}

void path_print(const Path *p, FILE *f, const Graph *g) {
    for (uint32_t i = 0; i < stack_size(p->vertices); i++) {
        uint32_t path_item;
        if (stack_peek(p->vertices, &path_item)) {
            fprintf(f, "%s", graph_get_vertex_name(g, path_item));
            if (i < stack_size(p->vertices) - 1) {
                fprintf(f, " -> ");
            }
        }
    }
    fprintf(f, "\n"); // Add a newline at the end of the path.
}
