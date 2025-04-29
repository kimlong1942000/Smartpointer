#include <iostream>
#include <utility> // cho std::move

class IntWrapper {
public:
    // Constructor
    IntWrapper(int value) : value(value) {
        std::cout << "Constructor called with value: " << value << std::endl;
    }

    // Destructor
    ~IntWrapper() {
        std::cout << "Destructor called for value: " << value << std::endl;
    }

    // Copy Constructor
    IntWrapper(const IntWrapper &other) : value(other.value) {
        std::cout << "Copy Constructor called, copied value: " << value << std::endl;
    }

    // Move Constructor
    IntWrapper(IntWrapper &&other) noexcept : value(other.value) {
        // Đánh dấu đối tượng tạm không còn giá trị
        std::cout << "Move Constructor called, moved value: " << value << std::endl;
    }

    // Hàm để lấy giá trị
    int getValue() const {
        return value;
    }

private:
    int value; // Lưu trữ giá trị int
};

int main() {
    IntWrapper int1(42); // Gọi constructor
    IntWrapper int2 = std::move(int1); // Gọi move constructor

    std::cout << "Value of int2: " << int2.getValue() << std::endl; // In ra giá trị của int2

    return 0;
}