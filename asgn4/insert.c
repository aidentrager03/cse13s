#include "insert.h"

#include "stats.h"

void insertion_sort(Stats *pstats, int A[], int length) {
    reset(pstats); // Reset the statistics before sorting
    for (int k = 1; k < length; k++) {
        int j = k;
        int temp = move(pstats, A[k]); // move A[k]
        while (j >= 1 && cmp(pstats, temp, A[j - 1]) < 0) { // compare temp and A[j - 1)
            A[j] = move(pstats, A[j - 1]); // move A[j - 1)
            j -= 1;
        }
        A[j] = move(pstats, temp); // move temp
    }
}
