/**
 * Test of vector calculation
*/
#define HTEST_EXTERN
#include <htest.h>
#include "../test_target/Calc.h"
#include <vector>

/**
 * Test Fixture
*/
class TestVectorCalc : public htest::Test
{
protected:
    void SetUp()
    {
        for(int i = 0; i < 5; i++){
            vx.push_back(i * 10);
            vy.push_back(i + 1);
        }
    }

    void TearDown()
    {
        vx.clear();
        vy.clear();
        vz.clear();
    }
    Calc oCalc;

    std::vector<int> vx;
    std::vector<int> vy;
    std::vector<int> vz;
};

TEST_F(TestVectorCalc, vadd)
{
    oCalc.vadd(vx, vy, vz);

    ASSERT_EQ(vx.size(), vz.size()) << "The size of result is different. No further test will be performed.\n";
    for(size_t i = 0U; i < vx.size(); i++)
    {
        EXPECT_EQ(vz[i], vx[i] + vy[i]);
    }
}

TEST_F(TestVectorCalc, vsub)
{
    oCalc.vsub(vx, vy, vz);

    ASSERT_EQ(vx.size(), vz.size()) << "The size of result is different. No further test will be performed.\n";
    for(size_t i = 0U; i < vx.size(); i++)
    {
        EXPECT_EQ(vz[i], vx[i] - vy[i]);
    }
}

TEST_F(TestVectorCalc, vmul)
{
    oCalc.vmul(vx, vy, vz);

    ASSERT_EQ(vx.size(), vz.size()) << "The size of result is different. No further test will be performed.\n";
    for(size_t i = 0U; i < vx.size(); i++)
    {
        EXPECT_EQ(vz[i], vx[i] * vy[i]);
    }
}

TEST_F(TestVectorCalc, vdiv)
{
    oCalc.vdiv(vx, vy, vz);

    ASSERT_EQ(vx.size(), vz.size()) << "The size of result is different. No further test will be performed.\n";
    for(size_t i = 0U; i < vx.size(); i++)
    {
        EXPECT_EQ(vz[i], vx[i] / vy[i]);
    }
}

// main() is defined in htest.cpp