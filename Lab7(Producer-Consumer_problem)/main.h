#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <random>

constexpr int buffer_size = 5;

std::queue<int> buffer;
std::mutex mtx;
std::condition_variable not_empty, not_full;

inline void producer(const int id) {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);

        not_full.wait(lock, [] { return buffer.size() < buffer_size; });

        std::random_device rd;
        std::mt19937 generator(rd());
        constexpr int min_value = 0;
        constexpr int max_value = 100;
        std::uniform_int_distribution<> distribution(min_value, max_value);
        int item = (distribution(generator));
        buffer.push(item);
        std::cout << "Producer " << id << " produced item: " << item << "\n";

        not_empty.notify_all();
    }
}

inline void consumer(const int id) {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);


        not_empty.wait(lock, [] { return !buffer.empty(); });


        const int item = buffer.front();
        buffer.pop();
        std::cout << "Consumer " << id << " consumed item: " << item << "\n";


        not_full.notify_all();
    }
}
