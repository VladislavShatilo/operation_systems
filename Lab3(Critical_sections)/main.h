#pragma once
#include<iostream>
#include<windows.h>
#include <random>
#include<vector>
struct prm {
    int counts = 0;
    int array_size;
    int x;
    int* arr;
    HANDLE start;
    int time_chilling;
    CRITICAL_SECTION work_critical_section;
    CRITICAL_SECTION count_element_critical_section;
    std::vector<int> new_vector;

    prm() : array_size(0), x(0), arr(nullptr), time_chilling(0)
    {
        InitializeCriticalSection(&work_critical_section);
        InitializeCriticalSection(&count_element_critical_section);
        start = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    }
    ~prm()
    {
        delete[]arr;
        DeleteCriticalSection(&work_critical_section);
        DeleteCriticalSection(&count_element_critical_section);
        CloseHandle(start);
    }



};


inline DWORD WINAPI count_element_func(const LPVOID prm_t)
{
    const auto parameters = static_cast<prm*>(prm_t);
    WaitForSingleObject(parameters->start, INFINITE);
    EnterCriticalSection(&parameters->count_element_critical_section);
    for (int i = 0; i < parameters->array_size; i++)
    {
        if (parameters->arr[i] != parameters->x)
        {
            parameters->counts++;
        }
    }
    LeaveCriticalSection(&parameters->count_element_critical_section);

    return 0;
}

inline DWORD WINAPI work_func(const LPVOID prm_t)
{
    const auto parameters = static_cast<prm*>(prm_t);
    EnterCriticalSection(&parameters->work_critical_section);
    WaitForSingleObject(parameters->start, INFINITE);
    for (int i = 0; i < parameters->array_size; i++)
    {
        if (parameters->arr[i] == parameters->x)
        {
            parameters->new_vector.push_back(parameters->arr[i]);
            Sleep(parameters->time_chilling);

        }

    }
    for (int i = 0; i < parameters->array_size; i++)
    {
        if (parameters->arr[i] != parameters->x)
        {
            parameters->new_vector.push_back(parameters->arr[i]);
            Sleep(parameters->time_chilling);
        }
    }
    LeaveCriticalSection(&parameters->work_critical_section);

    return 0;
}
