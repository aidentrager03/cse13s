#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 1024
int use_libm = 0;

// Prototype for the test_evaluate_expression function
void test_evaluate_expression(void);

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

// Function to test the evaluate_expression function
void test_evaluate_expression(void) {
    char buffer[BUFFER_SIZE];

    // Test with valid expressions and expected results
    const char *validExpressions[] = { "2 3 +", "3 2 -", "3 2 *", "6 3 /", "4 5 %", "0.5 s",
        "0.866025 c", "1 t", "25 r", "-4 a", "2 3 + 4 +", "2 3 4 + +", "2 3 4 5 + + +" };
    const char *validResults[] = { "5.0000000000", "1.0000000000", "6.0000000000", "2.0000000000",
        "4.0000000000", "0.4794260073", "0.5000000000", "1.5574077247", "5.0000000000",
        "4.0000000000", "9.0000000000", "9.0000000000", "14.0000000000" };
    for (size_t i = 0; i < sizeof(validExpressions) / sizeof(validExpressions[0]); i++) {
        snprintf(buffer, sizeof(buffer), "%s\n", validExpressions[i]);
        evaluate_expression(buffer);

        printf("Expected: %s\n", validResults[i]);
    }

    for (size_t i = 0; i < sizeof(validExpressions) / sizeof(validExpressions[0]); i++) {
        snprintf(buffer, sizeof(buffer), "%s\n", validExpressions[i]);
        evaluate_expression(buffer);
        assert(strcmp(buffer, validResults[i]) == 0);
    }

    const char *invalidExpressions[] = { "2 +", "3 - 2", "3 2 * *", "6 /", "4 % 5 5 +", "s", "c",
        "t r a", "+ + +", "2 + 3 - *" };

    for (size_t i = 0; i < sizeof(invalidExpressions) / sizeof(invalidExpressions[0]); i++) {
        snprintf(buffer, sizeof(buffer), "%s\n", invalidExpressions[i]);
        evaluate_expression(buffer);
        assert(strstr(buffer, "Invalid expression") != NULL);
    }
}

int main() {
    // Initialize the stack
    stack_clear();

    // Run the tests
    test_evaluate_expression();

    // Cleanup the stack
    stack_clear();
    printf("All tests passed!\n");
    return 0;
}
