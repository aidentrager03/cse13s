#include "quick.h"

#include "stats.h"

// Function to partition the array
int partition(int A[], int lo, int hi, Stats *stats) {
    int i = lo - 1;
    for (int j = lo; j < hi; j++) {
        if (cmp(stats, A[j], A[hi]) < 0) {
            i++;
            int temp = move(stats, A[i]);
            A[i] = move(stats, A[j]);
            A[j] = move(stats, temp);
        }
    }
    i++;
    int temp = move(stats, A[i]);
    A[i] = move(stats, A[hi]);
    A[hi] = move(stats, temp);
    return i;
}

// Recursive Quicksort function
void quickSorter(int A[], int lo, int hi, Stats *stats) {
    if (lo < hi) {
        int p = partition(A, lo, hi, stats);
        quickSorter(A, lo, p - 1, stats);
        quickSorter(A, p + 1, hi, stats);
    }
}

// Main Quicksort function
void quick_sort(Stats *stats, int A[], int n) {
    quickSorter(A, 0, n - 1, stats);
}
