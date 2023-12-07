#include "node.h"

#include <stdio.h>
#include <stdlib.h>

Node *node_create(uint8_t symbol, uint32_t weight) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL; // Memory allocation error
    }

    new_node->symbol = symbol;
    new_node->weight = weight;
    new_node->code = 0; // Initialize code to 0
    new_node->code_length = 0; // Initialize code_length to 0
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

void node_free(Node **pnode) {
    if (*pnode != NULL) {
        node_free(&((*pnode)->left));
        node_free(&((*pnode)->right));
        free(*pnode);
        *pnode = NULL;
    }
}

void node_print_node(Node *tree, char ch, int indentation) {
    if (tree == NULL) {
        return;
    }

    node_print_node(tree->right, '/', indentation + 3);

    printf("%*cweight = %d", indentation + 1, ch, tree->weight);

    if (tree->left == NULL && tree->right == NULL) {
        if (' ' <= tree->symbol && tree->symbol <= '~') {
            printf(", symbol = '%c'", tree->symbol);
        } else {
            printf(", symbol = 0x%02x", tree->symbol);
        }
    }

    printf("\n");

    node_print_node(tree->left, '\\', indentation + 3);
}

void node_print_tree(Node *tree) {
    node_print_node(tree, '<', 2);
}
