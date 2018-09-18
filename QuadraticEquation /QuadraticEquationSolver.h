#ifndef QUADRATICEQUATION_QUADRATICEQUATIONSOLVER_H
#define QUADRATICEQUATION_QUADRATICEQUATIONSOLVER_H

#endif //QUADRATICEQUATION_QUADRATICEQUATIONSOLVER_H

#ifndef QUADRATICEQUATION_EQUATIONRESULT_H
#include "EquationResult.h"

#endif //QUADRATICEQUATION_EQUATIONRESULT_H

int QuadraticEquationSolver(int argc, char *argv[]);

int EquationSolver(double a, double b, double c,
                   double *x, double *y);

void get_coefficients(char* argv[], int argc, double* coefficients);