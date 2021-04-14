#include "command_helper.hpp"

namespace midicmd {
namespace command {

/**
 * An interactive terminal applet that prompts the user to add a new command
 * to the config.
**/
void CommandHelper::add() const {
	// Get an instance of each of the required helpers
	auto configHelper = config::ConfigHelper();
	auto midiHelper = midi::MidiHelper();

	// Check if a midi port has already been opened before calling this method.
	// If it has been opened, carry on. Otherwise, try opening one with the device
	// specified in the config file.
	// If no device is mentioned there, or an invalid one is, then @midi_port will be -1
	// so we show an error message and exit
	if (midiHelper.hasPortOpen() == false) {
		int midi_port = midiHelper.getInputDeviceId( configHelper.getDevice() );
		if (midi_port < 0) {
			std::cout << toRed("Invalid device specified in the config file!") << std::endl;
			std::cout << "You can set a new device using " << toYellow("sudo midicmd device set") << std::endl;
			return;
		}
		midiHelper.setInputDevice(midi_port);
	} 
	
	// Get a map of all the commands from the config file
	// We need it to add a new command or to check if the user tries to overwrite one
	auto commands = configHelper.getCommands();

	// The ok-status of each section of adding a command
	bool status = false;
	midi::MidiEvent event;

	std::cout << "Press the key on your midi device you want to bind a macro to:" << std::endl;
	do {
		event = midiHelper.getMessage();

		if (event.isOk()) {
			std::cout << "Event: " << event.getEventName() << std::endl;
			std::cout << "Channel: " << event.getChannel() << std::endl;
			std::cout << "Note: " << event.getNoteName() << std::endl << std::endl;

			status = getYesNo("Is this ok?");

			if (status == true) {
				if (commands.find(event.getUID()) != commands.end()) {
					std::cout << toYellow("A macro is already bound to this key!") << std::endl;
					std::cout << "By continuing, you will OVERWRITE the existing macro." << std::endl;
					status = getYesNo("Continue?");
					
					if (status) commands.erase(event.getUID());
				}
			}

			if (status == false) std::cout << "Press another key: " << std::endl;
		}
	} while (status == false);

	std::string user_input = "";
	std::cout << "Type in the command you wish this macro to run: " << std::endl;
	do {
		std::getline(std::cin, user_input);
	} while(user_input.size() <= 0);

	std::pair<int, const char*> entry = { event.getUID(), user_input.c_str() };
	commands.emplace(entry);
	configHelper.setCommands(commands);
} //CommandHelper::add()

/* Prints a list of all of the commands currently configured */
void CommandHelper::list() const {
	const auto configHelper = config::ConfigHelper();
	std::map<int, const char*> commands = configHelper.getCommands();

	if (commands.size() == 0) {
		std::cout << toRed("There are no commands in the config file!") << std::endl;
		std::cout << "You can add some with: " << toYellow("sudo midicmd command add") << std::endl;
		return;
	}

	std::cout << toYellow("There are " + std::to_string(commands.size()) + " commands in the config file");
	std::cout << std::endl;
	for (auto it = commands.begin(); it != commands.end(); it++) {
		std::cout << it->first << ": " << it->second << std::endl;
	}
} // CommandHelper::list()

/**
 * Prints a list of all of the commands currently configured, and prompts the user to
 * delete one.
**/
void CommandHelper::remove() const {
	auto configHelper = config::ConfigHelper();
	std::map<int, const char*> commands = configHelper.getCommands();
	if (commands.empty()) {
		std::cout << toRed("There are no commands configured.") << std::endl;
		std::cout << toYellow("There is nothing to delete.") << std::endl;
		return;
	}
	
	// Print al the available commands
	list();

	std::string user_input = "";
	int value = 0; // the integer value that we will extract from @user_input
	bool is_value_ok = false; // whether or not the value extracted from @user_input is ok

	std::cout << std::endl;
	do {
		std::cout << "Enter the event ID of the command you want to remove: ";
		std::cin >> user_input;
		try {
			// extract the int value
			value = std::stoi(user_input);

			// Check if the value is an actual key in the @commands map
			is_value_ok = (commands.find(value) != commands.end());
			if (!is_value_ok) { // if the value is not a key in the map
				std::cout << toRed("Invalid value!") << std::endl;
			}
		} catch (std::invalid_argument &err) { // if the user didn't enter a number
			std::cout << toRed("Invalid argument!") << std::endl;
			is_value_ok = false;
		}
	} while (!is_value_ok);

	if (commands.erase(value) == 1) {
		configHelper.setCommands(commands);
		std::cout << toGreen("Command removed!") << std::endl;
	} else {
		std::cout << toRed("Failed to remove command!") << std::endl;
	}
} //CommandHelper::remove()

/* Shows all the available commands and a short explanation as to what they do */
void CommandHelper::help() const {
	using std::cout; using std::endl;

	cout << toYellow("Usage: ") << "midicmd command [OPTION]" << endl << endl;
	cout << "Available options: " << endl;

	cout << toBold("    add\t\t") << "Run through the wizard to add a new command mapping." << endl;

	cout << toBold("    rm\t\t") << endl;
	cout << toBold("    remove\t\t") << "Remove an existing command." << endl;

	cout << toBold("    ls\t\t") << endl;
	cout << toBold("    list\t\t") << "Lists all commands." << endl;
	cout << endl;
} //CommandHelper::help()


} //namespace command
} //namespace midicmd