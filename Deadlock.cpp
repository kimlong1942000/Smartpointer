#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex_1; // Mutex 1
std::mutex mutex_2; // Mutex 2

void thread1() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));//tam dung luong trong 100ms
    std::cout << "Thread 1: Đang cố gắng khóa mutex_1\n";
    mutex_1.lock(); // Khóa mutex_1
    std::cout << "Thread 1: Đã khóa mutex_1\n";
    
    std::cout << "Thread 1: Đang cố gắng khóa mutex_2\n";
    mutex_2.lock(); // Khóa mutex_2
    std::cout << "Thread 1: Đã khóa mutex_2\n";
        
    mutex_2.unlock(); // Mở khóa mutex_2
    mutex_1.unlock(); // Mở khóa mutex_1
}

void thread2() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); //tam dung luong trong 100ms
    std::cout << "Thread 2: Đang cố gắng khóa mutex_2\n";
    mutex_2.lock(); // Khóa mutex_2
    std::cout << "Thread 2: Đã khóa mutex_2\n";

    std::cout << "Thread 2: Đang cố gắng khóa mutex_1\n";
    mutex_1.lock(); // Khóa mutex_1
    std::cout << "Thread 2: Đã khóa mutex_1\n";

    mutex_1.unlock(); // Mở khóa mutex_1
    mutex_2.unlock(); // Mở khóa mutex_2
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}