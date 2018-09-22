#include "assert.h"
#include "math.h"
#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "QuadraticEquationSolver.h"
#include "LinearEquation.h"
#include "QuadraticEquation.h"

int QuadraticEquationSolver(int argc, char *argv[]) {
    double coefficients[3] = {0};
    if (argc > 1) {
        if (argc > 4) {
            std::cout << "Too many arguments\n";
            return 0;
        }

        for (size_t i = 1; i < argc; ++i) {
            sscanf(argv[i], "%lf", &coefficients[i - 1]);
        }
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

int EquationSolver(double a, double b, double c,
                   double *x, double *y) {
    if (a == 0) {
        return LinearEquation(b, c, x);
    }

    return QuadraticEquation(a, b, c, x, y);
}