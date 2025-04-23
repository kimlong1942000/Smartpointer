//Nhiệm vụ: Viết một chương trình thực hiện các phép toán cơ bản với hai đối tượng thông qua shared_ptr.

#include <iostream>
#include <memory>

class Calculator {
public:
    int add(int a, int b) {
        return a + b;
    }
    int subtract(int a, int b) {
        return a - b;
    }
    int multiply(int a, int b) {
        return a * b;
    }
};

int main() {
    std::shared_ptr<Calculator> calc1 = std::make_shared<Calculator>();
    std::shared_ptr<Calculator> calc2 = calc1; 
    std::cout << "Add: " << calc1->add(5, 10) << std::endl; 
    std::cout << "Subtract: " << calc2->subtract(5, 3) << std::endl; 
    std::cout << "Multiply: " << calc1->multiply(5, 4) << std::endl; 

    std::cout << "Use count: " << calc1.use_count() << std::endl; // Hiển thị số lượng con trỏ đang chia sẻ

    return 0; 
}