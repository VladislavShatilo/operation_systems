#pragma once
#include<iostream>
#include<windows.h>
#include<vector>
#include<thread>
#include <condition_variable>
#include<mutex>
#include <random>



struct prm {
    int counts = 0;
    int array_size;
    int x;
    int* arr;
    int time_chilling;
    std::condition_variable_any cv;
    std::condition_variable_any cv1;
    std::vector<int> new_vector;
    std::mutex mtx;

    prm() : array_size(0), x(0), arr(nullptr), time_chilling(0)
    {

    }
    ~prm()
    {
        delete[]arr;

    }

};


inline void count_element_func(prm& parameters)
{
    for (int i = 0; i < parameters.array_size; i++)
    {
        if (parameters.arr[i] != parameters.x)
        {
            parameters.counts++;
        }
    }
    parameters.cv1.notify_one();
}

inline void work_func(prm& parameters)
{
    for (int i = 0; i < parameters.array_size; i++)
    {
        if (parameters.arr[i] == parameters.x)
        {
            parameters.new_vector.push_back(parameters.arr[i]);
            Sleep(parameters.time_chilling);
        }
    }
    for (int i = 0; i < parameters.array_size; i++)
    {
        if (parameters.arr[i] != parameters.x)
        {
            parameters.new_vector.push_back(parameters.arr[i]);
            Sleep(parameters.time_chilling);
        }
    }
    parameters.cv.notify_one();

}