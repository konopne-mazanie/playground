#include "interface.hpp"
using namespace std;

Interpret::Interpret(istream& world, istream& program) {
    //load programu blok
    {
    string in1 = "";
    string in2 = "";
    string in3 = "";
    stringstream stream;

    string currproc = " null";
    string lastcommand = "";
    Procedure nullproc(" null");
    procedures.push_back(nullproc);
    unsigned int lineno = 0;
    
    while(program) {
        stream.clear();
        lineno++;
        getline(program, in1);
        stream.str(in1);

        in1 = "";
        in2 = "";
        in3 = "";
        stream >> in1;
        if (in1.empty() || (in1[0] == '#')) {
            stream.ignore();
            continue;
        }

        stream >> in2;
        stream >> in3;

        if (!in3.empty()) {
            cout << "::" << in1 << "::" << in2 << "::" << in3 << "::\n";
            Complain::invalidSource(lineno, "third word in line");
        }
        
        if (in1 == "DEFINE") {
            if (currproc != " null") {
                Complain::invalidSource(lineno, "missend");
            }
            if (in2.empty()) {
                Complain::invalidSource(lineno, "noparam");
            }
            for (char c : in2) {
                if (!isalnum(c)) {
                    Complain::invalidSource(lineno, "noalnumname");
                }
            }
            if ((procnames.find(in2) == procnames.end()) && (jumps.find(in2) == jumps.end()) && (basiccomm.find(in2) == basiccomm.end()) && (in2 != "DEFINE")&& (in2 != "END")) {
                addprocedure(in2);
                currproc = in2;
            }
            else {
                Complain::invalidSource(lineno, "forbiddenname");
            }
        }
        else if (in1 == "END") {
            if (!in2.empty()) {
                Complain::invalidSource(lineno, "end with param");
            }
            currproc = " null";
        }
        else if (jumps.find(in1) != jumps.end()) {
            if (in2.empty()) {
                Complain::invalidSource(lineno, "noparam");
            }
            for (char c : in2) {
                if (!isalnum(c)) {
                    Complain::invalidSource(lineno, "noalnumname");
                }
            }
            if ((jumps.find(in2) == jumps.end()) && (in2 != "DEFINE") && (in2 != "END")) {
                if ((in1 == "ELSE") && !((lastcommand == "IFWALL") || (lastcommand == "IFWALL"))) {
                    Complain::invalidSource(lineno, "lonelyelse");
                }
                else {
                    procedures[procedures.size()-1].addcommand(in1,in2);
                }
            }
            else {
                Complain::invalidSource(lineno, "forbiddenname");
            }
        }
        else {
            if (!in2.empty()) {
                Complain::invalidSource(lineno, "param with noparam command");
            }

            procedures[procedures.size()-1].addcommand(in1);
        }
        lastcommand = in1;
    }
    }
    //overenie referencii blok
    {
    procedures.erase(procedures.begin());
    procnames.erase(" null");
    bool cointainmain = false;
    for(const Procedure& proc : procedures) {
        if (proc.name == "MAIN") {
            check_ref(proc);
            cointainmain = true;
            break;
        }
    }
    if (!cointainmain) {
        Complain::undefinedReference("@ENTRY", "MAIN");
    }
    }

    //load sveta blok
    {
    world >> wrld.wwidth;
    world >> wrld.wheight;
    world.ignore();
    world >> rbt.startposx;
    world >> rbt.startposy;
    world >> rbt.dir;
    string line;
    int count = 0;
    unsigned int lineno = 3;
    world.ignore();

    if (!((rbt.dir == 'n') || (rbt.dir == 'e') || (rbt.dir == 's') || (rbt.dir == 'w'))) {
        Complain::invalidWorld(2, "e3"); //riadok s poziciou robota
    }
    
    int count2 = 0;
    while(count < wrld.wheight) {
        if (getline(world, line)) {
            lineno++;
            count ++;
            for (char c : line) {
                count2++;
                Tile til;
                Position pos;
                pos.y = count-1;
                pos.x = count2-1;
                wrld.worldpos.push_back(pos);
                if (c == ' ') {}
                else if (c == '#') {
                    til.wall = true;
                }
                else if (isdigit(c)) {
                    til.marks = c - '0';
                }
                else {
                    Complain::invalidWorld(lineno);
                }
                wrld.wordtile.push_back(til);
            }

            if (count2 != wrld.wwidth) {
                Complain::invalidWorld(lineno);
            }
            count2 = 0;
        }
        else {
            Complain::invalidWorld(lineno);
        }
    }
    if (getline(world, line)) {
        Complain::invalidWorld(lineno);
    }
    }
    //kontrola sveta blok
    {

    if (wrld.gettile(rbt.startposx,rbt.startposy).wall) {
        Complain::invalidWorld(2, "e2"); //riadok s poziciou robota
    }
    }
    //vytvorenie fronty prikazov a zaciatok vykonavania
    {
    for(const Procedure& proc : procedures) {
        if (proc.name == "MAIN") {
            Program::translateProc(procedures, jumps, basiccomm, commq, proc);
            isrunning = true;
            currproc = "MAIN";
            break;
        }
    }
    }
}

