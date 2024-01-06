#pragma once
#include<iostream>
#include "Windows.h"
#include<iomanip>
#include <random>
#include <vector>

class array_work
{

    std::vector<double> array_;
    std::vector<double> result_;
public:
    explicit array_work(const int size)
    {
        array_.resize(size);
    }
  
    void fill_array() 
    {
        std::random_device rd;
        std::mt19937 generator(rd());
        constexpr double min_value = 0;
        constexpr double max_value = 100;
        std::uniform_real_distribution<> distribution(min_value, max_value);
        for (double& i : array_)
        {
            i = (distribution(generator));
        }
    }
    void set_array(std::vector<double> const& array_t)
    {
        this->array_ = array_t;
    }
    std::vector<double> get_result() const
    {
        return this->result_;
    }
    
    void add_element(const double element)
    {
        this->result_.push_back(element);
    }
    void print_result() const
    {
        for (const double element : result_)
        {
            std::cout << element << " ";
        }
        std::cout << '\n';
    }
    void print_array() const 
    {
        for (const double element : array_)
        {
            std::cout << element<<" ";
        }
        std::cout << '\n';
    }
    std::vector<double> get_array() const
    {
        return this->array_;
    }
    void set_size(const int size)
    {
        array_.resize(size);
    }
    unsigned long long get_size() const
    {
       return this->array_.size();
    }

};

inline DWORD WINAPI work_with_array(const LPVOID siz)
{
    const auto params = static_cast<array_work*>(siz);
    std::cout << "Tread is started\n";
    for (unsigned long long i = 0; i < params->get_size(); ++i)
    {
        if (abs(static_cast<int>(params->get_array()[i] * 10)) % 10 < 5)
        {
            std::cout << params->get_array()[i] << " ";
            params->add_element(params->get_array()[i]);
        }
        Sleep(25);
    }
    std::cout << "\nTread is ended\n";
    return 0;
}
