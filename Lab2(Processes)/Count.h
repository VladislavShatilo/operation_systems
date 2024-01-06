#pragma once
#include<iostream>
#include<windows.h>

inline long long fibonacci(const int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}