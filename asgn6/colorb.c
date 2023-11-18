#include "bmp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    int opt;
    char *input_file = NULL;
    char *output_file = NULL;

    while ((opt = getopt(argc, argv, "hi:o:")) != -1) {
        switch (opt) {
        case 'h':
            fprintf(stdout, "Usage: %s -i infile -o outfile\ncolorb -h\n", argv[0]);
            return EXIT_SUCCESS;
        case 'i': input_file = optarg; break;
        case 'o': output_file = optarg; break;
        default:
            fprintf(stderr, "Usage: %s -i infile -o outfile\ncolorb -h\n", argv[0]);
            return EXIT_FAILURE;
        }
    }

    // Check if both input and output files are provided
    if (input_file == NULL || output_file == NULL) {
        fprintf(stderr, "Usage: %s -i infile -o outfile\ncolorb -h\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fin = fopen(input_file, "rb");
    if (fin == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    BMP *original_bmp = bmp_create(fin);
    fclose(fin);

    if (original_bmp == NULL) {
        fprintf(stderr, "Error creating BMP structure\n");
        return EXIT_FAILURE;
    }

    bmp_reduce_palette(original_bmp);

    FILE *fout = fopen(output_file, "wb");
    if (fout == NULL) {
        perror("Error opening output file");
        bmp_free(&original_bmp);
        return EXIT_FAILURE;
    }

    bmp_write(original_bmp, fout);
    fclose(fout);

    bmp_free(&original_bmp);

    return EXIT_SUCCESS;
}
