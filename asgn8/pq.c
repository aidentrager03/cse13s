// pq.c

#include "pq.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct ListElement {
    Node *tree;
    struct ListElement *next;
};

struct PriorityQueue {
    struct ListElement *list;
};

PriorityQueue *pq_create(void) {
    PriorityQueue *new_queue = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (new_queue == NULL) {
        return NULL; // Memory allocation error
    }

    new_queue->list = NULL;

    return new_queue;
}

void pq_free(PriorityQueue **q) {
    if (*q != NULL) {
        free(*q);
        *q = NULL;
    }
}

bool pq_is_empty(PriorityQueue *q) {
    return (q == NULL || q->list == NULL);
}

bool pq_size_is_1(PriorityQueue *q) {
    return (q != NULL && q->list != NULL && q->list->next == NULL);
}

static bool pq_less_than(struct ListElement *e1, struct ListElement *e2) {
    if (e1->tree->weight < e2->tree->weight) {
        return true;
    } else if (e1->tree->weight == e2->tree->weight) {
        return (e1->tree->symbol < e2->tree->symbol);
    }

    return false;
}

void enqueue(PriorityQueue *q, Node *tree) {
    struct ListElement *new_element = (struct ListElement *) malloc(sizeof(struct ListElement));
    if (new_element == NULL) {
        return;
    }

    new_element->tree = tree;
    new_element->next = NULL;

    if (pq_is_empty(q) || pq_less_than(new_element, q->list)) {
        new_element->next = q->list;
        q->list = new_element;
    } else {
        struct ListElement *current = q->list;
        while (current->next != NULL && pq_less_than(current->next, new_element)) {
            current = current->next;
        }

        new_element->next = current->next;
        current->next = new_element;
    }
}

Node *dequeue(PriorityQueue *q) {
    if (pq_is_empty(q)) {
        fprintf(stderr, "Fatal error: Dequeue from an empty queue.\n");
        exit(EXIT_FAILURE);
    }

    struct ListElement *front = q->list;
    q->list = front->next;
    Node *tree = front->tree;
    free(front);

    return tree;
}

void pq_print(PriorityQueue *q) {
    assert(q != NULL);
    struct ListElement *e = q->list;
    int position = 1;

    while (e != NULL) {
        if (position == 1) {
            printf("=============================================\n");
        } else {
            printf("---------------------------------------------\n");
        }

        node_print_tree(e->tree);
        e = e->next;
        position++;
    }

    printf("=============================================\n");
}
