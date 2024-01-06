#include"child.h"
#include<conio.h>
#include <string>

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
