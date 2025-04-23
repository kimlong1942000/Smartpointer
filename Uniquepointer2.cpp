//Viết một chương trình trong đó bạn tạo một đối tượng MyClass và sau đó chuyển quyền sở hữu từ một unique_ptr này sang một unique_ptr khác.
#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass() { std::cout << "MyClass Constructor" << std::endl; }
    ~MyClass() { std::cout << "MyClass Destructor" << std::endl; }
    void show() { std::cout << "This is MyClass!" << std::endl; }
};

int main() {
    std::unique_ptr<MyClass> ptr1(new MyClass());
    ptr1->show();

    // Chuyển sở hữu sang ptr2
    std::unique_ptr<MyClass> ptr2 = std::move(ptr1);

    if (ptr1 == nullptr) {
        std::cout << "ptr1 is null after move." << std::endl;
    }

    if (ptr2) {
        ptr2->show();
    }

    return 0; 
}