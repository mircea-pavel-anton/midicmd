#include "cmdhelper.hpp"

uint16_t CmdHelper::deviceList() {
	vector<string> devices = midiHelper->getInputDevices();
	const uint16_t device_count = devices.size();

	cout << toGreen( "There are " + std::to_string(device_count) + " devices available:" );
	cout << endl;
	for (uint16_t i = 0; i < device_count; i++) {
		cout << "\t" << i << ") " << devices[i] << endl;
	}

	return device_count;
}

void CmdHelper::deviceSet() {
	uint16_t device_count = deviceList();
	uint16_t user_input;

	cout << endl;
	do {
		cout << "Choose your device [0-" << device_count-1 << "]: ";
		cin >> user_input;
	} while (user_input < 0 || user_input >= device_count);

	deviceSet(user_input);
}

void CmdHelper::deviceSet(uint16_t port_id) {
	try {
		midiHelper->setInputDevice(port_id);
		cout << toGreen("Device changed!") << endl;
	} catch(std::range_error &err) {
		cout << toRed("Failed to set device. Index out of range!") << endl;
	}
}

void CmdHelper::deviceRemove() {
	midiHelper->clearDevice();
	cout << toGreen("Device cleared!") << endl;
}

void CmdHelper::deviceHelp() {
	cout << toYellow("Usage: ") << "midicmd device [OPTION]" << endl;
	cout << endl;

	cout << "Available options: " << endl;
	cout << toBold("    ls\t\t") << "Shows a list of all available devices." << endl;
	cout << toBold("    set\t\t") << "Shows a list of all available devices and then prompts" << endl;
	cout << "\t\t\t" << "you to pick one of them." << endl;
	cout << toBold("    set [VALUE]\t") << "Sets the active device based on the given id." << endl;
	cout << "\t\tThe id is the number associated to the device," << endl;
	cout << "\t\tas shown via the `ls` option." << endl;
	cout << toBold("    rm\t\t") << "Remove the current selection of active device, if any." << endl;
	cout << endl;
}