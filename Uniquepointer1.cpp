//Viết một chương trình sử dụng std::unique_ptr để quản lý một mảng động các số nguyên. Đặt kích thước mảng là 5 và lưu trữ các số nguyên từ 1 đến 5.

#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int[]> arr(new int[5]);
    for (int i = 0; i < 5; ++i) {
        arr[i] = i + 1;
    }
    for (int i = 0; i < 5; ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }

    return 0; 
}