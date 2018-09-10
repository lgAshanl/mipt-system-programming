#include <gtest/gtest.h>
#include "math.h"
#include "../EquationResult.h"
#include "../QuadraticEquationSolver.h"

TEST(tests, SIMPLE_TEST) {
    double x, y;
    ASSERT_EQ(EquationSolver(2, -5, 3, &x, &y), TWO_ROOTS);
    ASSERT_EQ(x, 1.5);
    ASSERT_EQ(y, 1);

    ASSERT_EQ(EquationSolver(2, 4, 1, &x, &y), TWO_ROOTS);
    ASSERT_EQ(x, -1 + sqrt(2) / 2);
    ASSERT_EQ(y, -1 - sqrt(2) / 2);
}

TEST(tests, NO_ROOTS_TEST) {
    double x, y;
    ASSERT_EQ(EquationSolver(1, 2, 3, &x, &y), NO_ROOTS);
    ASSERT_EQ(EquationSolver(2, 4, 8, &x, &y), NO_ROOTS);
    ASSERT_EQ(EquationSolver(2, 1, 4, &x, &y), NO_ROOTS);
}

TEST(tests, ZERO_TEST) {
    double x, y;
    ASSERT_EQ(EquationSolver(0, 2, 3, &x, &y), ONE_ROOT);
    ASSERT_EQ(x, -1.5);

    ASSERT_EQ(EquationSolver(2, 0, 3, &x, &y), NO_ROOTS);

    ASSERT_EQ(EquationSolver(2, 0, -3, &x, &y), TWO_ROOTS);
    ASSERT_EQ(x, sqrt(24) / 4);
    ASSERT_EQ(y, -sqrt(24) / 4);


    ASSERT_EQ(EquationSolver(2, 5, 0, &x, &y), TWO_ROOTS);
    ASSERT_EQ(x, 0);
    ASSERT_EQ(y, -2.5);
}

TEST(tests, ONE_ROOT_TEST) {
    double x, y;
    ASSERT_EQ(EquationSolver(1, 2, 1, &x, &y), ONE_ROOT);
    ASSERT_EQ(x, -1);

    ASSERT_EQ(EquationSolver(1, 4, 4, &x, &y), ONE_ROOT);
    ASSERT_EQ(x, -2);

    ASSERT_EQ(EquationSolver(2, 4, 2, &x, &y), ONE_ROOT);
    ASSERT_EQ(x, -1);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}