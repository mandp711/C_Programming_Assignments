
#include "operators.h"

#include <stdlib.h>

typedef double (*binary_operator_fn)(double lhs, double rhs);

typedef double (*unary_operator_fn)(double x);

double operator_add(double lhs, double rhs) {
    return lhs + rhs;
}

double operator_sub(double lhs, double rhs) {
    return lhs - rhs;
}

double operator_mul(double lhs, double rhs) {
    return lhs * rhs;
}

double operator_div(double lhs, double rhs) {
    return lhs / rhs;
}

// return false if there are fewer than 2 items on the stack. otherwise, pop
// rhs, then pop lhs, then pass them into op, then push the result. and return
// true

bool apply_binary_operator(binary_operator_fn op) {
    double rhs, lhs;
    if (stack_size < 2) {
        return false;
    }
    (stack_pop(&rhs));
    (stack_pop(&lhs));

    double result = op(lhs, rhs);
    (stack_push(result));

    return true;
}

// return false if the stack is empty, otherwise pop an item, call op on it, and
// push the result

bool apply_unary_operator(unary_operator_fn op) {
    // Make sure that the stack is not empty
    if (stack_size < 1) {
        return false;
    }
    double x;
    (stack_pop(&x));
    // Calculate the value we should push to the stack
    double result = op(x);
    (stack_push(result));
    return true;
}

// this function should be given to students
bool parse_double(const char *s, double *d) {
    char *endptr;
    double result = strtod(s, &endptr);
    if (endptr != s) {
        *d = result;
        return true;
    } else {
        return false;
    }
}
