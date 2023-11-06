#include "batcher.h"

#include "stats.h"

void comparator(Stats *stats, int A[], int x, int y) {
    if (cmp(stats, A[x], A[y]) > 0) {
        swap(stats, &A[x], &A[y]);
    }
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
            d = q - p;
            q >>= 1;
            r = p;
        }
        p >>= 1;
    }
}
