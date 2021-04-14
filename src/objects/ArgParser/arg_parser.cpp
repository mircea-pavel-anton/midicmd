#include "arg_parser.hpp"

namespace midicmd {

/**
 * Parse the first argument received from the cli, and delegate the parsing to a
 * dedicated method, based on the keyword.
**/
void ArgParser::parse(int argc, char **argv) const {
	if (argc < 2) { // if no argument has been passed
		std::cout << toRed("Insufficient parmeters!") << std::endl;
		return;
	}
	const std::string command(argv[1]);

	if (command.compare("device") == 0) return parse_device(argc, argv);
	if (command.compare("command") == 0) return parse_command(argc, argv);
	if (command.compare("feedback") == 0) return parse_feedback(argc, argv);
	return parse_service(argc, argv);
} //ArgParser::parse(int argc, char **argv)


/**
 * This method gets called if the first argument passed has been `device`,
 * as in: `midicmd device ...`
 * Parse the second argument received from the cli, and call the appropriate
 * helper method.
 * 
 * This method required the `DeviceHelper` found in the `device` namespace.
**/
void ArgParser::parse_device(int argc, char **argv) const {
	if (argc < 3) { // if no argument has been passed
		std::cout << toRed("Insufficient parmeters!") << std::endl;
		return;
	}
	// Get an instance of the required helper
	auto deviceHelper = device::DeviceHelper();

	// Extract the second argument, the particular device option
	// For example, if the user ran `midicmd device list`, this extracts just "list"
	std::string command = argv[2];

	// LIST
	if (command.compare("ls") == 0) return deviceHelper.list();
	if (command.compare("list") == 0) return deviceHelper.list();

	// STATUS
	if (command.compare("ps") == 0) return deviceHelper.status();
	if (command.compare("status") == 0) return deviceHelper.status();

	// SET
	if (command.compare("set") == 0) {
		if (argc == 4) { // midicmd device set X
			try {
				const int arg_value = std::stoi(argv[3]);
				deviceHelper.set(arg_value);
			} catch (std::invalid_argument &err) {
				std::cout << toRed("Invalid argument!") << std::endl;
			}
		} else { // midicmd device set
			deviceHelper.set();
		}
		return;
	}

	if (command.compare("help") == 0) return deviceHelper.help();

	// if we got this far, then argv[2] was an unknown command
	std::cout << toRed("Unknown command!") << std::endl;
	std::cout << "Run " << toYellow("midicmd device help") << " for more details.";
	std::cout << std::endl;
} //ArgParser::parse_device(int argc, char **argv)

/**
 * This method gets called if the first argument passed has been `command`,
 * as in: `midicmd command ...`
 * Parse the second argument received from the cli, and call the appropriate
 * helper method.
 * 
 * This method required the `CommandHelper` found in the `command` namespace.
**/
void ArgParser::parse_command(int argc, char **argv) const {
	if (argc < 3) { // if no argument has been passed
		std::cout << toRed("Insufficient parmeters!") << std::endl;
		return;
	}
	// Get an instance of the required helper
	auto commandHelper = command::CommandHelper();

	// Extract the second argument, the particular device option
	// For example, if the user ran `midicmd command list`, this extracts just "list"
	std::string command = argv[2];

	// ADD
	if (command.compare("add") == 0) return commandHelper.add();

	// LIST
	if (command.compare("ls") == 0) return commandHelper.list();
	if (command.compare("list") == 0) return commandHelper.list();

	// REMOVE
	if (command.compare("rm") == 0) return commandHelper.remove();
	if (command.compare("remove") == 0) return commandHelper.remove();

	// HELP
	if (command.compare("help") == 0) return commandHelper.help();

	// if we got this far, then argv[2] was an unknown command
	std::cout << toRed("Unknown command!") << std::endl;
	std::cout << "Run " << toYellow("midicmd command help") << " for more details.";
	std::cout << std::endl;
} //ArgParser::parse_command(int argc, char **argv)

/**
 * This method gets called if the first argument passed has been `feedback`,
 * as in: `midicmd feedback ...`
 * Parse the second argument received from the cli, and call the appropriate
 * helper method.
 * 
 * This method required the `FeedbackHelper` found in the `feedback` namespace.
**/
void ArgParser::parse_feedback(int argc, char **argv) const {
	if (argc < 3) { // if no argument has been passed
		std::cout << toRed("Insufficient parmeters!") << std::endl;
		return;
	}
	// Get an instance of the required helper
	auto feedbackHelper = feedback::FeedbackHelper();

	// Extract the second argument, the particular device option
	// For example, if the user ran `midicmd feedback status`, this extracts just "status"
	std::string command = argv[2];

	// TOGGLE (ENABLE/DISABLE)
	if (command.compare("enable") == 0) return feedbackHelper.enable();
	if (command.compare("disable") == 0) return feedbackHelper.disable();

	// STATUS
	if (command.compare("ps") == 0) return feedbackHelper.status();
	if (command.compare("status") == 0) return feedbackHelper.status();
	
	// HELP
	if (command.compare("help") == 0) return feedbackHelper.help();

	// if we got this far, then argv[2] was an unknown command
	std::cout << toRed("Unknown command!") << std::endl;
	std::cout << "Run " << toYellow("midicmd feedback help") << " for more details.";
	std::cout << std::endl;
} //ArgParser::parse_feedback(int argc, char **argv)

/**
 * This method gets called if the first argument passed has not been any of the
 * previous ones, so no `device`, `command` or `feedback`.
 * This means that it's either an unknown command, or a command that should interact
 * with the midicmd service.
 *  
 * This method required the `ServiceHelper` found in the `service` namespace.
**/
void ArgParser::parse_service(int argc, char **argv) const {
	if (argc > 2) { // if too many arguments have been passed
		std::cout << toRed("Too many arguments!") << std::endl;
		return;
	}
	// Get an instance of the required helper
	auto serviceHelper = service::ServiceHelper();
	
	// Extract the second argument, the particular device option
	// For example, if the user ran `midicmd start`, this extracts just "start"
	std::string command(argv[1]);

	// INITIALIZATION
	if (command.compare("init") == 0) return serviceHelper.init();

	// START/STOP
	if (command.compare("start") == 0) return serviceHelper.start();
	if (command.compare("stop") == 0) return serviceHelper.stop();

	// ENABLE/DISABLE
	if (command.compare("enable") == 0) return serviceHelper.enable();
	if (command.compare("disable") == 0) return serviceHelper.disable();

	// STATUS
	if (command.compare("status") == 0) return serviceHelper.status();
	if (command.compare("ps") == 0) return serviceHelper.status();

	// RUN
	if (command.compare("run") == 0) return serviceHelper.run();

	// HELP
	if (command.compare("help") == 0) return serviceHelper.help();

	// if we got this far, then argv[1] was an unknown command
	std::cout << toRed("Unknown command!") << std::endl;
	std::cout << "Run " << toYellow("midicmd help") << " for more details.";
	std::cout << std::endl;
} //ArgParser::parse_service(int argc, char **argv)

} //namespace midicmd