#include "batcher.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "shell.h"
#include "stats.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int generatePseudoRandom(void);

// Function to generate pseudorandom numbers and mask them to fit 30 bits
int generatePseudoRandom() {
    return random() & ((1 << 30) - 1);
}

void generateRandomArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = generatePseudoRandom(); // Generate random integers (bit-masked to 30 bits)
    }
}

void testSortingAlgorithm(const char *algorithmName, void (*sortFunction)(Stats *, int[], int),
    int arr[], int size, int print_elements) {
    Stats *stats = (Stats *) malloc(sizeof(Stats));
    stats->moves = (uint64_t) malloc(sizeof(uint64_t));
    stats->compares = (uint64_t) malloc(sizeof(uint64_t));

    reset(stats); // Reset the statistics before sorting

    // If the algorithm should be sorted, sort the array
    if (print_elements >= 0) {
        sortFunction(stats, arr, size);
        print_stats(stats, algorithmName, size);

        // Print the sorted array, limiting to print_elements or size, whichever is smaller
        int elements_to_print = (print_elements < size) ? print_elements : size;
        for (int i = 0; i < elements_to_print; i++) {
            printf(" %12d", arr[i]);
            if ((i + 1) % 5 == 0 || i == (elements_to_print - 1)) {
                printf("\n");
            }
        }
    }
}

int main(int argc, char *argv[]) {
    // Default options
    int size = 100;
    unsigned int seed = 13371453;
    int enable_all = 0;
    int enable_heap = 0;
    int enable_batcher = 0;
    int enable_shell = 0;
    int enable_quick = 0;
    int enable_insert = 0;
    int print_elements = 100; // Default number of elements to print

    int opt;
    while ((opt = getopt(argc, argv, "Hahbsqin:r:p:")) != -1) {
        switch (opt) {
        case 'H':
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "  A collection of comparison-based sorting algorithms.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "  %s [-Hahbsqi] [-n length] [-p elements] [-r seed]\n\n", argv[0]);
            fprintf(stderr, "OPTIONS\n");
            fprintf(stderr, "  -H              Display program help and usage.\n");
            fprintf(stderr, "  -a              Enable all sorts.\n");
            fprintf(stderr, "  -h              Enable Heap Sort.\n");
            fprintf(stderr, "  -b              Enable Batcher Sort.\n");
            fprintf(stderr, "  -s              Enable Shell Sort.\n");
            fprintf(stderr, "  -q              Enable Quick Sort.\n");
            fprintf(stderr, "  -i              Enable Insertion Sort.\n");
            fprintf(
                stderr, "  -n length       Specify the number of array elements (default: 100).\n");
            fprintf(stderr,
                "  -p elements     Specify the number of elements to print (default: 100).\n");
            fprintf(stderr, "  -r seed         Specify random seed (default: 13371453).\n");
            return 0;

        case 'a': enable_all = 1; break;

        case 'h': enable_heap = 1; break;

        case 'b': enable_batcher = 1; break;

        case 's': enable_shell = 1; break;

        case 'q': enable_quick = 1; break;

        case 'i': enable_insert = 1; break;

        case 'n': size = atoi(optarg); break;

        case 'r': seed = atoi(optarg); break;

        case 'p': print_elements = atoi(optarg); break;

        default: fprintf(stderr, "Invalid option\n"); return 1;
        }
    }
    if (!(enable_all || enable_heap || enable_batcher || enable_shell || enable_quick
            || enable_insert)) {
        fprintf(stderr, "Select at least one sort to perform.\n");
        fprintf(stderr, "SYNOPSIS\n");
        fprintf(stderr, "  A collection of comparison-based sorting algorithms.\n\n");
        fprintf(stderr, "USAGE\n");
        fprintf(stderr, "  %s [-Hahbsqi] [-n length] [-p elements] [-r seed]\n\n", argv[0]);
        fprintf(stderr, "OPTIONS\n");
        fprintf(stderr, "  -H              Display program help and usage.\n");
        fprintf(stderr, "  -a              Enable all sorts.\n");
        fprintf(stderr, "  -h              Enable Heap Sort.\n");
        fprintf(stderr, "  -b              Enable Batcher Sort.\n");
        fprintf(stderr, "  -s              Enable Shell Sort.\n");
        fprintf(stderr, "  -q              Enable Quick Sort.\n");
        fprintf(stderr, "  -i              Enable Insertion Sort.\n");
        fprintf(stderr, "  -n length       Specify the number of array elements (default: 100).\n");
        fprintf(
            stderr, "  -p elements     Specify the number of elements to print (default: 100).\n");
        fprintf(stderr, "  -r seed         Specify random seed (default: 13371453).\n");
        return 1;
    }

    // Use srandom and print the random seed
    srandom(seed);
    int *arr = (int *) malloc(size * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Generate a random array
    generateRandomArray(arr, size);
    if (enable_all || enable_insert) {
        testSortingAlgorithm("Insertion Sort", insertion_sort, arr, size, print_elements);
    }
    if (enable_all || enable_heap) {
        testSortingAlgorithm("Heap Sort", heap_sort, arr, size, print_elements);
    }
    if (enable_all || enable_shell) {
        testSortingAlgorithm("Shell Sort", shell_sort, arr, size, print_elements);
    }
    if (enable_all || enable_quick) {
        testSortingAlgorithm("Quick Sort", quick_sort, arr, size, print_elements);
    }
    if (enable_all || enable_batcher) {
        testSortingAlgorithm("Batcher Sort", batcher_sort, arr, size, print_elements);
    }

    // Free dynamically allocated memory
    free(arr);

    return 0;
}
