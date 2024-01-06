#include "pch.h"
#include "../Count/Count.h"
#include "../Child/child.h"
TEST(TestCaseName, Count) {
  EXPECT_EQ(fibonacci(12), 144);
  EXPECT_EQ(fibonacci(10), 55);
  EXPECT_EQ(fibonacci(0), 0);
}

TEST(TestCaseName, child) {
    constexpr double arr[5] = { 1.1,2.2,3.3,4.4,5.5 };
    const std::vector<double> except_result = { 1.1,2.2,3.3,4.4 };
    std::vector<double> result;
    std::string creator_cmd = "Child.exe " + std::to_string(5) + " ";

    fill_result(arr, 5, result);
    EXPECT_EQ(get_result(result) ,except_result);
}