void Interpret::check_ref(const Procedure& proc) {
    for(const Command& comm : proc.commands) {
        if (jumps.find(comm.name) != jumps.end()) {
            if (basiccomm.find(comm.param) != basiccomm.end()) {
                continue;
            }
            else if (comm.param == proc.name) {
                continue;
            }
            else if (procnames.find(comm.param) != procnames.end()) {
                for (Procedure& pr : procedures) {
                    if (pr.name == comm.param) {
                        check_ref(pr);
                        break;
                    }
                }
                continue;
            }
            else {
                Complain::undefinedReference(proc.name, comm.param);
            }
        }
        else if (basiccomm.find(comm.name) != basiccomm.end()) {
            continue;
        }
        else {
            if (procnames.find(comm.name) != procnames.end()) {
                for (Procedure& pr : procedures) {
                    if (pr.name == comm.name) {
                        check_ref(pr);
                        break;
                    }
                }
                continue;
            }
            else {
                Complain::undefinedReference(proc.name, comm.name);
            }
        }
    }
}

void Interpret::addprocedure(const std::string name) {
    procedures.push_back(Procedure(name));
    procnames.insert(name);
}

bool Interpret::hasProcedure(const std::string& name) const {
    if (procnames.find(name) != procnames.end()) {
        return true;
    }
    return false;
}

