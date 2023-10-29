#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Function to process and evaluate RPN expressions
void evaluate_expression(char *expr) {
    stack_clear();
    char *saveptr;
    char *token = strtok_r(expr, " \n", &saveptr);

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
        }else if (strcmp(token, "*") == 0) {
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
            apply_unary_operator(my_unary_operators['s']);
        } else if (strcmp(token, "c") == 0) {
            if (stack_size < 1) {
                fprintf(stderr, "%s", ERROR_UNARY_OPERATOR);
                return;
            }
            apply_unary_operator(my_unary_operators['c']);
        } else if (strcmp(token, "t") == 0) {
            if (stack_size < 1) {
                fprintf(stderr, "%s", ERROR_UNARY_OPERATOR);
                return;
            }
            apply_unary_operator(my_unary_operators['t']);
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
                stack_push(value);
            } else {
                if (strlen(token)==1){
                fprintf(stderr, ERROR_BAD_CHAR, token[0]);
                return;
                }
                else{
                    fprintf(stderr, ERROR_BAD_STRING, token);
                return;
                }
            }
        }
        token = strtok_r(NULL, " \n", &saveptr);
    }

    double result;
    if (stack_size == 1 && stack_peek(&result)) {
        printf("%.10f\n", result);
    } else {
        fprintf(stderr, "Invalid expression\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
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
