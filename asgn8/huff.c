#include "bitreader.h"
#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <stdio.h>

void huff_compress_file(BitWriter *outbuf, FILE *fin, uint32_t filesize, uint16_t num_leaves,
    Node *code_tree, Code *code_table);
Node *create_tree(uint32_t *histogram, uint16_t *num_leaves);
uint32_t fill_histogram(FILE *fin, uint32_t *histogram);

uint32_t fill_histogram(FILE *fin, uint32_t *histogram) {
    for (int i = 0; i < 256; ++i) {
        histogram[i] = 0;
    }

    uint32_t filesize = 0;

    while (1) {
        int b = fgetc(fin);
        if (b == EOF) {
            break;
        }

        histogram[b]++;
        filesize++;
    }

    histogram[0x00]++;
    histogram[0xff]++;

    return filesize;
}

void huff_compress_file(BitWriter *outbuf, FILE *fin, uint32_t filesize, uint16_t num_leaves,
    Node *code_tree, Code *code_table) {
    bit_write_uint8(outbuf, 'H');
    bit_write_uint8(outbuf, 'C');
    bit_write_uint32(outbuf, filesize);
    bit_write_uint16(outbuf, num_leaves);

    huff_write_tree(outbuf, code_tree);

    while (1) {
        int b = fgetc(fin);
        if (b == EOF) {
            break;
        }

        uint64_t code = code_table[b].code;
        uint8_t code_length = code_table[b].code_length;

        for (uint8_t i = 0; i < code_length; ++i) {
            bit_write_bit(outbuf, (uint8_t) (code & 1));
            code >>= 1;
        }
    }
}

Node *create_tree(uint32_t *histogram, uint16_t *num_leaves) {
    PriorityQueue *priority_queue = pq_create();

    for (uint16_t i = 0; i < 256; ++i) {
        if (histogram[i] > 0) {
            Node *new_node = node_create((uint8_t) i, histogram[i]);
            enqueue(priority_queue, new_node);
            (*num_leaves)++;
        }
    }

    while (!pq_size_is_1(priority_queue)) {
        Node *left = dequeue(priority_queue);
        Node *right = dequeue(priority_queue);

        Node *new_node = node_create(0, left->weight + right->weight);
        new_node->left = left;
        new_node->right = right;

        enqueue(priority_queue, new_node);
    }

    Node *huffman_tree = dequeue(priority_queue);

    pq_free(&priority_queue);

    return huffman_tree;
}
