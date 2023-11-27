#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 16
#define DELAY_MICROSECONDS 10000 // Adjust the delay as needed

void print_hex_ascii_line(const char *buffer, size_t size, size_t offset) {
    printf("%08zx: ", offset);

    for (size_t i = 0; i < size; ++i) {
        printf("%02x", (unsigned char) buffer[i]);
        if (i % 2 == 1)
            printf(" ");
    }

    if (size < BUFFER_SIZE) {
        for (size_t i = size; i < BUFFER_SIZE; ++i) {
            printf("  ");
            if (i % 2 == 1)
                printf(" ");
        }
    }

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
    int fd;
    if (filename) {
        fd = open(filename, O_RDONLY);
        if (fd == -1) {
            exit(EXIT_FAILURE);
        }
    } else {
        // Read from stdin
        fd = STDIN_FILENO;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    size_t offset = 0;

    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        print_hex_ascii_line(buffer, (size_t) bytesRead, offset);
        offset += bytesRead > 0 ? (size_t) bytesRead : 0;

        // Introduce a delay to simulate throttled input
        usleep(DELAY_MICROSECONDS);
    }

    if (filename) {
        close(fd);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        print_hex_ascii_file(argv[1]);
    } else if (argc == 1) {
        print_hex_ascii_file(NULL); // Read from stdin
    } else {
        exit(EXIT_FAILURE);
    }

    return 0;
}
