#pragma once
#include <iostream>
#include <string>

class Reservation {
    public:
    const std::string room_name;
    const std::string course_code;
    const int start_time;
    const int end_time;
        Reservation(const std::string& room_name, const std::string& course_code, int start_time, int end_time)
            : room_name(room_name), course_code(course_code), start_time(start_time), end_time(end_time) {}
        void print() const {
            std::cout << "Reservation for Course ";
            std::cout << course_code;
            std::cout << " in Room ";
            std::cout << room_name;
            std::cout << " [" << start_time << "-" << end_time << "]\n";
        }
};
