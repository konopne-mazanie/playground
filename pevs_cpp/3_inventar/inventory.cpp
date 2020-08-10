#include "inventory.h"

int main()
{
	pevs::InventoryHolder inventory;
	char input_buffer[20];
	char action = '\0';
	while (true) {
		printMenu();
		std::cin >> action;
		std::cin.ignore();
		std::cout << "[INF] Selected: " << action << std::endl;
		switch (action)
		{
		case 'i':
			{
			int type = -1;
			std::cout << "Enter type nr: ";
			std::cin >> type;
			std::cin.ignore();
			if (type < 0) {
				std::cout << "[ERR] Bad type" << std::endl;
				continue;
			}
			inventory.printInventory(nullptr, type);
			break;
			}
		case 'k':
		case 'p':
			{
			int type = -1;
			std::cout << "Enter type nr: ";
			std::cin >> type;
			std::cin.ignore();
			if (type < 0) {
				std::cout << "[ERR] Bad type" << std::endl;
				continue;
			}
			int count = -1;
			std::cout << "Enter count of items: ";
			std::cin >> count;
			std::cin.ignore();
			if (type < 0) {
				std::cout << "[ERR] Bad input" << std::endl;
				continue;
			}
			float price = -1.0;
			std::cout << "Enter price of item: ";
			std::cin >> price;
			std::cin.ignore();
			if (price < 0.0) {
				std::cout << "[ERR] Bad input" << std::endl;
				continue;
			}
			if (action == 'k') inventory.buy(type, count, price);
			else {
				if (!inventory.sell(type, count, price)) std::cout << "[ERR] Transaction not completed" << std::endl;
			}
			break;
			}
		case 'n':
			{
				std::cout << "Enter file name: ";
				std::cin.getline(input_buffer, 20);
				inventory.loadInventory(input_buffer);
				break;
			}
		case 'w':
			{
				std::cout << "Enter file name: ";
				std::cin.getline(input_buffer, 20);
				inventory.printInventory(input_buffer);
				break;
			}
		case 's':
			{
				inventory.printInventory(nullptr);
				break;
			}
		case 'e':
			{
				exit(0);
			}
		default:
			std::cout << "[ERR] No such choice" << std::endl;
		}
	}
	return 0;
}

void printMenu() {
	static char divider[21] = "====================";
	std::cout << divider << std::endl;
	std::cout << "Select action: " << std::endl; // bol som lenivy to predkladat, zvysok programu v EN
	std::cout << "<i> Inventar 	  - vypis inventar pre typ polozky" << std::endl;
	std::cout << "<k> Kup	   	  - Nakup N kusov polozky" << std::endl;
	std::cout << "<p> Predaj   	  - Predaj N kusov polozky" << std::endl;
	std::cout << "<n> Nacitaj  	  - Nacitaj inventar zo suboru" << std::endl;
	std::cout << "<w> Write    	  - Zapis inventar do suboru" << std::endl;
	std::cout << "<s> Statistika  - Vypis inventar" << std::endl;
	std::cout << "<e> Exit  	  - Ukonc program" << std::endl;
	std::cout << divider << std::endl;
}

