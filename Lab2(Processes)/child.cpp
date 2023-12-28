#include <iostream>
#include<string>
#include<windows.h>
#include<conio.h>
#include <vector>

void fill_result(const double* arr, const int size,std::vector<double>& result)
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

std::vector<double> get_result(std::vector<double>& result)
{
    return result;
}

int main(int argc, char* argv[])
{
    std::vector<double> result;
    const int size = std::stoi(argv[1]);
    const auto arr = new double[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = std::stod((argv[i+2]));
    }
    fill_result(arr, size, result);
    const HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h_console, FOREGROUND_GREEN);
    for(const double d : result)
    {
        std::cout << d << " ";
        Sleep(25);
    }
    Sleep(1000);
}