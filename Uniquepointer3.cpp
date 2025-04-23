//Nhiệm vụ: Viết một hàm nhận std::unique_ptr như một tham số, thay đổi nội dung của đối tượng mà nó quản lý, và in ra kết quả.

#include <iostream>
#include <memory>

class Rectangle {
private:
    double length;
    double width;
public:
    Rectangle(double l, double w) : length(l), width(w) {}
    void print() const {
        std::cout << "Rectangle: Length = " << length << ", Width = " << width << std::endl;
    }
    void resize(double l, double w) {
        length = l; 
        width = w;
    }
};

void resizeRectangle(std::unique_ptr<Rectangle>& rect, double newLength, double newWidth) {
    rect->resize(newLength, newWidth);
    rect->print();
}

int main() {
    std::unique_ptr<Rectangle> rectPtr(new Rectangle(10.0, 5.0));
    rectPtr->print(); // In kích thước ban đầu

    resizeRectangle(rectPtr, 20.0, 10.0); // Thay đổi kích thước

    return 0; 
}