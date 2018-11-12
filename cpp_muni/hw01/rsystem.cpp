#include "rsystem.h"

bool ReservationSystem::addRoom(const std::string& name) {
    if (hasRoom(name)) {
        return false;
    }
    Room room(name);
    rooms.push_back(room);
    return true;
}

bool ReservationSystem::hasRoom(const std::string& name) const {
    for(const Room& room : rooms) {
        if (room.name == name) {
            return true;
        }
    }
    return false;
}

const Room& ReservationSystem::getRoom(const std::string& name) const {
    for(const Room& room : rooms) {
        if (room.name == name) {
            return room;
        }
    }
    throw std::runtime_error("Room not found.");
}

bool ReservationSystem::addCourse(const std::string& code, const std::string& teacher) {
    if (hasCourse(code)) {
        return false;
    }
    Course crs(code, teacher);
    courses.push_back(crs);
    return true;
}

bool ReservationSystem::hasCourse(const std::string& code) const {
    for(const Course& crs : courses) {
        if (crs.code == code) {
            return true;
        }
    }
    return false;
}

const Course& ReservationSystem::getCourse(const std::string& code) const {
    for(const Course& crs : courses) {
        if (crs.code == code) {
            return crs;
        }
    }
    throw std::runtime_error("Course not found.");
}

const std::vector<Room>& ReservationSystem::getRooms() const {
    return rooms;
}

const std::vector<Course>& ReservationSystem::getCourses() const {
    return courses;
}

const std::vector<Reservation>& ReservationSystem::getReservations() const {
    return reservations;
}

bool ReservationSystem::makeAnyReservation(const std::string& course_code, int duration) {
    if (!hasCourse(course_code)) {return false;}
    if (duration < 1) {return false;}
    int start = 0;
    for(Room& room : rooms) {
        if ((start = room.isFreeFor(duration)) != -1) {
            if (room.occupy(start,start+duration)) {
                Reservation res(room.name, course_code, start, start+duration);
                reservations.push_back(res);
                return true;
            }
        }
    }
    return false;
}

bool ReservationSystem::makeReservation(const std::string& course_code, const std::string& room_name, int from, int to) {
    if (!hasCourse(course_code)) {return false;}
    if (!hasRoom(room_name)) {return false;}
    if (from < 0) {return false;}
    if ((to-from) < 1) {return false;}
    for(Room& room : rooms) {
        if (room.name == room_name) {
            if (!room.occupy(from,to)) {return false;}
            Reservation res(room_name, course_code, from, to);
            reservations.push_back(res);
            return true;
        }
    }
    return false;
}
