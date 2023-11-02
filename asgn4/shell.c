#include "gaps.h"
#include "stats.h"

#include <stdio.h>

void shell_sort(Stats *pstats, int *A, int length) {
    reset(pstats);
    int gapIndex;

    for (gapIndex = 0; gapIndex < GAPS; gapIndex++) {
        int gap = gaps[gapIndex];
        for (int k = gap; k < length; k++) {
            int j = k;
            int temp = move(pstats, A[k]);
            while (j >= gap && cmp(pstats, temp, A[j - gap]) < 0) {
                A[j] = move(pstats, A[j - gap]);
                j -= gap;
            }
            A[j] = move(pstats, temp);
        }
    }
}