bool Interpret::step() {
    if (commq.empty()) {
        return false;
    }
    Command currcomm = commq.front();
    commq.pop_front();
    if (currcomm.parentprocname != currproc) {
        currproc = currcomm.parentprocname;
        return true;
    }
    if (currcomm.name == "SKIP") {
        if (commq.empty()) {
            isrunning = false;
            currproc = " nullproc";
            return false;
        }
        return true;
    }
    if (currcomm.name == "HALT") {
        commq.clear();
        isrunning = false;
        currproc = " null";
        return false;
    }
    if (currcomm.name == "BREAK") {
        while (commq.front().parentprocname == currproc) {
            commq.pop_front();
        }
        if (commq.empty()) {
            isrunning = false;
            currproc = " nullproc";
            return false;
        }
        currproc = commq.front().parentprocname;
    }
    if (currcomm.name == "MOVE") {
        if (!Program::move(rbt, wrld)) {
            Complain::runtimeError(currcomm.parentprocname, currcomm.index);
        }
        if (commq.empty()) {
            isrunning = false;
            currproc = " nullproc";
            return false;
        }
    }
    if (currcomm.name == "LEFT") {
        Program::left(rbt);
        if (commq.empty()) {
            isrunning = false;
            currproc = " nullproc";
            return false;
        }
    }
    if (currcomm.name == "RIGHT") {
        Program::right(rbt);
        if (commq.empty()) {
            isrunning = false;
            currproc = " nullproc";
            return false;
        }
    }
    if (currcomm.name == "PICKUP") {
        if (!Program::pickup(rbt,wrld)) {
            Complain::runtimeError(currcomm.parentprocname, currcomm.index);
        }
        if (commq.empty()) {
            isrunning = false;
            currproc = " nullproc";
            return false;
        }
    }
    if (currcomm.name == "PUTDOWN") {
        Program::putdown(rbt,wrld);
        if (commq.empty()) {
            isrunning = false;
            currproc = " nullproc";
            return false;
        }
    }
    if (currcomm.name == "IFWALL") {
        if (Program::whatinfront(rbt, wrld).wall) {
            if (commq.front().name == "ELSE") {
                commq.pop_front();
            }
            if (currcomm.recursive) {
                for (int i = currcomm.conditionq.size()-1; i > -1; i--) {
                    commq.push_front(currcomm.conditionq_rec[i]);
                }
                commq.push_front(currcomm);
                for (int i = currcomm.conditionq.size()-1; i > -1; i--) {
                    commq.push_front(currcomm.conditionq[i]);
                }
            }
            else {
                for (int i = currcomm.conditionq.size()-1; i > -1; i--) {
                    commq.push_front(currcomm.conditionq[i]);
                } 
            }
        }
        if (commq.empty()) {
            isrunning = false;
            currproc = " nullproc";
            return false;
        }
    }

    if (currcomm.name == "IFMARK") {
        if (Program::whatinfront(rbt, wrld).marks > 0) {
            if (commq.front().name == "ELSE") {
                commq.pop_front();
            }
            if (currcomm.recursive) {
                for (int i = currcomm.conditionq.size()-1; i > -1; i--) {
                    commq.push_front(currcomm.conditionq_rec[i]);
                }
                commq.push_front(currcomm);
                for (int i = currcomm.conditionq.size()-1; i > -1; i--) {
                    commq.push_front(currcomm.conditionq[i]);
                }
            }
            else {
                for (int i = currcomm.conditionq.size()-1; i > -1; i--) {
                    commq.push_front(currcomm.conditionq[i]);
                } 
            }
        }
        if (commq.empty()) {
            isrunning = false;
            currproc = " nullproc";
            return false;
        }
    }

    if (currcomm.name == "ELSE") {
        if (currcomm.recursive) {
            for (int i = currcomm.conditionq.size()-1; i > -1; i--) {
                commq.push_front(currcomm.conditionq_rec[i]);
            }
            commq.push_front(currcomm);
            for (int i = currcomm.conditionq.size()-1; i > -1; i--) {
                commq.push_front(currcomm.conditionq[i]);
            }
        }
        else {
            for (int i = currcomm.conditionq.size()-1; i > -1; i--) {
                commq.push_front(currcomm.conditionq[i]);
            }
        }
        if (commq.empty()) {
            isrunning = false;
            currproc = " nullproc";
            return false;
        }
    }

    isrunning = false;
    currproc = " null";
    return false;
}

const Robot& Interpret::robot() const {
    return rbt;
}

const World& Interpret::world() const {
    return wrld;
}

bool Interpret::running() const {
    return isrunning;
}

unsigned Interpret::run() {
    unsigned steps = 0u;
    if (!isrunning) {
        return steps;
    }
    while (step()) {
        steps++;
    }
    return steps;
}

Tile& World::gettile(const Position& pos) {
    for (unsigned int i = 0; i < worldpos.size();i++) {
        if ((pos.x == worldpos[i].x) && (pos.y == worldpos[i].y)) {
            return wordtile[i];
        }
    }
    return wordtile[0];
}

Tile& World::gettile(unsigned x, unsigned y) {
    Position pos;
    pos.x = x;
    pos.y = y;
    return gettile(pos);
}

size_t World::width() const {
    return wwidth;
}

size_t World::height() const {
    return wheight;
}

Tile World::tile(Position where) const {
    for (unsigned int i = 0; i < worldpos.size();i++) {
        if ((where.x == worldpos[i].x) && (where.y == worldpos[i].y)) {
            return wordtile[i];
        }
    }
    return wordtile[0];
}

