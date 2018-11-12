#include "handler.h"
#include <stdexcept>
//vymaz tieto includy
#include "rsystem.h"

int main() {
	try {
		Handler().handle();
	} catch (std::runtime_error& ex) {
		std::cerr << "Exception: " << ex.what() << '\n';
	}


	//Room implementation test
	/*
	Room room("izba");
	room.print();
	room.schedule();
	room.occupy(10,20);
	room.schedule();
	if (room.isFree(9,10)) {std::cout << "true\n";}
	std::cout << "---\n";
	if (room.isFree(10,11)) {std::cout << "true\n";}
	std::cout << "---\n";
	std::cout << room.isFreeFor(10) << "\n";
	std::cout << "---\n";
	std::cout << room.isFreeFor(11) << "\n";
	*/

	//Course implementation test
	/*
	Course kurz("ib102","Marian Kotleba");
	Course kurz2("pb161", "");
	std::cout << kurz.code << kurz2.code << "\n" << kurz.teacher << kurz2.teacher << "\n";
	kurz.print();
	kurz2.print();
	*/

	//reservation implementation test
	/*
	Reservation reska("telocvicna", "pb161", 0, 20);
	reska.print();
	*/

	//test rsystem prvy blok
	/*
	ReservationSystem rsystem;
	if (rsystem.addRoom("izba") == true) {std::cout << "true";} else {std::cout << "false";}
	if (rsystem.addRoom("izba")== true) {std::cout << "true";} else {std::cout << "false";}
	if (rsystem.addRoom("neizba")== true) {std::cout << "true";} else {std::cout << "false";}
	*/
	return 0;
}
