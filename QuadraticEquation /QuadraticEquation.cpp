#include "QuadraticEquation.h"

int QuadraticEquation(double a, double b, double c,
                      double *x, double *y) {
    assert(a != 0);
    assert(x != nullptr);
    assert(y != nullptr);
    assert(x != y);

    double D = b * b - 4 * a * c;

    if (D < 0) {
        return NO_ROOTS;
    } else if (D == 0) {
        *x = (-b) / (2 * a);
        return ONE_ROOT;
    } else {
        double d_sqrt = sqrt(D);
        *x =  (d_sqrt - b) / (2 * a);
        *y = -(d_sqrt + b) / (2 * a);
        return TWO_ROOTS;
    }
}