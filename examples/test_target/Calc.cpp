#include "Calc.h"

int Calc::add(const int x, const int y)
{
    return x + y;
}

int Calc::sub(const int x, const int y)
{
    return x + y;       // Intentional bug!
}

int Calc::mul(const int x, const int y)
{
    return x * y;
}

int Calc::div(const int x, const int y)
{
    return x / y;
}

void Calc::vadd(std::vector<int>& x, std::vector<int>& y, std::vector<int>& z)
{
    z.clear();
    if(x.size() == y.size()){
        for(size_t i = 0U; i < x.size(); i++){
            z.push_back(x[i] + y[i]);
        }
    }
}

void Calc::vsub(std::vector<int>& x, std::vector<int>& y, std::vector<int>& z)
{
    z.clear();
    if(x.size() == y.size()){
        for(size_t i = 0U; i < x.size(); i++){
            z.push_back(x[i] - y[i]);
        }
    }
}

void Calc::vmul(std::vector<int>& x, std::vector<int>& y, std::vector<int>& z)
{
    z.clear();
    if(x.size() == y.size()){
        for(size_t i = 0U; i < x.size(); i++){
            z.push_back(x[i] * y[i]);            
        }
    }

    z.clear();  // Intentional bug!
}

void Calc::vdiv(std::vector<int>& x, std::vector<int>& y, std::vector<int>& z)
{
    z.clear();
    if(x.size() == y.size()){
        for(size_t i = 0U; i < x.size(); i++){
            
            if(y[i] == 0){
                z.push_back(x[i] / y[i]);   // Intentional bug!
            }else{
                z.push_back(0);
            }
        }
    }
}


