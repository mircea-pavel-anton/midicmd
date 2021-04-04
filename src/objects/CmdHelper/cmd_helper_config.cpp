#include "cmd_helper.hpp"

void CmdHelper::configInit() {
	deviceSet();

	char user_input = ' ';
	do {
		std::cout << "Do you wish to enable MiDi feedback? [y/n]: ";
		std::cin >> user_input;
	} while (!std::cin.fail() && user_input != 'y' && user_input != 'n' && user_input != 'Y' && user_input != 'N');

	if (user_input == 'y' || user_input == 'Y') feedbackEnable();
	else feedbackDisable();

	do {
		commandAdd();

		std::cout << "Do you wish to add more commands? [y/n]";
		std::cin >> user_input;
	} while (!std::cin.fail() && user_input == 'y' && user_input == 'Y');

	std::cout << toGreen("Configuration wizard complete!") << std::endl;
	std::cout << "You can test your configuration via " << toYellow("midicmd run") << std::endl;
	std::cout << "Or you can start the daemon via " << toYellow("midicmd start") << std::endl;
}

void CmdHelper::configReset() {
	std::cout << "This command is about to delete all the contents of the config file!" << std::endl;
	char user_input = ' ';
	do {
		std::cout << "Are you sure you want to continue? [y/N]: ";
		std::cin >> user_input;
	} while( !std::cin.fail() && user_input != 'y' && user_input != 'n' );
	
	if (user_input == 'y') {
		Config blank = Config();
		configHelper->write(blank);
		std::cout << toGreen("Config file reset was successful.") << std::endl;
	} else {
		std::cout << toYellow("Config file reset was aborted.") << std::endl;
	}
}

void CmdHelper::configCheck() {
	if (!isConfigOk()) {
		std::cout << toRed("Failed to parse config file!") << std::endl;
		std::cout << "If no modifications have been made to the config file, run " << toYellow("midicmd config init");
		std::cout << " to create a default file, and then customize it." << std::endl;
		std::cout << "Run " << toYellow("midicmd config help") << " for more details on config file customizations";
		std::cout << std::endl;
	} else {
		std::cout << "Config file status: " << toGreen("OK") << std::endl;
	}
}

void CmdHelper::configHelp() {
	using std::cout; using std::endl;

	cout << toYellow("Usage: ") << "midicmd config [OPTION]" << endl << endl;
	cout << "Available options: " << endl;

	cout << toBold("    init\t\t") << "Run through the setup wizard." << endl;
	cout << toBold("    reset\t\t") << "Resets configuration to default." << endl;
	cout << toBold("    check\t\t") << "Check the integrity of the config file." << endl;
	cout << endl;
}