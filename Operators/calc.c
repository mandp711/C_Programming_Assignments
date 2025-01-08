#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LENGTH_SIZE 1024

void help_message(void) {
    fprintf(stdout, USAGE, "calc");
}

int main(int argc, char *argv[]) {
    bool call_libm = false;
    int opt;
    while ((opt = getopt(argc, argv, "mh")) != -1) {
        switch (opt) {
        case 'm': call_libm = true; break;
        case 'h':
        default: help_message(); exit(EXIT_FAILURE);
        }
    }

    char buffer[MAX_LENGTH_SIZE];
    while (true) {
        fputs("> ", stderr);
        if (!fgets(buffer, MAX_LENGTH_SIZE, stdin)) {
            break; // Exit the loop if EOF or error occurs
        }

        char *ptrstore;
        char *temp = strtok_r(buffer, " \n", &ptrstore);
        bool error = false;

        while (temp != NULL && !error) {
            // Check if the token represents a number
            if (isdigit(temp[0]) || (temp[0] == '-' && isdigit(temp[1]))) {
                double value;
                // Parse the token into a double value
                if (parse_double(temp, &value)) {
                    // Attempt to push the value onto the stack
                    if (!stack_push(value)) {
                        // Print an error message if there's insufficient space on the stack
                        fprintf(stderr, ERROR_NO_SPACE, value);
                        error = true;
                    }
                } else {
                    // Print an error message if the token cannot be parsed into a double
                    fprintf(stderr, ERROR_BAD_STRING, temp);
                    error = true;
                }
            } else {
                binary_operator_fn bin_op = binary_operators[(unsigned char) temp[0]];
                unary_operator_fn un_op = call_libm ? libm_unary_operators[(unsigned char) temp[0]]
                                                    : my_unary_operators[(unsigned char) temp[0]];

                if (bin_op) {
                    if (stack_size < 2) {
                        fprintf(stderr, ERROR_BINARY_OPERATOR);
                        error = true;
                    } else {
                        if (!apply_binary_operator(bin_op)) {
                            error = true;
                        }
                    }
                } else if (un_op) {
                    if (stack_size < 1) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        error = true;
                    } else {
                        if (!apply_unary_operator(un_op)) {
                            error = true;
                        }
                    }
                } else {
                    fprintf(stderr, ERROR_BAD_CHAR, temp[0]);
                    error = true;
                }
            }
            temp = strtok_r(NULL, " \n", &ptrstore);
        }

        if (!error) {
            stack_print();
            printf("\n");
        }
        stack_clear();
    }
    return 0;
}
