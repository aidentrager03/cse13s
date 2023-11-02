#include "heap.h"

#include "stats.h"

// Function to find the index of the maximum child
int maxChild(int A[], int first, int last, Stats *stats) {
    int left = 2 * first + 1;
    int right = 2 * first + 2;

    if (right <= last && cmp(stats, A[right], A[left]) > 0) {
        return right;
    }

    return left;
}

// Function to fix the max-heap property
void fixHeap(int A[], int first, int last, Stats *stats) {
    int done = 0;
    int parent = first;

    while (2 * parent + 1 <= last && !done) {
        int largestChild = maxChild(A, parent, last, stats);

        if (cmp(stats, A[parent], A[largestChild]) < 0) {
            // Swap parent and largestChild
            int temp = move(stats, A[parent]);
            A[parent] = move(stats, A[largestChild]);
            A[largestChild] = move(stats, temp);
            parent = largestChild;
        } else {
            done = 1;
        }
    }
}

// Function to build a max-heap
void buildHeap(int A[], int first, int last, Stats *stats) {
    if (last > 0) {
        for (int parent = (last - 1) / 2; parent >= first; parent--) {
            fixHeap(A, parent, last, stats);
        }
    }
}

// Function to perform Heap Sort
void heap_sort(Stats *stats, int A[], int n) {
    int first = 0;
    int last = n - 1;

    buildHeap(A, first, last, stats);

    for (int leaf = last; leaf > first; leaf--) {
        // Swap first and leaf
        int temp = move(stats, A[first]);
        A[first] = move(stats, A[leaf]);
        A[leaf] = move(stats, temp);

        fixHeap(A, first, leaf - 1, stats);
    }
}
