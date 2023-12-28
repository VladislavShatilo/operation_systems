#include "pch.h"
#include "CppUnitTest.h"
#include "../OsLab6/FileName.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_test1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            prm parameters;
            parameters.array_size = 5;
            parameters.arr = new int[parameters.array_size] {1, 2, 3,3,5};
            parameters.x = 3;
            count_element_func(parameters);
            Assert::IsTrue(parameters.counts == 3);

		}
        TEST_METHOD(TestMethod2)
        {
            prm parameters;
            parameters.array_size = 7;
            parameters.arr = new int[parameters.array_size] {1, 2, 3, 3, 5,3,5};
            parameters.x = 3;
            count_element_func(parameters);
            Assert::IsTrue(parameters.counts == 4);

        }

        TEST_METHOD(TestMethod3)
        {
            prm parameters;
            parameters.array_size = 7;
            parameters.arr = new int[parameters.array_size] {1, 2, 3, 3, 5, 3, 5};
            parameters.x = 3;
            work_func(parameters);
            const std::vector<int> exp_vec = { 3,3,3,1,2,5,5 };
            Assert::IsTrue(parameters.new_vector == exp_vec);

        }
	};
}
