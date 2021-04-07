#include "arg_parser.hpp"

ArgParser::ArgParser() {
	midiHelper = new MidiHelper();

	configHelper = new ConfigHelper();
	feedbackHelper = new FeedbackHelper(configHelper);
	serviceHelper = new ServiceHelper(midiHelper, configHelper);
	deviceHelper = new DeviceHelper(midiHelper, configHelper);
	commandHelper = new CommandHelper(midiHelper, configHelper);
}

ArgParser::~ArgParser() {
	if (serviceHelper != nullptr) delete serviceHelper;
	if (midiHelper != nullptr) delete midiHelper;
	if (deviceHelper != nullptr) delete deviceHelper;
	if (feedbackHelper != nullptr) delete feedbackHelper;
	if (configHelper != nullptr) delete configHelper;
}


void ArgParser::parse(int argc, char **argv) {
	if (argc < 2) {
		std::cout << toRed("Insufficient parmeters!") << std::endl;
		return;
	}
	std::string command(argv[1]);

	if (command.compare("device") == 0) return parse_device(argc, argv);
	if (command.compare("command") == 0) return parse_command(argc, argv);
	if (command.compare("feedback") == 0) return parse_feedback(argc, argv);

	if (command.compare("start") == 0) return serviceHelper->start();
	if (command.compare("stop") == 0) return serviceHelper->stop();
	if (command.compare("status") == 0) return serviceHelper->status();
	if (command.compare("run") == 0) return serviceHelper->run();

	if (command.compare("help") == 0) return serviceHelper->help();

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

	if (command.compare("ls") == 0) return deviceHelper->list();
	if (command.compare("list") == 0) return deviceHelper->list();

	if (command.compare("ps") == 0) return deviceHelper->status();
	if (command.compare("status") == 0) return deviceHelper->status();

	if (command.compare("set") == 0) {
		if (argc == 4) { // midicmd device set X
			try {
				const int arg_value = std::stoi(argv[3]);
				deviceHelper->set(arg_value);
			} catch (std::invalid_argument &err) {
				std::cout << toRed("Invalid argument!") << std::endl;
			}
		} else { // midicmd device set
			deviceHelper->set();
		}
		return;
	}

	if (command.compare("help") == 0) return deviceHelper->help();

	// if we got this far, then argv[1] was an unknown command
	std::cout << toRed("Unknown command!") << std::endl;
	std::cout << "Run " << toYellow("midicmd device help") << " for more details.";
	std::cout << std::endl;
}

void ArgParser::parse_command(int argc, char **argv) {
	if (argc < 3) {
		std::cout << toRed("Insufficient parmeters!") << std::endl;
		return;
	}
	std::string command = argv[2];

	if (command.compare("add") == 0) return commandHelper->add();

	if (command.compare("ls") == 0) return commandHelper->list();
	if (command.compare("list") == 0) return commandHelper->list();

	if (command.compare("rm") == 0) return commandHelper->remove();
	if (command.compare("remove") == 0) return commandHelper->remove();

	if (command.compare("help") == 0) return commandHelper->help();

	// if we got this far, then argv[1] was an unknown command
	std::cout << toRed("Unknown command!") << std::endl;
	std::cout << "Run " << toYellow("midicmd command help") << " for more details.";
	std::cout << std::endl;
}

void ArgParser::parse_feedback(int argc, char **argv) {
	if (argc < 3) {
		std::cout << toRed("Insufficient parmeters!") << std::endl;
		return;
	}
	std::string command = argv[2];

	if (command.compare("enable") == 0) return feedbackHelper->enable();

	if (command.compare("disable") == 0) return feedbackHelper->disable();

	if (command.compare("ps") == 0) return feedbackHelper->status();
	if (command.compare("status") == 0) return feedbackHelper->status();

	if (command.compare("help") == 0) return feedbackHelper->help();

	// if we got this far, then argv[1] was an unknown command
	std::cout << toRed("Unknown command!") << std::endl;
	std::cout << "Run " << toYellow("midicmd feedback help") << " for more details.";
	std::cout << std::endl;
}