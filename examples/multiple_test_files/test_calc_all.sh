rm ut_calc_all

g++ -o ut_calc_all ../../htest/htest.cpp ut_calc.cpp ut_vcalc.cpp ../test_target/Calc.cpp -I../../htest

./ut_calc_all

