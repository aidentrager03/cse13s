#include "bmp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "-h") == 0) {
        fprintf(stdout, "Usage: %s -i infile -o outfile\ncolorb -h\n", argv[0]);
        return EXIT_SUCCESS;
    }
    if (argc != 5 || strcmp(argv[1], "-i") != 0 || strcmp(argv[3], "-o") != 0) {
        fprintf(stderr, "Usage: %s -i infile -o outfile\ncolorb -h\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *input_file = argv[2];
    char *output_file = argv[4];

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
