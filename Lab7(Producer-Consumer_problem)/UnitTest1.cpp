#include "pch.h"
#include "CppUnitTest.h"
#include "../OsLab7/FileName.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_test1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            std::thread producer1(producer, 1);
            std::thread producer2(producer, 2);
            std::thread producer3(producer, 3);

            std::thread consumer1(consumer, 1);
            std::thread consumer2(consumer, 2);
            std::thread consumer3(consumer, 3);

            producer1.join();
            producer2.join();
            producer3.join();
         
            consumer1.join();
            consumer2.join();
            consumer3.join();

            Assert::IsTrue(buffer.size() == 0);

		}

        TEST_METHOD(TestMetho2)
        {
            std::thread producer1(producer, 1);
            std::thread producer2(producer, 2);
            std::thread producer3(producer, 3);
            std::thread producer4(producer, 4);

            std::thread consumer1(consumer, 1);
            std::thread consumer2(consumer, 2);
            std::thread consumer3(consumer, 3);
            std::thread consumer4(consumer, 4);

            producer1.join();
            producer2.join();
            producer3.join();
            producer4.join();

            consumer1.join();
            consumer2.join();
            consumer3.join();
		    consumer4.join();

            Assert::IsTrue(buffer.size() == 0);

        }
	};
}
