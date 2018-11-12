#include "handler.h"

void Handler::handle() {
    std::string input;
    std::string input2;
    int action = -1;
    int duration = -1;
    while (true) {
        std::cout << "0: Ukonci handler\n1: Pridaj miestnost\n2: Pridaj kurz\n3: Pridaj rezervaciu\n4: Vypis vsetky miestnosti\n5: Vypis vsetky kurzy\n6: Vypis vsetky rezervacie\n7: Vypis obsadenost miestnosti\n";
        std::cin >> action;
        std::cin.ignore();
        switch (action) {
            case 0 :
                std::cout << "OK\n";
                return;
            case 1 :
                std::cout << "Zadaj nazov miestnosti:\n";
                std::getline(std::cin, input);
                while (input.empty()) {
                    std::cerr << "Bad input, type again:\n";
                    std::getline(std::cin, input);
                }
                if (!rsystem.addRoom(input)) {std::cerr << "This room already is in the regiter\n";break;}
                std::cout << "OK\n";
                break;
            case 2 :
                std::cout << "Zadaj kod kurzu:\n";
                std::getline(std::cin, input);
                while (input.empty()) {
                    std::cerr << "Bad input, type again:\n";
                    std::getline(std::cin, input);
                }
                std::cout << "Zadaj meno ucitela ak existuje:\n";
                std::getline(std::cin, input2);
                if (!rsystem.addCourse(input,input2)) {std::cerr << "This course already is in the regiter\n"; break;}
                std::cout << "OK\n";
                break;
            case 3 :
                std::cout << "Zadaj kod kurzu:\n";
                std::getline(std::cin, input);
                while (input.empty()) {
                    std::cerr << "Bad input, type again:\n";
                    std::getline(std::cin, input);
                }
                std::cout << "Iba na zaklade trvania?\n";
                std::getline(std::cin, input2);
                while (input2.empty() || (input2 != "yes" && input2 != "no")) {
                    std::cerr << "Bad input, type again:\n";
                    std::getline(std::cin, input2);
                }
                if (input2 == "yes") {
                    std::cout << "Zadaj dlzku:\n";
                    std::cin >> duration;
                    std::cin.ignore();
                    if (!rsystem.makeAnyReservation(input,duration)) {
                        std::cerr << "Error while creating reservation\n";
                        break;
                    }
                }
                else {
                    int from = -1;
                    int to = -1;
                    std::cout << "Zadaj nazov miestnosti:\n";
                    std::getline(std::cin, input2);
                    while (input.empty()) {
                        std::cerr << "Bad input, type again:\n";
                        std::getline(std::cin, input2);
                    }
                    std::cout << "Zadaj zaciatok:\n";
                    std::cin >> from;
                    std::cin.ignore();
                    std::cout << "Zadaj koniec:\n";
                    std::cin >> to;
                    std::cin.ignore();
                    if (!rsystem.makeReservation(input,input2,from,to)) {
                    std::cerr << "Error while creating reservation\n";
                    break;
                    }
                }
                std::cout << "OK\n";
                break;
            case 4 :
                for(const Room& room : rsystem.getRooms()) {
                    room.print();
                }
                std::cout << "OK\n";
                break;
            case 5 :
                for(const Course& crs : rsystem.getCourses()) {
                    crs.print();
                }
                std::cout << "OK\n";
                break;
            case 6 :
                for(const Reservation& res : rsystem.getReservations()) {
                    res.print();
                }
                std::cout << "OK\n";
                break;
            case 7 :
                std::cout << "Zadaj nazov miestnosti:\n";
                std::getline(std::cin, input);
                while (input.empty()) {
                    std::cerr << "Bad input, type again:\n";
                    std::getline(std::cin, input);
                }
                if (!rsystem.hasRoom(input)) {
                    std::cerr << "Room not found\n";
                    break;
                };
                rsystem.getRoom(input).schedule();
                std::cout << "OK\n";
                break;
            default :
                std::cerr << "Command not recognized\n";
        }
    }
}