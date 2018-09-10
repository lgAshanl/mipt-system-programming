#include "assert.h"
#include "math.h"
#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include "QuadraticEquationSolver.h"
#include "LinearEquation.h"
#include "QuadraticEquation.h"

int QuadraticEquationSolver(int argc, char *argv[]) {
    double coefficients[3];
    if (argc > 1) {
        if (argc > 4) {
            std::cout << "Too many arguments\n";
            return 0;
        }

        get_coefficients(argv, argc, coefficients);
    } else {
        std::cout << "Enter the arguments" << std::endl;
        scanf("%lf %lf %lf", &coefficients[0], &coefficients[1], &coefficients[2]);
    }

    double x, y;
    switch (EquationSolver(coefficients[0], coefficients[1], coefficients[2], &x, &y)) {
        case NO_ROOTS:
            std::cout << "No solutions" << std::endl;
            break;
        case ONE_ROOT:
            std::cout << "One root: " << x << std::endl;
            break;
        case TWO_ROOTS:
            std::cout << "Two roots: " << x << " & " << y << std::endl;
            break;
        case INF_ROOTS:
            std::cout << "Infinite number of solutions" << std::endl;
            break;
        default:
            std::cerr << "QuadraticEquation panic!" << std::endl;
            return -1;
    }

    return 0;
}

bool is_number(const char* arg) {
    while (*arg != 0) {
        if (!std::isdigit(*arg )) {
            return false;
        }
        arg++;
    }
    return true;
}

void get_coefficients(char* argv[], int argc, double* coefficients) {
    int i = 1;
    for (; i < argc; ++i) {
        assert(is_number(argv[i]));
        coefficients[i-1] = strtod(argv[i], NULL);
        assert(coefficients[i-1] != HUGE_VAL);
    }

    for (; i < 3; ++i) {
        coefficients[i] = 0;
    }
}

int EquationSolver(double a, double b, double c,
                   double *x, double *y) {
    if (a == 0) {
        if (b == 0) {
            return c == 0 ? INF_ROOTS: NO_ROOTS;
        }

        return LinearEquation(b, c, x);
    }

    return QuadraticEquation(a, b, c, x, y);
}