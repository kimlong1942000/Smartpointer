#include <iostream>
#include <thread>
#include <future>
#include <chrono>

void longRunningTask(std::promise<std::string> &&promise) {
    // Giả lập một công việc nặng (ngủ 1 giây)
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Giả định một điều kiện lỗi
    bool errorCondition = true; // Thay đổi thành false để thử trường hợp thành công

    if (errorCondition) {
        // Nếu có lỗi, không gọi set_value, simulating not setting a value
        return; // Kết thúc hàm mà không thiết lập giá trị cho promise
    }

    // Nếu không có lỗi, hoàn thành promise với giá trị bình thường
    promise.set_value("Kết quả từ Task");
}

int main() {
    // Khởi tạo một promise và lấy future từ promise đó
    std::promise<std::string> promise;
    std::future<std::string> future = promise.get_future();

    // Bắt đầu luồng để thực hiện công việc nặng
    std::thread worker(longRunningTask, std::move(promise));

    // In ra thông báo tạm thời
    std::cout << "Giá trị trước khi hoàn thành: 'Đang xử lý...'" << std::endl;

    // Tiến hành lấy giá trị từ future với giá trị mặc định
    std::string defaultValue = "Giá trị mặc định"; // Giá trị mặc định
    std::string result;

    // Sử dụng try-catch để kiểm tra tình huống không có giá trị
    try {
        // Thử lấy kết quả từ future
        result = future.get(); // Blocking call - sẽ chờ cho đến khi promise có giá trị.
    } catch (const std::future_error& e) {
        std::cout << "Lỗi khi lấy giá trị từ future: " << e.what() << std::endl;
        result = defaultValue; // Gán giá trị mặc định
    }

    // Kiểm tra nếu result không có giá trị vì không xảy ra promise set_value
    if (result.empty()) {
        result = defaultValue; // Gán giá trị mặc định nếu không có giá trị
    }
    
    std::cout << "Kết quả nhận được: " << result << std::endl;

    // Đợi cho đến khi luồng worker hoàn thành (nếu chưa)
    worker.join();

    return 0;
}