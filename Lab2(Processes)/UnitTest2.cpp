#include "pch.h"
#include "CppUnitTest.h"
#include "../Child/child.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_test2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            
            constexpr double arr[5] = { 1.1,2.2,3.3,4.4,5.5 };
            const std::vector<double> except_result = { 1.1,2.2,3.3,4.4 };
            std::vector<double> result;
            std::string creator_cmd = "Child.exe " + std::to_string(5) + " ";

            fill_result(arr, 5, result);
            Assert::IsTrue(get_result(result) == except_result);

            
		}
        TEST_METHOD(TestMethod2)
        {
            constexpr double arr[8] = { 1.0,1.1,2.2,3.3,4.4,5.5,56.7,235.32 };
            const std::vector<double> except_result = {1.0, 1.1,2.2,3.3,4.4,235.32};
            std::vector<double> result;
            std::string creator_cmd = "Child.exe " + std::to_string(5) + " ";

            fill_result(arr, 8, result);
            Assert::IsTrue(get_result(result) == except_result);


        }
	};
}
