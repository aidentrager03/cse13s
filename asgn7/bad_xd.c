#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define B 16

void p(const char *b, size_t s, size_t o) {
    printf("%08zx: ", o);

    for (size_t i = 0; i < s; ++i) {
        printf("%02x", (unsigned char) b[i]);
        if (i % 2 == 1)
            printf(" ");
    }

    if (s < B) {
        for (size_t i = s; i < B; ++i) {
            printf("  ");
            if (i % 2 == 1)
                printf(" ");
        }
    }

    printf(" ");
    for (size_t i = 0; i < s; ++i) {
        if (b[i] >= 32 && b[i] <= 126)
            putchar(b[i]);
        else
            putchar('.');
    }

    printf("\n");
}

void h(const char *f) {
    int fd;
    if (f) {
        fd = open(f, 00);
        if (fd == -1) {
            exit(1);
        }
    } else {
        fd = 0;
    }

    char U[B];
    size_t O = 0;
    ssize_t R = 1;

    while (R > 0) {
        ssize_t r = 0;
        while (r != B) {
            R = read(fd, &U[r], (size_t) (B - r));
            r += R;
            if (R == 0) {
                break;
            }
        }
        if (r > 0) {
            p(U, (size_t) r, O);
            O += r > 0 ? (size_t) r : 0;
        }
    }

    if (f) {
        close(fd);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        h(argv[1]);
    } else if (argc == 1) {
        h(NULL);
    } else {
        exit(1);
    }

    return 0;
}
