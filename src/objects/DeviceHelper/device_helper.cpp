#include "device_helper.hpp"

namespace midicmd {
namespace device {

DeviceHelper::DeviceHelper(midi::MidiHelper *midi, config::ConfigHelper *config) {
	midiHelper = midi;
	configHelper = config;
}
DeviceHelper::~DeviceHelper() { /* we don't delete here, but in ArgParser */ }

void DeviceHelper::list() {
	std::vector<std::string> devices = midiHelper->getInputDevices();
	const int device_count = devices.size();

	std::cout << toGreen("There are " + std::to_string(device_count) + " devices available:");
	std::cout << std::endl;

	for (int i = 0; i < device_count; i++) {
		std::cout << "\t" << i << ") " << devices[i] << std::endl;
	}
} //DeviceHelper::list()

void DeviceHelper::set() {
	list();

	int device_count = midiHelper->getInputPortCount();
	std::string user_input = "";
	int value = 0;
	bool is_value_ok = false;

	do {
		std::cout << "Enter the id of the desired device [0-" + std::to_string(device_count - 1) + "]: ";
		std::cin >> user_input;

		try {
			value = std::stoi(user_input);
			is_value_ok = (value >= 0 && value < device_count);
		} catch (std::invalid_argument &err){
			std::cout << toRed("Invalid argument!") << std::endl;
			is_value_ok = false;
		}
	} while (is_value_ok == false);

	set(value);
} //DeviceHelper::set()

void DeviceHelper::set(int port_id) {
	try {
		std::string device_name = midiHelper->setInputDevice(port_id);
		configHelper->setDevice(device_name);
		std::cout << toGreen("Device changed!") << std::endl;
	} catch(std::range_error &err) {
		std::cout << toRed("Failed to set device. Index out of range!");
		std::cout << std::endl;
	}
} //DeviceHelper::set(int port_id)

void DeviceHelper::status() {
	std::string device_name = configHelper->getDevice();

	if (midiHelper->getInputDeviceId(device_name) != -1) {
		std::cout << "Currently listenting to: ";
		std::cout << toYellow(device_name);
		std::cout << std::endl;
	} else {
		std::cout << toRed("Could not find the specified device!") << std::endl;
		return;
	}

	if (configHelper->getFeedback()) {
		if (midiHelper->getOutputDeviceId(device_name) != -1) {
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
} //DeviceHelper::status()

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
} //DeviceHelper::help()

} //namespace device
} //namespace midicmd