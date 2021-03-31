#include "argparser.hpp"

inline void alert_insufficient_params() {
	std::cout << Colors::Foreground::Red;
	std::cout << "Insufficient parameters!";
	std::cout << Colors::Modifiers::Reset << std::endl;
}

ArgParser::ArgParser() {
	cmdHelper = new CmdHelper();
}
ArgParser::~ArgParser() {
	delete cmdHelper;
}

void ArgParser::parse(int argc, char **argv) {
	if (argc < 2) return alert_insufficient_params();	

	if (strcmp(argv[1], "device") == 0) return parse_device(argc, argv);
	if (strcmp(argv[1], "config") == 0) return parse_config(argc, argv);
	if (strcmp(argv[1], "init") == 0) {
		std::cout << "init functions here";
		return;
	}
	if (strcmp(argv[1], "start") == 0) {
		std::cout << "start daemon";
		return;
	}
	if (strcmp(argv[1], "stop") == 0) {
		std::cout << "stop daemon";
		return;
	}
	if (strcmp(argv[1], "status") == 0) {
		std::cout << "status: unknown";
		return;
	}
	if (strcmp(argv[1], "help") == 0) {
		std::cout << "show help";
		return;
	}
}

void ArgParser::parse_device(int argc, char **argv) {
	if (argc < 3) return alert_insufficient_params();

	if ( strcmp(argv[2], "ls") == 0 ) {
		cmdHelper->deviceList();
		return;
	}

	if ( strcmp(argv[2], "set") == 0 ) {
		if (argc == 4) { // midicmd device set X
			try {
				uint16_t arg_value = std::stoi(argv[3]);
				cmdHelper->deviceSet(arg_value);
			} catch (std::invalid_argument &err) {
				std::cout << Colors::Foreground::Red;
				std::cout << "Invalid argument!";
				std::cout << Colors::Modifiers::Reset << std::endl;
				cmdHelper->deviceHelp();
			}
		} else { // midicmd device set
			cmdHelper->deviceSet();
		}
		return;
	}

	if ( strcmp(argv[2], "rm") == 0 ) {
		std::cout << "Device unset" << std::endl; //TODO
		return;
	}

	if ( strcmp(argv[2], "help") == 0 ) {
		cmdHelper->deviceHelp();
		return;
	}
}

void ArgParser::parse_config(int argc, char **argv) {
	if (argc < 3) return alert_insufficient_params();	

	if ( strcmp(argv[2], "ls") == 0 ) {
		std::cout << "Show config contents" << std::endl; //TODO
		return;
	}
	if ( strcmp(argv[2], "rm") == 0 ) {
		std::cout << "Delete config contents" << std::endl; //TODO
		return;
	}

	if ( strcmp(argv[2], "init") == 0 ) {
		std::cout << "Created config file" << std::endl; //TODO
		return;
	}

	if ( strcmp(argv[2], "reset") == 0 ) {
		std::cout << "Config file reset" << std::endl; //TODO
		return;
	}

	if ( strcmp(argv[2], "help") == 0 ) {
		std::cout << "config help" << std::endl; //TODO
		return;
	}
}
