#include "config_helper.hpp"

//* Config File I/O *//
void ConfigHelper::cacheFileContents() {
	std::ifstream file(filePath);
	std::string aux = "";

	// First line should be the device id
	file >> aux >> cache.device;
	file >> aux >> cache.feedback;

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
	file << "device: "   << config.device << std::endl;
	file << "feedback: " << config.feedback << std::endl;

	std::map<int, const char*>::iterator it = config.commands.begin();
	for (it; it != config.commands.end(); ++it) {
		file << it->first << " " << it->second << std::endl;
	}

	file.close();
}

bool ConfigHelper::checkFile() {
	std::string device = getDevice();
	if (device.compare("None")) return false;
	std::map<int, const char*> commands = getCommands();
	if (commands.empty()) return false;
	return true;
}


//* GETTERS *//
std::string ConfigHelper::getDevice() {
	if (cache.isSet == false) cacheFileContents();
	return cache.device;
}

std::map<int, const char*> ConfigHelper::getCommands() {
	if (cache.isSet == false) cacheFileContents();
	return cache.commands;
}

bool ConfigHelper::getFeedback() {
	if (cache.isSet == false) cacheFileContents();
	return cache.feedback;
}


//* SETTERS *//
void ConfigHelper::setDevice(std::string device) {
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