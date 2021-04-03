#include "argparser.hpp"

void ArgParser::parse(int argc, char **argv) {
	if (argc < 2) {
		std::cout << toRed("Insufficient parmeters!") << std::endl;
		return;
	}
	std::string command(argv[1]);

	if (command.compare("device") == 0) return parse_device(argc, argv);
	if (command.compare("config") == 0) return parse_config(argc, argv);

	if (command.compare("start") == 0) return cmdHelper->Start();
	if (command.compare("stop") == 0) return cmdHelper->Stop();
	if (command.compare("status") == 0) return cmdHelper->Status();

	if (command.compare("help") == 0) return cmdHelper->help();

	// if we got this far, then argv[1] was an unknown command
	std::cout << toRed("Unknown command!") << std::endl;
	std::cout << "Run " << toYellow("midicmd help") << " for more details.";
	std::cout << std::endl;
} //ArgParser::parse

void ArgParser::parse_device(int argc, char **argv) {
	if (argc < 3) {
		std::cout << toRed("Insufficient parmeters!") << std::endl;
		return;
	}
	std::string command = argv[2];

	if (command.compare("ls") == 0) return cmdHelper->deviceList();
	if (command.compare("ps") == 0) return cmdHelper->deviceStatus();
	if (command.compare("rm") == 0) return cmdHelper->deviceRemove();

	if (command.compare("set") == 0) {
		if (argc == 4) { // midicmd device set X
			try {
				const int arg_value = std::stoi(argv[3]);
				cmdHelper->deviceSet(arg_value);
			} catch (std::invalid_argument &err) {
				std::cout << toRed("Invalid argument!") << std::endl;
				cmdHelper->deviceHelp();
			}
		} else { // midicmd device set
			cmdHelper->deviceSet();
		}
		return;
	}

	if (command.compare("help") == 0) return cmdHelper->deviceHelp();

	// if we got this far, then argv[1] was an unknown command
	std::cout << toRed("Unknown command!") << std::endl;
	std::cout << "Run " << toYellow("midicmd device help") << " for more details.";
	std::cout << std::endl;
}

void ArgParser::parse_config(int argc, char **argv) {
	if (argc < 3) {
		std::cout << toRed("Insufficient parmeters!") << std::endl;
		return;
	}
	std::string command = argv[2];

	if (command.compare("ls") == 0) {
		std::cout << "Show config contents" << std::endl; //TODO
		return;
	}
	if (command.compare("rm") == 0) {
		std::cout << "Delete config contents" << std::endl; //TODO
		return;
	}

	if (command.compare("init") == 0) {
		std::cout << "Created config file" << std::endl; //TODO
		return;
	}

	if (command.compare("reset") == 0) {
		std::cout << "Config file reset" << std::endl; //TODO
		return;
	}

	if (command.compare("help") == 0) {
		std::cout << "config help" << std::endl; //TODO
		return;
	}

	// if we got this far, then argv[1] was an unknown command
	std::cout << toRed("Unknown command!") << std::endl;
	std::cout << "Run " << toYellow("midicmd config help") << " for more details.";
	std::cout << std::endl;
}
