#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define B 16

void p(const char *b, size_t s) {
    printf("%08zx: ", s);
    for (size_t i = 0; i < B; ++i) {
        if (i < s) {
            printf("%02x", (unsigned char) b[i]);
            if (i % 2 == 1 && i < B - 1) {
                printf(" ");
            }
        } else {
            printf("   ");
        }
    }
    for (size_t i = 0; i < B; ++i) {
        putchar(i < s && (b[i] >= 32 && b[i] <= 126) ? b[i] : '.');
    }
    printf("\n");
}

void f(const char *f) {
    int d = f ? open(f, 00) : 0;
    if (d == -1)
        exit(EXIT_FAILURE);

    char b[B];
    ssize_t r1 = 1;

    while (r1 > 0) {
        ssize_t r = 0;
        while (r != B) {
            r1 = read(d, &b[r], (size_t) (B - r));
            if (r1 < 0) {
                exit(EXIT_FAILURE);
            }
            r += (size_t) r1;
            if (r1 == 0)
                break;
        }
        if (r > 0) {
            p(b, (size_t) r);
        }
    }

    if (f)
        close(d);
}

int main(int c, char *v[]) {
    if (c == 2 || c == 1) {
        f(c == 1 ? NULL : v[1]);
    } else {
        exit(EXIT_FAILURE);
    }
    return 0;
}
