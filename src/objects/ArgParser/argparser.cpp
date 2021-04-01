#include "argparser.hpp"

ArgParser::ArgParser() { cmdHelper = new CmdHelper(); }
ArgParser::~ArgParser() { delete cmdHelper; }

void ArgParser::parse(int argc, char **argv) {
	if (argc < 2) {
		cout << toRed("Insufficient parmeters!") << endl;
		return;
	}
	string command(argv[1]);

	if (command.compare("device") == 0) return parse_device(argc, argv);
	if (command.compare("config") == 0) return parse_config(argc, argv);

	if (command.compare("start") == 0) return cmdHelper->Start();
	if (command.compare("stop") == 0) return cmdHelper->Stop();
	if (command.compare("status") == 0) return cmdHelper->Status();

	if (command.compare("help") == 0) return cmdHelper->help();

	// if we got this far, then argv[1] was an unknown command
	cout << toRed("Unknown command!") << endl;
	cout << "Run " << toYellow("midicmd help") << " for more details." << endl;
} //ArgParser::parse

void ArgParser::parse_device(int argc, char **argv) {
	if (argc < 3) {
		cout << toRed("Insufficient parmeters!") << endl;
		return;
	}
	string command = argv[2];

	if (command.compare("ls") == 0) return cmdHelper->deviceList();
	if (command.compare("ps") == 0) return cmdHelper->deviceStatus();
	if (command.compare("rm") == 0) return cmdHelper->deviceRemove();

	if (command.compare("set") == 0) {
		if (argc == 4) { // midicmd device set X
			try {
				const int arg_value = std::stoi(argv[3]);
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

	if (command.compare("help") == 0) return cmdHelper->deviceHelp();

	// if we got this far, then argv[1] was an unknown command
	cout << toRed("Unknown command!") << endl;
	cout << "Run " << toYellow("midicmd device help") << " for more details." << endl;
}

void ArgParser::parse_config(int argc, char **argv) {
	if (argc < 3) {
		cout << toRed("Insufficient parmeters!") << endl;
		return;
	}
	string command = argv[2];

	if (command.compare("ls") == 0) {
		cout << "Show config contents" << endl; //TODO
		return;
	}
	if (command.compare("rm") == 0) {
		cout << "Delete config contents" << endl; //TODO
		return;
	}

	if (command.compare("init") == 0) {
		cout << "Created config file" << endl; //TODO
		return;
	}

	if (command.compare("reset") == 0) {
		cout << "Config file reset" << endl; //TODO
		return;
	}

	if (command.compare("help") == 0) {
		cout << "config help" << endl; //TODO
		return;
	}

	// if we got this far, then argv[1] was an unknown command
	cout << toRed("Unknown command!") << endl;
	cout << "Run " << toYellow("midicmd config help") << " for more details." << endl;
}
