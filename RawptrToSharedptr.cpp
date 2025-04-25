#include <iostream>

template<typename T>
class SharedPointer {
public:
    // Constructor
    explicit SharedPointer(T* ptr = nullptr) 
        : ptr_(ptr), ref_count_(new size_t(1))  // Khởi tạo đếm tham chiếu
    {}

    // Copy constructor
    SharedPointer(const SharedPointer& other) 
        : ptr_(other.ptr_), ref_count_(other.ref_count_)
    {
        ++(*ref_count_);  // Tăng đếm tham chiếu
    }

    // Move constructor
    SharedPointer(SharedPointer&& other) noexcept 
        : ptr_(other.ptr_), ref_count_(other.ref_count_)
    {
        other.ptr_ = nullptr;
        other.ref_count_ = nullptr;  // Reset của đối tượng khác
    }

    // Destructor
    ~SharedPointer() {
        release();  // Giải phóng tài nguyên
    }

    // Gán copy
    SharedPointer& operator=(const SharedPointer& other) {
        if (this != &other) {
            release();  // Giải phóng tài nguyên hiện tại
            ptr_ = other.ptr_;          // Gán lại con trỏ
            ref_count_ = other.ref_count_; // Gán lại đếm tham chiếu
            ++(*ref_count_);            // Tăng đếm tham chiếu
        }
        return *this;
    }

    // Gán move
    SharedPointer& operator=(SharedPointer&& other) noexcept {
        if (this != &other) {
            release();  // Giải phóng tài nguyên hiện tại
            ptr_ = other.ptr_;          // Gán lại con trỏ
            ref_count_ = other.ref_count_; // Gán lại đếm tham chiếu
            other.ptr_ = nullptr;       // Nullify để tránh giải phóng
            other.ref_count_ = nullptr; // Nullify để tránh giải phóng
        }
        return *this;
    }

    // Overload dereference operator
    T& operator*() const {
        return *ptr_;
    }

    // Overload arrow operator
    T* operator->() const {
        return ptr_;
    }

    // Get số lượng tham chiếu
    size_t use_count() const {
        return *ref_count_;
    }

private:
    void release() {
        if (ref_count_ && --(*ref_count_) == 0) { // Giảm đếm và kiểm tra
            delete ptr_;       // Giải phóng tài nguyên
            delete ref_count_; // Giải phóng đếm tham chiếu
        }
    }

    T* ptr_;         // Con trỏ thô
    size_t* ref_count_; // Đếm tham chiếu
};

// Example usage
class Test {
public:
    void display() {
        std::cout << "Hello from Test!" << std::endl;
    }
};

int main() {
    SharedPointer<Test> sp1(new Test()); // Tạo đối tượng SharedPointer
    {
        SharedPointer<Test> sp2 = sp1; // Chia sẻ đối tượng
        std::cout << "Reference count: " << sp1.use_count() << std::endl; // Đếm tham chiếu
        sp2->display(); // Sử dụng đối tượng
    } // sp2 ra khỏi phạm vi, đếm tham chiếu giảm

    std::cout << "Reference count after sp2 out of scope: " << sp1.use_count() << std::endl; // Đếm tham chiếu

    return 0;
}