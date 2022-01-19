# htest
htest is a very simple C++ unit test library implemented in a header file.

You can test your code by just including htest.h.

## QuickStart
### Simple Test
```cxx
#include "htest/htest.h"

TEST(TestSuiteName, TestCaseName1)
{
    // Run Test
}

TEST(TestSuiteName, TestCaseName2)
{
    // Run Test
}

int main()
{
    htest::test();
    return 0;
}
```

### Test with custom TestSuite class
```cxx
#include "htest/htest.h"

class TestSuite : public htest::Test
{
public:
    void SetUp()
    {
        // Set up code
    }

    void TearDown()
    {
        // Tear down code
    }
};

TEST_F(TestSuite, TestCaseName1)
{
    // Run Test
}

TEST_F(TestSuite, TestCaseName2)
{
    // Run Test
}

int main()
{
    htest::test();
    return 0;
}
```

### Macros
1. EXPECT_EQ()
2. EXPECT_FLOAT_EQ()
3. EXPECT_NEAR()
4. EXPECT_LT()
5. EXPECT_GT()