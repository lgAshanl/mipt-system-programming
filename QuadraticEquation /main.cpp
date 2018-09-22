#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <cmath>
#include "QuadraticEquationSolver.h"

//-------------------------------------------------------
//! Command-line utility for solving quadratic(ax^2+bx+c=0) and linear(bx+c=0) equations
//! @param [in] a - first coefficient
//! @param [in] b - second coefficient
//! @param [in] c - third coefficient
//!
//! @return roots
//!
//! You must specify coefficients as program arcs, or in one line in dialog mode
//! Example:
//!     Command args:
//!         ~./QuadraticEquation 2 3 47
//!     Dialog mode:
//!         ~./QuadraticEquation
//!         ~Enter the arguments:
//!         ~2 3 47
//-------------------------------------------------------

int main(int argc, char *argv[]) {
    return QuadraticEquationSolver(argc, argv);
}