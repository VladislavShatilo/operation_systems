#include "main.h"
int main()
{
    prm parameters;
    std::random_device rd;
    std::mt19937 generator(rd());
    constexpr int min_value = 0;
    constexpr int max_value = 10;
    std::uniform_int_distribution<> distribution(min_value, max_value);



    std::cout << "Input array size\n";
    std::cin >> parameters.array_size;
    parameters.arr = new int[parameters.array_size];
    for (int i = 0; i < parameters.array_size; i++)
    {
        parameters.arr[i] = distribution(generator);
    }
    std::cout << "\nArray size: " << parameters.array_size <<"\n";
    for (int i = 0; i < parameters.array_size; i++)
    {
        std::cout << parameters.arr[i] << " ";
    }
    std::cout << "\n\nInput time for element chill\n";
    std::cin >> parameters.time_chilling;
  
    const HANDLE count_element = CreateThread(nullptr, 0, count_element_func, &parameters, 0, nullptr);
    if (count_element == nullptr)
    {
        return GetLastError();
    }
    const HANDLE work = CreateThread(nullptr, 0, work_func, &parameters, 0, nullptr);
    if (work == nullptr)
    {
        return GetLastError();
    }
    
    std::cout << "\nInput X\n";
    std::cin >> parameters.x;

   
    SetEvent(parameters.start);

    EnterCriticalSection(&parameters.work_critical_section);
    for (const double i : parameters.new_vector)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";
    LeaveCriticalSection(&parameters.work_critical_section);


    EnterCriticalSection(&parameters.count_element_critical_section);
    std::cout << "\nElements which not equals X " << parameters.counts << "\n";
    LeaveCriticalSection(&parameters.count_element_critical_section);


   
    CloseHandle(work);
    CloseHandle(count_element);


}
