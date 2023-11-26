#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 16

void print_hex_ascii_line(const char *buffer, size_t size, size_t offset) {
    // Print index in hexadecimal with zero padding
    printf("%08zx: ", offset);

    // Print hex values
    for (size_t i = 0; i < size; ++i) {
        printf("%02x", (unsigned char)buffer[i]);
        if (i % 2 == 1)
            printf(" ");
    }

    // Pad if needed
    if (size < BUFFER_SIZE) {
        for (size_t i = size; i < BUFFER_SIZE; ++i) {
            printf("  ");
            if (i % 2 == 1)
                printf(" ");
        }
    }

    // Print ASCII representation
    printf(" ");
    for (size_t i = 0; i < size; ++i) {
        if (buffer[i] >= 32 && buffer[i] <= 126)
            putchar(buffer[i]);
        else
            putchar('.');
    }

    printf("\n");
}

void print_hex_ascii_file(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    size_t offset = 0;

    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        print_hex_ascii_line(buffer, (size_t)bytesRead, offset);
        offset += bytesRead > 0 ? (size_t)bytesRead : 0;
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    print_hex_ascii_file(argv[1]);

    return 0;
}
