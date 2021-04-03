#include "config_helper.hpp"

void ConfigHelper::write(Config &config) {
	std::ofstream file(filePath);
	file << config.device << std::endl;
	file << config.feedback << std::endl;

	std::map<int, std::string>::iterator it = config.commands.begin();
	for (it; it != config.commands.end(); ++it) {
		file << it->first << " " << it->second << std::endl;
	}

	file.close();
}

int ConfigHelper::getDevice() {
	if (cache.isSet == false) cacheFile();
	return cache.device;
}

std::map<int, std::string> ConfigHelper::getCommands() {
	if (cache.isSet == false) cacheFile();
	return cache.commands;
}

bool ConfigHelper::isFeedbackEnabled() {
	if (cache.isSet == false) cacheFile();
	return cache.feedback;
}

void ConfigHelper::cacheFile() {
	std::ifstream file(filePath);

	// First line should be the device id
	file >> cache.device;
	file >> cache.feedback;

	int key = 0;;
	std::string value = "";

	while (file >> key >> value) {
		cache.commands.insert( std::pair<int, std::string>(key, value) );
	}

	cache.isSet = true;
	file.close();
}