#include "mathlib.h"

#include <math.h>
/*
 * Compute the absolute value of x.
 */
double Abs(double x) {
    return x > 0.0 ? x : -x;
}

/*
 * Compute the square root of x >= 0.
 */
double Sqrt(double x) {

    // Check domain.
    if (x < 0) {
        return nan("nan");
    }
    double old = 0.0;
    double new = 1.0;
    while (Abs(old - new) > EPSILON) {
        // Specifically, this is the Babylonian method--a simplification of
        // Newton's method possible only for Sqrt(x).
        old = new;

        new = 0.5 * (old + (x / old));
    }
    return new;
}

/*
 * Compute the sine of x.
 */

double Sin(double x) {
    double curr_val = x; // Initialize current value to x
    double prev_exp = x; // Initialize previous exponential term to x
    double prev_fact = 1; // Initialize previous factorial to 1
    int n = 2; // Start n from 2

    // Keep track of the sum of the series until it converges
    while (Abs(prev_exp / prev_fact) > EPSILON) {
        prev_exp *= -x * x; // Update prev_exp with alternating signs
        prev_fact *= n * (n + 1); // Update prev_fact
        curr_val += (prev_exp / prev_fact); // Update curr_val
        n += 2; // Increment n by 2 for the next term
    }

    return curr_val;
}

/*
 * Compute the cosine of x.
 */
double Cos(double x) {
    double curr_val = 1; // Initialize current value to 1 for the first term
    double prev_exp = 1; // Initialize previous exponential term to 1 for the first term
    double prev_fact = 1; // Initialize previous factorial to 1 for the first term
    int n = 2; // Start n from 2

    // Keep track of the sum of the series until it converges
    while (Abs(prev_exp / prev_fact) > EPSILON) {
        prev_exp *= -x * x; // Update prev_exp with alternating signs
        prev_fact *= n * (n - 1); // Update prev_fact
        curr_val += (prev_exp / prev_fact); // Update curr_val
        n += 2; // Increment n by 2 for the next term
    }

    return curr_val;
}

/*
 * Compute the tangent of x.
 *
 * NOTE:
 * Tan(M_PI / 2) will not be undefined for two reasons:
 * (1) the IEEE 754 double precision standard cannot perfectly represent
 *     pi in binary; and
 * (2) the Taylor-Maclaurin series used to approximate Cos(pi/2) will not
 *     converge to 0.
 *  Therefore, it will instead to converge to a very, very small
 *  number resulting in a very, very large value of Tan(pi/2).
 */
double Tan(double x) {
    return Sin(x) / Cos(x);
}
