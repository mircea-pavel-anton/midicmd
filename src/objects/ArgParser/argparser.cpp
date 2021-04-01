#include "argparser.hpp"

ArgParser::ArgParser() {
	cmdHelper = new CmdHelper();
}
ArgParser::~ArgParser() {
	delete cmdHelper;
}

void ArgParser::parse(int argc, char **argv) {
	if (argc < 2) {
		cout << toRed("Insufficient parmeters!");
		return;
	}

	if (strcmp(argv[1], "device") == 0) return parse_device(argc, argv);
	if (strcmp(argv[1], "config") == 0) return parse_config(argc, argv);

	if (strcmp(argv[1], "start") == 0) {
		cout << "start daemon";
		return;
	}
	if (strcmp(argv[1], "stop") == 0) {
		cout << "stop daemon";
		return;
	}
	if (strcmp(argv[1], "status") == 0) {
		cout << "status: unknown";
		return;
	}
	if (strcmp(argv[1], "help") == 0) {
		cmdHelper->help();
		return;
	}
} //ArgParser::parse

void ArgParser::parse_device(int argc, char **argv) {
	if (argc < 3) {
		cout << toRed("Insufficient parmeters!");
		return;
	}

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
				cout << toRed("Invalid argument!") << endl;
				cmdHelper->deviceHelp();
			}
		} else { // midicmd device set
			cmdHelper->deviceSet();
		}
		return;
	}

	if ( strcmp(argv[2], "rm") == 0 ) {
		cmdHelper->deviceRemove();
		return;
	}

	if ( strcmp(argv[2], "help") == 0 ) {
		cmdHelper->deviceHelp();
		return;
	}
}

void ArgParser::parse_config(int argc, char **argv) {
	if (argc < 3) {
		cout << toRed("Insufficient parmeters!");
		return;
	}

	if ( strcmp(argv[2], "ls") == 0 ) {
		cout << "Show config contents" << endl; //TODO
		return;
	}
	if ( strcmp(argv[2], "rm") == 0 ) {
		cout << "Delete config contents" << endl; //TODO
		return;
	}

	if ( strcmp(argv[2], "init") == 0 ) {
		cout << "Created config file" << endl; //TODO
		return;
	}

	if ( strcmp(argv[2], "reset") == 0 ) {
		cout << "Config file reset" << endl; //TODO
		return;
	}

	if ( strcmp(argv[2], "help") == 0 ) {
		cout << "config help" << endl; //TODO
		return;
	}
}
