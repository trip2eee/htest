/**
 * @file   htest.h
 * @author Jongmin Park
 * @date   20 Jan 2022
 * @brief  Very simple C++ unit test library.
*/

#ifndef __HTEST_H__
#define __HTEST_H__

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cfloat>
namespace htest
{
    class Test
    {
    public:
        virtual void SetUp(){}
        virtual void TearDown(){}
        virtual void TestBody(){}
        virtual void PrintResult(){
            if(m_bPassed){
                std::cout << "\033[0;32m" << " [PASS]\n";
                std::cout << "\033[0;0m";   // reset color.
            }else{
                std::cout << "\033[0;31m" << " [FAIL]\n";
                std::cout << "\033[0;0m";   // reset color.
            }
        }
        std::string GetTestCaseName(){return m_strTestCaseName;}
        bool IsPassed(){return m_bPassed;}
    protected:
        std::string m_strTestCaseName;
        bool m_bPassed;
    };

    std::vector<Test*> g_oVectTest;

    void test()
    {
        std::cout << "Start tests\n";

        size_t num_tests = 0U;
        size_t num_passed = 0U;

        for(Test* t : g_oVectTest){
            std::cout << "\033[0;33m" << t->GetTestCaseName() << std::endl;
            std::cout << "\033[0;0m";   // reset color.
            t->SetUp();
            t->TestBody();
            t->TearDown();
            t->PrintResult();
            num_tests ++;
            if(t->IsPassed()){
                num_passed++;
            }
        }
        if(num_tests > 1U){
            std::cout << num_tests << " Tests Done\n";
        }else{
            std::cout << num_tests << " Test Done\n";
        }
        if(num_passed == num_tests){
            if(num_tests > 1){
                std::cout << "\033[0;32m" << num_tests << " Tests PASSED\n";
            }else{
                std::cout << "\033[0;32m" << num_tests << " Test PASSED\n";
            }

            std::cout << "\033[0;0m";   // reset color.
        }
        else{
            const size_t num_failed = num_tests - num_passed;
            if(num_failed > 1U){
                std::cout << "\033[0;31m" << num_failed << " Tests FAILED\n";
            }else{
                std::cout << "\033[0;31m" << num_failed << " Test FAILED\n";
            }
            std::cout << "\033[0;0m";   // reset color.
        }     
    }
    
    #define HTEST_CLASS_NAME(test_suite_name, __test_name) test_suite_name##__test_name
    #define HTEST_INSTANCE_NAME(test_suite_name, __test_name) o##test_suite_name##__test_name
    
    #define HTEST_TEST(test_suite_name, test_name, parent_class)                                      \
        class HTEST_CLASS_NAME(test_suite_name, test_name) : public parent_class {                    \
        public:                                                                                       \
            HTEST_CLASS_NAME(test_suite_name, test_name)(){                                           \
                m_bPassed = true;                                                                     \
                htest::g_oVectTest.push_back(this);                                                   \
                m_strTestCaseName = #test_suite_name"::"#test_name;                                   \
            }                                                                                         \
            virtual void TestBody() override;                                                         \
        };                                                                                            \
        HTEST_CLASS_NAME(test_suite_name, test_name) HTEST_INSTANCE_NAME(test_suite_name, test_name); \
        void HTEST_CLASS_NAME(test_suite_name, test_name)::TestBody()                                 \

    #define TEST(test_suite_name, test_case_name) HTEST_TEST(test_suite_name, test_case_name, htest::Test)
    #define TEST_F(test_suite_name, test_case_name) HTEST_TEST(test_suite_name, test_case_name, test_suite_name)

    #define EXPECT_EQ(x, y) if((x) != (y)) {                                                                                        \
        m_bPassed = false;                                                                                                          \
        std::cout << #x << "(" << (x) << ") != " << #y << "(" << (y) << ") at line " << __LINE__ << " in " << __FILE__ << std::endl;\
    }                                                                                                                               \

    #define EXPECT_FLOAT_EQ(x, y) if(fabsf((x) - (y)) > FLT_EPSILON){                                                               \
        m_bPassed = false;                                                                                                          \
        std::cout << #x << "(" << (x) << ") != " << #y << "(" << (y) << ") at line " << __LINE__ << " in " << __FILE__ << std::endl;\
    }                                                                                                                               \

    #define EXPECT_NEAR(x, y, eps) if(fabsf((x) - (y)) > (eps)){                                                                    \
        m_bPassed = false;                                                                                                          \
        std::cout << #x << "(" << (x) << ") !~ " << #y << "(" << (y) << ") at line " << __LINE__ << " in " << __FILE__ << std::endl;\
    }                                                                                                                               \

    #define EXPECT_LT(x, y) if((x) >= (y)){                                                                                         \
        m_bPassed = false;                                                                                                          \
        std::cout << #x << "(" << (x) << ") >= " << #y << "(" << (y) << ") at line " << __LINE__ << " in " << __FILE__ << std::endl;\
    }                                                                                                                               \

    #define EXPECT_GT(x, y) if((x) <= (y)) {                                                                                        \
        m_bPassed = false;                                                                                                          \
        std::cout << #x << "(" << (x) << ") <= " << #y << "(" << (y) << ") at line " << __LINE__ << " in " << __FILE__ << std::endl;\
    }                                                                                                                               \

}

#endif

