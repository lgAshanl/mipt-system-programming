cmake_minimum_required(VERSION 3.12)
project(QuadraticEquation_)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lgtest")

add_executable(QuadraticEquation_ main.cpp LinearEquation.cpp QuadraticEquationSolver.h QuadraticEquationSolver.cpp LinearEquation.h QuadraticEquation.h QuadraticEquation.cpp EquationResult.h)
add_executable(Tests_ tests/test_main.cpp LinearEquation.cpp QuadraticEquationSolver.h QuadraticEquationSolver.cpp LinearEquation.h QuadraticEquation.h QuadraticEquation.cpp EquationResult.h )