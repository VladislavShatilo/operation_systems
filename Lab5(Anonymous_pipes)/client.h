#pragma once
#include<iostream>
#include<string>
#include<windows.h>
#include<vector>
#include<conio.h>


inline void sqrt_n(const int array_size, const int n, double* arr)
{
    for (int i = 0; i < array_size; i++)
    {
        if (arr[i] > n)
        {
            arr[i] = sqrt(arr[i]);

        }
    }
}

inline void great_n(const int array_size, const int n, std::vector<double>& res, const double* arr)
{
    for (int i = 0; i < array_size; i++)
    {
        if (arr[i] > n)
        {
            res.push_back(arr[i]);

        }
    }
}