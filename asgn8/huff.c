#include "bitreader.h"
#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Code {
    uint64_t code;
    uint8_t code_length;
} Code;

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

    // Ensure at least two values in the histogram array are non-zero
    histogram[0x00]++;
    histogram[0xff]++;

    // Rewind the file
    fseek(fin, 0, SEEK_SET);

    return filesize;
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

    while (!pq_is_empty(priority_queue) && !pq_size_is_1(priority_queue)) {
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

void fill_code_table(Code *code_table, Node *node, uint64_t code, uint8_t code_length) {
    if (node->left == NULL) {
        code_table[node->symbol].code = code;
        code_table[node->symbol].code_length = code_length;
    } else {
        fill_code_table(code_table, node->left, code, code_length + 1);
        code |= (uint64_t) 1 << code_length;
        fill_code_table(code_table, node->right, code, code_length + 1);
    }
}

void huff_write_tree(BitWriter *outbuf, Node *node) {
    if (node->left == NULL) {
        bit_write_bit(outbuf, 1);
        bit_write_uint8(outbuf, node->symbol);
    } else {
        huff_write_tree(outbuf, node->left);
        huff_write_tree(outbuf, node->right);
        bit_write_bit(outbuf, 0);
    }
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

int main(int argc, char *argv[]) {
    char *input_filename = NULL;
    char *output_filename = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            input_filename = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output_filename = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "-h") == 0) {
            printf("Usage: huff -i infile -o outfile\n       huff -v -i infile -o outfile\n       "
                   "huff -h\n");
            return 0;
        }
    }

    if (input_filename == NULL || output_filename == NULL) {
        fprintf(stderr, "Error: Input and output filenames are required.\n");
        return 1;
    }

    FILE *input_file = fopen(input_filename, "rb");
    if (input_file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    uint32_t histogram[256];
    uint32_t filesize = fill_histogram(input_file, histogram);
    fclose(input_file);

    histogram[0x00]++;
    histogram[0xff]++;

    uint16_t num_leaves = 0;
    Node *code_tree = create_tree(histogram, &num_leaves);

    Code code_table[256];
    fill_code_table(code_table, code_tree, 0, 0);

    input_file = fopen(input_filename, "rb");
    if (input_file == NULL) {
        perror("Error rewinding input file");
        return 1;
    }

    BitWriter *output_buffer = bit_write_open(output_filename);
    if (output_buffer == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return 1;
    }

    huff_compress_file(output_buffer, input_file, filesize, num_leaves, code_tree, code_table);
    fclose(input_file);
    bit_write_close(&output_buffer);

    node_free(&code_tree);

    return 0;
}
