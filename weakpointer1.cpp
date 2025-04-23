#include <iostream>  
#include <memory>  
#include <string>  

class Order; // Chỉ định trước lớp Order để có thể sử dụng trong lớp Customer  

// Khai báo lớp Customer  
class Customer : public std::enable_shared_from_this<Customer> {  
public:  
    // Constructor nhận tên khách hàng  
    Customer(const std::string& name)  
        : name_(name) {}  

    // Phương thức tạo Order và lưu trữ nó vào shared_ptr  
    void createOrder();  

    // Phương thức in tên khách hàng  
    std::string getName() const {  
        return name_;  
    }  

    // Phương thức in thông tin order  
    void printOrder();  

private:  
    std::string name_;  
    std::shared_ptr<Order> order_; // Shared pointer đến Order  
};  

// Khai báo lớp Order  
class Order {  
public:  
    // Constructor nhận một weak_ptr đến Customer  
    Order(std::weak_ptr<Customer> customer)  
        : customer_(customer) {}  

    // Phương thức in thông tin Order  
    void printOrder() {  
        if (auto customer = customer_.lock()) { // Sử dụng lock để kiểm tra xem Customer còn tồn tại không  
            std::cout << "Order for customer: " << customer->getName() << std::endl;  
        } else {  
            std::cout << "Customer no longer exists." << std::endl;  
        }  
    }  

private:  
    std::weak_ptr<Customer> customer_;  
};  

// Triển khai phương thức createOrder  
void Customer::createOrder() {  
    order_ = std::make_shared<Order>(shared_from_this());  
}  

// Triển khai phương thức printOrder  
void Customer::printOrder() {  
    if (order_) {  
        order_->printOrder();  
    } else {  
        std::cout << "No order created for " << name_ << std::endl;  
    }  
}  

int main() {  
    // Tạo một đối tượng Customer  
    auto customer = std::make_shared<Customer>("John Doe");  
    
    // Tạo một Order cho Customer  
    customer->createOrder();  
    
    // In thông tin Order  
    customer->printOrder();  

    // Giải phóng Customer  
    customer.reset();  

    // Kiểm tra lại  
    std::cout << "After customer reset:" << std::endl;  
    // Không gọi phương thức nếu customer đã reset  
    if (customer) {  
        customer->printOrder();  
    } else {  
        std::cout << "Customer has been reset." << std::endl;  
    }  

    return 0;  
}  