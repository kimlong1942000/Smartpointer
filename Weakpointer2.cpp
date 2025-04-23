// Viết một chương trình quản lý một danh sách sinh viên và điểm số của họ.

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Grade {
public:
    Grade(double score) : score(score) {
        std::cout << "Grade với điểm " << score << " được khởi tạo.\n";
    }
    
    double getScore() const {
        return score;
    }
    
    ~Grade() {
        std::cout << "Grade với điểm " << score << " bị hủy.\n";
    }

private:
    double score;
};

class Student {
public:
    Student(const std::string &name) : name(name) {
        std::cout << "Student " << name << " được khởi tạo.\n";
    }
    
    void setGrade(std::shared_ptr<Grade> grade) {
        this->grade = grade; // Lưu trữ shared_ptr đến Grade
    }
    
    void print() const {
        std::cout << "Student: " << name << "\n";
        if (grade) {
            std::cout << " Điểm: " << grade->getScore() << "\n";
        }
    }

    ~Student() {
        std::cout << "Student " << name << " bị hủy.\n";
    }

private:
    std::string name;
    std::shared_ptr<Grade> grade; // shared_ptr đến Grade
};

int main() {
    // Danh sách sinh viên
    std::vector<std::shared_ptr<Student>> students;

    // Thêm sinh viên và điểm số
    for (int i = 1; i <= 3; ++i) {
        auto student = std::make_shared<Student>("Student " + std::to_string(i));
        auto grade = std::make_shared<Grade>(i * 10.0); // Điểm: 10, 20, 30
        student->setGrade(grade);
        students.push_back(student);
    }

    // In ra danh sách sinh viên và điểm số
    for (const auto &student : students) {
        student->print();
    }
    return 0;
}