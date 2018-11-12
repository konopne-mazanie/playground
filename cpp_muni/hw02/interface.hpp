#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#pragma once

#include<iostream>
#include <string>
#include<set>
#include <algorithm>
#include <deque>
#include "defs.hpp"
#include "errors.hpp"

class Command {
    friend class Program;
    friend class Interpret;
    std::deque<Command> conditionq;
    std::deque<Command> conditionq_rec;
    bool recursive = false;
    public:
    std::string name;
    std::string param;
    const std::string parentprocname;
    const int index;
    Command(const std::string& name, const std::string& parentprocname, const int index)
    : name(name), parentprocname(parentprocname), index(index) {}
    Command(const std::string& name, const std::string& param, const std::string& parentprocname, const int index)
    : name(name), param(param), parentprocname(parentprocname), index(index) {}
};

class Procedure {
    int index = 0;
    public:
    std::string name;
    std::vector<Command> commands;
    Procedure(const std::string& name)
    : index(0), name(name) {}
    void addcommand(const std::string& nam) {
        commands.push_back(Command(nam, name, index));
        index++;
    }
    void addcommand(const std::string& nam, const std::string& param) {
        commands.push_back(Command(nam, param, name, index));
        index++;
    }
};

class Robot {
    friend class Interpret;
    friend class Program;
    char dir = 'o';
    int startposx = 0;
    int startposy = 0;
    public:
    Robot() {}
    Position position() const;
    Direction direction() const;
};

class World {
    friend class Interpret;
    friend class Program;
    std::vector<Position> worldpos;
    std::vector<Tile> wordtile;
    int wheight = 0;
    int wwidth = 0;
    public:
    World() {}
    size_t width() const;
    size_t height() const;
    Tile tile(Position where) const;
    Tile& gettile(const Position& pos);
    Tile& gettile(unsigned x, unsigned y);
};

class Interpret {
    friend class Program;
    std::vector<Procedure> procedures;
    const std::set<std::string> basiccomm = {"SKIP", "BREAK", "HALT", "MOVE", "LEFT", "RIGHT", "PICKUP", "PUTDOWN"};
    const std::set<std::string> jumps = {"IFWALL", "IFMARK", "ELSE"};
    std::set<std::string> procnames;
    World wrld;
    Robot rbt;
    bool isrunning = false;
    std::string currproc = " null";
    std::deque<Command> commq;
    public:
    Interpret(std::istream& world, std::istream& program);
    const Robot& robot() const;
    const World& world() const;
    bool hasProcedure(const std::string& name) const;
    bool running() const;
    bool step();
    unsigned run();
    private:
    void addprocedure(const std::string name);
    void check_ref(const Procedure& proc);
};

class Program {
    private:
    Program() {}
    public:
    static void translateProc(std::vector<Procedure>& procedures, const std::set<std::string>& jumps, const std::set<std::string>& basiccomm, std::deque<Command>& commq, const Procedure& proc);
    static Tile whatinfront(const Robot& rbt, World& wrld);
    static bool move(Robot& rbt, World& wrld);
    static void right(Robot& rbt);
    static void left(Robot& rbt);
    static bool pickup(Robot& rbt, World& wrld);
    static void putdown(Robot& rbt, World& wrld);
};

#endif // INTERFACE_HPP
