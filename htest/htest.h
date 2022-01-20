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
#include <chrono>
namespace htest
{
#ifdef WIN32
    static bool bUseColor = false;
#else
    static bool bUseColor = true;
#endif
    const std::string strMarkerInfo   = "[============] ";
    const std::string strMarkerRUN    = "[ RUN        ] ";
    const std::string strMarkerOK     = "[         OK ] ";
    const std::string strMarkerFAIL   = "[       FAIL ] ";
    const std::string strMarkerPASSED = "[   PASSED   ] ";
    const std::string strMarkerFAILED = "[   FAILED   ] ";
    const std::string strMarkerIndent = "               ";
    enum TextColor_e
    {
        RESET = 0,
        BLACK = 30,
        RED = 31,
        GREEN = 32,
        YELLOW = 33,
        BLUE = 34,
        MAGENTA = 35,
        CYAN = 36,
        WHITE = 37
    };
    void SetColor(const TextColor_e eColor){
        if(bUseColor){
            std::cout << "\033[0;" << eColor << "m";
        }
    }
    void PrintColorText(const std::string strText, const TextColor_e eColor){
        SetColor(eColor);
        std::cout << strText;
        SetColor(TextColor_e::RESET);
    }
    std::ostream& NumTests(const size_t num_tests){
        std::cout << num_tests;
        if(num_tests > 1U){
            std::cout << " tests";
        }else{
            std::cout << " test";
        }
        return std::cout;
    }
    class OutputStream{
    public:
        OutputStream(const bool bVerbose=true){
            m_bVerbose = bVerbose;
        }
        template<typename _T>
        OutputStream operator<<(_T msg){
            if(m_bVerbose){
                std::cout << msg;
            }
            return *this;
        }
    private:
        bool m_bVerbose;
    };

    class Test
    {
    public:
        virtual void SetUp(){}
        virtual void TearDown(){}
        virtual void TestBody(){}
        std::string _get_test_case_name(){return m_strTestCaseName;}
        bool _is_test_passed(){return m_bPassed;}
        void _print_line(const int line, const char* file){
            std::cout << "At line " << line << " in " << file << std::endl;
        }
        template<typename _T>
        void _print_value(const char* n, const _T v){
            std::cout << n << " (" << v << ")";
        }
        template<typename _T1, typename _T2>
        OutputStream _assert_eq(const int line, const char* file, const char* n1, const char* n2, const _T1 v1, const _T2 v2, const bool bTerminate){
            if(v1 != v2){
                m_bPassed = false;
                _print_line(line, file);
                _print_value(n1, v1); std::cout << " != "; _print_value(n2, v2); std::cout << "\n";
                if(bTerminate){
                    PrintColorText(strMarkerFAILED, TextColor_e::RED);
                    exit(-1);
                }
                OutputStream out(true);
                return out;
            }
            OutputStream out(false);
            return out;
        }

