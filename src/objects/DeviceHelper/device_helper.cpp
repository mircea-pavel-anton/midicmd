#include "device_helper.hpp"


void DeviceHelper::list() {
	std::vector<std::string> devices = midiHelper->getInputDevices();
	const int device_count = devices.size();

	std::cout << toGreen("There are " + std::to_string(device_count) + " devices available:");
	std::cout << std::endl;

	for (int i = 0; i < device_count; i++) {
		std::cout << "\t" << i << ") " << devices[i] << std::endl;
	}
}

void DeviceHelper::set() {
	if (!isRoot()) {
		std::cout << toRed("Setting a device requires sudo privileges in order to edit the config file!");
		std::cout << std::endl;
		return;
	}

	list();

	int device_count = midiHelper->getInputPortCount();
	int port_id = prompt_for_input(
		"Choose your device [0-" + std::to_string(device_count) + "]:",
		0,
		device_count - 1
	);

	set(port_id);
}

void DeviceHelper::set(int port_id) {
	if (!isRoot()) {
		std::cout << toRed("Setting a device requires sudo privileges in order to edit the config file!");
		std::cout << std::endl;
		return;
	}

	try {
		midiHelper->setInputDevice(port_id);
		configHelper->setDevice(port_id);
		std::cout << toGreen("Device changed!") << std::endl;
	} catch(std::range_error &err) {
		std::cout << toRed("Failed to set device. Index out of range!");
		std::cout << std::endl;
	}
}

void DeviceHelper::status() {
	std::string device_name = configHelper->getDevice();

	if (midiHelper->deviceExists(device_name)) {
		std::cout << "Currently listenting to: ";
		std::cout << toYellow(device_name);
		std::cout << std::endl;
	} else {
		std::cout << toRed("Could not find the specified device!") << std::endl;
		return;
	}

	if (configHelper->isFeedbackEnabled()) {
		if (midiHelper->outputDevice.isSet()) {
			std::cout << "Currently talking to: ";
			std::cout << toYellow(device_name);
			std::cout << std::endl;
		} else {
			std::cout << "The current device does not support MiDi output.";
			std::cout << std::endl;
		}
	} else {
		std::cout << "Midi feedback is disabled in the config. ";
		std::cout << "No device selected for output." << std::endl;
	}
}

void DeviceHelper::help() {
	using std::cout; using std::endl;

	cout << toYellow("Usage: ") << "midicmd device [OPTION]" << endl << endl;
	cout << "Available options: " << endl;

	cout << toBold("    ls\t\t") << endl;
	cout << toBold("    list\t\t");
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
	cout << toBold("    status\t\t") << endl;
	cout << "Shows the currently selected device(s).";
	cout << endl << endl;
}