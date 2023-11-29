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
        printf(i % 2 == 1 ? "  " : " ");

    printf(" ");

    for (size_t i = 0; i < s; ++i)
        putchar((b[i] >= 32 && b[i] <= 126) ? b[i] : '.');

    printf("\n");
}

void h(const char *f) {
    int d = f ? open(f, 00) : 0;
    if (d == -1)
        exit(1);

    char U[B];
    size_t O = 0;
    ssize_t R = 1;

    while (R > 0) {
        ssize_t r = 0;
        while (r != B) {
            R = read(d, &U[r], (size_t) (B - r));
            r += R;
            if (R == 0)
                break;
        }
        if (r > 0) {
            p(U, (size_t) r, O);
            O += r > 0 ? (size_t) r : 0;
        }
    }

    if (f)
        close(d);
}

int main(int argc, char *argv[]) {
    (argc == 2) ? h(argv[1]) : ((argc == 1) ? h(NULL) : exit(1));
    return 0;
}
