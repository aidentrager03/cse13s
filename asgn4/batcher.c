#include "batcher.h"

#include "stats.h"

#include <stdio.h>

// Merge Exchange Sort (Batcher's Method)
void batcher_sort(Stats *stats, int A[], int n) {
    if (n == 0) {
        return;
    }
    int t = 1;
    while ((1 << t) < n) {
        t++;
    }

    for (int p = (1 << (t - 1)); p > 0; p >>= 1) {
        int q = (1 << (t - 1));
        int r = 0;
        int d = p;

        while (d > 0) {
            for (int i = 0; i < n - d; i++) {
                if ((i & p) == r) {
                    if (cmp(stats, A[i], A[i + d]) > 0) {
                        swap(stats, &A[i], &A[i + d]);
                    }
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
    }
}