        template<typename _T1, typename _T2>
        OutputStream _assert_gt(const int line, const char* file, const char* n1, const char* n2, const _T1 v1, const _T2 v2, const bool bTerminate){
            if(v1 <= v2){
                m_bPassed = false;
                _print_line(line, file);
                _print_value(n1, v1); std::cout << " <= "; _print_value(n2, v2); std::cout << "\n";
                if(bTerminate){
                    PrintColorText(strMarkerFAILED, TextColor_e::RED);
                    exit(-1);
                }
                OutputStream out(true);
                return out;
            }
            OutputStream out(false);
            return out;
        }
        template<typename _T1, typename _T2>
        OutputStream _assert_lt(const int line, const char* file, const char* n1, const char* n2, const _T1 v1, const _T2 v2, const bool bTerminate){
            if(v1 >= v2){
                m_bPassed = false;
                _print_line(line, file);
                _print_value(n1, v1); std::cout << " >= "; _print_value(n2, v2); std::cout << "\n";
                if(bTerminate){
                    PrintColorText(strMarkerFAILED, TextColor_e::RED);
                    exit(-1);
                }
                OutputStream out(true);
                return out;
            }
            OutputStream out(false);
            return out;
        }
        template<typename _T1, typename _T2, typename _T3>
        OutputStream _assert_near(const int line, const char* file, const char* n1, const char* n2, const char* n3, const _T1 v1, const _T2 v2, const _T3 v3, const bool bTerminate){
            if( ((v1 > v2) && (v1 - v2) > v3) || ((v2 > v1) && (v2 - v1) > v3) ) {
                m_bPassed = false;
                _print_line(line, file);
                std::cout << "Diff btw "; _print_value(n1, v1); std::cout << " and "; _print_value(n2, v2); std::cout << " = " << (v1-v2) << " > "; _print_value(n3, v3); std::cout << "\n";
                if(bTerminate){
                    PrintColorText(strMarkerFAILED, TextColor_e::RED);
                    exit(-1);
                }
                OutputStream out(true);
                return out;
            }
            OutputStream out(false);
            return out;
        }
    protected:
        std::string m_strTestCaseName;
        bool m_bPassed;
    };
    std::vector<Test*> g_oVectTest; // Test class instance list.
    void parse_arguments(const int argc, const char* const argv[]){
        for(int i=0;i<argc;i++){
            std::string strArg(argv[i]);
            const std::string argHeader = "--htest_";
            if(strArg.substr(0, argHeader.length()) == argHeader){                    
                size_t nPosEq = strArg.find("=");
                if(nPosEq != std::string::npos){
                    const std::string strParam = strArg.substr(argHeader.length(), nPosEq-argHeader.length());
                    const std::string strValue = strArg.substr(nPosEq+1);
                    if("color"==strParam){
                        if("yes"==strValue){
                            bUseColor=true;
                        }else if("no"==strValue){
                            bUseColor=true;
                        }
                    }
                }
            }
        }
    }
    void test(const int argc=0, const char* const argv[]=nullptr){
        parse_arguments(argc, argv);
        const size_t num_tests = g_oVectTest.size();
        PrintColorText(strMarkerInfo, TextColor_e::GREEN);

        std::cout << "Running ";
        NumTests(num_tests) << std::endl;

        size_t num_passed = 0U;
        const std::chrono::high_resolution_clock::time_point start_test_suite = std::chrono::high_resolution_clock::now();
        for(Test* t : g_oVectTest){
            PrintColorText(strMarkerRUN, TextColor_e::GREEN);
            std::cout << t->_get_test_case_name() << std::endl;

            const std::chrono::high_resolution_clock::time_point start_test = std::chrono::high_resolution_clock::now();
            t->SetUp();
            t->TestBody();
            t->TearDown();
            const std::chrono::duration<float> duration_test = std::chrono::high_resolution_clock::now() - start_test;

            if(t->_is_test_passed()){
                num_passed++;
                PrintColorText(strMarkerOK, TextColor_e::GREEN);
            }else{
                PrintColorText(strMarkerFAIL, TextColor_e::RED);
            }
            std::cout << t->_get_test_case_name() << " (" << static_cast<int>(duration_test.count() * 1000.0F) << ")\n";
        }
        const std::chrono::duration<float> duration_test_suite = std::chrono::high_resolution_clock::now() - start_test_suite;

        PrintColorText(strMarkerInfo, TextColor_e::GREEN);
        NumTests(num_tests);
        std::cout << " ran. (" << static_cast<int>(duration_test_suite.count() * 1000.0F) << " ms total)\n";

        PrintColorText(strMarkerPASSED, TextColor_e::GREEN);
        NumTests(num_passed) << std::endl;
        const size_t num_failed = num_tests - num_passed;
        if(num_failed > 0){
            PrintColorText(strMarkerFAILED, TextColor_e::RED);
            NumTests(num_failed);
            std::cout << " listed below.\n";
            for(Test* t : g_oVectTest){
                if(!t->_is_test_passed()){
                    PrintColorText(strMarkerFAILED, TextColor_e::RED);
                    std::cout << t->_get_test_case_name() << std::endl;
                }
            }
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

    #define EXPECT_EQ(x, y)        _assert_eq(__LINE__, __FILE__, #x, #y, x, y, false)
    #define EXPECT_TRUE(x)         _assert_eq(__LINE__, __FILE__, #x, "true", x, true, false)
    #define EXPECT_FALSE(x)        _assert_eq(__LINE__, __FILE__, #x, "false", x, false, false)
    #define EXPECT_FLOAT_EQ(x, y)  _assert_near(__LINE__, __FILE__, #x, #y, "FLT_EPSILON", x, y, FLT_EPSILON, false)
    #define EXPECT_NEAR(x, y, eps) _assert_near(__LINE__, __FILE__, #x, #y, #eps, x, y, eps, false)
    #define EXPECT_LT(x, y)        _assert_lt(__LINE__, __FILE__, #x, #y, x, y, false)
    #define EXPECT_GT(x, y)        _assert_gt(__LINE__, __FILE__, #x, #y, x, y, false)

    #define ASSERT_EQ(x, y)        _assert_eq(__LINE__, __FILE__, #x, #y, x, y, true)
    #define ASSERT_TRUE(x)         _assert_eq(__LINE__, __FILE__, #x, "true", x, true, true)
    #define ASSERT_FALSE(x)        _assert_eq(__LINE__, __FILE__, #x, "false", x, false, true)
    #define ASSERT_FLOAT_EQ(x, y)  _assert_near(__LINE__, __FILE__, #x, #y, "FLT_EPSILON", x, y, FLT_EPSILON, true)
    #define ASSERT_NEAR(x, y, eps) _assert_near(__LINE__, __FILE__, #x, #y, #eps, x, y, eps, true)
    #define ASSERT_LT(x, y)        _assert_lt(__LINE__, __FILE__, #x, #y, x, y, true)
    #define ASSERT_GT(x, y)        _assert_gt(__LINE__, __FILE__, #x, #y, x, y, true)
}
#endif


