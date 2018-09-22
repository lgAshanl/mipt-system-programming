#include "LinearEquation.h"

int LinearEquation(double b, double c,
                   double *x) {
    assert(x != nullptr);

    if (b == 0) {
        return c == 0 ? INF_ROOTS: NO_ROOTS;
    }
    *x = (-c) / b;
    return ONE_ROOT;
}