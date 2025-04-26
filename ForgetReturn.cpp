#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex myMutex;

void thread() {
    std::lock_guard<std::mutex> lock(myMutex); // Khóa mutex

    std::cout << "Luồng 1: Đang truy cập tài nguyên." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Giả lập công việc

    if (false) {
        std::cout << "Lỗi xảy ra!" << std::endl;
        return; // Bỏ qua return do if không hoàn thiện -> không gọi unlock mutex
    }

    // lock sẽ tự động mở khóa khi ra khỏi phạm vi ????
}

int main() {
    std::thread t1(thread);
    std::thread t2(thread); // Phát sinh luồng thứ hai

    t1.join();
    t2.join(); // Có thể gặp deadlock nếu mutex vẫn bị giữ

    return 0;
}