#include "pch.h"
#include "../OsLab7/main.h"
TEST(TestCaseName, TestName) {
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

   
  EXPECT_EQ(buffer.size(), 0);
 
}
TEST(TestCaseName, TestName1) {
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

    EXPECT_EQ(buffer.size(), 0);
}