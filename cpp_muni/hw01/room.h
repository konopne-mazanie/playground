#pragma once
#include <iostream>
#include <string>


class Room {
    bool reserved[24];
    public:
    const std::string name;
	    Room(const std::string& name)
	        : name(name) {
                for (int i = 0; i < 24; i++) {
                    reserved[i] = false;
                }
            }
        bool isFree(int from, int to) const {
            if ((from >= to) || (from < 0) || (to > 24)) {return false;}
            for (int i = from; i < to; i++) {
                if (reserved[i]) {
                    return false;
                }
            }
            return true;
        }
        int isFreeFor(int duration) const {
            if (duration == 0) {return 0;}
            int count = 0;
            for (int i = 0; i < 24; i++) {
                if (!reserved[i]) {
                    count++;
                }
                else {
                    count = 0;
                    continue;
                }
                if (count == duration) {
                    return (i-count+1);
                }
            }
            return -1;
        }
        bool occupy(int from,int to) {
            if (isFree(from,to)) {
                for (int i = from; i < to; i++) {
                    reserved[i] = true;
                }
                return true;
            }
            return false;
        }
        void print() const {
            std::cout << "Room: " << name << "\n";
        }
        void schedule() const {
            for (int i = 0; i < 24;i++) {
                if (reserved[i]) {
                    std::cout << "X";
                }
                else {
                    std::cout << "_";
                }
            }
            std::cout << "\n";
        }
};
