#pragma once
#include <vector>
#include "reservation.h"
#include "course.h"
#include "room.h"

class ReservationSystem {
    std::vector<Room> rooms;
    std::vector<Reservation> reservations;
    std::vector<Course> courses;
    public:
        ReservationSystem() {}

        bool addRoom(const std::string& name);
        bool hasRoom(const std::string& name) const;
        const Room& getRoom(const std::string& name) const;
        bool addCourse(const std::string& code, const std::string& teacher);
        bool hasCourse(const std::string& code) const;
        const Course& getCourse(const std::string& code) const;
        const std::vector<Room>& getRooms() const;
        const std::vector<Course>& getCourses() const;
        const std::vector<Reservation>& getReservations() const;
        bool makeAnyReservation(const std::string& course_code, int duration);
        bool makeReservation(const std::string& course_code, const std::string& room_name, int from, int to);
};
