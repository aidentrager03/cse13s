#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
int use_libm;
// Function to process and evaluate RPN expressions
void evaluate_expression(char *expr) {
    stack_clear();
    char *saveptr;
    char *token = strtok_r(expr, " \n", &saveptr);
    double results[BUFFER_SIZE]; // Array to store results
    while (token != NULL) {
        if (strcmp(token, "+") == 0) {
            if (stack_size < 2) {
                fprintf(stderr, "%s", ERROR_BINARY_OPERATOR);
                return;
            }
            apply_binary_operator(binary_operators['+']);
        } else if (strcmp(token, "-") == 0) {
            if (stack_size < 2) {
                fprintf(stderr, "%s", ERROR_BINARY_OPERATOR);
                return;
            }
            apply_binary_operator(binary_operators['-']);
        } else if (strcmp(token, "%") == 0) {
            if (stack_size < 2) {
                fprintf(stderr, "%s", ERROR_BINARY_OPERATOR);
                return;
            }
            apply_binary_operator(binary_operators['%']);
        } else if (strcmp(token, "*") == 0) {
            if (stack_size < 2) {
                fprintf(stderr, "%s", ERROR_BINARY_OPERATOR);
                return;
            }
            apply_binary_operator(binary_operators['*']);
        } else if (strcmp(token, "/") == 0) {
            if (stack_size < 2) {
                fprintf(stderr, "%s", ERROR_BINARY_OPERATOR);
                return;
            }
            apply_binary_operator(binary_operators['/']);
        } else if (strcmp(token, "s") == 0) {
            if (stack_size < 1) {
                fprintf(stderr, "%s", ERROR_BINARY_OPERATOR);
                return;
            }
            if (use_libm) {
                apply_unary_operator(my_unary_operators['s']);
            } else {
                apply_unary_operator(libm_unary_operators['s']);
            }

        } else if (strcmp(token, "c") == 0) {
            if (stack_size < 1) {
                fprintf(stderr, "%s", ERROR_UNARY_OPERATOR);
                return;
            }
            if (use_libm) {
                apply_unary_operator(my_unary_operators['c']);
            } else {
                apply_unary_operator(libm_unary_operators['c']);
            }
        } else if (strcmp(token, "t") == 0) {
            if (stack_size < 1) {
                fprintf(stderr, "%s", ERROR_UNARY_OPERATOR);
                return;
            }
            if (use_libm) {
                apply_unary_operator(my_unary_operators['t']);
            } else {
                apply_unary_operator(libm_unary_operators['t']);
            }
        } else if (strcmp(token, "r") == 0) {
            if (stack_size < 1) {
                fprintf(stderr, "%s", ERROR_UNARY_OPERATOR);
                return;
            }
            apply_unary_operator(my_unary_operators['r']);
        } else if (strcmp(token, "a") == 0) {
            if (stack_size < 1) {
                fprintf(stderr, "%s", ERROR_UNARY_OPERATOR);
                return;
            }
            apply_unary_operator(my_unary_operators['a']);
        } else {
            double value;
            if (parse_double(token, &value)) {
                if (!stack_push(value)) {
                    fprintf(stderr, ERROR_NO_SPACE, value);
                    return;
                }
            } else {
                if (strlen(token) == 1) {
                    fprintf(stderr, ERROR_BAD_CHAR, token[0]);
                    return;
                } else {
                    fprintf(stderr, ERROR_BAD_STRING, token);
                    return;
                }
            }
        }
        token = strtok_r(NULL, " \n", &saveptr);
    }

    int i = 0;
    while (stack_pop(&results[i])) {
        i++;
    }

    for (int j = i - 1; j >= 0; j--) {
        if (j == 0) {
            printf("%.10f\n", results[j]);
        } else {
            printf("%.10f ", results[j]);
        }
    }
}

int main(int argc, char *argv[]) {
    use_libm = 0;
    int show_help = 0;

    // Parse command-line options
    int opt;
    while ((opt = getopt(argc, argv, "mh")) != -1) {
        switch (opt) {
        case 'm': use_libm = 1; break;
        case 'h': show_help = 1; break;
        default: fprintf(stdout, USAGE, argv[0]); return 1;
        }
    }

    if (show_help) {
        fprintf(stdout, USAGE, argv[0]);
        return 0;
    }

    char input_buffer[BUFFER_SIZE];

    while (1) {
        fprintf(stderr, "> ");
        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
            break;
        }
        evaluate_expression(input_buffer);
    }

    return 0;
}
