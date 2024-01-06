#pragma once
#include <iostream>
#include<windows.h>
#include <vector>

inline void fill_result(const double* arr, const int size, std::vector<double>& result)
{
    for (int i = 0; i < size; i++)
    {
        if (abs(static_cast<int>(arr[i] * 10)) % 10 < 5)
        {
            result.push_back(arr[i]);
        }
        Sleep(25);
    }
}

inline std::vector<double> get_result(std::vector<double>& result)
{
    return result;
}