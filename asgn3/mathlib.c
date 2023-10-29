#include "mathlib.h"

#include <math.h>

int IsZero(double x) {
    return (x < EPSILON) && (x > -EPSILON);
}

double Abs(double x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

double Sqrt(double x) {
    if (x < 0) {
        return nan("nan");
    }

    if (x == 0) {
        return 0;
    }

    double old = 0.0;
    double new = x;

    while (Abs(old - new) > EPSILON) {
        old = new;
        new = 0.5 * (old + (x / old));
    }

    return new;
}

double Sin(double x) {
    double result = 0;
    double term = x;
    double given = x;
    int i = 1;

    while (!IsZero(term)) {
        result += term;
        i += 2;
        given *= -x * x / i / (i - 1);
        term = given;
    }

    return result;
}

double Cos(double x) {
    double result = 0;
    double term = 1;
    double given = 1;
    int i = 0;

    while (!IsZero(term)) {
        result += term;
        i += 2;
        given *= -x * x / i / (i - 1);
        term = given;
    }

    return result;
}

double Tan(double x) {
    return Sin(x) / Cos(x);
}
