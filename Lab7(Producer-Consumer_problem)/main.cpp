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

void producer(const int id) {
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

void consumer(const int id) {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);

       
        not_empty.wait(lock, [] { return !buffer.empty(); });


        const int item = buffer.front();
        buffer.pop();
        std::cout << "Consumer " << id << " consumed item: " << item << "\n";

       
        not_full.notify_all();
    }
}

int main() {
    std::thread producer1(producer, 1);
    std::thread producer2(producer, 2);
    std::thread producer3(producer, 3);
    std::thread producer4(producer, 4);
    std::thread consumer1(consumer, 1);
    std::thread consumer2(consumer, 2);
    std::thread consumer3(consumer, 3);
    std::thread consumer4(consumer, 4);

    producer1.join();
    producer2.join();
    producer3.join();
    producer4.join();
    consumer1.join();
    consumer2.join();
    consumer3.join();
    consumer4.join();

    return 0;
}