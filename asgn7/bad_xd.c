#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define B 16

void p(const char *b, size_t s, size_t o) {
    printf("%08zx: ", o);

    for (size_t i = 0; i < B; ++i) {
        printf(i < s ? "%02x%c" : "  ", (unsigned char) b[i], i % 2 == 1 ? ' ' : ' ');
    }

    for (size_t i = 0; i < B; ++i) {
        putchar(i < s && (b[i] >= 32 && b[i] <= 126) ? b[i] : '.');
    }

    printf("\n");
}

void f(const char *f) {
    int d = f ? open(f, 00) : 0;
    if (d == -1) {
        exit(1);
    }

    char b[B];
    size_t o = 0;
    ssize_t r1 = 1;

    while (r1 > 0) {
        ssize_t r = 0;
        while (r != B) {
            r1 = read(d, &b[r], (size_t) (B - r));
            r += (size_t) r1;
            if (r1 == 0) {
                break;
            }
        }
        if (r > 0) {
            p(b, (size_t) r, o);
            o += r > 0 ? (size_t) r : 0;
        }
    }

    if (f) {
        close(d);
    }
}

int main(int c, char *v[]) {
    if (c == 2 || c == 1) {
        f(c == 1 ? NULL : v[1]);
    } else {
        exit(1);
    }
    return 0;
}
