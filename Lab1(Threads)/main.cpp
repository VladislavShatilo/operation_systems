#include "ArrayWork.h"
DWORD WINAPI work_with_array(const LPVOID siz)
{
    const auto params = static_cast<array_work*>(siz);
    std::cout << "Tread is started\n";
    for (unsigned long long i = 0; i < params->get_size(); ++i)
    {
        if (abs(static_cast<int>(params->get_array()[i] * 10)) % 10 < 5)
        {
            std::cout << params->get_array()[i]<<" ";
            params->add_element(params->get_array()[i]);
        }
        Sleep(25);
    }
    std::cout << "\nTread is ended\n";
    return 0;
}

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