#include "../htest/htest.h"

/**
 * Test target class
*/
class Calc
{
public:
    Calc(){

    }
    float add(const float a, const float b)
    {
        return a + b;
    }

    float sub(const float a, const float b)
    {
        return a - b;
    }
};

TEST(CalcTest, TestAdd)
{
    Calc oCalc;
    const double x = 10.4567;
    const double y = 20.1234;

    const float result = oCalc.add(x, y);
    EXPECT_NEAR(result, x + y, 0.0000001);
}

TEST(CalcTest, TestSub)
{
    Calc oCalc;
    const float x = 10.4567;
    const float y = 20.1234;

    const float result = oCalc.sub(x, y);
    EXPECT_FLOAT_EQ(result, x - y);
}

int main()
{
    htest::test();
    return 0;
}