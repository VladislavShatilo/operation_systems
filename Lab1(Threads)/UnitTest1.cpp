#include "pch.h"
#include "CppUnitTest.h"
#include"../osLab1/FileName2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_test1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            
            array_work array_work(8);
            const std::vector<double> array = {1.1,2.2, 3.3,4.4,5.5,6.6,7.7,8.8};
            const std::vector<double> result = { 1.1,2.2, 3.3,4.4 };
            array_work.set_array(array);
                
            DWORD id_thread;
            const HANDLE worker = CreateThread(nullptr, 0, work_with_array, &array_work, 0, &id_thread);
            if (worker == nullptr)
            {
                Assert::Fail();
            }       
            WaitForSingleObject(worker, INFINITE);
            CloseHandle(worker);
          
            Assert::IsTrue(array_work.get_result() == result);
         
		}
        TEST_METHOD(TestMethod2)
        {
            array_work array_work(10);
            const std::vector<double> array = {2.3,1.0, 1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8 };
            const std::vector<double> result = { 2.3,1.0, 1.1,2.2, 3.3,4.4 };
            array_work.set_array(array);

            DWORD id_thread;
            const HANDLE worker = CreateThread(nullptr, 0, work_with_array, &array_work, 0, &id_thread);
            if (worker == nullptr)
            {
                Assert::Fail();
            }
            WaitForSingleObject(worker, INFINITE);
            CloseHandle(worker);

            Assert::IsTrue(array_work.get_result() == result);

        }
	};
}
