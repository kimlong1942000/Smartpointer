//Nhiệm vụ: Tạo một danh sách liên kết đơn đơn giản sử dụng std::unique_ptr để quản lý các nút.

#include <iostream>
#include <memory>

struct Node {
    int data;
    std::unique_ptr<Node> next;

    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    std::unique_ptr<Node> head;

public:
    LinkedList() : head(nullptr) {}

    void add(int value) {
        auto newNode = std::make_unique<Node>(value);
        if (!head) {
            head = std::move(newNode);
        } else {
            Node* current = head.get();
            while (current->next) {
                current = current->next.get();
            }
            current->next = std::move(newNode);
        }
    }

    void print() const {
        Node* current = head.get();
        while (current) {
            std::cout << current->data << " ";
            current = current->next.get();
        }
        std::cout << std::endl;
    }
};

int main() {
    LinkedList list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.print(); // In danh sách: 1 2 3

    return 0; // Tài nguyên sẽ được giải phóng khi danh sách ra khỏi phạm vi
}