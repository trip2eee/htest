/**
 * Test of scalar calculation.
*/
#define HTEST_EXTERN
#include <htest.h>
#include "../test_target/Calc.h"

TEST(TestCalc, add)
{
    Calc oCalc;

    int x = 10;
    int y = 20;
    int z = oCalc.add(x, y);

    EXPECT_EQ(z, x+y);
}

TEST(TestCalc, sub)
{
    Calc oCalc;

    int x = 10;
    int y = 20;
    int z = oCalc.sub(x, y);

    EXPECT_EQ(z, x-y);
}

TEST(TestCalc, mul)
{
    Calc oCalc;

    int x = 10;
    int y = 20;
    int z = oCalc.mul(x, y);

    EXPECT_EQ(z, x*y);
}

TEST(TestCalc, div)
{
    Calc oCalc;

    int x = 10;
    int y = 20;
    int z = oCalc.div(x, y);

    EXPECT_EQ(z, x/y);
}

// main() is defined in htest.cpp