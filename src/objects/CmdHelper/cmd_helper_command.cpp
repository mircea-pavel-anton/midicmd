#include "cmd_helper.hpp"

void CmdHelper::commandAdd() {}

void CmdHelper::commandRemove() {
	commandList();

	std::map<int, const char*> commands = configHelper->getCommands();
	int value = 0;
	bool is_value_ok = false;
	std::string user_input = "";

	std::cout << std::endl;
	do {
		std::cout << "Which event ID do you want to remove?";
		std::cin >> user_input;
		try {
			value = std::stoi(user_input);
			is_value_ok = (commands.find(value) != commands.end());
		} catch (std::invalid_argument &err) {
			std::cout << toRed("Invalid argument!") << std::endl;
			is_value_ok = false;
		}
	} while (!is_value_ok);

	commands.erase(value);
	configHelper->setCommands(commands);
}

void CmdHelper::commandList() {
	std::map<int, const char*> commands = configHelper->getCommands();
	std::map<int, const char*>::iterator it = commands.begin();

	std::cout << toYellow("There are ") << toYellow(std::to_string(commands.size()));
	std::cout << toYellow(" commands configured: ") << std::endl;
	for (it; it != commands.end(); ++it) {
		std::cout << it->first << ": " << it->second << std::endl;
	}
}

void CmdHelper::commandHelp() {
	using std::cout; using std::endl;

	cout << toYellow("Usage: ") << "midicmd command [OPTION]" << endl << endl;
	cout << "Available options: " << endl;

	cout << toBold("    add\t\t") << "Run through the wizard to add a new command mapping." << endl;
	cout << toBold("    rm\t\t") << "Remove an existing command." << endl;
	cout << toBold("    ls\t\t") << "Lists all commands." << endl;
	cout << endl;
}
