#include "LinearEquation.h"

int LinearEquation(double b, double c,
                   double *x) {
    assert(b != 0);
    assert(x != nullptr);

    *x = (-c) / b;
    return ONE_ROOT;
}