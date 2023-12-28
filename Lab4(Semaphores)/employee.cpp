#include<iostream>
#include<windows.h>
#include<string>
#include<conio.h>
#include <vector>

void print_messages(int count_of_messages, const HANDLE * events, const HANDLE h_semaphore,std::vector<int>& messages)
{
    while (count_of_messages > 0)
    {
        const DWORD message = WaitForMultipleObjects(5, events, FALSE, INFINITE);
        if (message == 4)
        {
            ReleaseSemaphore(h_semaphore, 1, nullptr);
            break;
        }
        switch (message) {
        case 0:
            messages.push_back(0);
            std::cout << messages[messages.size() - 1] << "\n";
            count_of_messages--;
            break;
        case 1:
            messages.push_back(1);
            std::cout << messages[messages.size() - 1] << "\n";
            count_of_messages--;
            break;
        case 2:
            messages.push_back(2);
            std::cout << messages[messages.size() - 1] << "\n";
            count_of_messages--;
            break;
        case 3:
            messages.push_back(3);
            std::cout << messages[messages.size() - 1] << "\n";
            count_of_messages--;
            break;
        default:
            break;
        }
    }
}
int main(int argc, char* argv[])
{
    std::vector<int> messages;
    std::string sem_name = "emp";
    const std::wstring w_sem_name(sem_name.begin(), sem_name.end());
    const LPCWSTR lp_sem_name = w_sem_name.c_str();

    const HANDLE h_semaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, lp_sem_name);
    if (h_semaphore == nullptr)
    {
        return GetLastError();
    }

    int count_of_messages = std::stoi(argv[1]);
    const int index = std::stoi(argv[2]);
    std::string event_str = "eve";
    const std::wstring event_string(event_str.begin(), event_str.end());
    const LPCWSTR event_name = event_string.c_str();
    HANDLE events[5];
    for (int i = 0; i < 5; i++)
    {
        std::wstring numbered_event = event_name + std::to_wstring(i);
        events[i] = OpenEvent(EVENT_ALL_ACCESS, FALSE, numbered_event.c_str());
        if (events[i] == nullptr)
        {
            std::cout << "error\n";
        }
    }

    WaitForSingleObject(h_semaphore, INFINITE);
    std::cout << "Process number "+ std::to_string(index) +" is active \n";

    print_messages(count_of_messages,events,h_semaphore,messages);
    

   

    CloseHandle(h_semaphore);
    for (const auto& event : events)
    {
        if (event != nullptr)
        {
            CloseHandle(event);
        }

    }
    _cprintf("Employee is worked, press any key to exit\n");
    char e = _getch();


    return 0;

}