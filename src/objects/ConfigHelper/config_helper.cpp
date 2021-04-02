#include "config_helper.hpp"

void ConfigHelper::write(int device_id, std::map<int, std::string> commands) {
	std::ofstream file(filePath);
	file << device_id << std::endl;

	std::map<int, std::string>::iterator it = commands.begin();
	for (it; it != commands.end(); ++it) {
		file << it->first << " " << it->second << std::endl;
	}

	file.close();
}

int ConfigHelper::getDevice() {
	if (device == -1) read();
	return device;
}

std::map<int, std::string> ConfigHelper::getCommands() {
	if (commands.empty()) read();
	return commands;
}

void ConfigHelper::read() {
	std::ifstream file(filePath);

	// First line should be the device id
	file >> device;

	int key = 0;;
	std::string value = "";

	while (file >> key >> value) {
		commands.insert( std::pair<int, std::string>(key, value) );
	}

	file.close();
}