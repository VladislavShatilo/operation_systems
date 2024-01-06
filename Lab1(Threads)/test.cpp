#include "pch.h"
#include "gtest/gtest.h"
#include "../osLab1/ArrayWork.h"

TEST(TestArray, Test1) {
    array_work array_work(8);
    const std::vector<double> array = { 1.1,2.2, 3.3,4.4,5.5,6.6,7.7,8.8 };
    const std::vector<double> result = { 1.1,2.2, 3.3,4.4 };
    array_work.set_array(array);

    DWORD id_thread;
    const HANDLE worker = CreateThread(nullptr, 0, work_with_array, &array_work, 0, &id_thread);
    if (worker == nullptr)
    {
        ASSERT_FALSE(false);
    }
    WaitForSingleObject(worker, INFINITE);
    CloseHandle(worker);
    
    EXPECT_EQ(array_work.get_result() , result);
}

TEST(TestArray, Test2) {
    array_work array_work(10);
    const std::vector<double> array = { 2.3,1.0, 1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8 };
    const std::vector<double> result = { 2.3,1.0, 1.1,2.2, 3.3,4.4 };
    array_work.set_array(array);

    DWORD id_thread;
    const HANDLE worker = CreateThread(nullptr, 0, work_with_array, &array_work, 0, &id_thread);
    if (worker == nullptr)
    {
        ASSERT_FALSE(false);
    }
    WaitForSingleObject(worker, INFINITE);
   
    CloseHandle(worker);

    EXPECT_EQ(array_work.get_result(), result);
}
