#include <iostream>

template<typename T>
class UniquePointer {
public:
    // Constructor
    explicit UniquePointer(T* ptr = nullptr) : ptr_(ptr) {}

    // Destructor
    ~UniquePointer() {
        delete ptr_;
    }

    // Disable copy constructor and copy assignment
    UniquePointer(const UniquePointer&) = delete;
    UniquePointer& operator=(const UniquePointer&) = delete;

    // Move constructor
    UniquePointer(UniquePointer&& other) noexcept : ptr_(other.ptr_) {
        other.ptr_ = nullptr; // Set the other pointer to null
    }

    // Move assignment operator
    UniquePointer& operator=(UniquePointer&& other) noexcept {
        if (this != &other) {
            delete ptr_; // Delete current resource
            ptr_ = other.ptr_; // Transfer ownership
            other.ptr_ = nullptr; // Reset other pointer
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

    // Function to get raw pointer
    T* get() const {
        return ptr_;
    }

    // Function to release ownership
    T* release() {
        T* temp = ptr_;
        ptr_ = nullptr; // Set to null to avoid deleting
        return temp;
    }

private:
    T* ptr_; // Raw pointer
};

int main() {
    UniquePointer<int> up(new int(12)); // Create unique pointer
    std::cout << &up << std::endl;
    std::cout << up.get() << std::endl; 

    if (up.get() == nullptr) {
        std::cout << "up is now nullptr." << std::endl;
    }

    return 0;
}