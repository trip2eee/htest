#ifndef __CALC_H__
#define __CALC_H__

#include <vector>

class Calc
{
public:
    // scalar calculations.
    int add(const int x, const int y);
    int sub(const int x, const int y);
    int mul(const int x, const int y);
    int div(const int x, const int y);

    // vector calculations.
    void vadd(std::vector<int>& x, std::vector<int>& y, std::vector<int>& z);
    void vsub(std::vector<int>& x, std::vector<int>& y, std::vector<int>& z);
    void vmul(std::vector<int>& x, std::vector<int>& y, std::vector<int>& z);
    void vdiv(std::vector<int>& x, std::vector<int>& y, std::vector<int>& z);
};

#endif


