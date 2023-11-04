#include "batcher.h"
#include "stats.h"
#include <stdio.h>

// Comparator function for sorting
int comparator(Stats *stats, int A[], int x, int y) {
    int cmp_result = cmp(stats, A[x], A[y]);
    if (cmp_result > 0) {
        swap(stats, &A[x], &A[y]);
    }
    return cmp_result;
}

void batcher_sort(Stats *pstats, int A[], int n) {
    if (n == 0) {
        return;
    }

    int t = 1;
    while ((1 << t) < n) {
        t++;
    }

    int p = 1 << (t - 1);
    while (p > 0) {
        int q = 1 << (t - 1);
        int r = 0;
        int d = p;

        while (d > 0) {
            for (int i = 0; i < n - d; i++) {
                if ((i & p) == r) {
                    comparator(pstats, A, i, i + d);
                }
            }
            int t2 = p + q;
            if (t2 < p) {
                r = t2;
                d = t2;
                p = q;
            } else {
                d = q;
            }
            q >>= 1;
        }
        p >>= 1;
    }
}
