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
        parameters.arr[i] = (distribution(generator));
    }
    std::cout << "\nArray size: " << parameters.array_size <<"\n";
    for (int i = 0; i < parameters.array_size; i++)
    {
        std::cout << parameters.arr[i] << " ";
    }
    std::cout << "\nInput time for element chill\n";
    std::cin >> parameters.time_chilling;
    std::cout << "Input X\n";
    std::cin >> parameters.x;

    std::thread t1(count_element_func, std::ref(parameters));
    std::thread t2(work_func, std::ref(parameters ));

    std::unique_lock<std::mutex> lc(parameters.mtx);
    parameters.cv.wait(lc);

    for (const double i : parameters.new_vector)
    {
        std::cout << i << " ";
    }
    std::cout <<"\n";

    std::cout << "\nElements which not equals X " << parameters.counts<< "\n";

    t1.join();
    t2.join();


}