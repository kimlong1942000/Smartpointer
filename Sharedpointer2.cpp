//Nhiệm vụ: Tạo một danh sách liên kết đơn giản sử dụng std::shared_ptr để quản lý các nút.

#include <iostream>
#include <memory>

struct Node {
    int data;
    std::shared_ptr<Node> next;

    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    std::shared_ptr<Node> head;

public:
    LinkedList() : head(nullptr) {}

    void add(int value) {
        auto newNode = std::make_shared<Node>(value);
        if (!head) {
            head = newNode;
        } else {
            std::shared_ptr<Node> current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void print() const {
        std::shared_ptr<Node> current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    LinkedList list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.print(); 

    return 0; 