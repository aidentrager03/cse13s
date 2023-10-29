#include "stack.h"
#include <stdio.h>
double stack[STACK_CAPACITY];
int stack_size = 0;

bool stack_push(double item) {
    if (stack_size < STACK_CAPACITY) {
        stack[stack_size] = item;
        stack_size++;
        return true;
    }
    return false; // Stack is full.
}

bool stack_peek(double *item) {
    if (stack_size > 0) {
        *item = stack[stack_size - 1];
        return true;
    }
    return false; // Stack is empty.
}

bool stack_pop(double *item) {
    if (stack_size > 0) {
        stack_size--;
        *item = stack[stack_size];
        return true;
    }
    return false; // Stack is empty.
}

void stack_clear(void) {
    stack_size = 0;
}

void stack_print(void) {
    if (stack_size == 0) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack contents:\n");
    for (int i = 0; i < stack_size; i++) {
        printf("%lf\n", stack[i]);
    }
}
