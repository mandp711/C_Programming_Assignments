#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 16

int main(int argc, char **argv) {
    int fd = 0;

    if (argc == 1) {
        fd = 0;
    } else if (argc == 2) {
        char *filename = argv[1];
        fd = open(filename, O_RDONLY);

        if (fd == -1) {
            exit(1);
        }
    } else {
        exit(1);
    }

    int curr = 0;
    ssize_t res = 0;
    unsigned int index = 0;
    char buffer[BUFFER_SIZE] = { 0 };
    do {

        res = read(fd, &buffer[curr], BUFFER_SIZE - curr);
        curr += res;

        if (res == -1) {
            exit(1);
        } else if (res == 0 || curr == 16) {
            if (curr == 0) {
                exit(0);
            }
            printf("%08x: ", index);

            for (int i = 0; i < curr; ++i) {
                printf("%02x", (unsigned char) buffer[i]);

                if (i % 2 == 1)
                    printf(" ");
            }
            for (int i = curr; i < BUFFER_SIZE; ++i) {
                printf("  ");
                if (i % 2 == 1)
                    printf(" ");
            }
            printf(" ");
            for (int i = 0; i < curr; ++i) {
                char c = isprint(buffer[i]) ? buffer[i] : '.';
                printf("%c", c);
            }
            printf("\n");

            for (int i = 0; i < BUFFER_SIZE; i++) {
                buffer[i] = 0;
            }
            curr = 0;
            index += 16;
        }
    } while (res > 0);

    res = close(fd);

    if (res == -1) {
        exit(1);
    }

    return 0;
}
