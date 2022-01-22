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
#include <setjmp.h>
namespace htest
{
#ifdef WIN32
    static bool bUseColor = false;
#else
    static bool bUseColor = true;
#endif

#ifdef HTEST_EXTERN
#define __htest_decl_global extern
#else
#define __htest_decl_global 
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
    __htest_decl_global jmp_buf g_jump_buffer;
    
    static void SetColor(const TextColor_e eColor){
        if(bUseColor){
            std::cout << "\033[0;" << eColor << "m";
        }
    }
    static void PrintColorText(const std::string strText, const TextColor_e eColor){
        SetColor(eColor);
        std::cout << strText;
        SetColor(TextColor_e::RESET);
    }
    static std::ostream& NumTests(const size_t num_tests){
        std::cout << num_tests;
        if(num_tests > 1U){
            std::cout << " tests";
        }else{
            std::cout << " test";
        }
        return std::cout;
    }
    class AssertionStream{
    public:
        AssertionStream(const bool bVerbose=true, const bool bAbort=false, const bool bChained=false):
            m_bVerbose(bVerbose), m_bAbort(bAbort), m_bChained(bChained)
        {            
        }
        ~AssertionStream(){
            if(!m_bChained && m_bAbort){
                longjmp(g_jump_buffer, -1);
            }
        }
        template<typename _T>
        AssertionStream operator<<(_T msg){
            if(m_bVerbose){
                std::cout << msg;
            }
            m_bChained = true;
            return AssertionStream(m_bVerbose, m_bAbort);
        }
        // for std::endl
        AssertionStream operator <<(std::ostream& (*os)(std::ostream&)){
            if(m_bVerbose){
                std::cout << os;
            }
            m_bChained = true;
            return AssertionStream(m_bVerbose, m_bAbort);
        }
    protected:
        bool m_bVerbose;
        bool m_bAbort;
        bool m_bChained;    // This flag is set true if this stream is followed by another output message.
    };

    class Test
    {
    public:
        Test(){
            m_bHTestPassed = true;
        }
    protected:
        virtual void SetUp(){}
        virtual void TearDown(){}
        virtual void TestBody(){}
        std::string _get_test_case_name(){return m_strHTestTestCaseName;}
        bool _is_test_passed(){return m_bHTestPassed;}
        void _print_line(const int line, const char* file){
            std::cout << "At line " << line << " in " << file << std::endl;
        }
        template<typename _T>
        void _print_value(const char* n, const _T v){
            std::cout << n << " (" << v << ")";
        }
        template<typename _T1, typename _T2>
        AssertionStream _assert_eq(const int line, const char* file, const char* n1, const char* n2, const _T1 v1, const _T2 v2, const bool bAbort){
            if(v1 != v2){
                m_bHTestPassed = false;
                _print_line(line, file);
                _print_value(n1, v1); std::cout << " != "; _print_value(n2, v2); std::cout << "\n";                
                return AssertionStream(true, bAbort);
            }
            return AssertionStream(false);
        }

        template<typename _T1, typename _T2>
        AssertionStream _assert_gt(const int line, const char* file, const char* n1, const char* n2, const _T1 v1, const _T2 v2, const bool bAbort){
            if(v1 <= v2){
                m_bHTestPassed = false;
                _print_line(line, file);
                _print_value(n1, v1); std::cout << " <= "; _print_value(n2, v2); std::cout << "\n";
                return AssertionStream(true, bAbort);
            }            
            return AssertionStream(false);
        }
        template<typename _T1, typename _T2>
        AssertionStream _assert_lt(const int line, const char* file, const char* n1, const char* n2, const _T1 v1, const _T2 v2, const bool bAbort){
            if(v1 >= v2){
                m_bHTestPassed = false;
                _print_line(line, file);
                _print_value(n1, v1); std::cout << " >= "; _print_value(n2, v2); std::cout << "\n";
                return AssertionStream(true, bAbort);
            }            
            return AssertionStream(false);
        }
        template<typename _T1, typename _T2, typename _T3>
        AssertionStream _assert_near(const int line, const char* file, const char* n1, const char* n2, const char* n3, const _T1 v1, const _T2 v2, const _T3 v3, const bool bAbort){
            if( ((v1 > v2) && (v1 - v2) > v3) || ((v2 > v1) && (v2 - v1) > v3) ) {
                m_bHTestPassed = false;
                _print_line(line, file);
                std::cout << "Diff btw "; _print_value(n1, v1); std::cout << " and "; _print_value(n2, v2); std::cout << " = " << (v1-v2) << " > "; _print_value(n3, v3); std::cout << "\n";
                return AssertionStream(true, bAbort);
            }
            return AssertionStream(false);
        }
        friend void test(const int argc, char** argv);
        std::string m_strHTestTestCaseName;
    private:
        bool m_bHTestPassed;
    };
    
    __htest_decl_global std::vector<Test*> g_oVectTest; // Test class instance list.
    static void parse_arguments(const int argc, char** argv){
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
    inline void test(const int argc=0, char** argv=nullptr){
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
            // if first run, perform test. Otherwise skip the test body because it's jumped from ASSERT_XX().
            if(setjmp(g_jump_buffer) == 0){
                t->TestBody();
            }
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
                htest::g_oVectTest.push_back(this);                                                   \
                m_strHTestTestCaseName = #test_suite_name"::"#test_name;                              \
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
    
    #define HTEST_GLOBAL namespace htest { \
        jmp_buf g_jump_buffer;             \
        std::vector<Test*> g_oVectTest;    \
    }                                      \

    #define HTEST_MAIN int main(int argc, char* argv[]) { \
        htest::test(argc, argv);                          \
        return 0;                                         \
    }                                                     \

}
#endif


