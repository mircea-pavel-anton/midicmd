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
