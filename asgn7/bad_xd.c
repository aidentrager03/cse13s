#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define B 16

void p(const char *b, size_t s, size_t o) {
    if (s == 0)
        return;

    printf("%08zx: ", o);
    for (size_t i = 0; i < B; ++i)
        printf(i < s ? "%02x%c" : "  ", (unsigned char) b[i], i % 2 == 1 ? ' ' : ' ');

    printf(" ");
    for (size_t i = 0; i < B; ++i)
        putchar(i < s && ((b[i] >= 32 && b[i] <= 126) || b[i] == '\n') ? b[i] : '.');

    printf("\n");
}

void f(const char *f) {
    int d = f ? open(f, 00) : 0;
    if (d == -1)
        exit(EXIT_FAILURE);

    char b[B];
    size_t o = 0, r1 = 1;

    while (r1 > 0) {
        ssize_t r = 0;
        while (r != B) {
            ssize_t r1 = read(d, &b[r], (size_t) (B - r));
            r += r1;
            if (r1 == 0)
                break;
        }
        if (r == B)
            p(b, (size_t) r, o);
        o += r > 0 ? (size_t) r : 0;
    }

    if (f)
        close(d);
}

int main(int c, char *v[]) {
    if (c == 2)
        f(v[1]);
    else if (c == 1)
        f(NULL);
    else
        exit(EXIT_FAILURE);

    return 0;
}
