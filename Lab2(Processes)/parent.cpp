#include <iostream>
#include <conio.h>
#include <random>
#include <string>
#include <windows.h>


int main()
{   
    std::random_device rd;
    std::mt19937 generator(rd());   
    constexpr double min_value = 0;
    constexpr double max_value = 100;
    std::uniform_real_distribution<> distribution(min_value, max_value);
    int array_size;
    std::cout << "Input array size\n";
    std::cin >> array_size;
    const auto arr = new double[array_size];
    for (int k = 0; k < array_size; k++)
    {
        arr[k] = (distribution(generator));
        std::cout << arr[k] << " ";
    }
    std::cout << "\n\n";
    std::string creator_cmd = "Child.exe " + std::to_string(array_size) + " ";

    for (int j = 0; j < array_size; j++)
    {
        creator_cmd += std::to_string(arr[j]);
        if (j < array_size - 1)
        {
            creator_cmd += " ";
        }
    }

    auto converting_creator_to_lpsz = std::wstring(creator_cmd.begin(), creator_cmd.end());
    const LPWSTR lpsz_creator_process_command_line =  &converting_creator_to_lpsz[0];
    STARTUPINFO si;
    PROCESS_INFORMATION pi;


    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    if (!CreateProcess(nullptr, lpsz_creator_process_command_line, nullptr, nullptr, TRUE, CREATE_NEW_CONSOLE, nullptr,
                       nullptr, &si, &pi))
    {
        std::cout << "Creator.exe was not launched.\n";
        return GetLastError();
    }


    std::string parent_cmd = "Count.exe ";
    std::wstring converting_parent_to_lpsz(parent_cmd.begin(), parent_cmd.end());
    const LPWSTR parent_command_line = &converting_parent_to_lpsz[0];
    STARTUPINFO si1;
    PROCESS_INFORMATION pi1;
    
    ZeroMemory(&si1, sizeof(STARTUPINFO));
    si1.cb = sizeof(STARTUPINFO);
    if (!CreateProcess(nullptr, parent_command_line, nullptr, nullptr, TRUE, IDLE_PRIORITY_CLASS, nullptr, nullptr,
                       &si1, &pi1))
    {
        std::cout << "Creator.exe was not launched.\n";
        return GetLastError();
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    TerminateProcess(pi.hProcess,0);
    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    ExitProcess(0);
    
   
    
}
