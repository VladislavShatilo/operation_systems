#include<iostream>
#include <random>
#include<string>
#include<windows.h>


int main()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    constexpr double min_value = 0;
    constexpr double max_value = 100;
    std::uniform_real_distribution<> distribution(min_value, max_value);
    int array_size, n;
    std::cout << "Input array size\n";
    std::cin >> array_size;

    const auto arr = new double[array_size];
    for (int i = 0; i < array_size; i++)
    {
        arr[i] = (distribution(generator));
    }
    for (int i = 0; i < array_size; i++)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << "\nInput N\n";
    std::cin >> n;

    HANDLE h_write_pipe, h_read_pipe, h_inherit_write_pipe;
    SECURITY_ATTRIBUTES sa_attr;
    sa_attr.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa_attr.bInheritHandle = TRUE;
    sa_attr.lpSecurityDescriptor = nullptr;

    if (!CreatePipe(&h_read_pipe, &h_write_pipe, &sa_attr, 0))
    {
        std::cout << "create pipe is failed\n";
        return GetLastError();
    }
    if (!DuplicateHandle(GetCurrentProcess(), h_write_pipe, GetCurrentProcess(), &h_inherit_write_pipe, 0, TRUE, DUPLICATE_SAME_ACCESS))
    {
        std::cout << "duplicate write pipe is failed\n";
        return GetLastError();
    }


    DWORD bytes_written;
    if (!WriteFile(h_inherit_write_pipe, &array_size, sizeof(int), &bytes_written, nullptr))
    {
        std::cout << "array size write is failed\n";
        return GetLastError();
    }

    if (!WriteFile(h_inherit_write_pipe, arr, sizeof(double) * array_size, &bytes_written, nullptr))
    {
        std::cout << "array  write is failed\n";
        return GetLastError();
    }
    if (!WriteFile(h_inherit_write_pipe, &n, sizeof(n), &bytes_written, nullptr))
    {
        std::cout << "N  write is failed\n";
        return GetLastError();
    }


    std::string client_cmd = "client.exe " + std::to_string(reinterpret_cast<int>(h_write_pipe)) + " " + std::to_string(
        reinterpret_cast<int>(h_read_pipe)) + " ";
    auto w_client_cmd = std::wstring(client_cmd.begin(), client_cmd.end());
    const LPWSTR  client = &w_client_cmd[0];
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    si.cb = sizeof(STARTUPINFO);

    if (!CreateProcess(nullptr, client, nullptr, nullptr, TRUE, CREATE_NEW_CONSOLE, nullptr, nullptr, &si, &pi))
    {
        std::cout << "client.exe was not launched.\n";
        return GetLastError();
    }




    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD byte_read;
    if (!ReadFile(h_read_pipe, arr, sizeof(double) * array_size, &byte_read, nullptr))
    {
        std::cout << "N read is failed\n";
        return GetLastError();
    }

    std::cout << "\nArray sqrt\n";
    for (int i = 0; i < array_size; i++)
    {
        std::cout << arr[i]<< " ";
    }

    CloseHandle(h_read_pipe);
    CloseHandle(h_write_pipe);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

}