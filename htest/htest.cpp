#define HTEST_EXTERN
#include "htest.h"

HTEST_GLOBAL

int main(int argc, char* argv[])
{
    htest::test(argc, argv);
    return 0;
}


