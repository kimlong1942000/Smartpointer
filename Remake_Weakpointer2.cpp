// Viết một chương trình quản lý một danh sách sinh viên và điểm số của họ.
#include <iostream>
#include <memory>
#include <string>

class Grade; // Forward declaration

class Student {
public:
    Student(const std::string& name) : name(name) {
        std::cout << "Student " << name << " created." << std::endl;
    }
    
    ~Student() {
        std::cout << "Student " << name << " destroyed." << std::endl;
    }

    void setGrade(std::shared_ptr<Grade> Grade) {
        this->Grade = Grade;
    }

    void printInfo() const {
        std::cout << "Student Name: " << name << std::endl;
    }

private:
    std::string name;
    std::shared_ptr<Grade> Grade; // shared_ptr to Grade
};

class Grade {
public:
    Grade(const std::string& product) : product(product) {
        std::cout << "Grade for " << product << " created." << std::endl;
    }

    ~Grade() {
        std::cout << "Grade for " << product << " destroyed." << std::endl;
    }

    void setStudent(std::weak_ptr<Student> Student) {
        this->Student = Student;
    }

    void printStudentInfo() const {
        if (auto cust = Student.lock()) { // Lock the weak_ptr to get a shared_ptr
            std::cout << "Grade " << product << " is associated with Student: ";
            cust->printInfo();
        } else {
            std::cout << "Grade " << product << " has no associated Student." << std::endl;
        }
    }

private:
    std::string product;
    std::weak_ptr<Student> Student; // weak_ptr to Student
};

int main() {
    // Tạo một đối tượng Student và Grade
    std::shared_ptr<Student> Student = std::make_shared<Student>("anh A");
    std::shared_ptr<Grade> Grade = std::make_shared<Grade>("Bike");
    
    // Thiết lập mối quan hệ giữa Student và Grade
    Student->setGrade(Grade);
    Grade->setStudent(Student);

    // In thông tin
    Student->printInfo();
    Grade->printStudentInfo();

    return 0; // Khi kết thúc, các đối tượng sẽ tự động được giải phóng
}