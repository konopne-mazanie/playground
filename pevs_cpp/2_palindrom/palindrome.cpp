#include "palindrome.h"

int main(int argc, char **argv)
{
	auto& logger = pevs::Logger::getInstance();
	std::unique_ptr<pevs::Stack> stack1 = nullptr;
	std::unique_ptr<pevs::Stack> stack2 = nullptr;

	char input[30];
	int action = 0;
	while (true) {
		printMenu(logger);
		std::cin >> action;
		std::cin.ignore();
		sprintf(input, "[INF] Selected: %d", action);
		logger.log(input);
		if ((action > 2) && (!stack1 || !stack2)) {
				logger.log("[ERR] No stacks!");
				continue;
		}
		switch (action)
		{
		case 0:
			exit(0);
		case 1:
		case 2:
			{
				stack1 = std::make_unique<pevs::Stack>();
				stack2 = std::make_unique<pevs::Stack>();
				logger.log("[INF] DONE");
				break;
			}
		case 3:
			{
				std::cin.getline(input, 30);
				logger.log(input);
				for (int i = 0; i < strlen(input); i++) {
					if (!stack1->push(input[i]) || !stack2->push(input[i])) {
						logger.log("[ERR] Stack overflow!");
						break;
					}
				}
				break;
			}
		case 4:
			{
				logger.log(stack1->toString());
				break;
			}
		case 5:
			{
				logger.log(stack2->toReverseString().cbegin());
				break;
			}
		case 6:
			{
				int pos1 = 0;
				int pos2 = 0;
				char c1, c2 = ' ';
				do {
					do {c1 = stack1->get(pos1++);} while ((c1 != '\0') && !isalpha(c1));
					do {c2 = stack2->getFront(pos2++);} while ((c2 != '\0') && !isalpha(c2));
					if (tolower(c1) != tolower(c2)) {
						logger.log("Not palindrome");
						goto end; //creating additional variable for this is even uglier, so...
					}
				} while (c1 != '\0');

				logger.log("Palindrome");
				end:
				break;
			}
		default:
			logger.log("[ERR] Invalid option)");
		}
	}
	return 0;
}

void printMenu(pevs::Logger& logger) {
	static char divider[21] = "====================";
	logger.log(divider);
	logger.log("PALINDROME");
	logger.log(divider);
	logger.log("0 :: Exit");
	logger.log("1 :: Create two empty stacks");
	logger.log("2 :: Empty both stacks");
	logger.log("3 :: Load string");
	logger.log("4 :: Print first stack");
	logger.log("5 :: Print second stack");
	logger.log("6 :: Determine whether stored string is palindrome");
	logger.log(divider);
}
