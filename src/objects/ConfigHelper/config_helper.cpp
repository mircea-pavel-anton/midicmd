#include "config_helper.hpp"

void ConfigHelper::cacheFileContents() {
	std::ifstream file(filePath);

	// First line should be the device id
	file >> cache.device;
	file >> cache.feedback;

	int key = 0;;
	std::string value = "";

	while (file >> key >> value) {
		cache.commands.insert( std::pair<int, const char*>(key, value.c_str()) );
	}

	cache.isSet = true;
	file.close();
}

void ConfigHelper::write(Config &config) {
	std::ofstream file(filePath);
	file << config.device << std::endl;
	file << config.feedback << std::endl;

	std::map<int, const char*>::iterator it = config.commands.begin();
	for (it; it != config.commands.end(); ++it) {
		file << it->first << " " << it->second << std::endl;
	}

	file.close();
}

bool ConfigHelper::checkFile() {
	int device = getDevice();
	if (device == -1) return false;
	std::map<int, const char*> commands = getCommands();
	if (commands.empty()) return false;
	return true;
}

int ConfigHelper::getDevice() {
	if (cache.isSet == false) cacheFileContents();
	return cache.device;
}

std::map<int, const char*> ConfigHelper::getCommands() {
	if (cache.isSet == false) cacheFileContents();
	return cache.commands;
}

bool ConfigHelper::isFeedbackEnabled() {
	if (cache.isSet == false) cacheFileContents();
	return cache.feedback;
}

void ConfigHelper::setDevice(int device) {
	if (cache.isSet == false) cacheFileContents();
	cache.device = device;
	write(cache);
}

void ConfigHelper::setFeedback(bool feedback) {
	if (cache.isSet == false) cacheFileContents();
	cache.feedback = feedback;
	write(cache);
}

void ConfigHelper::setCommands(std::map<int, const char*> commands) {
	if (cache.isSet == false) cacheFileContents();
	cache.commands = commands;
	write(cache);
}