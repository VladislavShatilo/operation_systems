#include<iostream>
#include<windows.h>
#include<vector>
#include<thread>
#include <condition_variable>
#include<mutex>
#include <random>



struct prm {
    int counts = 0;
    int array_size;
    int x;
    int* arr;
    int time_chilling;
    std::condition_variable_any cv;
    std::condition_variable_any cv1;
    std::vector<int> new_vector;
    std::mutex mtx;

    prm() : array_size(0), x(0), arr(nullptr), time_chilling(0)
    {
        
    }
    ~prm()
    {
        delete[]arr;
       
    }

};


void count_element_func(prm &parameters)
{
    for (int i = 0; i < parameters.array_size; i++)
    {
        if (parameters.arr[i] != parameters.x)
        {
            parameters.counts++;
        }
    }
    parameters.cv1.notify_one();
}

void work_func(prm &parameters)
{ 
    for (int i = 0; i < parameters. array_size; i++)
    {
        if (parameters.arr[i] == parameters. x)
        {
            parameters. new_vector.push_back(parameters.arr[i]);
            Sleep(parameters.time_chilling);
        }
    }
    for (int i = 0; i < parameters.array_size; i++)
    {
        if (parameters.arr[i] != parameters.x)
        {
            parameters.new_vector.push_back(parameters.arr[i]);
            Sleep(parameters.time_chilling);
        }
    }
    parameters.cv.notify_one();

}

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