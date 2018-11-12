#pragma once
#include <iostream>
#include <string>

class Course {
    public:
        const std::string code;
        const std::string teacher;
        Course(const std::string& code, const std::string& teacher)
            : code(code), teacher(teacher) {}
        void print() const {
            std::cout << "Course: " << code;
            if (!teacher.empty()) {
                std::cout << " " << "[Teacher: " << teacher << "]";
            }
            std::cout << "\n";
        }
};