void Program::translateProc(vector<Procedure>& procedures, const set<string>& jumps, const set<string>& basiccomm, deque<Command>& commq,const Procedure& proc) {
    bool isproc = false;
    for (const Command& com : proc.commands) {
        for (const Procedure& pr : procedures) {
            if (pr.name == com.name) {
                translateProc(procedures, jumps, basiccomm,commq,pr);
                isproc = true;
                break;
            }
        }
        if (!isproc) {
            commq.push_back(com);
            if (jumps.find(com.name) != jumps.end()) {
                if (basiccomm.find(com.param) != basiccomm.end()) {
                    commq.back().conditionq.push_back(Command(com.param, com.parentprocname, com.index));
                }
                else if (com.param == proc.name) {
                    commq.back().recursive = true;
                    Procedure pr = proc;
                    Procedure pr2 = proc;
                    pr2.commands.clear();
                    while (!((pr.commands.back().name == com.name) && (pr.commands.back().param == com.param))) {
                        pr2.commands.push_back(pr.commands.back());
                        pr.commands.pop_back();
                    }
                    translateProc(procedures, jumps, basiccomm, commq.back().conditionq, pr);
                    translateProc(procedures, jumps, basiccomm, commq.back().conditionq_rec, pr2);
                }
                else {
                    for (const Procedure& pr : procedures) {
                        if (pr.name == com.param) {
                        translateProc(procedures, jumps, basiccomm, commq.back().conditionq, pr);
                        break;
                        }
                    }
                }
            }
        }
        isproc = false;
    }
}

Tile Program::whatinfront(const Robot& rbt, World& wrld) {
    if (rbt.dir == 'n') {
        if (rbt.startposy == 0) {
            Tile tl;
            tl.wall = true;
            return tl;
        }
        return wrld.gettile(rbt.startposx,rbt.startposy-1);
    }
    else if (rbt.dir == 'w') {
        if (rbt.startposx == 0) {
            Tile tl;
            tl.wall = true;
            return tl;
        }
        return wrld.gettile(rbt.startposx-1,rbt.startposy);
    }
    else if (rbt.dir == 'e') {
        if ((rbt.startposx + 1) == wrld.wwidth) {
            Tile tl;
            tl.wall = true;
            return tl;
        }
        return wrld.gettile(rbt.startposx+1,rbt.startposy);
    }
    else {
        if ((rbt.startposy + 1) == wrld.wheight) {
            Tile tl;
            tl.wall = true;
            return tl;
        }
        return wrld.gettile(rbt.startposx,rbt.startposy+1);
    }
}

bool Program::move(Robot& rbt, World& wrld) {
    if (rbt.dir == 'n') {
        if (rbt.startposy == 0) {
            return false;
        }
        rbt.startposy--;
    }
    else if (rbt.dir == 's') {
        if (rbt.startposy == (wrld.wheight-1)) {
            return false;
        }
        rbt.startposy++;
    }
    else if (rbt.dir == 'e') {
        if (rbt.startposx == (wrld.wwidth-1)) {
            return false;
        }
        rbt.startposx++;
    }
    else {
        if (rbt.startposx == 0) {
            return false;
        }
        rbt.startposx--;
    }
    return true;
}

void Program::right(Robot& rbt) {
    if (rbt.dir == 'n') {
        rbt.dir = 'e'; 
    }
    else if (rbt.dir == 's') {
        rbt.dir = 'w'; 
    }
    else if (rbt.dir == 'w') {
        rbt.dir = 'n'; 
    }
    else {
        rbt.dir = 's';
    }
}

void Program::left(Robot& rbt) {
    if (rbt.dir == 'n') {
        rbt.dir = 'w'; 
    }
    else if (rbt.dir == 's') {
        rbt.dir = 'e'; 
    }
    else if (rbt.dir == 'w') {
        rbt.dir = 's'; 
    }
    else {
        rbt.dir = 'n';
    }
}

bool Program::pickup(Robot& rbt, World& wrld) {
    Tile& tile = wrld.gettile(rbt.startposx,rbt.startposy);
    if (tile.marks == 0) {
        return false;
    }
    tile.marks--;
    return true;
}

void Program::putdown(Robot& rbt, World& wrld) {
    Tile& tile = wrld.gettile(rbt.startposx,rbt.startposy);
    tile.marks++;
}

Direction Robot::direction() const {
    Direction dr = Direction::East;
    if (dir == 'n') {
        dr = Direction::North;
    }
    else if (dir == 's') {
        dr = Direction::South;
    }
    else if (dir == 'w') {
        dr = Direction::West;
    }
    return dr;
}

Position Robot::position() const {
    Position position;
    position.x = startposx;
    position.y = startposy;
    return position;
}
