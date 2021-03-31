#include "argparser.hpp"

ArgParser::ArgParser() {}

void ArgParser::parse(int argc, char **argv) {
	if (argc < 2) {
		std::cout << "Insufficient parameters!" << std::endl;
		return;
	}

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
	if (argc < 3) {
		std::cout << "Insufficient parameters!" << std::endl;
		return;
	}

	if ( strcmp(argv[2], "ls") == 0 ) {
		std::cout << "List of devices:" << std::endl;
		return;
	}

	if ( strcmp(argv[2], "set") == 0 ) {
		std::cout << "Device set!" << std::endl;
		return;
	}

	if ( strcmp(argv[2], "rm") == 0 ) {
		std::cout << "Device unset" << std::endl;
		return;
	}

	if ( strcmp(argv[2], "help") == 0 ) {
		std::cout << "device help" << std::endl;
		return;
	}
}

void ArgParser::parse_config(int argc, char **argv) {
	if (argc < 3) {
		std::cout << "Insufficient parameters!" << std::endl;
		return;
	}

	if ( strcmp(argv[2], "ls") == 0 ) {
		std::cout << "Show config contents" << std::endl;
		return;
	}
	if ( strcmp(argv[2], "rm") == 0 ) {
		std::cout << "Delete config contents" << std::endl;
		return;
	}

	if ( strcmp(argv[2], "init") == 0 ) {
		std::cout << "Created config file" << std::endl;
		return;
	}

	if ( strcmp(argv[2], "reset") == 0 ) {
		std::cout << "Config file reset" << std::endl;
		return;
	}

	if ( strcmp(argv[2], "help") == 0 ) {
		std::cout << "config help" << std::endl;
		return;
	}
}
