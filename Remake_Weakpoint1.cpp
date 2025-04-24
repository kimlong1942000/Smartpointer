// Viết một chương trình đơn giản tạo ra hai lớp Customer và Order. 
// Customer chứa thông tin về khách hàng và một shared_ptr đến Order. Order sẽ chứa một weak_ptr đến Customer. 
// Code bằng C++, KHÔNG SỬ DỤNG "enable_shared_from_this"


#include <iostream>
#include <memory>
#include <string>

class Order; // Forward declaration

class Customer {
public:
    Customer(const std::string& name) : name(name) {
        std::cout << "Customer " << name << " created." << std::endl;
    }
    
    ~Customer() {
        std::cout << "Customer " << name << " destroyed." << std::endl;
    }

    void setOrder(std::shared_ptr<Order> order) {
        this->order = order;
    }

    void printInfo() const {
        std::cout << "Customer Name: " << name << std::endl;
    }

private:
    std::string name;
    std::shared_ptr<Order> order; // shared_ptr to Order
};

class Order {
public:
    Order(const std::string& product) : product(product) {
        std::cout << "Order for " << product << " created." << std::endl;
    }

    ~Order() {
        std::cout << "Order for " << product << " destroyed." << std::endl;
    }

    void setCustomer(std::weak_ptr<Customer> customer) {
        this->customer = customer;
    }

    void printCustomerInfo() const {
        if (auto cust = customer.lock()) { // Lock the weak_ptr to get a shared_ptr
            std::cout << "Order " << product << " is associated with customer: ";
            cust->printInfo();
        } else {
            std::cout << "Order " << product << " has no associated customer." << std::endl;
        }
    }

private:
    std::string product;
    std::weak_ptr<Customer> customer; // weak_ptr to Customer
};

int main() {
    // Tạo một đối tượng Customer và Order
    std::shared_ptr<Customer> customer = std::make_shared<Customer>("anh A");
    std::shared_ptr<Order> order = std::make_shared<Order>("Bike");
    
    // Thiết lập mối quan hệ giữa Customer và Order
    customer->setOrder(order);
    order->setCustomer(customer);

    // In thông tin
    customer->printInfo();
    order->printCustomerInfo();

    return 0; // Khi kết thúc, các đối tượng sẽ tự động được giải phóng
}