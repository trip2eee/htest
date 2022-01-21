# htest
htest is a very simple C++ unit test library implemented in a single header file. Therefore you do not need to build or link any library.

You can test your code by just including htest.h.

In addition, htest mimics interfaces of googletest for easier use.

https://github.com/google/googletest

## QuickStart

### Assertions
htest provides assertion macros as googletest does. When assertion failes, htest prints the source file and line location at which failure occurred.

The assertion macros are in pairs: ASSERT_*() and EXPECT_*(). They have different behaviour after test. 

ASSERT_*() returns the test immediately without performing further test. On the other hand, EXPECT_*() does not return and execute following test codes.

|Name                   | Description                                                          |
|-----------------------|----------------------------------------------------------------------|
| EXPECT_EQ(x, y)       | Test if x and y are equal.                                           |
| EXPECT_FLOAT_EQ(x, y) | Test if floating point x and y are equal i.e. abs(x-y) < FLT_EPSILON |
| EXPECT_NEAR(x, y, z)  | Test if x is near to y by z i.e. abs(x-y) < z                        |
| EXPECT_LT(x, y)       | Test if x is less than y i.e. x < y                                  |
| EXPECT_RT(x, y)       | Test if x is greater than y i.e. x > y                               |

You may also write custom failure messages same as googletest as below.
```cxx
const int x = 10;
const int y = 10;
const int z = add(x, y);
EXPECT_EQ(z, x + y) << " add function failed\n";
```


### Simple Test
To create a test:

1. Use TEST() macro to define a test function.
2. Write a test case.
3. Use assertions to check values returned from the test case.
```cxx
TEST(TestSuiteName, TestCaseName)
{
    // Test Body.
}
```

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
You can find the simple test example in examples/simple_test.

As described in the example code, main() can be replaced by HTEST_MAIN macro.

### Test using Test Fixture

You can use test fixture to reuse test configurations.

To create a fixture:

1. Derive a class from htest::Test. Start its body with protected:.
2. Declare objects to be used in tests.
3. If neccessary, override SetUp() method to prepare obects for each test.
4. If neccessary, override TearDown() method to release resources allocated in SetUp().
5. If needed, define subroutines for your tests to share.
6. Write test cases using TEST_F() instead of TEST().
```cxx
TEST_F(TestFixtureName, TestName)
{
    // Test Body.
}
```

```cxx
#include "htest/htest.h"

class TestFixture : public htest::Test
{
public:
    void SetUp()
    {
        // Initialization code here.
    }

    void TearDown()
    {
        // Release code here.
    }
};

TEST_F(TestFixture, TestCaseName1)
{
    // Run Test
}

TEST_F(TestFixture, TestCaseName2)
{
    // Run Test
}

int main()
{
    htest::test();
    return 0;
}
```

Test fixture example is in examples/test_fixture.

### Test with Multiple Test Files

The intention of this project is not to build any codes in unit test framework. For multiple test files,  however, there is no other option but build 'htest.cpp' together with test codes.

In addition, HTEST_EXTERN has to be defined before including htest.h to prevent multiple declaration of several internal variables.

Example code for multiple test files can be found in examples/multiple_test_files

```cxx
#define HTEST_EXTERN
#include <htest.h>

// Test codes

```

If you build your test files with 'htest.cpp', you must not declare main function because main function is declared in htest.cpp.


### Command Line Arguments
In main() function, you may pass command line arguments to test().

Please note that the following main function can be replaced by HTEST_MAIN macro.
```cxx
int main(int argc, char* argv[])
{
    htest::test(argc, argv);
    return 0;
}
```

Color print is enabled in Linux by default. However, it's disabled in Windows because windows command prompt does not support this feature. If you run your test in Windows Powershell, you may enable color print by passing argument --htest_color=yes.

