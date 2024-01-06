#include "pch.h"
#include"../OsLab6/main.h"
TEST(TestCaseName, TestName) {
    prm parameters;
    parameters.array_size = 5;
    parameters.arr = new int[parameters.array_size] {1, 2, 3, 3, 5};
    parameters.x = 3;
    count_element_func(parameters);
    EXPECT_EQ(parameters.counts,3);
 
}
TEST(TestCaseName, TestName1) {
    prm parameters;
    parameters.array_size = 7;
    parameters.arr = new int[parameters.array_size] {1, 2, 3, 3, 5, 3, 5};
    parameters.x = 3;
    count_element_func(parameters);
    EXPECT_EQ(parameters.counts, 4);

}
TEST(TestCaseName, TestName2) {
    prm parameters;
    parameters.array_size = 7;
    parameters.arr = new int[parameters.array_size] {1, 2, 3, 3, 5, 3, 5};
    parameters.x = 3;
    work_func(parameters);
    const std::vector<int> exp_vec = { 3,3,3,1,2,5,5 };
    EXPECT_EQ(parameters.new_vector , exp_vec);

}