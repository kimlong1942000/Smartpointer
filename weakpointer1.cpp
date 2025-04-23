// Viết một chương trình đơn giản tạo ra hai lớp Customer và Order. 
// Customer chứa thông tin về khách hàng và một shared_ptr đến Order.
// Order sẽ chứa một weak_ptr đến Customer.

#include <iostream>
#include <memory>
#include <string>

class Order; // Khai báo lớp Order

class Customer {
public:
    Customer(const std::string& name) : name(name) {
        std::cout << "Customer " << name << " được khởi tạo.\n";
    }
    ~Customer() {
        std::cout << "Customer " << name << " bị hủy.\n";
    }
    void setOrder(std::shared_ptr<Order> order) {
        this->order = order; // Lưu trữ shared_ptr đến Order
    }
    
private:
    std::string name;
    std::shared_ptr<Order> order; // shared_ptr đến Order
};

class Order {
public:
    Order(double amount) : amount(amount) {
        std::cout << "Order trị giá " << amount << " được khởi tạo.\n";
    }
    ~Order() {
        std::cout << "Order trị giá " << amount << " bị hủy.\n";
    }
    
private:
    double amount;
};

int main() {
    // Tạo đối tượng Customer và Order
    std::shared_ptr<Customer> customer = std::make_shared<Customer>("Nguyen Van A");
    std::shared_ptr<Order> order = std::make_shared<Order>(150.0);
    
    // Kết nối customer và order
    customer->setOrder(order);
    
    return 0;
}