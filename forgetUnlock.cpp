#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex my_mutex;

void threadFunction() {
    std::unique_lock<std::mutex> lock(my_mutex); // Khóa mutex

    std::cout << "Luồng 1: Đang truy cập tài nguyên." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2)); 

    // lock.unlock(); // Nếu cần phải mở khóa sớm
}

int main() {
    std::thread t1(threadFunction);
    std::thread t2(threadFunction); // Phát sinh luồng thứ hai

    t1.join();
    t2.join(); // Deadlock! Luồng thứ hai không thể truy cập tài nguyên vì đã bị khóa bởi luồng đầu tiên

    return 0;
}