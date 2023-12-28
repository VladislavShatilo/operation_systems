#include<iostream>
#include<windows.h>
#include<string>
#include <vector>


int main()
{
    int message;
    HANDLE events[5]{};
    std::string event_str = "eve";
    const  std::wstring event_string(event_str.begin(), event_str.end());
    const LPCWSTR event_name = event_string.c_str();

    for (int i = 0; i < 5; i++)
    {
        std::wstring numbered_event = event_name + std::to_wstring(i);
        events[i] = CreateEvent(nullptr, TRUE, FALSE, numbered_event.c_str());
    }
    if (nullptr == events)
    {
        return GetLastError();
    }


    std::string sem_name = "emp";
    std::wstring w_sem_name(sem_name.begin(), sem_name.end());
    LPCWSTR lp_sem_name = w_sem_name.c_str();

    HANDLE semaphore = CreateSemaphore(nullptr, 3, 3, lp_sem_name);
    int count_of_process, count_of_messages;
    std::cout << "Input count of process\n";
    std::cin >> count_of_process;

    std::cout << "Input count of messages\n";
    std::cin >> count_of_messages;

    std::string employee_cmd;
    std::wstring converting_employee_to_lpsz;
    LPWSTR lpsz_employee_process_command_line;
    STARTUPINFO si;
    PROCESS_INFORMATION pi{};
    std::vector<int> answers;

    for (int i = 0; i < count_of_process; i++)
    {

        employee_cmd = "Employee.exe " + std::to_string(count_of_messages) + " " + std::to_string(i);
        converting_employee_to_lpsz = std::wstring(employee_cmd.begin(), employee_cmd.end());
        lpsz_employee_process_command_line = &converting_employee_to_lpsz[0];
        ZeroMemory(&si, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);

        if (!CreateProcess(nullptr, lpsz_employee_process_command_line, nullptr, nullptr, TRUE, CREATE_NEW_CONSOLE,
            nullptr, nullptr, &si, &pi))
        {
            std::cout << "Creator.exe was not launched.\n";
            return GetLastError();
        }

    }

    for (int j = 0; j < count_of_messages; j++)
    {
        std::cout << "Enter a message (0-3 to send, 4 to end session): ";
        std::cin >> message;

        if (events[message] != nullptr && !SetEvent(events[message]))
        {
            std::cout << "did not set event\n";
            return GetLastError();
        }
        if (events[message] != nullptr && !ResetEvent(events[message]))
        {
            std::cout << "did not reset event\n";
            return GetLastError();

        }

    }


    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);


}
