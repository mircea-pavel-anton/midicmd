#include "cmdhelper.hpp"

uint16_t CmdHelper::deviceList() {
	std::vector<std::string> devices = midiHelper->getInputDevices();
	const uint16_t device_count = devices.size();

	std::cout << Colors::Foreground::Green;
	std::cout << "There are " << device_count << " devices available:";
	std::cout << Colors::Modifiers::Reset << std::endl;
	for (uint16_t i = 0; i < device_count; i++) {
		std::cout << "\t" << i << ") " << devices[i] << std::endl;
	}

	return device_count;
}

void CmdHelper::deviceSet() {
	uint16_t device_count = deviceList();
	uint16_t user_input;

	std::cout << std::endl;
	do {
		std::cout << "Choose your device [0-" << device_count-1 << "]: ";
		std::cin >> user_input;
	} while (user_input < 0 || user_input >= device_count);

	deviceSet(user_input);
}

void CmdHelper::deviceSet(uint16_t port_id) {
	try {
		midiHelper->setInputDevice(port_id);
		std::cout << Colors::Foreground::Green;
		std::cout << "Device changed!";
		std::cout << Colors::Modifiers::Reset << std::endl;
	} catch(std::range_error &err) {
		std::cout << Colors::Foreground::Red;
		std::cout << "Failed to set device!";
		std::cout << Colors::Modifiers::Reset << std::endl;
	}
}
