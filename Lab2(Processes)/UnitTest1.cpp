#include "pch.h"
#include "CppUnitTest.h"
#include "../Count/Count.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_test1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            Assert::IsTrue(fibonacci(12) == 144);
		}
        TEST_METHOD(TestMethod2)
        {
            Assert::IsTrue(fibonacci(10) == 55);
        }
        TEST_METHOD(TestMethod3)
        {
            Assert::IsTrue(fibonacci(0) == 0);
        }


	};
}
