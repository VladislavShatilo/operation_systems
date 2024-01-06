#include "pch.h"
#include "CppUnitTest.h"
#include "../OsLab3/main.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_test1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            prm parameters;
            parameters.array_size = 2;
            parameters.arr = new int[parameters.array_size]{4,3};
            parameters.x = 4;
            InitializeCriticalSection(&parameters.count_element_critical_section);
           
            const HANDLE count_element = CreateThread(nullptr, 0, count_element_func, &parameters, 0, nullptr);
            if (count_element == nullptr)
            {
                Assert::Fail();
            }
            SetEvent(parameters.start);
            WaitForSingleObject(count_element, INFINITE);
            
            Assert::IsTrue(parameters.counts == 1);
		  

		}

        TEST_METHOD(TestMethod2)
        {
            prm parameters;
            parameters.array_size = 6 ;
            parameters.arr = new int[parameters.array_size] {1,3,3,3,3,4};
            parameters.x = 3;
            InitializeCriticalSection(&parameters.count_element_critical_section);
            const HANDLE count_element = CreateThread(nullptr, 0, count_element_func, &parameters, 0, nullptr);
            if (count_element == nullptr)
            {
                Assert::Fail();
            }
            SetEvent(parameters.start);
            WaitForSingleObject(count_element, INFINITE);
            Assert::IsTrue(parameters.counts == 2);
          

        }
        TEST_METHOD(TestMethod3)
        {
            prm parameters;
            parameters.array_size = 6;
            parameters.arr = new int[parameters.array_size] {1, 3, 3, 3, 3, 4};
            parameters.x = 3;
            const std::vector<int> result = { 3,3,3,3,1,4 };
            InitializeCriticalSection(&parameters.work_critical_section);
            const HANDLE work = CreateThread(nullptr, 0, work_func, &parameters, 0, nullptr);
            if (work == nullptr)
            {
                Assert::Fail();
            }
            SetEvent(parameters.start);
            WaitForSingleObject(work, INFINITE);
            Assert::IsTrue(parameters.new_vector == result);
         

        }

        TEST_METHOD(TestMethod4)
        {
            prm parameters;
            parameters.array_size = 8;
            parameters.arr = new int[parameters.array_size] {9,3,4,6,7,3,3,4};
            parameters.x = 3;
            const std::vector<int> result = { 3,3,3,9,4,6,7,4 };
            InitializeCriticalSection(&parameters.work_critical_section);
            const HANDLE work = CreateThread(nullptr, 0, work_func, &parameters, 0, nullptr);
            if (work == nullptr)
            {
                Assert::Fail();
            }
            SetEvent(parameters.start);
            WaitForSingleObject(work, INFINITE);
            Assert::IsTrue(parameters.new_vector == result);
          

        }

	};
}
