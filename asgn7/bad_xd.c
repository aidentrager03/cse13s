#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define B 16

void p(const char *b, size_t s, size_t o) {
    printf("%08zx: ", o);

    for (size_t i = 0; i < s; ++i)
        printf("%02x%c", (unsigned char) b[i], i % 2 == 1 ? ' ' : ' ');

    for (size_t i = s; i < B; ++i)
        printf("  %c", i % 2 == 1 ? ' ' : ' ');

    printf(" ");
    for (size_t i = 0; i < s; ++i)
        putchar(b[i] >= 32 && b[i] <= 126 ? b[i] : '.');

    printf("\n");
}

void f(const char *f) {
    int d;
    if ((d = open(f, 00)) == -1) exit(1);

    char b[B];
    ssize_t r;
    size_t o = 0;

    while ((r = read(d, b, B)) > 0) {
        p(b, (size_t) r, o);
        o += r > 0 ? (size_t) r : 0;
    }

    if (f) close(d);
}

int main(int c, char *v[]) {
    if (c == 2 || (c == 1 && (f(NULL), 0)))
        f(v[1]);

    exit(1);
}
