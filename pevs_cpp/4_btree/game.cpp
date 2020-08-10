#include "game.h"

int main()
{
	std::unique_ptr<pevs::BinTree> pBtree = nullptr;
	{
		std::ifstream in("tree.db");
		if (in.is_open()) {
			pBtree = pevs::BinTree::deserialize(in);
			in.close();
		}
	}
	static const std::string withoutBtree = "aix";
	char action = '\0';
	while (true) {
		printMenu(pBtree != nullptr);
		std::cin >> action;
		std::cin.ignore();
		std::cout << "[INF] Selected: " << action << std::endl;
		if (!pBtree && (withoutBtree.find(action) == std::string::npos)) {
			std::cout << "[ERR] Create tree first by choosing a or i" << std::endl;
			continue;
		}
		switch (action)
		{
		case 'a':
			{
			char question[30];
			std::cout << "Specify root question: " << std::endl;
			std::cin.getline(question, 30);
			pBtree = std::make_unique<pevs::BinTree>(question);
			break;
			}
		case 'b':
		case 'c':
			{
			char isAnimal = '\0';
			char question[30];
			std::cout << "Are you inserting animal (y/n)?" << std::endl;
			std::cin >> isAnimal;
			std::cin.ignore();
			std::cout << "Enter question: " << std::endl;
			std::cin.getline(question, 30);
			pBtree->insertKnowledge(question, (action == 'b'), !(isAnimal == 'y'));
			break;
			}
		case 'd':
			{
			pBtree->reset();
			std::cout << "[INF] Done" << std::endl;
			break;
			}
		case 'e':
		case 'f':
			{
			if (pBtree->move(action == 'e')) std::cout << "[INF] Done" << std::endl;
			else std::cout << "[INF] End reached" << std::endl;
			break;
			}
		case 'g':
			{
			if (pBtree->moveBack()) std::cout << "[INF] Done" << std::endl;
			else std::cout << "[INF] No parent" << std::endl;
			break;
			}
		case 'h':
			{
			std::cout << pBtree->printAct();
			break;
			}
		case 'i':
			{
				play(pBtree);
				break;
			}
		case 'x':
			{
				if (pBtree) {
					std::ofstream out("tree.db");
					if (out.is_open()) {
						pBtree->serialize(out);
						out << "#END#\n";
						out.close();
					} else std::cout << "[ERR] Unable to save db" << std::endl;
				}
				exit(0);
			}
		default:
			std::cout << "[ERR] No such choice" << std::endl;
		}
	}
}

void printMenu(bool isTree) {
	static char divider[21] = "====================";
	std::cout << divider << std::endl;
	std::cout << "Select action: " << std::endl;
	std::cout << "<a> vytvor strom" << std::endl;
	if (isTree)
	{
	std::cout << "<b> vytvor yes naslednika" << std::endl;
	std::cout << "<c> vytvor no naslednika" << std::endl;
	std::cout << "<d> posun sa na root" << std::endl;
	std::cout << "<e> posun sa na yes dieta" << std::endl;
	std::cout << "<f> posun sa na no dieta" << std::endl;
	std::cout << "<g> posun sa na rodica" << std::endl;
	std::cout << "<h> vypise hodnoru aktivneho vrchola a jeho priamych potomkov" << std::endl;
	}
	std::cout << "<i> spustenie hry" << std::endl;
	std::cout << "<x> koniec" << std::endl;
	std::cout << divider << std::endl;
}

void play(std::unique_ptr<pevs::BinTree>& pBtree) {
	if (!pBtree) {
		std::unique_ptr<std::string> animal, question;
		while (!getNewAnimal(animal, question)) {std::cout << ">> Bad Input!" << std::endl;} 
		pBtree = std::make_unique<pevs::BinTree>(*question);
		pBtree->insertKnowledge("Is it " + *animal + "?", true);
		return;
	} else pBtree->reset();

	char prevAction = '\0';
	while (true) {
		char action = '\0';
		std::cout << ">> " << pBtree->getActData() << "(y/n)" << std::endl;
		std::cin >> action;
		std::cin.ignore();
		if (pBtree->onLeaf()) {
			if (action == 'y') std::cout << ">> I guessed right!" << std::endl;
			else {
				std::unique_ptr<std::string> animal, question;
				while (!getNewAnimal(animal, question)) {std::cout << ">> Bad Input!" << std::endl;}
				pBtree->insertKnowledgeLeaf("Is it " + *animal + "?", *question, (prevAction == 'y'));
			}
			return;
		} else if (!pBtree->move(action == 'y')) {
			char animal[10];
			std::cout << ">> What animal are you thinking of?" << std::endl;
			std::cin.getline(animal, 10);
			pBtree->insertKnowledge("Is it " + (std::string) animal + "?", (action == 'y'));
			return;
		} //else move to another question
		prevAction = action;
	}
}

bool getNewAnimal(std::unique_ptr<std::string>& ret_animal, std::unique_ptr<std::string>& ret_question) {
	char animal[10];
	char question[30];
	std::cout << ">> What animal are you thinking of?" << std::endl;
	std::cin.getline(animal, 10);
	std::cout << ">> Please give me a question with answer yes for this animal" << std::endl;
	std::cin.getline(question, 30);
	ret_animal = std::make_unique<std::string>(animal);
	ret_question = std::make_unique<std::string>(question);
	return (!(ret_question->empty() || ret_animal->empty()));
}
