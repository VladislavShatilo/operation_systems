#include "pch.h"
#include "CppUnitTest.h"
#include "../client/client.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_test2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            const auto arr = new double[2] {16,25};
            sqrt_n(2, 0,arr);
            const auto exp_arr = new double[2] {4,5};
            for(int i = 0; i<2;i++)
            {
                Assert::IsTrue(arr[i] == exp_arr[i]);
            }

		}
        TEST_METHOD(TestMethod2)
        {
            const auto arr = new double[3] {16, 25,19.36};
            sqrt_n(3, 0, arr);
            const auto exp_arr = new double[3] {4, 5,4.4};
            for (int i = 0; i < 3; i++)
            {
                Assert::IsTrue(arr[i] == exp_arr[i]);
            }

        }
        TEST_METHOD(TestMethod3)
        {
            const auto arr = new double[3] {16, 25,9};
            sqrt_n(3, 10, arr);
            const auto exp_arr = new double[3] {4, 5,9};
            for (int i = 0; i < 3; i++)
            {
                Assert::IsTrue(arr[i] == exp_arr[i]);
            }

        }
	    TEST_METHOD(TestMethod4)
        {
            const auto arr = new double[4] {16, 25, 9,225};
            sqrt_n(4, 10, arr);
            const auto exp_arr = new double[4] {4, 5, 9,15};
            for (int i = 0; i < 4; i++)
            {
                Assert::IsTrue(arr[i] == exp_arr[i]);
            }

        }
        TEST_METHOD(TestMethod5)
        {
            const auto arr = new double[4] {16, 25, 9, 225};
            std::vector<double>v1;
            const  std::vector<double> exp_vector = { 16,25,225 };
            great_n(4, 10,v1, arr);
          
            Assert::IsTrue(v1 == exp_vector);

        }
        TEST_METHOD(TestMethod6)
        {
            const auto arr = new double[7] {16, 25, 9, 225,11.23,24,21};
            std::vector<double>v1;
            const  std::vector<double> exp_vector = { 225 };
            great_n(7, 25, v1, arr);

            Assert::IsTrue(v1 == exp_vector);

        }

	};
}
