//Nhiệm vụ: Viết một chương trình sử dụng std::shared_ptr để chia sẻ một đối tượng giữa nhiều con trỏ.
#include <iostream>
#include <memory>
#include <string>

class Person {
public:
    Person(std::string name, int age) : name(name), age(age) { }
    void showInfo() {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
private:
    std::string name;
    int age;
};

int main() {
    std::shared_ptr<Person> person1 = std::make_shared<Person>("Alice", 30);
    std::shared_ptr<Person> person2 = person1; // Chia sẻ quyền sở hữu

    person1->showInfo();
    person2->showInfo();

    std::cout << "Use count: " << person1.use_count() << std::endl; 

    return 0; 
}