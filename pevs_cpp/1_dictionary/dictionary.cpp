#include "dictionary.h"
std::ofstream logfile; //usefull in this specific case
std::stringstream buffer;

int main(int argc, char **argv)
{
	logfile.open("out.txt");

	std::unique_ptr<RecordsHolder> pHldr;
	if (argc > 1) pHldr = std::make_unique<RecordsHolder>(argv[1]);
	else pHldr = std::make_unique<RecordsHolder>("slovnik.txt");
	if (pHldr->isEmpty()) {
		buffer << "[WARNING] Empty dictionary, check source file!" << std::endl;
		doubleStream();
	}

	char input[30];
	int action = 0;
	while (true) {
		printMenu();
		std::cin >> action;
		std::cin.ignore();
		logfile << action << std::endl;
		switch (action)
		{
		case 4:
			logfile.close();
			exit(0);
		default:
			if (0 < action < 4) {
				buffer << "Type word you are looking for: " << std::endl;
				doubleStream();
				std::cin.getline(input, 30);
				logfile << input << std::endl;
				std::vector<const MyString*> res = pHldr->find((RecordsHolder::Action) action, MyString(input));
				if (res.empty()) {
					buffer << "Not found" << std::endl;
				} else if (res.size() == 1) {
					buffer << "| " << *res[0] << " | " << *pHldr->getDefinition(*res[0]) << " |" << std::endl;
				} else {
					for (const auto pMstr: res) buffer << "| " << *pMstr << " |" << std::endl;
				}
				buffer << "Press Enter to countinue..." << std::endl;
				doubleStream();
				std::cin.getline(input, 30);
			}
		}
	}
	return 0;
}

void printMenu() {
	char divider[21] = "====================";
	buffer << divider << std::endl << "DICTIONARY" << std::endl << divider << std::endl;
	buffer << "Choose option:" << std::endl;
	buffer << "1 :: Starts with" << std::endl;
	buffer << "2 :: Ends with" << std::endl;
	buffer << "3 :: Contains" << std::endl;
	buffer << "4 :: Exit" << std::endl;
	buffer << divider << std::endl;
	doubleStream();
}

void doubleStream()
{
	logfile << buffer.str();
	std::cout << buffer.str();
	buffer.str("");
}