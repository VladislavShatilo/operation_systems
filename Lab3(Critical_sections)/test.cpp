#include "pch.h"
#include "../OsLab3/main.h"

TEST(TestCaseName, Test1) {
    prm parameters;
    parameters.array_size = 2;
    parameters.arr = new int[parameters.array_size] {4, 3};
    parameters.x = 4;
    InitializeCriticalSection(&parameters.count_element_critical_section);

    const HANDLE count_element = CreateThread(nullptr, 0, count_element_func, &parameters, 0, nullptr);
    if (count_element == nullptr)
    {
        EXPECT_FALSE(false);
    }
    SetEvent(parameters.start);
    WaitForSingleObject(count_element, INFINITE);

    
   EXPECT_EQ(parameters.counts, 1);

}

TEST(TestCaseName, Test2) {
    prm parameters;
    parameters.array_size = 6;
    parameters.arr = new int[parameters.array_size] {1, 3, 3, 3, 3, 4};
    parameters.x = 3;
    InitializeCriticalSection(&parameters.count_element_critical_section);

    const HANDLE count_element = CreateThread(nullptr, 0, count_element_func, &parameters, 0, nullptr);
    if (count_element == nullptr)
    {
        EXPECT_FALSE(false);
    }
    SetEvent(parameters.start);
    WaitForSingleObject(count_element, INFINITE);


    EXPECT_EQ(parameters.counts, 2);

}

TEST(TestCaseName, Test3) {
    prm parameters;
    parameters.array_size = 6;
    parameters.arr = new int[parameters.array_size] {1, 3, 3, 3, 3, 4};
    parameters.x = 3;
    const std::vector<int> result = { 3,3,3,3,1,4 };
    InitializeCriticalSection(&parameters.work_critical_section);
    const HANDLE work = CreateThread(nullptr, 0, work_func, &parameters, 0, nullptr);
    if (work == nullptr)
    {
        EXPECT_FALSE(false);
    }
    SetEvent(parameters.start);
    WaitForSingleObject(work, INFINITE);

    EXPECT_EQ(parameters.new_vector ,result);

}
TEST(TestCaseName, Test4) {
    prm parameters;
    parameters.array_size = 8;
    parameters.arr = new int[parameters.array_size] {9, 3, 4, 6, 7, 3, 3, 4};
    parameters.x = 3;
    const std::vector<int> result = { 3,3,3,9,4,6,7,4 };
    InitializeCriticalSection(&parameters.work_critical_section);
    const HANDLE work = CreateThread(nullptr, 0, work_func, &parameters, 0, nullptr);
    if (work == nullptr)
    {
        EXPECT_FALSE(false);
    }
    SetEvent(parameters.start);
    WaitForSingleObject(work, INFINITE);
   

    EXPECT_EQ(parameters.new_vector, result);

}