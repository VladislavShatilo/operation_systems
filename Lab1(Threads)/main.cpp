#include "ArrayWork.h"

int main()
{
    array_work array_work(10);
    array_work.fill_array();
    array_work.print_array();
    std::cout << "Input time for suspend\n";
    int sleep_time;
    std::cin >> sleep_time;
    DWORD id_thread;
    const HANDLE worker = CreateThread(nullptr, 0, work_with_array, &array_work, 0, &id_thread);
    if (worker == nullptr)
    {
        std::cout << "Error of creating thread\n";
        return GetLastError();
    }

    SuspendThread(worker);
    Sleep(sleep_time); 
    ResumeThread(worker);
    WaitForSingleObject(worker, INFINITE);
    CloseHandle(worker);
    array_work.print_result();

    
}
