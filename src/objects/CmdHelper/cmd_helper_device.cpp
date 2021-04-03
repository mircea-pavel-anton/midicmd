#include "cmd_helper.hpp"

void CmdHelper::deviceList() {
	std::vector<std::string> devices = midiHelper->getInputDevices();
	const int device_count = devices.size();

	std::cout << toGreen(
		"There are " +
		std::to_string(device_count) +
		" devices available:"
	) << std::endl;

	for (int i = 0; i < device_count; i++) {
		std::cout << "\t" << i << ") " << devices[i] << std::endl;
	}
}

void CmdHelper::deviceSet() {
	deviceList(); //print a list of all available devices
	int device_count = midiHelper->getInputPortCount();
	std::string user_input = ""; // vaslue entered by the user
	int value; // integer extracted from the user entered string
	bool is_value_ok = false;

	std::cout << std::endl;
	do {
		std::cout << "Choose your device [0-" << device_count-1 << "]: ";
		std::cin >> user_input;
		try {
			value = std::stoi(user_input);
			is_value_ok = (value < device_count && value >= 0);
		} catch (std::invalid_argument &err) {
			std::cout << toRed("Invalid argument!") << std::endl;
			is_value_ok = false;
		}
	} while (!is_value_ok);

	deviceSet(value);
}

void CmdHelper::deviceSet(int port_id) {
	try {
		midiHelper->setInputDevice(port_id);
		std::cout << toGreen("Device changed!") << std::endl;
	} catch(std::range_error &err) {
		std::cout << toRed("Failed to set device. Index out of range!");
		std::cout << std::endl;
	}
}

void CmdHelper::deviceStatus() {
	if (midiHelper->inputDevice.isSet()) {
		std::cout << "Currently listenting to: ";
		std::cout << toYellow(midiHelper->inputDevice.getName());
		std::cout << " on port " << midiHelper->inputDevice.getPort();
		std::cout << std::endl;
	} else {
		std::cout << toRed("No input device set!") << std::endl;
		return;
	}

	if (midiHelper->outputDevice.isSet()) {
		std::cout << "Currently talking to: ";
		std::cout << toYellow(midiHelper->outputDevice.getName());
		std::cout << " on port " << midiHelper->outputDevice.getPort();
		std::cout << std::endl;
	} else {
		std::cout << "The current device does not support MiDi output.";
		std::cout << std::endl;
	}
}

void CmdHelper::deviceRemove() {
	midiHelper->clearDevice();
	std::cout << toGreen("Device cleared!") << std::endl;
}

void CmdHelper::deviceHelp() {
	using std::cout; using std::endl;

	cout << toYellow("Usage: ") << "midicmd device [OPTION]" << endl << endl;
	cout << "Available options: " << endl;

	cout << toBold("    ls\t\t");
	cout << "Shows a list of all available devices.";
	cout << endl;

	cout << toBold("    set\t\t");
	cout<< "Shows a list of all available devices and then prompts" << endl;
	cout << "\t\t\t" << "you to pick one of them.";
	cout << endl;

	cout << toBold("    set [VALUE]\t");
	cout << "Sets the active device based on the given id." << endl;
	cout << "\t\tThe id is the number associated to the device" << endl;
	cout << "\t\tas shown via the `ls` option.";
	cout << endl;

	cout << toBold("    ps\t\t");
	cout << "Shows the currently selected device(s).";
	cout << endl;

	cout << toBold("    rm\t\t");
	cout << "Remove the current selection of active device, if any.";
	cout << endl << endl;
}