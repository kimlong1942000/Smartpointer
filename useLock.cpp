#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex_1; // Mutex 1
std::mutex mutex_2; // Mutex 2

void thread1() {
    std::cout << "Thread 1: Đang cố gắng khóa mutex_1 và mutex_2\n";
    std::lock(mutex_1, mutex_2); // Khóa cả hai mutex

    std::lock_guard<std::mutex> lock1(mutex_1, std::adopt_lock); // Khóa mutex_1
    std::lock_guard<std::mutex> lock2(mutex_2, std::adopt_lock); // Khóa mutex_2

    std::cout << "Thread 1: Đã giữ cả hai mutex\n";
}

void thread2() {
    std::cout << "Thread 2: Đang cố gắng khóa mutex_1 và mutex_2\n";
    std::lock(mutex_1, mutex_2); // Khóa cả hai mutex

    std::lock_guard<std::mutex> lock1(mutex_1, std::adopt_lock); // Khóa mutex_1
    std::lock_guard<std::mutex> lock2(mutex_2, std::adopt_lock); // Khóa mutex_2

    std::cout << "Thread 2: Đã giữ cả hai mutex\n";
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}