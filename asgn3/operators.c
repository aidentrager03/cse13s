#include "operators.h"

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

double operator_add(double lhs, double rhs) {
    return lhs + rhs;
}

double operator_sub(double lhs, double rhs) {
    return lhs - rhs;
}

double operator_mul(double lhs, double rhs) {
    return lhs * rhs;
}
double operator_mod(double lhs, double rhs) {
    return fmod(lhs, rhs);
}
double operator_div(double lhs, double rhs) {
    if (rhs == 0.0) {
        // Handle division by zero here
        return 0.0;
    }
    return lhs / rhs;
}

bool apply_binary_operator(binary_operator_fn op) {
    if (stack_size < 2) {
        return false; // Handle the case where the stack is too small for binary operations
    }
    double rhs;
    double lhs;

    if (stack_pop(&rhs) && stack_pop(&lhs)) {
        double result = op(lhs, rhs);
        stack_push(result);
        return true;
    } else {
        return false; // Handle the case where popping failed
    }
}

bool apply_unary_operator(unary_operator_fn op) {
    if (stack_size < 1) {
        return false; // Handle the case where the stack is empty for unary operations
    }
    double x;

    if (stack_pop(&x)) {
        double result = op(x);
        stack_push(result);
        return true;
    } else {
        return false; // Handle the case where popping failed
    }
}

bool parse_double(const char *s, double *d) {
    char *endptr;
    double result = strtod(s, &endptr);
    if (endptr != s) {
        *d = result;
        return true;
    } else {
        return false; // Handle the case where parsing failed
    }
}
